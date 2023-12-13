#include <stdio.h>
#include "DecisionTree.h"

int main(int argc, char **argv)
{
    char path[128] = "../Datasets/PENDIGITS_train.txt";
    // char path[128] = "./Datasets/MNIST_test.txt";
    // char path[128] = "./Datasets/DATASET_A_MOI.txt";

    Dataset *trainData = Dataset_readFromFile(path);
    Subproblem *sp = Dataset_getSubproblem(trainData);
    printf("fin get subproblems");
    DecisionTreeNode *tree = DecisionTree_create(sp, 0, 30, 1.0);
    printf("fin decision tree create");
    printf("Génération d'un arbre de %d nœuds\n", Decision_nodeCount(tree));
    DecisionTree_destroy(tree);
    Dataset_destroy(trainData);
    return 0;
}