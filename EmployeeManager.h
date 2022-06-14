//
// Created by Aviv on 5/30/2022.
//

#ifndef PROJECT_EMPLOYEEMANAGER_H
#define PROJECT_EMPLOYEEMANAGER_H

#include "UF.h"
#include "RankTree.h"
typedef enum {
    SUCCESS1 = 0,
    FAILURE1 = -1,
    ALLOCATION_ERROR1 = -2,
    INVALID_INPUT1 = -3
} statusType;


class EmployeeManager {
private:
    int num_of_zero_salary;
    long double sum_of_grades_zero_sal;
    RankTree<employeeCondition_Salary_Id>* non_zero_sal_avl;
    MyHash* all_employees_hash;
    unionFind* compUF;
    int num_of_comps;
public:
    EmployeeManager(int k):num_of_zero_salary(0),sum_of_grades_zero_sal(0),num_of_comps(k){
        all_employees_hash=new MyHash();
        compUF=new unionFind (k);
        non_zero_sal_avl=new RankTree<employeeCondition_Salary_Id>();
    }

    statusType addEmployee(int empid, int compid, int grade);

    statusType  removeEmployee(int empid);

    statusType acquireCompany(int aquireId, int tarId, double Factor);

    statusType employeeSalaryIncrease(int EmployeeID, int SalaryIncrease);

    statusType promoteEmployee(int EmployeeID, int BumpGrade);

    statusType sumOfBumpGradeBetweenTopWorkersByGroup (int CompanyID, int m);

    statusType averageBumpGradeBetweenSalaryByGroup (int CompanyID, int lowerSalary, int higherSalary);

    statusType companyValue(int CompanyID);

    ~EmployeeManager();
};


#endif //PROJECT_EMPLOYEEMANAGER_H
