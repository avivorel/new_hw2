#include "library2.h"
#include "EmployeeManager.h"
void *Init(int k)
{
    if(k<=0)
    {
        return nullptr;
    }
    return new EmployeeManager(k);
}
StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Grade)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    statusType status;
    try{
        status= ((EmployeeManager*) DS)->addEmployee(EmployeeID,CompanyID,Grade);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;
}

StatusType RemoveEmployee(void *DS, int employeeID)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    statusType status;
    try{
        status= ((EmployeeManager*) DS)->removeEmployee(employeeID);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType)status;
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    statusType status;
    try{
        status= ((EmployeeManager*) DS)->acquireCompany(companyID1,companyID2,factor);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;
}


StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease)
{
    if(!DS)
    {
        return INVALID_INPUT;
    }
    statusType status;
    try{
        status= ((EmployeeManager*) DS)->employeeSalaryIncrease(employeeID,salaryIncrease);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade)
{

    if(!DS)
    {
        return INVALID_INPUT;
    }
    statusType status;
    try{
        status= ((EmployeeManager*) DS)->promoteEmployee(employeeID,bumpGrade);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;

}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m) {
    if (!DS) {
        return INVALID_INPUT;
    }
    statusType status;
    try {
        status = ((EmployeeManager *) DS)->sumOfBumpGradeBetweenTopWorkersByGroup(companyID, m);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;
}


StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary)
{
    if (!DS) {
        return INVALID_INPUT;
    }
    statusType status;
    try {
        status = ((EmployeeManager *) DS)->averageBumpGradeBetweenSalaryByGroup(companyID, lowerSalary,higherSalary);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;
}

StatusType CompanyValue(void *DS, int companyID)
{
    if (!DS) {
        return INVALID_INPUT;
    }
    statusType status;
    try {
        status = ((EmployeeManager *) DS)->companyValue(companyID);
    }
    catch (const std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    return (StatusType )status;
}

void Quit(void** DS)
{
    if(*DS!= nullptr)
    {
        delete ((EmployeeManager*)*DS);
    }
    *DS= nullptr;
}