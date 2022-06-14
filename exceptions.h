//
// Created by Aviv on 5/30/2022.
//

#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <exception>

class ALLOCATION_ERROR public std::exception{};
class INVALID_INPUT public std::exception{};
class SUCCESS public std::exception{};
class FAILURE public std::exception{};


#include <exception>

template <typename T>
class KeyAlreadyExists : public std::exception{

    T key;
public:
    KeyAlreadyExists(const T& key = T()) : key(key) {}
    virtual const char* what() const throw(){
        return "Key already exists";
    }

    const T& whatKey() const{
        return key;
    }

};

class NoSuchKey : public  std::exception{
public:
    virtual const char* what() const throw(){
        return "No such key";
    }
};

class MemError : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Memory error";
    }
};

class IllegalIndex : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Illegal Index";
    }
};

class UnionFailed : public std::exception{
public:
    virtual const char* what() const throw(){
        return "KeysAreInTheSameGroup";
    }
};


class IllegalParameters : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Illegal Parameters";
    }
};



#endif //PROJECT_EXCEPTIONS_H
