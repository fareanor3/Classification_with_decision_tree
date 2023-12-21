#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#include "DecisionTree.h"

typedef struct sRandomForest
{
    DecisionTreeNode **trees;
    int treeCount;
    int classCount;
} RandomForest;

RandomForest *RandomForest_create(int numberOfTrees, Dataset *data, int maxDepth, float baggingProportion, float ferature_Bagging, float prunningThreshold, int GiniOrEntropy);

int RandomForest_predict(RandomForest *rf, Instance *instance);

float RandomForest_evaluate(RandomForest *rf, Dataset *data);

int RandomForest_nodeCount(RandomForest *rf);

void RandomForest_destroy(RandomForest *rf);