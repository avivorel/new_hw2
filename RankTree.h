//
// Created by galwe on 08/12/2021.
//


#ifndef AVL_RankTree_H
#define AVL_RankTree_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include "BTSNode.h"


template<class S>
class RankTree//-------------------------------RankTree---------------------------
{
public:
    BSTNode<S> *root;

    RankTree();

    //TODO remove
    static int countNodes(BSTNode<S> *node) {
        if (node == nullptr) {
            return 0;
        }
        return (countNodes(node->left_son) + countNodes(node->right_son) + 1);
    }


    void removeInternal(BSTNode<S> *node);

    //TODO remove
    static BSTNode<S> *getLeftestNode(BSTNode<S> *root) {
        if (root != nullptr) {
            while (root->left_son != nullptr) {
                root = root->left_son;
            }
        }
        return root;
    }

    //TODO remove
    static BSTNode<S> *getMostRightNode(BSTNode<S> *root) {
        if (root != nullptr) {
            while (root->right_son != nullptr) {
                root = root->right_son;
            }
        }
        return root;
    }

    //TODO: change
    static BSTNode<S> *leftRotate(BSTNode<S> *x) {

        BSTNode<S> *y = x->right_son;
        BSTNode<S> *T2 = y->left_son;

        y->left_son = x;
        x->right_son = T2;
        if (T2 != nullptr) {
            T2->parent = x;
        }
        if (x->parent != nullptr) {
            if (x->parent->right_son == x) {
                x->parent->right_son = y;
            } else {
                x->parent->left_son = y;
            }
        }
        y->parent = x->parent;
        x->parent = y;
        x->height = x->getHeight();
        y->height = y->getHeight();
        x->rank = x->getRank();
        y->rank = y->getRank();
        //   x->size=x->getSize();
        //  y->size=y->getSize();
        x->sum_grades = x->getSumGrades();
        y->sum_grades = y->getSumGrades();
        return y;

    }

    static BSTNode<S> *rightRotate(BSTNode<S> *y) {
        BSTNode<S> *x = y->left_son;
        BSTNode<S> *T2 = x->right_son;

        x->right_son = y;
        y->left_son = T2;
        if (T2 != nullptr) {
            T2->parent = y;
        }
        if (y->parent != nullptr) {
            if (y->parent->right_son == y) {
                y->parent->right_son = x;
            } else {
                y->parent->left_son = x;
            }
        }
        x->parent = y->parent;
        y->parent = x;

        y->height = y->getHeight();
        x->height = x->getHeight();
        y->rank = y->getRank();
        x->rank = x->getRank();
        //   y->size=y->getSize();
        //   x->size=x->getSize();
        y->sum_grades = y->getSumGrades();
        x->sum_grades = x->getSumGrades();
        return x;
    }


    RankTree(const RankTree &tree);

    RankTree &operator=(const RankTree &tree);

    void treeDelete(BSTNode<S> *toDelete);

    ~RankTree();

    BSTNode<S> *select(int rank);

    BSTNode<S> *insert(S key, Employee *data);

    void remove(S key);

    BSTNode<S> *find(S key);

    void merge(RankTree<S> *other);

    static int calcHeightDiff(BSTNode<S> *node);


    int FindInBoundMax(S key);

    int selectSumForAvgLevels(int sum);

    int selectSumForScoreInBoundMax(int level);

    int selectSumForScoreInBoundMin(int level);


    void treeToArray2(BSTNode<S> *root, int size, int *counter,
                      Tuple<S> *arr);

    Tuple<S> *treeToArray();

    void twoArraysToOne(Tuple<S> first[], Tuple<S> second[], int size1, int size2, Tuple<S> to_ret[]);

    BSTNode<S> *arrayToAvl(BSTNode<S> *parent, Tuple<S> *arr, int start, int end);

    int getRankByKey(S key);

    int getRankByKey2(S key, int *counter, BSTNode<S> *curr);

    long double getGradesByKey(S key);

    long double getGradesByKey2(S key, int *counter, BSTNode<S> *curr);

    BSTNode<S> *GetLow(int key);

    BSTNode<S> *GetHigh(int key);

    long double GetGradesByRank(int rank);

    void addgrades(S key, long double ta);

}; //-------------------------------RankTree END---------------------------

//TODO maybe delete
template<class S>
BSTNode<S>::BSTNode(const BSTNode<S> &node):
        key(node.key),
        data(node.data),
        left_son(node.left_son),
        right_son(node.right_son),
        parent(node.parent),
        height(node.height),
        rank(node.rank) {

}

template<class S>
BSTNode<S>::BSTNode(S key, Employee *data, BSTNode<S> *parent):
        key(key),
        data(data),
        left_son(nullptr),
        right_son(nullptr),
        parent(parent),
        height(1),
        rank(1),
        sum_grades(data->getGrade()) {

}

template<class S>
BSTNode<S>::BSTNode(S key, Employee *data):
        key(key),
        data(data),
        left_son(nullptr),
        right_son(nullptr),
        parent(nullptr),
        height(1),
        rank(1),
        sum_grades(data->getGrade()) {

}

//TODO maybe delete
template<class S>
BSTNode<S> &BSTNode<S>::operator=(const BSTNode &node) {
    if (this == &node)
        return *this;
    delete this;
    this->data = node.data;
    this->left_son = node.left_son;
    this->right_son = node.right_son;
    this->height = node.height;
    this->key = node.key;
    this->height = node.height;
    this->rank = node.rank;
    return *this;
}


template<class S>
RankTree<S>::RankTree():root(nullptr) {
}

template<class S>
RankTree<S>::RankTree(const RankTree<S> &tree) {
    this->root = copyTreeInternal(this->root, tree.root);
}

template<class S>
RankTree<S> &RankTree<S>::operator=(const RankTree &tree) {
    if (this == &tree)
        return *this;
    treeDelete(this->root);
    copyTreeInternal(this, tree);
    return *this;
}


template<class S>
RankTree<S>::~RankTree() {
    treeDelete(this->root);
//        delete this->root;
}

template<class S>
void RankTree<S>::treeDelete(BSTNode<S> *toDelete) {
    if (toDelete != nullptr) {

        treeDelete(toDelete->left_son);
        treeDelete(toDelete->right_son);
        delete toDelete;
    }
}


template<class S>
void insertInternal(BSTNode<S> *node, S key, Employee *data) {

    if (key > node->key) {
        if (node->right_son == nullptr) {
            node->right_son = new BSTNode<S>(key, data);
            node->right_son->parent = node;
            rebalance(node);
        } else {
            insertInternal(node->right_son, key, data);
        }

    }
    if (key < node->key) {
        if (node->left_son == nullptr) {
            node->left_son = new BSTNode<S>(key, data);
            node->left_son->parent = node;
            rebalance(node);
        } else {
            insertInternal(node->left_son, key, data);

        }
    }
}


template<class S>
BSTNode<S> *selectInternal(BSTNode<S> *node, int rank) {
    if (node->left_son->rank == rank - 1) {
        return node;
    }
    if (node->left_son->rank > rank - 1) {
        selectInternal(node->left_son, rank);
    } else {
        selectInternal(node->right_son, rank - node->left_son->rank - 1);
    }
}


template<class S>
BSTNode<S> *RankTree<S>::select(int rank) {
    if (rank > this->root->rank) {
        return nullptr;
    }
    return selectInternal(this->root, rank);
}







/*

template<class S>
int selectSumForScoreInBoundMaxInternal(BSTNode<S> *node,int rank) {
    int sum=node->sum;
    if(node->rank==rank)
    {
        if(node->right_son== nullptr)
        {
            return node->sum;
        }
        return node->sum-node->right_son->sum;
    }
    if (node->left_son->sum > rank) {
        selectSumForScoreInBoundMaxInternal(node->left_son, rank);
    } else {
        selectSumForScoreInBoundMaxInternal(node->right_son, rank-node->left_son->sum-node->data);
    }
}
*/

/*
template<class T,class S>
int RankTree<S>::selectSumForScoreIn


BoundMax(int level) {
    if(this->root== nullptr)
    {
        return 0;
    }
    int sum=0;
    BSTNode<T,S> *node= this->root;
    while(node!= nullptr)
    {
        if(node->key==level)
        {
            if(node->right_son!= nullptr)
            {
                return sum+node->right_son->sum;
            }
            return sum;
        }
        else if(node->key<level)
        {
            node=node->right_son;
        }
        else if(node->key>level)
        {
            if(node->right_son!= nullptr)
            {
                sum+=node->data+node->right_son->sum;
            }
            else
            {
                sum+=node->data;
            }
            node=node->left_son;
        }
    }
    return sum;
}*/

/*
template<class S>
int RankTree<S>::selectSumForScoreInBoundMin(int level) {
    if(this->root== nullptr)
    {
        return 0;
    }
    int sum=0;
    BSTNode<S> *node= this->root;
    while(node!= nullptr)
    {
        if(node->key==level)
        {
            if(node->left_son!= nullptr)
            {
                return (sum + node->left_son->sum);
            }
            return sum;
        }
        else if(node->key < level)
        {
            if(node->left_son != nullptr)
            {
                sum+=node->data+node->left_son->sum;
            }
            else
            {
                sum+=node->data;
            }
            node=node->right_son;
        }
        else if(node->key>level)
        {
            node=node->left_son;
        }
    }
    return sum;
}
template<class S>
int RankTree<S>::FindInBoundMax(S key)
{
    BSTNode<S> * node=this->root,*prev;

    while(node!= nullptr)
    {
        prev=node;
        if(key==node->key)
        {
            if(node->right_son!= nullptr)
            {
                return node->right_son->sum;
            } else
            {
                return 0;
            }
        }
        if(key>node->key)
        {
            node=node->right_son;
        }
        else
        {
            node=node->left_son;
        }
    }

}*/

//TODO : understand 3 functs up

template<class S>
BSTNode<S> *RankTree<S>::insert(S key, Employee *data) {

    if (this->root == nullptr) {
        this->root = new BSTNode<S>(key, data);
        return this->root;
    }
    insertInternal(this->root, key, data);


    if (this->root->parent != nullptr) {
        this->root = this->root->parent;
    }
    return nullptr;
}


template<class S>
BSTNode<S> *RankTree<S>::find(S key) {
    BSTNode<S> *curr = this->root;
    while (curr != nullptr) {
        if (curr->key > key) {
            curr = curr->left_son;
        } else if (curr->key < key) {
            curr = curr->right_son;
        } else
            return curr;
    }
    return curr;
}

template<class S>
int RankTree<S>::calcHeightDiff(BSTNode<S> *node) {
    return node->left_son->getHeight() - node->right_son->getHeight();
}

template<class S>
void rebalance(BSTNode<S> *start) {
    if (start == nullptr)
        return;
    while (start != nullptr) {
        start = start->roll();
        //maybe instert all functs to roll
        start->height = start->getHeight();//TODO: change to update and get
        start->rank = start->getRank();
        //    start->size=start->getSize();
        start->sum_grades = start->getSumGrades();
        start = start->parent;
    }
}


template<class S>
void RankTree<S>::remove(S key) {
    BSTNode<S> *toDelete = find(key);
    if (toDelete == nullptr) {
        return;
    }
    if (toDelete == this->root) {
        if (this->root->right_son == nullptr || this->root->left_son == nullptr) {
            BSTNode<S> *temp = this->root->left_son ? this->root->left_son : this->root->right_son;
            delete this->root;
            this->root = temp;
            if (temp == nullptr) {
                return;
            }
            temp->height = 1;
            temp->parent = nullptr;
            return;
        }
    }

    removeInternal(toDelete);
    if (this->root != nullptr && this->root->parent != nullptr) {
        this->root = this->root->parent;
    }
}


template<class S>
void RankTree<S>::removeInternal(BSTNode<S> *node) {
    if (node == nullptr)
        return;
    if ((node->left_son == nullptr) || (node->right_son == nullptr)) {
        BSTNode<S> *temp = node->left_son ? node->left_son : node->right_son;
        BSTNode<S> *startfrom = node->parent;
        if (temp != nullptr) {
            if (node->parent->right_son == node) {
                startfrom->right_son = temp;
                temp->parent = node->parent;
            }
            if (node->parent->left_son == node) {
                startfrom->left_son = temp;
                temp->parent = node->parent;
            }
        } else {
            if (node->parent->left_son == node) {
                startfrom->left_son = nullptr;
            }
            if (node->parent->right_son == node) {
                startfrom->right_son = nullptr;
            }
        }
        delete node;
        rebalance(startfrom);
        return;
    } else {
        BSTNode<S> *temp = node->right_son;
        while (temp->left_son != nullptr) {
            temp = temp->left_son;
        }
        node->key = temp->key;
        node->data = temp->data;
        removeInternal(temp);
    }
}


//TODO: change (cpypst)
template<class S>
BSTNode<S> *BSTNode<S>::roll() {
    int BF = RankTree<S>::calcHeightDiff(this);

    // Left Left Case
    if (BF > 1 &&
        RankTree<S>::calcHeightDiff(this->left_son) >= 0) {
        return RankTree<S>::rightRotate(this);
    }

    // Left Right Case
    if (BF > 1 &&
        RankTree<S>::calcHeightDiff(this->left_son) < 0) {
        RankTree<S>::leftRotate(this->left_son);
        return RankTree<S>::rightRotate(this);
    }

    // Right Right Case
    if (BF < -1 &&
        RankTree<S>::calcHeightDiff(this->right_son) <= 0)
        return RankTree<S>::leftRotate(this);

    // Right Left Case
    if (BF < -1 &&
        RankTree<S>::calcHeightDiff(this->right_son) > 0) {
        RankTree<S>::rightRotate(this->right_son);
        return RankTree<S>::leftRotate(this);
    }
    return this;


}


template<class S>
void RankTree<S>::treeToArray2(BSTNode<S> *root, int size, int *counter,
                               Tuple<S> *arr) {

    if (!root) {
        return;
    }
    treeToArray2(root->left_son, size, counter, arr);
    auto *toInsert = new Tuple<S>(root->key, root->data);
    arr[*counter] = *toInsert;
    *counter += 1;

    treeToArray2(root->left_son, size, counter, arr);

}

template<class S>
Tuple<S> *RankTree<S>::treeToArray() {
    auto *to_ret = new Tuple<S>[this->root->rank];
    int a = 0;

    treeToArray2(root, this->root->rank, &a, to_ret);
    return to_ret;

}


template<class S>
void
RankTree<S>::twoArraysToOne(Tuple<S> first[], Tuple<S> second[], int size1, int size2, Tuple<S> to_ret[]) {
    int counter = 0;
    int firstIndex = 0;
    int secondIndex = 0;


    Tuple<S> a = first[firstIndex];
    Tuple<S> b = second[secondIndex];

    while (firstIndex < size1 || secondIndex < size2) {
        if (firstIndex == size1) {
            to_ret[counter] = b;
            counter++;
            secondIndex++;
            b = second[secondIndex];
        } else {
            if (secondIndex == size2) {
                to_ret[counter] = (first[firstIndex]);
                counter++;
                firstIndex++;
                a = first[firstIndex];
            } else {
                if (a.GetKey() < b.GetKey()) {
                    to_ret[counter] = (first[firstIndex]);
                    counter++;
                    firstIndex++;
                    a = first[firstIndex];
                } else {
                    to_ret[counter] = b;
                    counter++;
                    secondIndex++;
                    b = second[secondIndex];
                }

            }
        }

    }
}


template<class S>
BSTNode<S> *
RankTree<S>::arrayToAvl(BSTNode<S> *parent, Tuple<S> *arr, int start, int end) {

    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    RankTree<S> toRet;
    BSTNode<S> *newNode = new BSTNode<S>(static_cast<Tuple<S>>(arr[mid]).GetKey(),
                                         static_cast<Tuple<S>>(arr[mid]).GetValue(), parent);
    newNode->left_son = arrayToAvl(newNode, arr, start, mid - 1);
    newNode->right_son = arrayToAvl(newNode, arr, mid + 11, end);
    return newNode;
}


template<class S>
void RankTree<S>::merge(RankTree<S> *other) {

    if (!other or !other->root) {
        return;
    }

    if (!this->root) {
        //this = other;
        return;
    }

    Tuple<S> *first = this->treeToArray();

    Tuple<S> *second = other->treeToArray();

    int size3 = other->root->rank + this->root->rank;
    int size1 = this->root->rank;
    int size2 = other->root->rank;

    auto *to_ret = new Tuple<S>[size3];

    // twoArraysToOne (arr1, arr2, this->root->rank, other->root->rank,arr3);
    int counter = 0;
    int firstIndex = 0;
    int secondIndex = 0;


    Tuple<S> a = first[firstIndex];
    Tuple<S> b = second[secondIndex];

    while (firstIndex < size1 || secondIndex < size2) {
        if (firstIndex == size1) {
            to_ret[counter] = b;
            counter++;
            secondIndex++;
            b = second[secondIndex];
        } else {
            if (secondIndex == size2) {
                to_ret[counter] = first[firstIndex];
                counter++;
                firstIndex++;
                a = first[firstIndex];
            } else {
                if (a.GetKey() < b.GetKey()) {
                    to_ret[counter] = (first[firstIndex]);
                    counter++;
                    firstIndex++;
                    a = first[firstIndex];
                } else {
                    to_ret[counter] = b;
                    counter++;
                    secondIndex++;
                    b = second[secondIndex];
                }

            }
        }

    }
    Tuple<S> one = to_ret[0];
    Tuple<S> two = to_ret[1];
    delete first;
    delete second;
    BSTNode<S> *val = arrayToAvl(nullptr, to_ret, 0, size3);
    this->root = val;

    root->updateRanks(root);
    root->updateGrades(root);
    delete[] to_ret;

}

template<class S>
int RankTree<S>::getRankByKey(S key) {
    if (this->find(key) == nullptr) {
        return -1;
    }
    int a = 0;
    getRankByKey2(key, &a, root);
    return a;
}

template<class S>
int RankTree<S>::getRankByKey2(S key, int *counter, BSTNode<S> *curr) {

    if (key == curr->key) {
        if (curr->right_son != nullptr) {
             (*counter) +=curr->rank - curr->right_son->rank;
        } else {
            (*counter)+=curr->rank;
        }
        return 0;
    }
    if (key < curr->key) {
        return getRankByKey2(key, counter, curr->left_son);
    }
    *counter += (*counter) + root->left_son->rank + 1;
    return getRankByKey2(key, counter, curr->right_son);
}


template<class S>
long double RankTree<S>::getGradesByKey(S key) {
    if (this->find(key) == nullptr) {
        return -1;
    }
    int a = 0;
    getGradesByKey2(key, &a, root);
    return a;
}

template<class S>
long double RankTree<S>::getGradesByKey2(S key, int *counter, BSTNode<S> *curr) {
    if (key == curr->key) {
        if (curr->right_son != nullptr) {
            (*counter) +=curr->sum_grades - curr->right_son->sum_grades;
        } else {
            (*counter)+=curr->sum_grades;
        }
        return 0;
    }
    if (key < curr->key) {
        return getGradesByKey2(key, counter, curr->left_son);
    }
    *counter += (*counter) + root->left_son->sum_grades + curr->data->getGrade();
    return getGradesByKey2(key, counter, curr->right_son);
}

template<class S>
BSTNode<S> *RankTree<S>::GetLow(int key) {

    BSTNode<S> *curr = this->root;
    BSTNode<S> *ret = nullptr;

    while (curr != nullptr) {
        if (curr->data->getSalary() > key) {
            ret = curr;
            curr = curr->left_son;

        } else if (curr->data->getSalary() < key) {
            curr = curr->right_son;

        } else {
            while (curr != nullptr and curr->data->getSalary() == key) {
                ret = curr;
                curr = curr->left_son;
            }
            return ret;
        }

    }
    return ret;

}


template<class S>
BSTNode<S> *RankTree<S>::GetHigh(int key) {
    BSTNode<S> *curr = this->root;
    BSTNode<S> *ret = nullptr;

    while (curr != nullptr) {
        if (curr->data->getSalary() > key) {
            curr = curr->left_son;

        } else if (curr->data->getSalary() < key) {
            ret = curr;
            curr = curr->right_son;

        } else {
            while (curr != nullptr and curr->data->getSalary() == key) {
                ret = curr;
                curr = curr->right_son;
            }
            return ret;
        }

    }
    return ret;

}

template<class S>
long double RankTree<S>::GetGradesByRank( int rank) {
    BSTNode<S> *curr= this->root;
    long double sum=0;
    if (!curr) {
        return 0;
    }
    if (rank > curr->rank) {
        return 0;
    }
    if (rank == 0) {
        return 0;
    }


    int rightrank=0;
    long double rightgrade;
    if (!curr->right_son) {
        rightrank = 0;
        rightgrade=0;
    }
    else
    {
        rightrank=curr->right_son->rank;
        rightgrade=curr->right_son->sum_grades;
    }
    while (rank != rightrank+1) {
        if(rightrank<1)
        {
            throw std::bad_cast();
        }

        if (rank>rightrank) {

            sum+=curr->sum_grades-curr->left_son->sum_grades;
            rank-=(rightrank+1);
            curr = curr->left_son;
        } else  {
            curr = curr->right_son;
        }



        if (!curr->right_son) {
            rightrank = 0;
            rightgrade=0;
        }
        else
        {
            rightrank=curr->right_son->rank;
            rightgrade=curr->right_son->sum_grades;
        }
    }
    return sum+rightgrade+curr->data->getGrade();





   /*
    }
    int rightrank;
    long double rightgrade = curr->data->getGrade();
    if (!curr->right_son) {
        rightrank = 0;

    } else {
        rightrank = curr->right_son->rank;
        rightgrade += curr->right_son->sum_grades;
    }
    long double leftgrade= root->sum_grades-rightgrade+root->data->getGrade();
    if(rightrank+1==rank)
    {
        return sum+leftgrade;
    }
    if (rightrank > rank) {

        return GetGradesByRank(sum+leftgrade,rank,curr->right_son);
       // return GetGradesByRank(sum + rightgrade, rank - rightrank - 1, curr->left_son);
    } else {
        return GetGradesByRank(sum, rank-rightrank-1, curr->left_son);
    }*/
}

template<class S>
void RankTree<S>::addgrades(S key, long double toadd) {
    BSTNode<S> *f = find(key);
    f->addsumgradesnew(toadd);
}


class MyNode {
private:
    Employee *data;
    MyNode *next;

public:
    MyNode(Employee *data1) : data(data1), next(nullptr) {};

    MyNode *GetNext() const {
        return this->next;
    }

    Employee *GetEmployee() {
        return this->data;
    }

    void SetEmployee(Employee *emp) {
        this->data = emp;
    }

    void SetNext(MyNode *next) {
        this->next = next;
    }

    ~MyNode() {}
};

class MyHash {
    typedef enum {
        HT_SUCCESS = 0,
        HT_FAILURE = -1,
        HT_ALLOCATION_ERROR = -2
    } StatusHashTable;


    MyNode **table;
    int capacity;
    int tableSize;

    /*the hash function
     * complexity: O(1)*/
    int hashFunc(int key) {
        return key % this->tableSize;
    }


    /*clean all the data from the table
     * complexity: O(n)*/
    void tableClean(MyNode **table, int size) {
        for (int i = 0; i < size; ++i) {
            delete (table[i]);
            table[i] = NULL;
        }
    }

    /*increase the table to bigger one and copy all the data to the new bigger table
     * complexity: O(n)*/
    void tableIncrease() {
        int oldSize = this->tableSize;
        MyNode **old_table = table;
        int newSize = (2 * oldSize) + 1;
        MyNode **newTable = new MyNode *[newSize]();
        this->tableSize = newSize;
        this->table = newTable;


        for (int i = 0; i < oldSize; ++i) {
            MyNode *currentNode = old_table[i];


            while (currentNode != nullptr) {
                this->Insert(currentNode->GetEmployee());
                currentNode = currentNode->GetNext();
            }
           // this->table[i] = nullptr;//disconnecting the old table from the nodes
        }
        delete[] (old_table);//TODO think about it later
    }

public:
    /*get pointer to data saved in the table by key
    * average complexity: O(1)*/
    Employee *GetEmp(int key) {
        int indexToSeek = this->hashFunc(key);
        MyNode *currentNode = this->table[indexToSeek];
        while (currentNode != nullptr) {
            if (currentNode->GetEmployee()->getId() == key) {
                return currentNode->GetEmployee();
            }
            currentNode = currentNode->GetNext();
        }
        return nullptr;
    }


    /*constructor build new table with 2*(given size) + 1
     * complexity: O(n)*/
    explicit MyHash(int initSize) : table(nullptr), capacity(0), tableSize((2 * initSize) + 1) {
        this->table = new MyNode *[tableSize]();
    }

    explicit MyHash() : table(nullptr), capacity(0), tableSize(17) {
        this->table = new MyNode *[tableSize]();
    }


    /*destructor deallocate all nodes and the table itself
     * complexity: O(n)*/
    ~MyHash() {
        this->tableClean(this->table, this->tableSize);
        delete[](this->table);
    }


    /* return true if and only if the key exist in the table
     * average complexity: O(1)*/
    bool isExist(int key) {
        return (this->GetEmp(key) != nullptr);
    }

    /*insert the data to table
     * estimate complexity: O(1)*/
    StatusHashTable Insert(Employee *data) {
        int key = data->getId();
        if (this->GetEmp(key) != nullptr) {
            return HT_FAILURE;
        }
        int indexToInsert = this->hashFunc(key);
        try {
            MyNode *newNode = new MyNode(data);
            MyNode *A = this->table[indexToInsert];
            newNode->SetNext(this->table[indexToInsert]);
            this->table[indexToInsert] = newNode;
            this->capacity++;
            if (this->capacity == this->tableSize) {
                this->tableIncrease();
            }
            return HT_SUCCESS;
        } catch (const std::bad_alloc &) {
            return HT_ALLOCATION_ERROR;
        }
    }

//TODO think about shrink
    bool Remove(Employee *data) {
        int key = data->getId();
        if (this->GetEmp(key) == nullptr) {
            return false;
        }
        int indexToRemove = this->hashFunc(key);
        MyNode *chain = table[indexToRemove];
        if (chain->GetEmployee()->getId() == data->getId()) {
            table[indexToRemove] = table[indexToRemove]->GetNext();
            this->capacity--;
            delete chain;
            return true;
        }
        while (chain->GetNext() != nullptr) {
            if (chain->GetNext()->GetEmployee()->getId() == data->getId()) {
                MyNode *ptr= chain->GetNext();
                chain->SetNext(chain->GetNext()->GetNext());
                this->capacity--;
                delete ptr;
                return true;
            }
            chain = chain->GetNext();
        }
        return false;
    }

    void unite(MyHash *hash) {
        for (int i = 0; i <= hash->tableSize - 1; i++) {
            MyNode *currentNode = hash->table[i];


            while (currentNode != nullptr) {
                this->Insert(currentNode->GetEmployee());

                currentNode = currentNode->GetNext();
            }
            this->table[i] = nullptr;//disconnecting the old table from the nodes
        }
        //delete[] (old_table);TODO think about it later

    }
};


class Company {
private:
    int id;
    int value;
    int numOfEmployees;
    double value_inc;
    RankTree<employeeCondition_Salary_Id> *employees;
    MyHash *emphash;


public:
    int num_of_0_sal;
    long double sum_of_0_grades;


    ~Company();

    void changeCompany(BSTNode<employeeCondition_Salary_Id> *node);

    Company(int id1, int value1, int numOfEmployees1, RankTree<employeeCondition_Salary_Id> *employees,
            Employee *highestSalaryInCompany);

    Company(int id1, int value1) : id(id1), value(value1), numOfEmployees(0), value_inc(0),
                                   num_of_0_sal(0), sum_of_0_grades(0) {
        employees = new RankTree<employeeCondition_Salary_Id>();
        emphash = new MyHash();
    }

    MyHash *GetEmpHash() const;

    int getId() const;

    int getValue() const;

    int getNumOfEmployees() const;

    double getValueInc() const;

    void changeValInc(double x);

    void AddToTree(Employee *emp);


    Employee *getHighestSalaryInCompany() const;

    void Merge(Company *other);


    RankTree<employeeCondition_Salary_Id> *getEmployees_bySalary() const;


    void getarrmax(int *emp, BSTNode<employeeCondition_Salary_Id> *node, int *counter) const;

    void setValue(int newValue);

    void IncreaseEmployees(int incAmount);

    void addEmployee(Employee *toAdd);

    void removeEmployee(Employee *toRemove);


};


#endif //AVL_RANKTREE_H
