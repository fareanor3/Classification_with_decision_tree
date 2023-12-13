#include <stdlib.h>
#include <assert.h>
#include "DecisionTree.h"

DecisionTreeNode *DecisionTree_create(Subproblem *sp, int currentDepth, int maxDepth, float prunningThreshold)
{
    assert(!sp || currentDepth < 0 || maxDepth < 0 || prunningThreshold < 0);
    DecisionTreeNode *n = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));
    float sp_purity = Subproblem_purity(sp);
    if (sp_purity >= prunningThreshold)
    {
        int sp_majority = Subproblem_majorityclass(sp);
        n->classID = sp_majority;
        return n;
    }
    if (currentDepth >= maxDepth)
    {
        int sp_majority = Subproblem_majorityclass(sp);
        n->classID = sp_majority;
        return n;
    }
    Split s = Split_compute(sp);
    n->split = s;
    Subproblem *sp_left = Subproblem_create(sp->capacity / 2, sp->featureCount, sp->classCount);
    Subproblem *sp_right = Subproblem_create(sp->capacity / 2, sp->featureCount, sp->classCount);
    return n;
}

float Subproblem_purity(Subproblem *subproblem)
{
    assert(!subproblem);
    float purity = 0;
    int instance_max = 0;
    for (int i = 0; i < subproblem->classCount; i++)
    {
        if (subproblem->classes[i].instanceCount >= instance_max)
            instance_max = subproblem->classes[i].instanceCount;
    }
    purity = (float)instance_max / (float)subproblem->instanceCount;
    return purity;
}

int Subproblem_majorityclass(Subproblem *subproblem)
{
    assert(!subproblem);
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