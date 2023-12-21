#include "Sauvegarde.h"

void DecisionTree_SaveTree(DecisionTreeNode *node, FILE *file)
{
    if (node == NULL || file == NULL)
        return;
    if (node->left != NULL)
    {
        fprintf(file, "n %d %d %f\n", node->classID, node->split.featureID, node->split.threshold);
        DecisionTree_SaveTree(node->left, file);
        DecisionTree_SaveTree(node->right, file);
    }
    else
        fprintf(file, "f %d %d %f\n", node->classID, node->split.featureID, node->split.threshold);
}

void DecisionTree_File(DecisionTreeNode *tree, const char *filename)
{
    if (tree == NULL)
        abort();
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Le fichier n'a pas pu être ouvert");
        abort();
    }
    DecisionTree_SaveTree(tree, file);
    fclose(file);
}

DecisionTreeNode *DecisionTree_RecreateTree(FILE *file, DecisionTreeNode *node)
{
    if (file == NULL)
    {
        printf("Fichier non-existant");
        return NULL;
    }
    char type = 0;
    fscanf(file, "%c ", &type);
    DecisionTreeNode *node = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));
    if (type == "n")
    {
        fscanf(file, "%d %d %f\n", &node->classID, &node->split.featureID, &node->split.threshold);
        node->left = DecisionTree_RecreateTree(file, node->left);
        node->right = DecisionTree_RecreateTree(file, node->right);
        return node;
    }
    else if (type == "f")
    {
        fscanf(file, "%d %d %f\n", &node->classID, &node->split.featureID, &node->split.threshold);
        return node;
    }
}

DecisionTreeNode *DecisionTree_GetinFile(FILE *file, int l_or_r)
{
    if (file == NULL)
    {
        printf("Fichier non-existant");
        return NULL;
    }
    DecisionTreeNode *node = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));
    DecisionTreeNode *tree = DecisionTree_RecreateNode(file, node);
    return tree;
}