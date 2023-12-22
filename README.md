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

## Features

> Decision tree for classification

* geni and entropy as split criteria

* Dataset_bagging and feature_bagging

* load a train and test tree from a file

> Random forest with :

* geni and entropy as split criteria

* Dataset_bagging and feature_bagging

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
Dataset : 7494 instances, 16 features, 10 classes
Dataset : 3498 instances, 16 features, 10 classes
Subproblem : 7494 instances, 16 features, 10 classes
RandomForest : 20 trees, 10 classes
treeCount = 20, nodeCount = 14786
train = 0.996, test = 0.953
Elapsed time: 0.385 seconds
```

> Fashion

```txt
Dataset : 60000 instances, 784 features, 10 classes
Dataset : 10000 instances, 784 features, 10 classes
Subproblem : 60000 instances, 784 features, 10 classes
RandomForest : 20 trees, 10 classes
treeCount = 20, nodeCount = 187722
train = 0.984, test = 0.850
Elapsed time: 242.810 seconds
```

> Letter

```txt

```

## WARNING

> PTHREADS make some dataleaks...
288 bytes in 1 blocks are possibly lost

## Authors

@fareanor3
@Solp1
