#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "DecisionTree.h"

DecisionTreeNode *DecisionTree_create(Subproblem *sp, int currentDepth, int maxDepth, float prunningThreshold)
{
    if (!sp || currentDepth < 0 || maxDepth < 0 || prunningThreshold < 0)
        abort();
    DecisionTreeNode *n = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));
    float purity = Subproblem_purity(sp);
    if (currentDepth >= maxDepth || purity >= prunningThreshold)
    {
        n->classID = Subproblem_majorityclass(sp);
        return n;
    }
    Split s = Split_compute(sp);
    n->split = s;
    Subproblem *sp_left = Subproblem_create(sp->capacity, sp->featureCount, sp->classCount);
    Subproblem *sp_right = Subproblem_create(sp->capacity, sp->featureCount, sp->classCount);
    for (int i = 0; i < sp->instanceCount; i++)
    {
        if (sp->instances[i]->values[n->split.featureID] < n->split.threshold)
            Subproblem_insert(sp_left, sp->instances[i]);
        else
            Subproblem_insert(sp_right, sp->instances[i]);
    }

    n->left = DecisionTree_create(sp_left, currentDepth + 1, maxDepth, prunningThreshold);
    n->right = DecisionTree_create(sp_right, currentDepth + 1, maxDepth, prunningThreshold);
    Subproblem_destroy(sp_left);
    Subproblem_destroy(sp_right);
    return n;
}

float Subproblem_purity(Subproblem *subproblem)
{
    if (!subproblem)
        abort();
    float purity = 1.0f;
    int instance_max = 0;
    for (int i = 0; i < subproblem->classCount; i++)
    {
        if (subproblem->classes[i].instanceCount > instance_max)
            instance_max = subproblem->classes[i].instanceCount;
    }
    if (subproblem->instanceCount > 0)
        purity = (float)instance_max / (float)subproblem->instanceCount;
    return purity;
}

int Subproblem_majorityclass(Subproblem *subproblem)
{
    if (!subproblem)
        abort();
    int instance_max = 0;
    int class_majority = -1;
    for (int i = 0; i < subproblem->classCount; i++)
    {
        if (subproblem->classes[i].instanceCount >= instance_max)
        {
            instance_max = subproblem->classes[i].instanceCount;
            class_majority = i;
        }
    }
    return class_majority;
}

void DecisionTree_destroyRec(DecisionTreeNode *node)
{
    if (!node)
        return;
    DecisionTree_destroyRec(node->left);
    DecisionTree_destroyRec(node->right);
    free(node);
}

void DecisionTree_destroy(DecisionTreeNode *decisionTree)
{
    if (decisionTree == NULL)
        return;
    DecisionTree_destroyRec(decisionTree);
    return;
}

int DecisionTreeNode_parcours(DecisionTreeNode *node, int nb_node)
{
    if (!node)
        return nb_node;
    nb_node++;
    nb_node += DecisionTreeNode_parcours(node->left, 0);
    nb_node += DecisionTreeNode_parcours(node->right, 0);
    return nb_node;
}

int Decision_nodeCount(DecisionTreeNode *node)
{
    if (node == NULL)
        abort();
    int nb_node = 0;
    nb_node = DecisionTreeNode_parcours(node, nb_node);
    return nb_node;
}

int DecisionTree_predictRec(DecisionTreeNode *node, Instance *instance)
{
    if (node->left == NULL && node->right == NULL)
        return node->classID;
    int test = instance->values[node->split.featureID];
    // TO FINISH
    if (test < node->split.threshold)
        DecisionTree_predictRec(node->left, instance);
    else if (test >= node->split.threshold)
        DecisionTree_predictRec(node->right, instance);
    return node->classID;
}

int DecisionTree_predict(DecisionTreeNode *tree, Instance *instance)
{
    if (tree == NULL || instance == NULL)
        abort();
    int prediction = -1;
    prediction = DecisionTree_predictRec(tree, instance);
    return prediction;
}