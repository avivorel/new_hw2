//
// Created by darkm on 02/06/2022.
//

#ifndef PROJECT_AVLTREE_H
#define PROJECT_AVLTREE_H


#include <iostream>
#include <cstdio>
#include <cmath>
#include <assert.h>
#include <cassert>
#include "exceptions.h"
#include "Array.h"


using namespace std;

template<class T, class S>
class AVLNode {
public:
    T key_m;
    S value_m;
    AVLNode *left_m;
    AVLNode *right_m;
    int height_m;
    int rank_m;
    T leftSum;
    T rightSum;


    AVLNode(const T &key = T(), const S &value = S(), const T &leftSum = T(),
            const T &rightSum = T())
            : key_m(key),
              value_m(value),
              left_m(nullptr),
              right_m(nullptr),
              height_m(1),
              rank_m(1),
              leftSum(leftSum),
              rightSum(rightSum) {}

    ~AVLNode() {
        delete left_m;
        delete right_m;
    }
};

template<typename T, typename S>
static void
mergeSortedArrays(T *arr1Keys, S *arr1Values, T *arr2Keys, S *arr2Values,
                  int arr1Size, int arr2Size, int *mergedSize, AVLNode<T,S>* mergedArr);

template<class T, class S>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    AVLTree(const AVLTree &aTree);

    AVLTree &operator=(const AVLTree &aTree);

    bool insertElement(const T &key, const S &value = S());

    void deleteElement(const T &key);

    bool searchKey(const T &key);

    const AVLNode<T, S> *searchIndex(const int &index) const;

    S &operator[](const T &key);

    const S &operator[](const T &key) const;

    void printTree(T *keyArr, S *valArr) const; //prints inorder into array

    void printInOrder();

    void printRanksInOrder();

    void printSumsInOrder();

    int countNodesInTree() const;

    void mergeTrees(const AVLTree<T, S> &treeA, const AVLTree &treeB);

    AVLNode<T, S> *getRoot();

    const T getSumOfLargerKeys(const T &key) const;


private:
    AVLNode<T, S> *root;

    AVLNode<T, S> *rollLL(AVLNode<T, S> *aNode);

    AVLNode<T, S> *rollRR(AVLNode<T, S> *aNode);

    int height(AVLNode<T, S> *aNode);

    int rank(AVLNode<T, S> *aNode);

    int countNodes(const AVLNode<T, S> *aNode) const;

    void
    printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr, int *iteration) const;

    bool checkIfBalanced(AVLNode<T, S> *aNode);

    AVLNode<T, S> *
    createTreeFromSortedArr(AVLNode<T, S> *nodeArr, int start, int end);

    AVLNode<T, S> *deleteNode(AVLNode<T, S> *root, const T &keyToDelete);

    AVLNode<T, S> *
    insertNode(AVLNode<T, S> *root, const T &key, const S &value);

    AVLNode<T, S> *getMin(AVLNode<T, S> *);

    int getBalance(AVLNode<T, S> *aNode);

    AVLNode<T, S> *searchIndex(const int &rank, AVLNode<T, S> *root) const;

    void printInOrder(AVLNode<T, S> *root);

    void printRanksInOrder(AVLNode<T, S> *root);

    void printSumsInOrder(AVLNode<T, S> *root);

    const T getSumOfLargerKeys(const T &key, const AVLNode<T, S> *root,
                               const T &currSum) const;


};


template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollLL(AVLNode<T, S> *aNode) {
    AVLNode<T, S> *rotatedNode = aNode->right_m;
    AVLNode<T, S> *temp = rotatedNode->left_m;

    rotatedNode->left_m = aNode;
    aNode->right_m = temp;

    aNode->height_m = std::max(height(aNode->left_m),
                               height(aNode->right_m)) + 1;
    aNode->rank_m = 1 + rank(aNode->left_m) + rank(aNode->right_m);
    aNode->leftSum = aNode->left_m != nullptr ? aNode->left_m->leftSum +
                                                aNode->left_m->rightSum +
                                                aNode->left_m->key_m : 0;
    aNode->rightSum = aNode->right_m != nullptr ? aNode->right_m->leftSum +
                                                  aNode->right_m->rightSum +
                                                  aNode->right_m->key_m : 0;

    rotatedNode->height_m = std::max(height(rotatedNode->left_m),
                                     height(rotatedNode->right_m)) + 1;
    rotatedNode->rank_m =
            1 + rank(rotatedNode->left_m) + rank(rotatedNode->right_m);
    rotatedNode->leftSum =
            rotatedNode->left_m != nullptr ? rotatedNode->left_m->leftSum +
                                             rotatedNode->left_m->rightSum +
                                             rotatedNode->left_m->key_m : 0;
    rotatedNode->rightSum =
            rotatedNode->right_m != nullptr ? rotatedNode->right_m->leftSum +
                                              rotatedNode->right_m->rightSum +
                                              rotatedNode->right_m->key_m : 0;

    return rotatedNode;
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollRR(AVLNode<T, S> *aNode) {
    AVLNode<T, S> *rotatedNode = aNode->left_m;
    AVLNode<T, S> *temp = rotatedNode->right_m;

    rotatedNode->right_m = aNode;
    aNode->left_m = temp;

    aNode->height_m = max(height(aNode->left_m),
                          height(aNode->right_m)) + 1;
    aNode->rank_m = 1 + rank(aNode->right_m) + rank(aNode->left_m);
    aNode->leftSum = aNode->left_m != nullptr ? aNode->left_m->leftSum +
                                                aNode->left_m->rightSum +
                                                aNode->left_m->key_m : 0;
    aNode->rightSum = aNode->right_m != nullptr ? aNode->right_m->leftSum +
                                                  aNode->right_m->rightSum +
                                                  aNode->right_m->key_m : 0;

    rotatedNode->height_m = max(height(rotatedNode->left_m),
                                height(rotatedNode->right_m)) + 1;
    rotatedNode->rank_m =
            1 + rank(rotatedNode->right_m) + rank(rotatedNode->left_m);
    rotatedNode->leftSum =
            rotatedNode->left_m != nullptr ? rotatedNode->left_m->leftSum +
                                             rotatedNode->left_m->rightSum +
                                             rotatedNode->left_m->key_m : 0;
    rotatedNode->rightSum =
            rotatedNode->right_m != nullptr ? rotatedNode->right_m->leftSum +
                                              rotatedNode->right_m->rightSum +
                                              rotatedNode->right_m->key_m : 0;

    return rotatedNode;
}

template<class T, class S>
int AVLTree<T, S>::height(AVLNode<T, S> *aNode) {
    if (aNode == nullptr) {
        return 0;
    }
    return aNode->height_m;
}

template<class T, class S>
int AVLTree<T, S>::rank(AVLNode<T, S> *aNode) {
    if (aNode == nullptr) {
        return 0;
    }
    return aNode->rank_m;
}


template<class T, class S>
AVLTree<T, S>::AVLTree() : root(nullptr) {}

template<class T, class S>
AVLTree<T, S>::~AVLTree() {
    delete root;
}

template<class T, class S>
bool AVLTree<T, S>::insertElement(const T &key, const S &value) {
    if (searchKey(key)) {
        throw KeyAlreadyExists<T>(key);
    }
    root = insertNode(root, key, value);
    return true;
}


template<class T, class S>
void AVLTree<T, S>::deleteElement(const T &delKey) {
    if (!searchKey(delKey)) {
        throw NoSuchKey();
    }
    root = deleteNode(root, delKey);
}

template<class T, class S>
bool AVLTree<T, S>::searchKey(const T &key) {

    AVLNode<T, S> *iterator = root;

    while (iterator != nullptr) {
        if (iterator->key_m == key)
            return true;

        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;
    }
    return false;
}

template<class T, class S>
S &AVLTree<T, S>::operator[](const T &key) {

    AVLNode<T, S> *iterator = root;
    while (iterator != nullptr) {
        if (iterator->key_m == key)
            return iterator->value_m;

        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;
    }
    throw NoSuchKey();
}

template<class T, class S>
const S &AVLTree<T, S>::operator[](const T &key) const {
    AVLNode<T, S> *iterator = root;
    while (iterator != nullptr) {
        if (iterator->key_m == key)
            return iterator->value_m;

        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;
    }
    throw NoSuchKey();
}


template<class T, class S>
int AVLTree<T, S>::countNodesInTree() const {
    return countNodes(root);
}

template<class T, class S>
int AVLTree<T, S>::countNodes(const AVLNode<T, S> *aNode) const {
    int count = 0;
    if (aNode != nullptr) {
        count += countNodes(aNode->left_m);
        count++;
        count += countNodes(aNode->right_m);
    }
    return count;
}

template<class T, class S>
void AVLTree<T, S>::printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr,
                              int *iteration) const {
    if (aNode == nullptr) {
        return;
    }
    if (aNode->left_m != nullptr) {
        printTree(aNode->left_m, keyArr, valArr, iteration);
    }
    *(keyArr + *iteration) = aNode->key_m;
    *(valArr + *iteration) = aNode->value_m;
    *iteration += 1;

    if (aNode->right_m != nullptr) {
        printTree(aNode->right_m, keyArr, valArr, iteration);
    }
}

template<class T, class S>
void AVLTree<T, S>::printTree(T *keyArr, S *valArr) const {
    int iteration = 0;
    printTree(root, keyArr, valArr, &iteration);
}

template<class T, class S>
bool AVLTree<T, S>::checkIfBalanced(AVLNode<T, S> *aNode) {
    if (aNode == nullptr) {
        return true;
    }
    return ((checkIfBalanced(aNode->left_m)) && abs(getBalance(aNode)) < 2 &&
            checkIfBalanced(aNode->right_m));
}

template<class T, class S>
void
AVLTree<T, S>::mergeTrees(const AVLTree<T, S> &treeA, const AVLTree &treeB) {
    int treeASize = treeA.countNodesInTree();
    int treeBSize = treeB.countNodesInTree();
    T *treeAKeys = new T[treeASize];
    S *treeAVals = new S[treeASize];
    T *treeBKeys = new T[treeBSize];
    S *treeBVals = new S[treeBSize];
    auto nodeArr = new AVLNode<T,S>[treeASize + treeBSize];
    try {

        treeA.printTree(treeAKeys, treeAVals);
        treeB.printTree(treeBKeys, treeBVals);

        int nodeArrSize = 0;
        mergeSortedArrays(treeAKeys, treeAVals,
                          treeBKeys,
                          treeBVals, treeASize,
                          treeBSize, &nodeArrSize, nodeArr);
        delete[] treeAKeys;
        delete[] treeAVals;
        delete[] treeBKeys;
        delete[] treeBVals;

        AVLNode<T, S> *temp = root;
        AVLNode<T, S> *res = createTreeFromSortedArr(nodeArr, 0,
                                                     (nodeArrSize) - 1);
        delete [] nodeArr;
        root = res;



        if (temp != nullptr) {
            delete temp;
        }

    }
    catch (KeyAlreadyExists<T>& e){
        delete[] treeAKeys;
        delete[] treeAVals;
        delete[] treeBKeys;
        delete[] treeBVals;
        delete [] nodeArr;
        throw KeyAlreadyExists<T>(e.whatKey());
    }
}


template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::getRoot() {
    return root;
}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::createTreeFromSortedArr(AVLNode<T, S> *nodeArr, int start,
                                       int end) {
    if (!nodeArr) {
        throw MemError();
    }
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    T key = nodeArr[mid].key_m;
    S value = nodeArr[mid].value_m;
    auto aNode = new AVLNode<T, S>(key, value);
    aNode->left_m = createTreeFromSortedArr(nodeArr, start, mid - 1);
    aNode->right_m = createTreeFromSortedArr(nodeArr, mid + 1, end);
    aNode->height_m = std::max(height(aNode->left_m),
                               height(aNode->right_m)) + 1;
    aNode->rank_m = 1 + rank(aNode->left_m) + rank(aNode->right_m);
    aNode->leftSum = aNode->left_m != nullptr ? aNode->left_m->key_m +
                                                aNode->left_m->leftSum +
                                                aNode->left_m->rightSum : 0;
    aNode->rightSum = aNode->right_m != nullptr ? aNode->right_m->key_m +
                                                  aNode->right_m->rightSum +
                                                  aNode->right_m->leftSum : 0;
    return aNode;
}


template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::getMin(AVLNode<T, S> *node) {
    AVLNode<T, S> *current = node;

    while (current->left_m != nullptr)
        current = current->left_m;

    return current;
}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::deleteNode(AVLNode<T, S> *root, const T &keyToDelete) {

    if (root == nullptr) {
        return root;
    }

    if (keyToDelete < root->key_m) {
        root->left_m = deleteNode(root->left_m, keyToDelete);
    } else if (keyToDelete > root->key_m) {
        root->right_m = deleteNode(root->right_m, keyToDelete);
    }

        // key is equal
    else {
        if ((root->left_m == nullptr) ||
            (root->right_m == nullptr)) {
            AVLNode<T, S> *temp = root->left_m ?
                                  root->left_m :
                                  root->right_m;

            //no child
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else { //one child
                root->key_m = temp->key_m;
                root->value_m = temp->value_m;
                root->left_m = temp->left_m;
                root->right_m = temp->right_m;
            }

            delete (temp);
        } else {
            //two children
            AVLNode<T, S> *temp = getMin(root->right_m);

            root->key_m = temp->key_m;
            root->value_m = temp->value_m;

            root->right_m = deleteNode(root->right_m,
                                       temp->key_m);
        }

    }

    if (root == nullptr) {
        return root;
    }

    root->height_m = 1 + std::max(height(root->left_m),
                                  height(root->right_m));
    root->rank_m = 1 + rank(root->left_m) + rank(root->right_m);
    root->leftSum = root->left_m != nullptr ? root->left_m->leftSum +
                                              root->left_m->rightSum +
                                              root->left_m->key_m : 0;
    root->rightSum = root->right_m != nullptr ?root->right_m->leftSum +
                                               root->right_m->rightSum +
                                               root->right_m->key_m : 0;

    int balance = getBalance(root);

    //RR
    if (balance > 1 &&
        getBalance(root->left_m) >= 0)
        return rollRR(root);

    //LR
    if (balance > 1 &&
        getBalance(root->left_m) < 0) {
        root->left_m = rollLL(root->left_m);
        return rollRR(root);
    }

    //LL
    if (balance < -1 &&
        getBalance(root->right_m) <= 0)
        return rollLL(root);

    //RL
    if (balance < -1 &&
        getBalance(root->right_m) > 0) {
        root->right_m = rollRR(root->right_m);
        return rollLL(root);
    }

    return root;

}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::insertNode(AVLNode<T, S> *root, const T &key, const S &value) {

    if (root == nullptr)
        return new AVLNode<T, S>(key, value);

    if (key < root->key_m) {
        root->left_m = insertNode(root->left_m, key, value);
    } else if (key > root->key_m) {
        root->right_m = insertNode(root->right_m, key, value);
    } else // is equal
        throw KeyAlreadyExists<T>(key);


    root->height_m = 1 + std::max(height(root->left_m),
                                  height(root->right_m));

    root->rank_m = 1 + rank(root->left_m) + rank(root->right_m);

    root->leftSum = root->left_m != nullptr ? root->left_m->leftSum + root->left_m->rightSum + root->left_m->key_m : 0;
    root->rightSum = root->right_m != nullptr ? root->right_m->rightSum + root->right_m->leftSum + root->right_m->key_m : 0;


    int balance = getBalance(root);

    // LL
    if (balance > 1 && key < root->left_m->key_m)
        return rollRR(root);

    // RR
    if (balance < -1 && key > root->right_m->key_m)
        return rollLL(root);

    // LR
    if (balance > 1 && key > root->left_m->key_m) {
        root->left_m = rollLL(root->left_m);
        return rollRR(root);
    }

    // RL
    if (balance < -1 && key < root->right_m->key_m) {
        root->right_m = rollRR(root->right_m);
        return rollLL(root);
    }

    return root;
}

template<class T, class S>
AVLTree<T, S>::AVLTree(const AVLTree<T, S> &aTree) {
    try {
        T *keysArr = new T[aTree.countNodesInTree()];
        S *valuesArr = new S[aTree.countNodesInTree()];
        auto nodeArr = new AVLNode<T, S>[aTree.countNodesInTree()];
        aTree.printTree(keysArr, valuesArr);
        for (int i = 0; i < aTree.countNodesInTree(); i++) {
            nodeArr[i].key_m = keysArr[i];
            nodeArr[i].value_m = valuesArr[i];
        }
        delete[] keysArr;
        delete[] valuesArr;
        root = createTreeFromSortedArr(nodeArr, 0,
                                       aTree.countNodesInTree() - 1);
        delete[] nodeArr;
    }
    catch (std::bad_alloc &e) {
        throw MemError();
    }
}

template<class T, class S>
AVLTree<T, S> &AVLTree<T, S>::operator=(const AVLTree<T, S> &aTree) {
    AVLNode<T, S> *temp = root;
    if (this == &aTree) {
        return *this;
    }
    try {
        T *keysArr = new T[aTree.countNodesInTree()];
        S *valuesArr = new S[aTree.countNodesInTree()];
        auto nodeArr = new AVLNode<T, S>[aTree.countNodesInTree()];
        aTree.printTree(keysArr, valuesArr);
        for (int i = 0; i < aTree.countNodesInTree(); i++) {
            nodeArr[i].key_m = keysArr[i];
            nodeArr[i].value_m = valuesArr[i];
        }
        delete[] keysArr;
        delete[] valuesArr;
        root = createTreeFromSortedArr(nodeArr, 0,
                                       aTree.countNodesInTree() - 1);
        delete[] nodeArr;
    }
    catch (std::bad_alloc &e) {
        throw MemError();
    }
    delete temp;
    return *this;
}

template<class T, class S>
int AVLTree<T, S>::getBalance(AVLNode<T, S> *aNode) {
    if (aNode == nullptr)
        return 0;
    return height(aNode->left_m) -
           height(aNode->right_m);
}


template<class T, class S>
const AVLNode<T, S> *AVLTree<T, S>::searchIndex(const int &index) const {
    return searchIndex(index, root);
}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::searchIndex(const int &index, AVLNode<T, S> *root) const {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->left_m == nullptr) {
        if (index == 1) {
            return root;
        }
        if (index == 2) {
            return root->right_m;
        }
        return nullptr;
    }
    int kMinusOne = index - 1;
    if (root->left_m->rank_m == kMinusOne) {
        return root;
    }
    if (root->left_m->rank_m > kMinusOne) {
        return searchIndex(index, root->left_m);
    }
    if (root->left_m->rank_m < kMinusOne) {
        return searchIndex(kMinusOne - root->left_m->rank_m, root->right_m);
    }
    return nullptr;
}

template<class T, class S>
void AVLTree<T, S>::printInOrder() {
    printInOrder(root);
}

template<class T, class S>
void AVLTree<T, S>::printRanksInOrder() {
    printRanksInOrder(root);
}

template<class T, class S>
void AVLTree<T, S>::printSumsInOrder() {
    printSumsInOrder(root);
}

template<class T, class S>
void AVLTree<T, S>::printInOrder(AVLNode<T, S> *root) {
    if (root == nullptr)
        return;

    printInOrder(root->left_m);

    cout << root->key_m << " ";

    printInOrder(root->right_m);
}

template<class T, class S>
void AVLTree<T, S>::printRanksInOrder(AVLNode<T, S> *root) {
    if (root == nullptr)
        return;

    printRanksInOrder(root->left_m);

    cout << root->rank_m << " ";

    printRanksInOrder(root->right_m);
}

template<class T, class S>
void AVLTree<T, S>::printSumsInOrder(AVLNode<T, S> *root) {
    if (root == nullptr)
        return;

    printSumsInOrder(root->left_m);

    cout << root->leftSum << " ";
    cout << root->rightSum << " ";

    printSumsInOrder(root->right_m);
}

template<class T, class S>
const T
AVLTree<T, S>::getSumOfLargerKeys(const T &key, const AVLNode<T, S> *root,
                                  const T &currSum) const {
    if (root == nullptr)
        throw NoSuchKey();
    T newSum = currSum + root->rightSum;
    if (root->key_m == key) {
        return newSum;
    }
    if (key > root->key_m) {
        return getSumOfLargerKeys(key, root->right_m, currSum);
    }
    if (key < root->key_m) {
        return getSumOfLargerKeys(key, root->left_m, newSum + root->key_m);
    }
    throw NoSuchKey();
}

template<class T, class S>
const T AVLTree<T, S>::getSumOfLargerKeys(const T &key) const {
    return getSumOfLargerKeys(key, root, T(0));
}


template<typename T, typename S>
void
mergeSortedArrays(T *arr1Keys, S *arr1Values, T *arr2Keys, S *arr2Values,
                  int arr1Size, int arr2Size, int *mergedSize, AVLNode<T,S>* mergedArr) {
    if (!arr1Keys || !arr2Keys || !arr1Values || !arr2Values || !mergedSize) {
        throw MemError();
    }
    int i = 0, j = 0, k = 0;
    while (i < arr1Size && j < arr2Size) {
        if (arr1Keys[i] <= arr2Keys[j]) {
            mergedArr[k].key_m = arr1Keys[i];
            mergedArr[k].value_m = arr1Values[i];
            if (arr1Keys[i] == arr2Keys[j]) {
                throw KeyAlreadyExists<T>(arr1Keys[i]);
            }
            i++;
        } else {
            mergedArr[k].key_m = arr2Keys[j];
            mergedArr[k].value_m = arr2Values[j];
            j++;
        }
        k++;
    }

    while (i < arr1Size) {
        mergedArr[k].key_m = arr1Keys[i];
        mergedArr[k].value_m = arr1Values[i];
        i++;
        k++;
    }

    while (j < arr2Size) {
        mergedArr[k].key_m = arr2Keys[j];
        mergedArr[k].value_m = arr2Values[j];
        j++;
        k++;
    }
    *mergedSize = k;
}



#endif //PROJECT_AVLTREE_H
