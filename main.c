#include <stdio.h>
#include "RandomForest.h"

int main(int argc, char **argv)
{
    char pathTrain[128] = "./Datasets/PENDIGITS_train.txt";
    Dataset *trainData = Dataset_readFromFile(pathTrain);
    char pathTest[128] = "./Datasets/PENDIGITS_test.txt";
    Dataset *testData = Dataset_readFromFile(pathTest);
    Subproblem *sp = Dataset_getSubproblem(trainData);
    printf("Subproblem : %d instances, %d features, %d classes\n", sp->instanceCount, sp->featureCount, sp->classCount);
    RandomForest *rf = RandomForest_create(20, trainData, 30, 0.5f, 1.0f);
    printf("RandomForest : %d trees, %d classes\n", rf->treeCount, rf->classCount);
    float scoreTrain = RandomForest_evaluate(rf, trainData);
    float scoreTest = RandomForest_evaluate(rf, testData);
    printf("treeCount = %d, nodeCount = %d\n", rf->treeCount, RandomForest_nodeCount(rf));
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);
    RandomForest_destroy(rf);
    Subproblem_destroy(sp);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    return 0;
}