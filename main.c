#include <stdlib.h>
#include <stdio.h>
#include "Dataset.h"

int main(int argc, char** argv)
{
char path[128] = "./Datasets/PENDIGITS_train.txt";
Dataset *trainData = Dataset_readFromFile(path);
Subproblem *subproblem = Dataset_getSubproblem(trainData);
Subproblem_print(subproblem);
Subproblem_destroy(subproblem);
Dataset_destroy(trainData);
return 0;
}