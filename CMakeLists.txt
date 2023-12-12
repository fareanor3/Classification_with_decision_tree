cmake_minimum_required(VERSION 3.27)
project(Classification_with_decision_tree C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Classification_with_decision_tree
        Dataset.c
        Dataset.h
        Split.h
        Split.c
        main.c
        Datasets/
        DecisionTree.h
        DecisionTree.c
)
