//
// Created by Aviv on 5/30/2022.
//

#include "EmployeeManager.h"
#include <iostream>

// TODO: a. access all the employees in the list.
//       b. put them all in the right_son company.

statusType EmployeeManager::addEmployee(int empid, int compid, int grade) {
    if (empid <= 0 or compid <= 0 or compid > num_of_comps) {
        return INVALID_INPUT1;
    }
    bool exists = all_employees_hash->isExist(empid);
    if (exists) {
        return FAILURE1;
    }
    Company *toinsert = compUF->Find(compid);
    Employee *newemp;
    try {
        newemp = new Employee(empid, grade, toinsert);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR1;
    }
    toinsert->addEmployee(newemp);
    all_employees_hash->Insert(newemp);
    sum_of_grades_zero_sal += grade;
    num_of_zero_salary++;
    return SUCCESS1;
}

statusType EmployeeManager::removeEmployee(int empid) {


    if (empid <= 0) {
        return INVALID_INPUT1;
    }
    bool exists = all_employees_hash->isExist(empid);
    if (!exists) {
        return FAILURE1;
    }
    Employee *toremove = all_employees_hash->GetEmp(empid);
    Company *removefrom = compUF->Find(toremove->getCompanyId());
    if (toremove->getSalary() > 0) {
        employeeCondition_Salary_Id key(toremove->getSalary(), empid);
        non_zero_sal_avl->remove(key);
    } else {
        sum_of_grades_zero_sal -= toremove->getGrade();
        num_of_zero_salary -= 1;
    }
    all_employees_hash->Remove(toremove);
    removefrom->removeEmployee(toremove);

    return SUCCESS1;
}

statusType EmployeeManager::acquireCompany(int aquireId, int tarId, double factor) {
    if (aquireId <= 0 or aquireId > num_of_comps or tarId <= 0 or tarId > num_of_comps or factor < 0.0) {
        return INVALID_INPUT1;
    }
    Company *aqcomp = compUF->Find(aquireId);
    Company *tarcomp = compUF->Find(tarId);
    if (aqcomp == tarcomp) {
        return INVALID_INPUT1;
    }
    double toadd= compUF->FindValue(tarcomp->getId());

    compUF->Union(aquireId,tarId,factor);

    aqcomp->GetEmpHash()->unite(tarcomp->GetEmpHash());
    aqcomp->getEmployees_bySalary()->merge(tarcomp->getEmployees_bySalary());
    aqcomp->sum_of_0_grades += tarcomp->sum_of_0_grades;
    aqcomp->num_of_0_sal += tarcomp->num_of_0_sal;
    return SUCCESS1;

}

statusType EmployeeManager::employeeSalaryIncrease(int EmployeeID, int SalaryIncrease) {
    if (EmployeeID <= 0 or SalaryIncrease <= 0) {
        return INVALID_INPUT1;
    }

    if (!all_employees_hash->isExist(EmployeeID)) {
        return FAILURE1;
    }
    Employee *emp = all_employees_hash->GetEmp(EmployeeID);
    employeeCondition_Salary_Id oldkey( emp->getSalary(),EmployeeID);
    if (emp->getSalary() > 0) {
        non_zero_sal_avl->remove(oldkey);

    } else {
        num_of_zero_salary--;
        sum_of_grades_zero_sal -= emp->getGrade();
    }
    emp->getCompany()->removeEmployee(emp);
    emp->increaseSalary(SalaryIncrease);
    employeeCondition_Salary_Id newkey( emp->getSalary(),EmployeeID);
    non_zero_sal_avl->insert(newkey, emp);
    emp->getCompany()->addEmployee(emp);
    return SUCCESS1;
}

statusType EmployeeManager::promoteEmployee(int EmployeeID, int BumpGrade) {
    if (EmployeeID <= 0) {
        return INVALID_INPUT1;
    }

    if (!all_employees_hash->isExist(EmployeeID)) {
        return FAILURE1;
    }
    if (BumpGrade <= 0) {
        return SUCCESS1;
    }

    Employee *emp = all_employees_hash->GetEmp(EmployeeID);
    emp->promote(BumpGrade);
    employeeCondition_Salary_Id empkey(emp->getSalary(), emp->getId());
    if (emp->getSalary() > 0) {
        non_zero_sal_avl->addgrades(empkey, BumpGrade);
        emp->getCompany()->getEmployees_bySalary()->addgrades(empkey, BumpGrade);
    } else {
        sum_of_grades_zero_sal += BumpGrade;
        emp->getCompany()->sum_of_0_grades += BumpGrade;
    }
    return SUCCESS1;
}

statusType EmployeeManager::sumOfBumpGradeBetweenTopWorkersByGroup(int CompanyID, int m) {
    if (CompanyID > num_of_comps or CompanyID < 0 or m <= 0) {
        return INVALID_INPUT1;
    }

    long double print;
    if (CompanyID > 0) {
        Company *comp = compUF->Find(CompanyID);
        if (!comp->getEmployees_bySalary()->root or comp->getEmployees_bySalary()->root->rank < m) {
            return FAILURE1;
        }
        print = comp->getEmployees_bySalary()->GetGradesByRank(m);
    } else {
        if (non_zero_sal_avl->root->rank < m) {
            return FAILURE1;
        }
        print = non_zero_sal_avl->GetGradesByRank(m);
    }


    printf("SumOfBumpGradeBetweenTopWorkersByGroup: ");
    std::cout<<print<<"\n";
    return SUCCESS1;
}

statusType EmployeeManager::averageBumpGradeBetweenSalaryByGroup(int CompanyID, int lowerSalary, int higherSalary) {
    if (higherSalary < 0 or lowerSalary < 0 or lowerSalary > higherSalary or CompanyID < 0 or
        CompanyID > num_of_comps) {
        return INVALID_INPUT1;
    }
    long double print;
    double amountofemployees=0;
    long double amoutofgrades=0;
    if (CompanyID == 0) {
        BSTNode<employeeCondition_Salary_Id> *first = non_zero_sal_avl->GetLow(lowerSalary);
        BSTNode<employeeCondition_Salary_Id> *last = non_zero_sal_avl->GetHigh(higherSalary);

        if (!first or !last) {
            if (first and !last) {
                throw std::bad_cast();
            }
            if (last and !first) {
                throw std::bad_cast();
            }
            if (num_of_zero_salary == 0) {
                return FAILURE1;
            } else {
                print = sum_of_grades_zero_sal / num_of_zero_salary;
                printf("AverageBumpGradeBetweenSalaryByGroup: ");
                std::cout<<print*1.0<<"\n";
                return SUCCESS1;
            }
        }

        Employee *firstemp = first->data;
        Employee *lastemp = last->data;
        employeeCondition_Salary_Id one(first->data->getSalary(), first->data->getId());
        employeeCondition_Salary_Id two(last->data->getSalary(), last->data->getId());
        amountofemployees += non_zero_sal_avl->getRankByKey(two);
        amountofemployees -= non_zero_sal_avl->getRankByKey(one);
        amountofemployees++;
        amoutofgrades += non_zero_sal_avl->getGradesByKey(two);
        amoutofgrades -= non_zero_sal_avl->getGradesByKey(one);
        amoutofgrades += first->data->getGrade();
        if (lowerSalary == 0) {
            amoutofgrades += sum_of_grades_zero_sal;
            amountofemployees += num_of_zero_salary;
        }
        print = amoutofgrades / amountofemployees;
    }
    else
    {
        Company* comp= compUF->Find(CompanyID);
        BSTNode<employeeCondition_Salary_Id> *first = comp->getEmployees_bySalary()->GetLow(lowerSalary);
        BSTNode<employeeCondition_Salary_Id> *last = comp->getEmployees_bySalary()->GetHigh(higherSalary);

        if (!first or !last) {
            if (first and !last) {
                throw std::bad_cast();
            }
            if (last and !first) {
                throw std::bad_cast();
            }
            if (comp->num_of_0_sal == 0) {
                return FAILURE1;
            } else {
                print = comp->sum_of_0_grades / comp->num_of_0_sal;
                printf("AverageBumpGradeBetweenSalaryByGroup: ");
                std::cout<<print*1.0<<"\n";
                return SUCCESS1;
            }

        }

        Employee *firstemp = first->data;
        Employee *lastemp = last->data;
        employeeCondition_Salary_Id one(first->data->getSalary(), first->data->getId());
        employeeCondition_Salary_Id two(last->data->getSalary(), last->data->getId());
        amountofemployees += comp->getEmployees_bySalary()->getRankByKey(two);
        amountofemployees -= comp->getEmployees_bySalary()->getRankByKey(one);
        amountofemployees++;
        amoutofgrades += comp->getEmployees_bySalary()->getGradesByKey(two);
        amoutofgrades -= comp->getEmployees_bySalary()->getGradesByKey(one);
        amoutofgrades += first->data->getGrade();

        if (lowerSalary == 0) {
            amoutofgrades += comp->sum_of_0_grades;
            amountofemployees += comp->num_of_0_sal;
        }
        print = amoutofgrades / amountofemployees;

    }

    printf("AverageBumpGradeBetweenSalaryByGroup: ");
    std::cout<<print*1.0<<"\n";
    return SUCCESS1;

}

statusType EmployeeManager::companyValue(int CompanyID) {
    if(CompanyID<=0 or CompanyID>num_of_comps)
    {
        return INVALID_INPUT1;
    }
    if(CompanyID == 11){
        int s =6;
    }
    double val=compUF->FindValue(CompanyID);
    printf("CompanyValue: %.1f\n", val);
    return SUCCESS1;
}

EmployeeManager::~EmployeeManager() {
    delete compUF;
    delete all_employees_hash;
    delete non_zero_sal_avl;

}
