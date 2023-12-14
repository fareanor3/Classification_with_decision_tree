#include <stdio.h>
#include "DecisionTree.h"

int main(int argc, char **argv)
{
    // char path[128] = "./Datasets/PENDIGITS_train.txt";
    //  char path[128] = "./Datasets/MNIST_test.txt";
    //  char path[128] = "./Datasets/DATASET_A_MOI.txt";

    /*
        Dataset *trainData = Dataset_readFromFile(path);
        Subproblem *sp = Dataset_getSubproblem(trainData);
        Subproblem_print(sp);
        DecisionTreeNode *tree = DecisionTree_create(sp, 0, 30, 1.0);
        printf("fin decision tree create\n");
        printf("Generation d'un arbre de %d noeuds\n", Decision_nodeCount(tree));
        DecisionTree_destroy(tree);
        Dataset_destroy(trainData);
        return 0;
    */
    char pathTrain[128] = "./Datasets/PENDIGITS_train.txt";
    Dataset *trainData = Dataset_readFromFile(pathTrain);
    char pathTest[128] = "./Datasets/PENDIGITS_test.txt";
    Dataset *testData = Dataset_readFromFile(pathTest);
    Subproblem *sp = Dataset_getSubproblem(trainData);
    DecisionTreeNode *tree = DecisionTree_create(sp, 0, 30, 1.0f);
    float scoreTrain = DecisionTree_evaluate(tree, trainData);
    float scoreTest = DecisionTree_evaluate(tree, testData);
    printf("train = %.3f, test = %.3f\n", scoreTrain, scoreTest);
    Subproblem_destroy(sp);
    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);
    Dataset_destroy(testData);
    return 0;
}