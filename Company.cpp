//
// Created by OR on 24/04/2022.
//


#include "RankTree.h"


Company::~Company()
{

    delete emphash;
    delete employees ;

}

int Company::getId()const
{
    return id;
}

int Company::getValue()const
{
    return value;
}

int Company::getNumOfEmployees()const
{
    return numOfEmployees;
}

RankTree<employeeCondition_Salary_Id>* Company::getEmployees_bySalary() const
{
    return employees;
}


void Company::setValue(int newValue)
{
    value=newValue;
}

void Company::IncreaseEmployees(int incAmount)
{
    numOfEmployees+=incAmount;
}

void Company::addEmployee( Employee* const toAdd)
{
    toAdd->changeCompany(this);
    emphash->Insert(toAdd);
    if(toAdd->getSalary()>0) {
        const employeeCondition_Salary_Id key2(toAdd->getSalary(), toAdd->getId());
        employees->insert(key2, toAdd);
    }
    else
    {
        num_of_0_sal++;
        sum_of_0_grades+=toAdd->getGrade();
    }
    numOfEmployees++;
    toAdd->changeCompany(this);
}

void Company::removeEmployee(Employee* toRemove)
{
    numOfEmployees--;
    if(toRemove->getSalary()>0) {
        const employeeCondition_Salary_Id key2(toRemove->getSalary(), toRemove->getId());
        employees->remove(key2);
    }
    else
    {
        num_of_0_sal--;
        sum_of_0_grades-=toRemove->getGrade();
    }
    emphash->Remove(toRemove);
}


double Company::getValueInc() const {
    return value_inc;
}

void Company::changeValInc(double x) {
    value_inc+=x;
}

MyHash *Company::GetEmpHash() const {
    return emphash;
}

void Company::AddToTree(Employee *emp) {
    if(emp->getSalary()>0) {
        const employeeCondition_Salary_Id key2(emp->getSalary(), emp->getId());
        employees->insert(key2, emp);
    }
}

void Company::Merge(Company* other)
{

}



/*
Employee* Company::getHighestSalaryInCompany() const {

    if(employees_by_id->size()==0) {
        return nullptr;
    }
    //return employees->getBiggest().data;
    return highestSalaryInCompany;
}

Company::Company(int id1, int value1, int numOfEmployees1, RankTree<employeeCondition_Salary_Id, Employee *>* employees1,
                 Employee *highestSalaryInCompany1, RankTree<employeeCondition_Id, Employee *>* employees_by_id1)
        :id(id1),value(value1),employees(employees1),numOfEmployees(numOfEmployees1),highestSalaryInCompany(highestSalaryInCompany1),employees_by_id(employees_by_id1){

}

void Company::changeCompany(BSTNode<employeeCondition_Salary_Id>*node) {
    if(!node)
    {
        return;
    }
    node->data->changeCompany(this);
    changeCompany(node->right_son);
    changeCompany(node->left_son);

}

void Company::getarrmax(int *emp, BSTNode<employeeCondition_Salary_Id> *node, int *counter) const {


    if(node== nullptr)
    {
        return ;
    }
    *counter=*counter+1;
    getarrmax(emp, node->right_son, counter);
    emp[*counter]=node->data->getId();
    getarrmax(emp, node->left_son, counter);
}



void Company::fromKeyToKeycondcomp2(BSTNode<employeeCondition_Id> root, BSTNode<employeeCondition_Id> *start,
                                    BSTNode<employeeCondition_Id> *end, int *counter, int minSal,
                                    int MinGrade) const{
    if (start==NULL or start->key>end->key)
    {
        return ;
    }
    if(start->data->getSalary()>minSal and start->data->getGrade()>MinGrade) {
        *counter = *counter + 1;
    }
    fromKeyToKeycondcomp2(root, start->left_son, end, counter, minSal, MinGrade);
    if (start->key==end->key)
    {
        return ;
    }
    fromKeyToKeycondcomp2(root, start->right_son, end, counter, minSal, MinGrade);
    if(start->key!=root.key)
    {
        fromKeyToKeycondcomp2(root,start->parent,end,counter,minSal,MinGrade);
    }

}


int Company::fromKeyToKeycondcomp(employeeCondition_Id start, employeeCondition_Id end, int minSal, int MinGrade)const {

    int counter = 0;
    BSTNode<employeeCondition_Id> first = employees_by_id->findMin(employees_by_id->getRoot(), start);
    BSTNode<employeeCondition_Id> last = employees_by_id->findMax(employees_by_id->getRoot(), start);;
    fromKeyToKeycondcomp2(*employees_by_id->getRoot(),&first,&last,&counter,minSal,MinGrade);
    return counter;
}
*/


