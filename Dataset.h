typedef struct sInstance
{
    int *values;
    int classID;
} Instance;

typedef struct sDataset
{
    Instance *instances;
    int instanceCount;
    int featureCount;
    int classCount;
} Dataset;
typedef struct sSubproblemClass
{
    int instanceCount;
    Instance **instances;
} SubproblemClass;

typedef struct sSubproblem
{
    Instance **instances;
    int instanceCount;
    int capacity;
    int featureCount;
    int classCount;
    SubproblemClass *classes;
} Subproblem;

/// @brief lit le fichier et extrait toutes les informations du dataset
/// @param filename le fichier à lire
/// @return l'adresse du Dataset dans lequel les informations ont été rangées, NULL si la lecture a échoué
Dataset *Dataset_readFromFile(char *filename);

/// @brief détruit proprement une allocation de la structure Dataset. On pensera également à désallouer le tableau d’instances présent à l’intérieur de la structure.
/// @param data adressede la structure à désallouer
void Dataset_destroy(Dataset *data);

/// @brief Attention : on ne demande pas de copier les instances contenues dans Dataset, mais de simplement stocker leur adresse dans un tableau. On en profitera également pour recopier les valeurs instanceCount, featureCount et classCount, qui seront identiques dans les deux structures.
/// @param data adresse du Dataset à prendre en compte
/// @return un Subproblem avec les informations
Subproblem *Dataset_getSubproblem(Dataset *data);

/// @brief Crée une structure Subproblem correctement allouée
/// @param maximumCapacity capacité du tableau de pointeurs
/// @param featureCount valeurs des attributs
/// @param classCount valeurs des attributs
/// @return une allocation de la structure Subproblem
Subproblem *Subproblem_create(int maximumCapacity, int featureCount, int classCount);

/// @brief détruit proprement une allocation de Subproblem, en détruisant les différents tableaux. Attention : ce n’est pas parce que l’on travaille avec des tableaux de pointeurs qu’il faut détruire ce qui se trouve dans les cases des dits-tableaux, les adresses stockées font références aux instances présentes dans la structure Dataset.
/// @param subproblem La structure Subproblem
void Subproblem_destroy(Subproblem *subproblem);

/// @brief insère l’adresse d’une instance dans le sous-problème, à la fois dans le tableau principal et le tableau dédié à la classe de l’instance, et met à jour le nombre d’instances considérées.
/// @param subproblem la structure où l'on insère
/// @param instance l'instance à insérer
void Subproblem_insert(Subproblem *subproblem, Instance *instance);

/// @brief affiche le nombre de features, de classes et d’instances référencées, ainsi que le nombre d’instances pour chacune des classes.
/// @param subproblem la structure dont on affiche les données
void Subproblem_print(Subproblem *subproblem);