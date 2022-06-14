//
// Created by User on 07/06/2022.
//

#include "UF.h"

unionFind::unionFind(int size) : size(size) {
    size_ = new int[size+1];
    parents = new int[size+1];
    companies = new Company *[size+1];
    owner = new int[size+1];
    val= new double [size+1];
    for (int i = 1; i <= size; ++i) {
        parents[i] = -1;
        size_[i] = 1;
        companies[i] = new Company(i, i);
        owner[i]=i;
        val[i]=0;
    }

}

unionFind::~unionFind() {
    delete[] size_;
    delete[] parents;
    delete[]owner;
    delete[] val;
    //TODO maybe for
    delete[] companies;

}


Company *unionFind::Find(int index) {
    int parent = this->parents[index];
    int av_kadmon = index;
    double sum = 0;
    while (parent > -1) {
        av_kadmon = parent;
        sum += val[index];
        parent = this->parents[parent];
    }
  /*  parent = av_kadmon;
    int temp = index;
    int new_temp;
    while (temp != parent) {
        new_temp = parents[temp];
        parents[temp] = parent;
        int sum_to_sub = companies[temp]->getValueInc();
        companies[temp]->changeValInc(-sum);
        sum -= sum_to_sub;
        temp = new_temp;
    }*/
    return companies[owner[av_kadmon]];
}


int unionFind::unite(int index1, int index2,  double toadd) {


    int parent1 = index1;
    int parent2 = index2;
    while (parents[parent1] != -1) {
        parent1 = parents[parent1];
    }
    while (parents[parent2] != -1) {
        parent2 = parents[parent2];
    }

    if (parent1==parent2) {
        return -1;
    }

    if (size_[parent1] >size_[parent2]) {

        val[parent1]+=toadd;
        val[parent2]-=val[parent1];
        parents[parent2] = parent1;
        size_[parent1] += size_[parent2];
    } else {


        double valinc=toadd-val[parent2];
        val[parent1]+=valinc;
        owner[parent2]=owner[parent1];
        parents[parent1] = parent2;
        size_[parent2] += size_[parent1];
    }


    return parent1;
}

void unionFind::Union(int acquire, int target, double Factor)
{
    Company* acquirecomp = Find(acquire);
    Company* tarcomp = Find(target);
    double value = Factor * FindValue(target);
    if (size_[target] <= size_[acquire])
    {
        int temp, last = acquire;
        while (last != -1)
        {
            temp = last;
            last = parents[temp];
            if (last != -1)
            {
                //    elements[last - 1]->IncreaseValue(-1 * value);
            }
        }
        int temp2, last2 = target;
        while (last2 != -1)
        {
            temp2 = last2;
            last2 = parents[temp2];
        }
        val[temp] += value;
        val[temp2] -= val[temp];
        parents[temp2 ] = temp;
    }
    else
    {
        int temp, last = acquire;
        while (last != -1)
        {
            temp = last;
            last = parents[temp ];
        }
        int temp2, last2 = target;
        while (last2 != -1)
        {
            temp2 = last2;
            last2 = parents[temp2];
        }
        val[temp ] += value - val[temp2 ];
        parents[temp ] = temp2;
    }
    size_[acquire] += size_[target];
    owner[target] = acquire;
}

double unionFind::FindValue(int index) {
    if (index > size || index < 0) {
        return -1;
    }
    if(index==10)
    {
        int a=4;
    }

    int uf_iter = index;
    double value = 0;

    while (uf_iter != -1) {
        value += val[uf_iter];
        uf_iter = parents[uf_iter];
    }
    value += companies[index]->getValue();
    return value;
}