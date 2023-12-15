#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Dataset.h"

Dataset *Dataset_readFromFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        abort();
    // On alloue la structure data
    Dataset *dataset = (Dataset *)calloc(1, sizeof(Dataset));
    int test = 0;
    // On récupère les données de la première ligne du fichier (instanceCount/classCount/featureCount)
    test = fscanf(file, "%d %d %d", &dataset->instanceCount, &dataset->classCount, &dataset->featureCount);
    if (test != 3)
        abort();
    // On alloue le tableau d'instances
    dataset->instances = (Instance *)calloc(dataset->instanceCount, sizeof(Instance));
    // On remplit le tableau d'instances avec les values
    for (int i = 0; i < dataset->instanceCount; i++)
    {
        // On alloue le tableau de values de chaque instance
        dataset->instances[i].values = calloc(dataset->featureCount, sizeof(int));
        test = fscanf(file, "%d\t", &dataset->instances[i].classID);
        if (test != 1)
            abort();
        for (int j = 0; j < dataset->featureCount; j++)
        {
            test = fscanf(file, "%d ", &dataset->instances[i].values[j]);
            if (test != 1)
                abort();
        }
    }
    fclose(file);
    printf("Dataset : %d instances, %d features, %d classes\n", dataset->instanceCount, dataset->featureCount, dataset->classCount);
    // On renvoie dataset
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
    Subproblem *subproblem = (Subproblem *)calloc(1, sizeof(Subproblem));
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
    // On cherche combien d'instances sont la proportion qu'on nous a donné
    int quantite_inst = data->instanceCount * proportion;
    // On alloue le nouveau dataset
    Dataset *rand_data = (Dataset *)calloc(1, sizeof(Dataset));
    // On lui attribue ses composantes
    rand_data->instanceCount = quantite_inst;
    rand_data->featureCount = data->featureCount;
    rand_data->classCount = data->classCount;
    // On alloue son tableau d'instances
    rand_data->instances = (Instance *)calloc(rand_data->instanceCount, sizeof(Instance));
    // On choisit aléatoirement les instances qui composeront le nouveau dataset
    for (int i = 0; i < rand_data->instanceCount; i++)
    {
        // On cherche un nombre aléatoire compris entre 0 et le nombre d'instances de data
        int inf = 0, sup = data->instanceCount - 1;
        int nb_rand = (rand() % (sup + 1 - inf)) + inf;
        // On met l'instance de rand_data à la place i avec la valeur celle de data à la place nb_rand
        rand_data->instances[i].values = (int *)calloc(data->featureCount, sizeof(int));
        // On remplit le tableau de values de l'instance de rand_data à la place i avec les valeurs de data à la place nb_rand
        for (int j = 0; j < data->featureCount; j++)
            rand_data->instances[i].values[j] = (int)data->instances[nb_rand].values[j];
        // On met la classID de rand_data à la place i avec la valeur celle de data à la place nb_rand
        rand_data->instances[i].classID = data->instances[nb_rand].classID;
    }
    // On crée un subproblem avec ce nouveau dataset
    Subproblem *subproblem = Dataset_getSubproblem(rand_data);
    // On retourne le subproblem crée
    return subproblem;
}