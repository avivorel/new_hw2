#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H

#include "exceptions.h"
template <typename T>
class Array {
    T* uf_array;
    int array_size;
public:

    Array(const int& size = 1, const T& defVal = T()){
        array_size = size;
        uf_array = new T[array_size];
        for(int i = 0; i < size; i++){
            uf_array[i] = defVal;
        }
    }


    Array(const Array& array_to_copy){
        array_size = array_to_copy.array_size;
        uf_array = new  T[array_size];
        for(int i =0; i < array_size; i++){
            uf_array[i] = array_to_copy[i];
        }
    }
    ~Array(){
        delete [] uf_array;
    }

    Array& operator=(const Array& array_to_copy){
        if(this == &array_to_copy){
            return *this;
        }
        T* temporary_instance = uf_array;
        uf_array = new T[array_to_copy.array_size];
        delete [] temporary_instance;
        array_size = array_to_copy.array_size;
        for(int i =0; i < array_to_copy.array_size; i++){
            uf_array[i] = array_to_copy.uf_array[i];
        }
        return *this;
    }

    T& operator[](const int& index_to_fetch){
        if(index_to_fetch >= array_size){
            throw IllegalIndex();
        }
        return uf_array[index_to_fetch];
    }

    const T& operator[] (const int& index_to_fetch) const{
        if(index_to_fetch >= array_size){
            throw IllegalIndex();
        }
        return uf_array[index_to_fetch];
    }

    const int& getSize() const{
        return array_size;
    }

};


#endif //PROJECT_ARRAY_H
