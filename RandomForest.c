#include "RandomForest.h"

RandomForest *RandomForest_create(int numberOfTrees, Dataset *data, int maxDepth, float baggingProportion, float ferature_Bagging, float prunningThreshold, int GiniOrEntropy)
{
    if (numberOfTrees <= 0 || !data || maxDepth <= 0 || baggingProportion <= 0 || prunningThreshold <= 0)
        abort();

    RandomForest *randomForest = (RandomForest *)calloc(1, sizeof(RandomForest));
    randomForest->treeCount = numberOfTrees;
    randomForest->classCount = data->classCount;
    randomForest->trees = (DecisionTreeNode **)calloc(numberOfTrees, sizeof(DecisionTreeNode *));

#pragma omp parallel for num_threads(2)
    for (int i = 0; i < numberOfTrees; i++)
    {
        bool *ferature_Bagg = Dataset_bagging_features(data, ferature_Bagging);
        Subproblem *sp = Dataset_bagging(data, baggingProportion);
        randomForest->trees[i] = DecisionTree_create(sp, 0, maxDepth, prunningThreshold, GiniOrEntropy, ferature_Bagg);
        Subproblem_destroy(sp);
        free(ferature_Bagg);
    }
    return randomForest;
}

int RandomForest_predict(RandomForest *rf, Instance *instance)
{
    if (!rf || !instance)
    {
        // printf("Erreur de prédiction\n");
        return -1;
    }
    int *votes = (int *)calloc(rf->classCount, sizeof(int));
    for (int i = 0; i < rf->treeCount; i++)
    {
        int prediction = DecisionTree_predict(rf->trees[i], instance);
        votes[prediction]++;
    }
    int majorityVote = 0;
    int maxVotes = votes[0];
    for (int i = 1; i < rf->classCount; i++)
    {
        if (votes[i] > maxVotes)
        {
            maxVotes = votes[i];
            majorityVote = i;
        }
    }
    free(votes);
    return majorityVote;
}

float RandomForest_evaluate(RandomForest *rf, Dataset *data)
{
    int correctPredictions = 0;
    for (int i = 0; i < data->instanceCount; i++)
    {
        if (RandomForest_predict(rf, &data->instances[i]) == data->instances[i].classID)
            correctPredictions++;
    }
    return (float)correctPredictions / (float)data->instanceCount;
}

int RandomForest_nodeCount(RandomForest *rf)
{
    int totalNodes = 0;
    for (int i = 0; i < rf->treeCount; i++)
    {
        totalNodes += Decision_nodeCount(rf->trees[i]);
    }
    return totalNodes;
}

void RandomForest_destroy(RandomForest *rf)
{
    for (int i = 0; i < rf->treeCount; i++)
    {
        DecisionTree_destroy(rf->trees[i]);
    }
    free(rf->trees);
    free(rf);
}