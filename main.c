#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "RandomForest.h"

int main(int argc, char **argv)
{
    int GiniOrEntropy = -1;
    while (GiniOrEntropy != 0 && GiniOrEntropy != 1)
    {
        printf("Choose Gini (0) or Entropy (1) : ");
        scanf("%d", &GiniOrEntropy);
    }

    clock_t start_time = clock();

    char pathTrain[128] = "./Datasets/MNIST_train.txt";
    printf("Dataset : %s\n", pathTrain);
    Dataset *trainData = Dataset_readFromFile(pathTrain);
    char pathTest[128] = "./Datasets/MNIST_test.txt";
    Dataset *testData = Dataset_readFromFile(pathTest);
    Subproblem *sp = Dataset_getSubproblem(trainData);

    printf("Subproblem : %d instances, %d features, %d classes\n", sp->instanceCount, sp->featureCount, sp->classCount);
    RandomForest *rf = RandomForest_create(20, trainData, 30, 0.5f, 1.0, 0.9, 0);
    printf("RandomForest : %d trees, %d classes\n", rf->treeCount, rf->classCount);
    float scoreTrain = RandomForest_evaluate(rf, trainData);
    float scoreTest = RandomForest_evaluate(rf, testData);
    printf("treeCount = %d, nodeCount = %d\n", rf->treeCount, RandomForest_nodeCount(rf));
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);

    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.3f seconds\n", elapsed_time);

    RandomForest_destroy(rf);
    Subproblem_destroy(sp);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    return 0;
}