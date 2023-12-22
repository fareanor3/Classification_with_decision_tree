#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Dataset.h"

Dataset *Dataset_readFromFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        abort();

    int instanceCount = 0;
    int classCount = 0;
    int featureCount = 0;
    // On récupère les données de la première ligne du fichier (instanceCount/classCount/featureCount)
    int test = fscanf(file, "%d %d %d", &instanceCount, &classCount, &featureCount);
    if (test != 3)
        abort();

    // On alloue la structure data
    Dataset *dataset = (Dataset *)calloc(1, sizeof(Dataset));

    // On alloue le tableau d'instances
    // dataset->instances = (Instance *)calloc(instanceCount, sizeof(Instance));
    dataset->instances = (Instance *)malloc(instanceCount * sizeof(Instance));

    for (int i = 0; i < instanceCount; i++)
    {
        // On alloue le tableau de values de chaque instance
        // dataset->instances[i].values = calloc(featureCount, sizeof(int));
        dataset->instances[i].values = malloc(featureCount * sizeof(int));
    }

    // On remplit le tableau d'instances avec les values
    for (int i = 0; i < instanceCount; i++)
    {
        test = fscanf(file, "%d\t", &dataset->instances[i].classID);
        if (test != 1)
            abort();
        for (int j = 0; j < featureCount; j++)
        {
            test = fscanf(file, "%d ", &dataset->instances[i].values[j]);
            if (test != 1)
                abort();
        }
    }
    fclose(file);
    dataset->instanceCount = instanceCount;
    dataset->classCount = classCount;
    dataset->featureCount = featureCount;
    // printf("Dataset : %d instances, %d features, %d classes\n", dataset->instanceCount, dataset->featureCount, dataset->classCount);
    //  On renvoie dataset
    return dataset;
}

void Dataset_destroy(Dataset *data)
{
    if (!data)
        abort();
    // On libère d'abord toutes les valeurs du tableau d'instances
    for (int i = 0; i < data->instanceCount; i++)
        free(data->instances[i].values);
    // On libère ensuite le tableau d'instances
    free(data->instances);
    // Puis la structure data
    free(data);
}

Subproblem *Subproblem_create(int maximumCapacity, int featureCount, int classCount)
{
    if (maximumCapacity <= 0 || featureCount <= 0 || classCount <= 0)
        abort();
    // On alloue la structure subproblem
    // Subproblem *subproblem = (Subproblem *)calloc(1, sizeof(Subproblem));
    Subproblem *subproblem = (Subproblem *)malloc(sizeof(Subproblem));
    subproblem->capacity = maximumCapacity;
    // On récupère les valeurs données dans les paramètres
    subproblem->featureCount = featureCount;
    subproblem->classCount = classCount;
    // On alloue le tableau d'instances de subproblem
    subproblem->instances = (Instance **)calloc(maximumCapacity, sizeof(Instance *));
    // On alloue la structure class de suproblem
    subproblem->classes = (SubproblemClass *)calloc(subproblem->classCount, sizeof(SubproblemClass));
    // On alloue les tableaux d'instances des class
    for (int i = 0; i < classCount; i++)
        subproblem->classes[i].instances = (Instance **)calloc(maximumCapacity, sizeof(Instance *));
    // On renvoie subproblem
    return subproblem;
}

void Subproblem_destroy(Subproblem *subproblem)
{
    if (!subproblem)
        abort();
    // On libère les tableaux d'instances des class de subproblem
    for (int i = 0; i < subproblem->classCount; i++)
        free(subproblem->classes[i].instances);
    // On libère la structure class
    free(subproblem->classes);
    // On libère le tableau instances de subproblem
    free(subproblem->instances);
    // On libère la structure subproblem
    free(subproblem);
}

void Subproblem_insert(Subproblem *subproblem, Instance *instance)
{
    if (!subproblem || !instance)
        abort();
    // On vérifie qu'on ne dépasse pas la capacité d'instances du subproblem
    if (subproblem->instanceCount < subproblem->capacity)
    {
        // On ajoute l'instance en paramètre au tableau d'instances de subproblem
        subproblem->instances[subproblem->instanceCount] = instance;
        // On augmente le nombre d'instances dans subproblem
        subproblem->instanceCount++;
        // On cherche la classe de l'instance que l'on veut ajouter
        for (int i = 0; i < subproblem->classCount; i++)
        {
            // Quand on l'a trouvée
            if (instance->classID == i)
            {
                // On ajoute l'instance en paramètre au tableau d'instances de class de subproblem
                subproblem->classes[i].instances[subproblem->classes[i].instanceCount] = instance;
                // On augmente le nombre d'instances dans class de subproblem
                subproblem->classes[i].instanceCount++;
            }
        }
    }
}

Subproblem *Dataset_getSubproblem(Dataset *data)
{
    if (data == NULL)
        abort();
    // On crée une structure subproblem avec data
    Subproblem *subproblem = Subproblem_create(data->instanceCount, data->featureCount, data->classCount);
    // On insère toutes les instances de data dans la structure subproblem créée
    for (int i = 0; i < data->instanceCount; i++)
        Subproblem_insert(subproblem, &data->instances[i]);
    // On renvoie subproblem
    return subproblem;
}

void Subproblem_print(Subproblem *subproblem)
{
    if (!subproblem)
        abort();
    // On renvoie le nombre de feature, le nombre de class, le nombre d'instance
    printf("Nb Features = %d, Nb classes = %d, Nb instances = %d \n", subproblem->featureCount, subproblem->classCount, subproblem->instanceCount);
    // On renvoie le nombre d'instances par class
    for (int i = 0; i < subproblem->classCount; i++)
        printf("Class %d : %d instances\n", i, subproblem->classes[i].instanceCount);
}

Subproblem *Dataset_bagging(Dataset *data, float proportion)
{
    if (data == NULL || proportion <= 0)
        abort();
    // On crée une structure subproblem avec data
    Subproblem *subproblem = Subproblem_create(data->instanceCount * proportion, data->featureCount, data->classCount);
    // On insère toutes les instances de data dans la structure subproblem créée
    for (int i = 0; i < data->instanceCount * proportion; i++)
    {
        int random = rand() % data->instanceCount;
        Subproblem_insert(subproblem, &data->instances[random]);
    }
    // On renvoie subproblem
    return subproblem;
}

// Renvoie une
bool *Dataset_bagging_features(Dataset *data, float proportion)
{
    if (data == NULL || proportion <= 0)
        abort();
    bool *features = (bool *)calloc(data->featureCount * proportion, sizeof(int));

    for (int i = 0; i < data->featureCount * proportion; i++)
    {
        int random = rand() % data->featureCount;
        features[random] = true;
    }
    return features;
}