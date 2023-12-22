#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "DecisionTree.h"
#include "RandomForest.h"

void DecisionTree_SaveTree(DecisionTreeNode *node, FILE *file);

void DecisionTree_File(DecisionTreeNode *tree, const char *filename);

DecisionTreeNode *DecisionTree_RecreateTree(FILE *file, DecisionTreeNode *tree);

DecisionTreeNode *DecisionTree_GetinFile(FILE *file);

void RandomForest_File(RandomForest *forest, const char *filename);

void RandomForest_SaveForest(RandomForest *forest, FILE *file);

RandomForest *RandomForest_GetinFile(FILE *file);
