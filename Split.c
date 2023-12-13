#include "Split.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float Split_gini(Subproblem *sp, int featureID, float threshold)
{
    /*
    1. Pour chaque sous-problème, parcourir toutes les classes l'une après l'autre
    2. Pour chaque classe, calculer la quantité d'individu de cette classe au
       dessus et en dessous de la valeur de seuil et diviser par le total
       d'individus dans le sous-problème et mettre au carré
    3. Retourner 1 - la somme de ce qu'on a calculé en 2
    4. Calculer la moyenne pondérée selon tous les sous-problème
       (pondération calculée en fonction
       du nombre d'individus dans chaque sous-problème)
    5. Retourner la valeur final en float
    */
    int i;
    float gini = 0.0, sum_sup = 0.0, sum_inf = 0.0, p;
    int total_instances = sp->instanceCount;
    int total_sup = 0, total_inf = 0;
    int *class_counts_sup = calloc(sp->classCount, sizeof(int));
    int *class_counts_inf = calloc(sp->classCount, sizeof(int));
    for (i = 0; i < sp->classCount; i++)
        class_counts_sup[i] = class_counts_inf[i] = 0;
    for (i = 0; i < sp->instanceCount; i++) // Parcourir toutes les instances du sous-problème
    {
        if (sp->instances[i]->values[featureID] < threshold)
        {
            class_counts_inf[sp->instances[i]->classID]++;
            total_inf++;
        }
        else
        {
            class_counts_sup[sp->instances[i]->classID]++;
            total_sup++;
        }
    }
    for (i = 0; i < sp->classCount; i++) // Calculer l'indice de Gini pour le sous-problème
    {
        p = (float)class_counts_sup[i] / total_sup;
        sum_sup += p * p;
        p = (float)class_counts_inf[i] / total_inf;
        sum_inf += p * p;
    }

    free(class_counts_sup);
    free(class_counts_inf);
    gini = (1.0 - sum_inf) * total_inf / total_instances + (1.0 - sum_sup) * total_sup / total_instances;
    return gini;
}

// Todo: a aptimiser ! en temps et en précision !!
Split Split_compute(Subproblem *subproblem)
{
    /*
    1. Parcourir toutes les features l'une après l'autre
    2. Pour chaque feature, parcourir toutes les valeurs de cette feature l'une après l'autre
    3. Pour chaque valeur, calculer l'indice de Gini
    4. Retourner le split avec l'indice de Gini le plus faible
    */
    int i, j;
    float gini, min_gini = 1.0;
    Split split;
    for (i = 0; i < subproblem->featureCount; i++) // Parcourir toutes les features
    {                                              // Rechercher comment faire une optimisation pour trouver rapidement le seuil optimal d'une feature (dichotomie peut-être ?)
        // for (j = 0; j < subproblem->instanceCount; j++) // Parcourir toutes les valeurs de la feature
        // {
        //     gini = Split_gini(subproblem, i, subproblem->instances[j]->values[i]);
        //     if (gini < min_gini)
        //     {
        //         min_gini = gini;
        //         split.featureID = i;
        //         split.threshold = subproblem->instances[j]->values[i];
        //     }
        // }
        float max = -INFINITY, min = INFINITY;
        for (j = 0; j < subproblem->instanceCount; j++)
        {
            // recup max et min
            if (subproblem->instances[j]->values[i] > max)
                max = subproblem->instances[j]->values[i];
            if (subproblem->instances[j]->values[i] < min)
                min = subproblem->instances[j]->values[i];
        }
        float PhiJ = (max + min) / 2.0;

        gini = Split_gini(subproblem, i, PhiJ);
        if (gini < min_gini)
        {
            min_gini = gini;
            split.featureID = i;
            split.threshold = PhiJ;
        }
    }
    printf("Split feature : %d threshold : %f min_gini : %f\n", split.featureID, split.threshold, min_gini);
    return split;
}

// int testunit()
// {
//     Split split = Split_compute(Dataset_getSubproblem(Dataset_readFromFile("./Datasets/PENDIGITS_train.txt")));

// vérifier que split est bien le bon
/*
1. Cherche le min et le maximum d'une colonne :
2. faire la moyene (max + min) / 2 = 17
2. calculer l'indice de gini pour cette valeur :
dessous de 17: 1-((2/3)^2+(1/3)^2) = 0.444444
strictement au dessus de 17:1-((1/2)^2+(1/2)^2) = 0.500000
3. faire la moyenne pondérée : 0.444444 * 3/5  + 0.500000 * 2/5 = 0.466667
*/
// }