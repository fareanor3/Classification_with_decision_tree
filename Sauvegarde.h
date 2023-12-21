#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "DecisionTree.h"

void DecisionTree_SaveTree(DecisionTreeNode *node, FILE *file);

void DecisionTree_SaveinFile(DecisionTreeNode *tree, FILE *file);

void DecisionTree_File(DecisionTreeNode *tree, const char *filename);

DecisionTreeNode *DecisionTree_RecreateNode(FILE *file, DecisionTreeNode *node);

DecisionTreeNode *DecisionTree_GetinFile(FILE *file);