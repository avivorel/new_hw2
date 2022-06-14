
#ifndef PROJECT_UNIONFIND_H
#define PROJECT_UNIONFIND_H

#include "Array.h"
#include <cassert>
#include "exceptions.h"
#include "RankTree.h"//for the company


class UnionFind {


    class UnionNode{
    public:
        int union_index;
        UnionNode* union_father;
        int amount_of_children;
        double value_inc;
        UnionNode(const int& union_find_index, UnionNode* UF_parent = nullptr) : union_index(union_find_index), union_father(UF_parent), amount_of_children(0),value_inc(0){}

    };

    //TODO change to **
    Array<UnionNode*> node_array;
    Array<Company*> company_array;
    int amount_of_elements;

public:

    UnionFind(const int& number_of_elements = 0) : amount_of_elements(number_of_elements){
        node_array = Array<UnionNode*>(number_of_elements);
        company_array = Array<Company*>(number_of_elements);

        for(int i = 0; i < number_of_elements; i++){
            node_array[i] = new UnionNode(i, nullptr);
            company_array[i] = new T();
        }
    }

    ~UnionFind(){
        for(int i = 0; i < amount_of_elements; i++){
            if(node_array[i]->union_father == nullptr){
                delete company_array[i];
            }
        }
        for(int i = 0; i < amount_of_elements; i++){
            delete node_array[i];
        }
    }



    Company* find(const int& uf_index){
        if (uf_index > amount_of_elements || uf_index < 0){
            throw IllegalIndex();
        }

        Array<UnionNode*> nodes_needed_to_connect = Array<UnionNode*>(amount_of_elements);
        UnionNode* uf_iter = node_array[uf_index];
        int uf_number_of_children = 0;
        double sum=0;
        while(uf_iter->union_father != nullptr){
            sum+=uf_iter->value_inc;
            uf_iter = uf_iter->union_father;}

        UnionNode* uf_iter2 = node_array[uf_index];
        while(uf_iter2->union_father != nullptr){
            nodes_needed_to_connect[uf_number_of_children] = uf_iter;
            uf_number_of_children++;
            uf_iter2 = uf_iter2->union_father;
            int s=uf_iter2->value_inc;
            uf_iter->value_inc=sum;
            sum=sum-s;

        }

        while(uf_number_of_children > 0){
            nodes_needed_to_connect[uf_number_of_children - 1]->union_father = uf_iter;
            company_array[nodes_needed_to_connect[uf_number_of_children - 1]->union_index] = company_array[uf_iter->union_index];
            uf_number_of_children--;
        }

        return company_array[uf_iter->union_index];
    }



    int unite(const int& index1, const int& index2,double factor){
        UnionNode* root_of_first = node_array[index1];
        UnionNode* root_of_second = node_array[index2];

        while(root_of_first->union_father != nullptr){
            root_of_first = root_of_first->union_father;
        }

        while(root_of_second->union_father != nullptr){
            root_of_second = root_of_second->union_father;
        }

        UnionNode* bigger_root;
        UnionNode* smaller_root;

        if(root_of_second == root_of_first){
            throw UnionFailed();
        }

        if(root_of_first->amount_of_children > root_of_second->amount_of_children){
            bigger_root = root_of_first;
            smaller_root = root_of_second;
            double smaller_val= smaller_root->value_inc;
            double bigger_val=bigger_root->value_inc;
            smaller_root->value_inc-=bigger_val;
            bigger_root->value_inc+=smaller_val*factor;

            smaller_root->union_father = bigger_root;
            bigger_root->amount_of_children += 1 + smaller_root->amount_of_children;
            Company* temp = company_array[smaller_root->union_index];
            company_array[smaller_root->union_index] = company_array[bigger_root->union_index];
            delete temp;
        }
        else{
            bigger_root = root_of_second;
            smaller_root = root_of_first;
            double bigger_val=bigger_root->value_inc;
            smaller_root->value_inc-=bigger_val;
            smaller_root->union_father = bigger_root;
            bigger_root->amount_of_children += 1 + smaller_root->amount_of_children;
            Company* temp = company_array[smaller_root->union_index];
            company_array[smaller_root->union_index] = company_array[bigger_root->union_index];
            delete temp;
        }



        return bigger_root->union_index;
    }
    // TODO understand and add shortcuts
    double FindValue(int index)
    {
        if (index > amount_of_elements || index < 0){
            throw IllegalIndex();
        }

        UnionNode* uf_iter = node_array[index];
        double val= index;
        while(uf_iter->union_father != nullptr){
            val+=uf_iter->value_inc;
            uf_iter = uf_iter->union_father;
        }
        return val;
    }
};




#endif //PROJECT_UNIONFIND_H
