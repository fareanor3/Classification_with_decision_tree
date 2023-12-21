#include "Sauvegarde.h"

void DecisionTree_SaveTree(DecisionTreeNode *node, FILE *file)
{
    if (node == NULL || file == NULL)
        return;
    if (node->left != NULL)
    {
        fwrite("n", sizeof(char), 1, file);
        fwrite(&node->split.featureID, sizeof(int), 1, file);
        fwrite(&node->split.threshold, sizeof(float), 1, file);
        DecisionTree_SaveTree(node->left, file);
        DecisionTree_SaveTree(node->right, file);
    }
    else
    {
        fwrite("f", sizeof(char), 1, file);
        fwrite(&node->classID, sizeof(int), 1, file);
    }
}

void DecisionTree_File(DecisionTreeNode *tree, const char *filename)
{
    if (tree == NULL)
        abort();
    FILE *file = fopen(filename, "wb+");
    if (file == NULL)
    {
        printf("Le fichier n'a pas pu être ouvert");
        abort();
    }
    DecisionTree_SaveTree(tree, file);
    fclose(file);
}

DecisionTreeNode *DecisionTree_RecreateTree(FILE *file, DecisionTreeNode *tree)
{
    char type;
    fread(&type, sizeof(char), 1, file);
    DecisionTreeNode *node = (DecisionTreeNode *)calloc(1, sizeof(DecisionTreeNode));
    if (type == 'n')
    {
        fread(&node->split.featureID, sizeof(int), 1, file);
        fread(&node->split.threshold, sizeof(float), 1, file);
        node->left = DecisionTree_RecreateTree(file, node->left);
        node->right = DecisionTree_RecreateTree(file, node->right);
        return node;
    }
    else if (type == 'f')
    {
        fread(&node->classID, sizeof(int), 1, file);
        return node;
    }
    else
    {
        printf("Erreur de lecture/d'écriture");
        return NULL;
    }
}

DecisionTreeNode *DecisionTree_GetinFile(FILE *file)
{
    if (file == NULL)
    {
        printf("Fichier non-existant");
        return NULL;
    }
    DecisionTreeNode *tree = DecisionTree_RecreateTree(file, NULL);
    fclose(file);
    return tree;
}

RandomForest *RandomForest_GetinFile(FILE *file)
{
    if (file == NULL)
    {
        printf("Fichier non-existant");
        return NULL;
    }
    int treeCount = 0;
    int classCount = 0;
    fread(&treeCount, sizeof(int), 1, file);
    fread(&classCount, sizeof(int), 1, file);
    RandomForest *forest = (RandomForest *)calloc(1, sizeof(RandomForest));
    forest->trees = (DecisionTreeNode **)calloc(treeCount, sizeof(DecisionTreeNode *));
    for (int i = 0; i < treeCount; i++)
    {
        forest->trees[i] = DecisionTree_GetinFile(file);
        if (forest->trees[i] == NULL)
        {
            printf("Erreur de lecture/d'écriture");
            return NULL;
        }
    }
    forest->treeCount = treeCount;
    forest->classCount = classCount;
    fclose(file);
    return forest;
}

void RandomForest_SaveForest(RandomForest *forest, FILE *file)
{
    if (forest == NULL || file == NULL)
        return;
    fwrite(&forest->treeCount, sizeof(int), 1, file);
    fwrite(&forest->classCount, sizeof(int), 1, file);
    for (int i = 0; i < forest->treeCount; i++)
    {
        DecisionTree_SaveTree(forest->trees[i], file);
    }
}