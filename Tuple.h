//
// Created by User on 03/06/2022.
//

#ifndef PROJECT_TUPLE_H
#define PROJECT_TUPLE_H

template<class S>
class Tuple {
    Employee* val;
    S key;






public:
    Key GetKey() const;

    Value GetValue() const;


    Tuple() ;


    Tuple(S k, Employee* v) : key(k), val(v) {};



};

template<class S>
S Tuple<S>::GetKey() const {
    return key;
}

template<class Key, class Value>
Value Tuple<Key, Value>::GetValue() const {
    return val;
}

template<class Key, class Value>
Tuple<Key, Value>::Tuple() {

}
#endif //PROJECT_TUPLE_H
