#include "Split.h"

typedef struct sDecisionTreeNode
{
    struct sDecisionTreeNode *left;
    struct sDecisionTreeNode *right;
    Split split;
    int classID;
} DecisionTreeNode;

DecisionTreeNode *DecisionTree_create(Subproblem *sp, int currentDepth, int maxDepth, float prunningThreshold);

/// @brief Calcule la pureté d'un subproblem
/// @param subproblem Le subroblem
/// @return La ppureté du subproblem
float Subproblem_purity(Subproblem *subproblem);

/// @brief Calcule la class majoritaire d'un subproblem
/// @param subproblem Le subproblem
/// @return La class majoritaire du subproblem
int Subproblem_majorityclass(Subproblem *subproblem);

/// @brief La fonction récursive pour détruire un arbre
/// @param node L'arbre à détruire
void DecisionTree_destroyRec(DecisionTreeNode *node);

/// @brief détruit récursivementles noeuds de l’arbre
/// @param decisionTree L'arbre à détruire
void DecisionTree_destroy(DecisionTreeNode *decisionTree);

/// @brief Fait la fonction suivante mais en récursif
/// @param tree L'arbre a tester
/// @return Le nombre de node
int DecisionTreeNode_parcours(DecisionTreeNode* tree);

/// @brief renvoie le nombre de noeuds présents dans l’arbre, qui servira à vérifier le bon fonctionnement de votre procédure de construction, et également d’obtenir la taille de votre modèle.
/// @param node L'arbre a tester
/// @return Le nombre de node
int Decision_nodeCount(DecisionTreeNode *node);