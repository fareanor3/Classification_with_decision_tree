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
        printf("Choose Entropy (0) or Gini (1) : ");
        scanf("%d", &GiniOrEntropy);
    }

    int ChoixDataset = -1;
    while (ChoixDataset != 0 && ChoixDataset != 1 && ChoixDataset != 2)
    {
        printf("Choose MNIST (0) or PENDIGITS (1) or FASHION (2): ");
        scanf("%d", &ChoixDataset);
    }

    int ChoixTreeCount = -1;
    while (ChoixTreeCount != 1 && ChoixTreeCount != 2 && ChoixTreeCount != 3)
    {
        printf("Choose TreeCount (1) 20, (2) 30, (3) 100 : ");
        scanf("%d", &ChoixTreeCount);
    }

    switch (ChoixTreeCount)
    {
    case 1:
        ChoixTreeCount = 20;
        break;

    case 2:
        ChoixTreeCount = 10;
        break;

    case 3:
        ChoixTreeCount = 100;
        break;

    default:
        printf("U are suposly lost in a random forest with random tree, so.... u must be a random peaple, right ?\n");
        break;
    }

    clock_t start_time = clock();

    char pathTrain[128] = "./Datasets/MNIST_train.txt";
    char pathTest[128] = "./Datasets/MNIST_test.txt";
    printf("Dataset : ");
    switch (ChoixDataset)
    {
    case 0:
        printf("MNIST\n");
        strncpy(pathTrain, "./Datasets/MNIST_train.txt", sizeof(pathTrain) - 1);
        strncpy(pathTest, "./Datasets/MNIST_test.txt", sizeof(pathTest) - 1);
        break;

    case 1:
        printf("PENDIGITS\n");
        strncpy(pathTrain, "./Datasets/PENDIGITS_train.txt", sizeof(pathTrain) - 1);
        strncpy(pathTest, "./Datasets/PENDIGITS_test.txt", sizeof(pathTest) - 1);
        break;

    case 2:
        printf("FASHION\n");
        strncpy(pathTrain, "./Datasets/FASHION_train.txt", sizeof(pathTrain) - 1);
        strncpy(pathTest, "./Datasets/FASHION_test.txt", sizeof(pathTest) - 1);
        break;

    default:
        printf("Lost in the dark ?! ... How do u doooooo ???\n ARE U A H@CK3R ?!\n");
        break;
    }

    Dataset *trainData = Dataset_readFromFile(pathTrain);
    Dataset *testData = Dataset_readFromFile(pathTest);
    Subproblem *sp = Dataset_getSubproblem(trainData);
    printf("Subproblem : %d instances, %d features, %d classes\n", sp->instanceCount, sp->featureCount, sp->classCount);
    RandomForest *rf = RandomForest_create(ChoixTreeCount, trainData, 30, 1.0, 1.0, 0.96f, GiniOrEntropy);
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