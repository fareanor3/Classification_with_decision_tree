# Classification_with_decision_tree

## Who to use ?

* to compile

```bash
gcc *.c -Wall -O3 -fopenmp -lm
```

* to run

```bash
./a.out
```

## features

> Decision tree for classification

* geni and entropy as split criteria

// * load a train and test tree from a file

> Random forest with :

* geni and entropy as split criteria

* Dataset_bagging

# Results

> MNIST

```txt
Dataset : 60000 instances, 784 features, 10 classes
Dataset : 10000 instances, 784 features, 10 classes
Subproblem : 60000 instances, 784 features, 10 classes
RandomForest : 20 trees, 10 classes
treeCount = 20, nodeCount = 114392
train = 0.994, test = 0.943
Elapsed time: 62.921 seconds
```

> Pendigits

```txt

```

> Fashion

```txt

```

> Letter

```txt

```

## WARNING

> PTHREADS make some dataleaks...
288 bytes in 1 blocks are possibly

## Authors

@fareanor3
@Solp1
