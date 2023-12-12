#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Split.h"
#include "Dataset.h"
#include "DecisionTree.h"

int main(int argc, char **argv)
{
    char path[128] = "./Datasets/PENDIGITS_train.txt";
    // char path[128] = "./Datasets/MNIST_test.txt";
    // char path[128] = "./Datasets/DATASET_A_MOI.txt";

    printf("Reading file %s\n", path);
    Dataset *trainData = Dataset_readFromFile(path);
    Subproblem *subproblem = Dataset_getSubproblem(trainData);
    Subproblem_print(subproblem);

    Split_compute(subproblem);

    Subproblem_destroy(subproblem);
    Dataset_destroy(trainData);
    return 0;
}