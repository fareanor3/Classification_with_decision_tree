#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "RandomForest.h"
#include "Sauvegarde.h"

int main(int argc, char **argv)
{
    clock_t start_time = clock();

    char pathTrain[128] = "./Datasets/PENDIGITS_train.txt";
    char pathTest[128] = "./Datasets/PENDIGITS_test.txt";
    Dataset *trainData = Dataset_readFromFile(pathTrain);
    Dataset *testData = Dataset_readFromFile(pathTest);
    Subproblem *sp = Dataset_getSubproblem(trainData);
    printf("Subproblem : %d instances, %d features, %d classes\n", sp->instanceCount, sp->featureCount, sp->classCount);
    RandomForest *rf = RandomForest_create(20, trainData, 30, 1.0, 1.0, 0.96f, 1);
    printf("RandomForest : %d trees, %d classes\n", rf->treeCount, rf->classCount);
    float scoreTrain = RandomForest_evaluate(rf, trainData);
    float scoreTest = RandomForest_evaluate(rf, testData);
    printf("treeCount = %d, nodeCount = %d\n", rf->treeCount, RandomForest_nodeCount(rf));
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);
    RandomForest_File(rf, "RandomForestPENDIGITS.txt");
    FILE *file = fopen("RandomForestPENDIGITS.txt", "rb");
    RandomForest *rf2 = RandomForest_GetinFile(file);
    fclose(file);
    float scoreTrain2 = RandomForest_evaluate(rf2, trainData);
    float scoreTest2 = RandomForest_evaluate(rf2, testData);
    printf("treeCount = %d, nodeCount = %d\n", rf2->treeCount, RandomForest_nodeCount(rf2));
    printf("train 2 = %.3f, test 2 = %.3f\n", scoreTrain2, scoreTest2);
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.3f seconds\n", elapsed_time);

    RandomForest_destroy(rf);
    RandomForest_destroy(rf2);
    Subproblem_destroy(sp);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    return 0;
}