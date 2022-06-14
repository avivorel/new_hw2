//
// Created by OR on 24/04/2022.
//

#include "RankTree.h"

Employee::~Employee(){}

int Employee::getId()const{
    return id;
}

int Employee::getSalary()const{
    return salary;
}

void Employee::increaseSalary(int salaryInc){

    salary+=salaryInc;
   /* if(salary==salaryInc) {
        company->AddToTree(this);
    }*/

}

int Employee::getCompanyId()const{
    return company->getId();
}

Company* Employee::getCompany()const{
    return company;
}

int Employee::getGrade()const{
    return grade;
}

void Employee::promote(int a){
    grade+=a;
}

void Employee::changeCompany(Company* comp)
{
    company=comp;
}

