#include "RandomForest.h"

RandomForest *RandomForest_create(int numberOfTrees, Dataset *data, int maxDepth, float baggingProportion, float prunningThreshold)
{
    if (numberOfTrees <= 0 || !data || maxDepth <= 0 || baggingProportion <= 0 || prunningThreshold <= 0)
        abort();
    RandomForest *randomForest = (RandomForest *)calloc(1, sizeof(RandomForest));
    RandomForest->treeCount = numberOfTrees;
    RandomForest->classCount = data->classCount;
    RandomForest->trees = (DecisionTreeNode **)calloc(numberOfTrees, sizeof(DecisionTreeNode *));
    return randomForest;
}

int RandomForest_predict(RandomForest *rf, Instance *instance)
{
    return 0;
}

float RandomForest_evaluate(RandomForest *rf, Dataset *data)
{
    return 0.0f;
}

int RandomForest_nodeCount(RandomForest *rf)
{
    return 0;
}

void RandomForest_destroy(RandomForest *rf)
{
    return;
}