//
// Created by User on 02/06/2022.
//

#ifndef PROJECT_BTSNODE_H
#define PROJECT_BTSNODE_H

class Company;


class Employee {
private:
    int id;
    int salary;
    int grade;
    Company *company;


public:
    ~Employee();

    explicit Employee(int id1, int salary1, int grade1, Company *company1) : id(id1), salary(salary1), grade(grade1),
                                                                             company(company1) {};

    explicit Employee(int id1, int grade1, Company *company1) : id(id1), salary(0), grade(grade1),
                                                                company(company1) {};

    int getId() const;

    int getSalary() const;

    void increaseSalary(int salaryInc);

    int getCompanyId() const;

    Company *getCompany() const;

    int getGrade() const;

    void promote(int a);

    void changeCompany(Company *comp);


};

// How it works? First, it judges by the biggest salary, in case they're the same, by ID.
class employeeCondition_Salary_Id {

    int salary;
    int id;


public:
    explicit employeeCondition_Salary_Id() : salary(0), id(0) {};

    explicit employeeCondition_Salary_Id(int sal, int i) : salary(sal), id(i) {}

    int getSalary() const {
        return salary;
    }

    int getId() const {
        return id;
    }


    bool operator==(const employeeCondition_Salary_Id &other) const {
        return other.salary == salary && other.id == id;
    }

    bool operator!=(const employeeCondition_Salary_Id &other_class) const {
        return !((*this) == other_class);
    }

    friend bool
    operator>(const employeeCondition_Salary_Id &employee_one, const employeeCondition_Salary_Id &employee_second) {
        if (employee_one.getSalary() > employee_second.getSalary()) {
            return true;
        } else if (employee_one.getSalary() == employee_second.getSalary()) {
            if (employee_one.getId() > employee_second.getId()) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    friend bool
    operator<(const employeeCondition_Salary_Id &employee_one, const employeeCondition_Salary_Id &employee_second) {
        if (employee_one.getSalary() < employee_second.getSalary()) {
            return true;
        } else if (employee_one.getSalary() == employee_second.getSalary()) {
            if (employee_one.getId() < employee_second.getId()) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }// no = because cant have the same id




};


template<class S>
class Tuple {
    Employee *val;
    S key;


public:
    S GetKey() const;

    Employee *GetValue() const;


    Tuple();


    Tuple(S k, Employee *v) : key(k), val(v) {};


};

template<class S>
S Tuple<S>::GetKey() const {
    return key;
}

template<class S>
Employee *Tuple<S>::GetValue() const {
    return val;
}

template<class S>
Tuple<S>::Tuple() {

}


template<class S>
class BSTNode//---------------BSTNode-----------------------------
{
public:
    S key;
    Employee *data;
    BSTNode *left_son;
    BSTNode *right_son;
    BSTNode *parent;
    int height;
    int rank;
    long double sum_grades;


    explicit BSTNode(S key, Employee *data);

    explicit BSTNode(S key, Employee *data, BSTNode<S> *parent);

    BSTNode() = default;

    BSTNode(const BSTNode<S> &node);

    BSTNode *roll();


    BSTNode &operator=(const BSTNode &node);

    ~BSTNode() = default;

/*

    //todo: what is sum doing?
    int getSize() {
        if (this == nullptr) {
            return 0;
        }
        if (this->left_son == nullptr && this->right_son == nullptr) {
            return 1;
        } else if (this->left_son == nullptr) {
            return 1+ this->right_son->size;
        } else if (this->right_son == nullptr) {
            return 1+ this->left_son->size;
        } else {
            return 1+ this->left_son->size+ this->right_son->size;
        }
    }
*/

// TODO: chnage 2 functs
    long double getSumGrades() {
        if (this == nullptr) {
            return 0;
        }
        if (this->left_son == nullptr && this->right_son == nullptr) {
            return (data->getGrade());
        } else if (this->left_son == nullptr) {
            return (data->getGrade() + this->right_son->sum_grades);
        } else if (this->right_son == nullptr) {
            return (data->getGrade() + this->left_son->sum_grades);
        } else {
            return (data->getGrade() + this->left_son->sum_grades + this->right_son->sum_grades);
        }
    }


    int getRank() {
        if (this == nullptr) {
            return 0;
        }
        if (this->left_son == nullptr && this->right_son == nullptr) {
            return 1;
        } else if (this->left_son == nullptr) {
            return 1 + this->right_son->rank;
        } else if (this->right_son == nullptr) {
            return 1 + this->left_son->rank;
        } else {
            return 1 + this->left_son->rank + this->right_son->rank;
        }
        return rank;
    }


    /*  int getHeight() {
          if (this == nullptr) {
              return 0;
          }
          int left_height=0;
          if(left_son!= nullptr)
          {
          left_height = left_son->height;
         }
          int right_height=0;
          if(left_son!= nullptr)
          {
              right_height = right_son->height;
          }
          return (left_height > right_height ? left_height : right_height) + 1;
          //return height;
      }*/

    int getHeight() {
        if (this == nullptr) {
            return 0;
        }
        if (this->left_son == nullptr && this->right_son == nullptr) {
            return 1;
        } else if (this->left_son == nullptr) {
            return 1 + this->right_son->height;
        } else if (this->right_son == nullptr) {
            return 1 + this->left_son->height;
        } else {
            return 1 + std::max(this->left_son->height,
                                this->right_son->height);
        }
    }

    void calcHeight() {


        int left_height = getHeight(left_son);
        int right_height = getHeight(right_son);
        height = (left_height > right_height ? left_height : right_height) + 1;

    }

    int returnBalanceFactor() const {
        return (getHeight(left_son) - getHeight(right_son));
    }

    void increaseAllNodesInTrack() {
        BSTNode<S> *node = this;
        node->data++;
        while (node != nullptr) {
            node->size++;
            node->sum_grades += node->data->getGrade();
            node = node->parent;
        }
    }


    void addsumgrades(int a) {
        BSTNode<S> *node = this;
        node->data++;
        while (node != nullptr) {
            node->size++;
            node->sum_grades += node->data->getGrade();
            node = node->parent;
        }
    }

    void addsumgradesnew(int a) {
        BSTNode<S> *node = this;

        while (node != nullptr) {
            node->sum_grades += a;
            node = node->parent;
        }
    }

    void decreaseAllNodesInTrack() {
        BSTNode<S> *node = this;
        node->data--;
        while (node != nullptr) {
            node->size--;
            node->sum_grades -= node->data->getGrade();
            node = node->parent;
        }
    }


    int updateRanks(BSTNode<S> *curr) {
        if (curr == nullptr) {
            return 0;
        }
        int left1 = updateRanks(curr->left_son);
        int right1 = updateRanks(curr->right_son);
        curr->rank = left1 + right1 + 1;
    }

    long double updateGrades(BSTNode<S> *curr) {
        if (curr == nullptr) {
            return 0;
        }
        long double left1 = updateGrades(curr->left_son);
        long double right1 = updateGrades(curr->right_son);
        curr->rank = left1 + right1 + data->getGrade();
    }

};//-------------------------------BSTNode END---------------------------

#endif //PROJECT_BTSNODE_H
