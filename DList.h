//
// Created by Aviv on 5/30/2022.
//

#ifndef PROJECT_DLIST_H
#define PROJECT_DLIST_H


template<class T>
class DList;

template<class T>
class Node {
    friend DList<T>;
    Node *next;
    Node *previous;
    void deleteNode()
    {
        this->previous->next = this->next;
        if (this->next != nullptr) {
            this->next->previous = this->previous;
        }
        delete this;
    }
public:
    T node_data;
};

template<class T>
class DList {
    friend Node<T>;
    Node<T> *head;

public:
    DList() : head(new(Node<T>)) {
        head->next = nullptr;
        head->previous = nullptr;
    }

    DList(const DList& to_copy) = delete;

    ~DList() {
        while (head->next != nullptr) {
            head->next->deleteNode();
        }
        delete head;
    }


    DList& operator= (const DList& list_to_copy)
    {
        if(this == &list_to_copy){
            return *this;
        }
        Node<T>* new_lists_head  = new Node<T>;
        new_lists_head->next = nullptr;
        new_lists_head->previous = nullptr;
        const Node<T>* curr = list_to_copy.head->next;
        Node<T>* last_one = new_lists_head; // was prev
        while(curr != nullptr) {
            Node<T> *next = new (std::nothrow) Node<T>;
            if(next == nullptr){
                while(new_lists_head->next != nullptr) {
                    deleteNode(new_lists_head->next);
                }
                delete new_lists_head;
                throw std::bad_alloc();
            }
            next->node_data = curr->node_data;
            next->next = nullptr;
            next->previous = last_one;
            last_one->next = next;
            curr = curr->next;
            last_one = next;
        }
        while(this->head->next != nullptr) {
            deleteNode(this->head->next);
        }
        delete this->head;
        this->head = new_lists_head;
        return *this;
    }

    Node<T>* insertFirst(const T& to_insert_first)
    {
        Node<T>* new_node = new (Node<T>);
        new_node->node_data = to_insert_first;
        new_node->next = head->next;
        new_node->previous = head;
        if(head->next != nullptr){
            head->next->previous = new_node;
        }
        head->next = new_node;
        return new_node;
    }

    void deleteNode(Node<T>* node_to_delete)
    {
        if (node_to_delete == nullptr){
            return;
        }
        node_to_delete->deleteNode();
    }

    /*
     * iterator made to iterate through the node_data in the list.
     */
    class iterator{
        Node<T>* current;
        friend DList;
        explicit iterator(Node<T>* init) : current(init) {}
    public:
        T& getNodeData() const{
            return current->node_data;
        }

        Node<T>* operator* ()
        {
            return current;
        }
        const iterator& operator ++ ()
        {
            current = current->next;
            return *this;
        }
        iterator operator++ (int)
        {
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        bool operator == (const iterator& iter) const
        {
            return (iter.current == current);
        }
        bool operator != (const iterator& iter) const
        {
            return !(iter == *this);
        }

    };

    iterator begin()
    {
        return iterator(head->next);
    }
    iterator end()
    {
        return iterator(nullptr);
    }

    class constIter{
        const Node<T>* curr;
        friend DList;
        explicit constIter(const Node<T>* init) : curr(init) {}
    public:
        const T& getNodeData() const{
            return curr->node_data;
        }

        const Node<T>* operator* () const
        {
            return curr;
        }
        constIter& operator ++ ()
        {
            curr = curr->next;
            return *this;
        }
        constIter operator++ (int)
        {
            constIter tmp = *this;
            curr = curr->next;
            return tmp;
        }

        bool operator == (const constIter& iter) const
        {
            return (iter.curr == curr);
        }
        bool operator != (const constIter& iter) const
        {
            return !(iter == *this);
        }

    };

    constIter constantIteratorBegin() const
    {
        return constIter(head->next);
    }
    constIter constantIteratorEnd() const
    {
        return constIter(nullptr);
    }

};

#endif //PROJECT_DLIST_H
