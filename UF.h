//
// Created by User on 07/06/2022.
//

#ifndef PROJECT_UF_H
#define PROJECT_UF_H

#include <stdio.h>
#include <stdlib.h>
#include "RankTree.h"

class unionFind {
    int size;

    int* parents;

    int* size_;

    int* owner;

    double * val;

    Company** companies;

public:
    explicit unionFind(int size);
    ~unionFind();
    Company* Find(int x);
    int unite( int index1,  int index2, double factor);
    void Union(int acquire, int target, double Factor);
    double FindValue(int index);

};



typedef unionFind *UnionFind;

#endif //PROJECT_UF_H
