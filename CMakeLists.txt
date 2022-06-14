cmake_minimum_required(VERSION 3.16)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp UF.h UF.cpp EmployeeManager.cpp EmployeeManager.h Company.cpp  HashTable.h DList.h  Employee.cpp  exceptions.h  AVLTree.h UnionFind.h Array.h library2.h library2.cpp)
