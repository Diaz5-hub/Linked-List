//
//  list.h
//  CS20AP3
//
//  Created by Alexander Diaz on 10/27/20.
//

#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both m_head and m_tail pointers
// and the m_size of the list.  Note that you have to keep the m_head,
// m_tail and m_size consistent with the intended state of the List
// otherwise very bad things happen.
template<typename Item>
class List {
public:

    List();

    List(const List<Item>& other);

    List<Item>& operator=(const List<Item>& other);

    ~List();

    void    print() const;
    bool    empty() const;

    void    push_front(const Item &item);
    void    push_rear(const Item &item);
    void    insert(int index, const Item &item);

    // Note that the user must first ensure the list is not empty
    // prior to calling these functions.
    Item    front() const;
    Item    rear() const;
    Item    get(int index) const;

    int        size() const;
    int        find(const Item &item) const;

    bool    pop_front();
    bool    pop_rear();
    bool    remove(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
    // Forward declare the nodes for our List.
    // Will be implemented along with list's
    // member functions
    class Node;

    // We'll have both m_head and m_tail points for
    // Fast insertion/deletion from both ends.
    Node*    m_head;
    Node*    m_tail;

    // Keep track of number of nodes in the list
    int        m_size;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//        Already implemented, nothing to do here but to use it.
*/
template<typename Item>
struct List<Item>::Node {
    Node() :next(nullptr), prev(nullptr) {}
    Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

    Item  item;
    Node* next;
    Node* prev;
};



/* List default constructor
//        Set m_head and m_tail pointer to point to nothing, m_size is zero
//        Already implemented, nothing to do.
*/
template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}


/* Copy constructor
*/
template<typename Item>
List<Item>::List(const List<Item>& other) {
    /* TODO */
    if(other.m_head == nullptr){
        m_head = nullptr;
    }
    else{
        Node *p = other.m_head;
        Node *q = new Node;
        q->item = p->item;
        q->next = nullptr;
        m_head = q;
        p = p->next;
        int i= 0;
        while(i != (m_size - 1)){
            Node * r = new Node;
            r->item = p->item;
            r->next = nullptr;
            q->next = r;
            p = p->next;
            q = q->next;
            m_tail = q;
            i++;
        }
    }
}
/* Overloaded assignment operator
*/
template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
    /* TODO */
    if(other.m_head == nullptr){
        m_head = nullptr;
    }
    else{
        Node *p = other.m_head;
    Node *q = new Node;
    q->item = p->item;
    q->next = nullptr;
    m_head = q;
    p = p->next;
    int i= 0;
    while(i != (m_size - 1)){
        Node * r = new Node;
        r->item = p->item;
        r->next = nullptr;
        q->next = r;
        p = p->next;
        q = q->next;
        m_tail = q;
        i++;
        }
    }
    return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
    /* TODO */
    Node *p = m_head;
    while(p!= nullptr){
        Node *temp = p->next;
        delete p;
        p = temp;
    }
}
/* List print
*/
template<typename Item>
void List<Item>::print() const {
    /* TODO */
    Node *p = new Node;
    p = m_head;
    while(p!= nullptr){     //traverse and print
        std::cout << p->item << " ";
        p = p->next;
    }
}

/* List empty
*/
template<typename Item>
bool List<Item>::empty() const {
    /* TODO */
    if(m_head == nullptr){return true;}
    else
        return false;
}


/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item &item) {
    /* TODO */
    m_size++;
    if(m_size == 1){
    
        Node* p;
        p = new Node;
        p->item = item;
        p->next = m_head;
        m_head = p;
        m_tail = p;
       // m_size++;
    }
    else{
        Node* p;
        p = new Node;
        p->item = item;
        p->next = m_head;
        p->prev = nullptr;
        m_head->prev = p;
        m_head = p;

    }
}
/* List push_rear
*/
template<typename Item>
void List<Item>::push_rear(const Item &item) {
    /* TODO */
    if(m_head == nullptr){ // if list is empty
        push_front(item);
    }
    else{
        Node *p;
        p = m_head;
        while(p->next != nullptr)
            p = p->next;
        Node *n = new Node;
        n->item = item;
        p->next = n;
        n->next = nullptr;
        m_tail = n;
        m_size++;
        //Node *n = new Node;
        //n->item = item;
        //m_tail->next = n;
        //n->next = nullptr;
        //m_tail = n;
    }
}

/* List insert
*/
template<typename Item>
void List<Item>::insert(int index, const Item &item) {
    /* TODO */
    if(index < 0 || index == 0){    // if index is less than or equal to 0, push item to front
        push_front(item);
    }
    else if(index >= m_size){ // if index greater than or equal to size, add it to the end
        push_rear(item);
    }
    else{
        Node *p = m_head;
        for(int i = 0;i < index-1;i++){
            p=p->next;
        }
        m_size++;

        Node *latest = new Node;
        latest->item = item;
        latest->next = p->next;
        p->next = latest;
        latest->prev = p;
        std::cout << "the item " << item << " is at index " << index << std::endl;
    }
}

/*  List front
*/
template<typename Item>
Item List<Item>::front() const {
    // Force check that the m_head is pointing to a Node
    // Typical solution for deployement code is to throw
    // exceptions, but since we haven't covered that yet
    // we'll make due with assert, which is used for testing
    assert(m_head != nullptr);

    /* TODO */
    Item first = m_head->item;
    return first;
}

/* List rear
*/
template<typename Item>
Item List<Item>::rear() const {

    // Force check that the m_tail is pointing to a Node
    // Typical solution for deployement code is to throw
    // exceptions, since we haven't covered that yet
    // we'll make due with assert, which is used for testing
    assert(m_tail != nullptr);

    /* TODO */
    //CHECK AGAIN
    //Node * p = m_tail;
    Item last = m_tail->item;
    return last;
    
}

/* List get
//        returns the item at index
*/
template<typename Item>
Item List<Item>::get(int index) const {

    // Force index to be correct before getting the Item
    // Typical solution for deployement code is to throw
    // exceptions, since we haven't covered that yet
    // we'll make due with assert, which is used for testing
    assert(index >= 0 && index < m_size);
    /* TODO */
    //Node *p = m_head;
    //while(p!= nullptr){
      //  if(p->item == index)
        //    break;
       // p = p->next;
    //}
    //if(p->item == index)
    //m_head->item;
    int i = 0;
    Node *p = m_head;
    while(i != index){
        p = p->next;
        i++;
    }
    Item m_head = p->item;;
    return m_head;
}

/* List size
*/
template<typename Item>
int List<Item>::size() const {
    /* TODO */
    
    return m_size;
}

/* List find
*/
template<typename Item>
int List<Item>::find(const Item &item) const {

    /* TODO */
    Node *p = m_head;
    int index = 0;
    while(p != nullptr){
        if(p->item == item)
            break;
        p = p->next;
        index++;
    }
    if(p != nullptr){
        return index;
    }
    return -1;
}

/* List pop_front
*/
template<typename Item>
bool List<Item>::pop_front() {
    /* TODO */
    if(m_head == nullptr){
        return false;
    }
    else{
        Node *p = new Node;
        p->item = m_head->item;
        p->next = m_head->next;
        m_head = p ->next;
        delete p;
        m_size--;
    
        return true;
    }

}

/* List pop_rear
*/
template<typename Item>
bool List<Item>::pop_rear() {
    // Check Again
    /* TODO */
    if(m_head == nullptr){
        return false;
    }
    else{
        Node *p = m_tail;
        m_tail = m_tail->prev;
        m_tail->next = nullptr;
        delete p;
        m_size--;
    
        return true;
    }
}

/* List remove
*/
template<typename Item>
bool List<Item>::remove(int index) {// Check Again

    /* TODO */
    if(m_head == nullptr) {return false;}
    else if(index == 0){     // if we want to remove the first node
        pop_front();
        m_size--;
        return true;
    }
    else if(index == m_size-1){     // if we want to remove the last node
        pop_rear();
        m_size--;
        return true;
    }
    else if(index > m_size || index < 0){
        return false;
    }
    else{
        Node *p = m_head;
        for(int i = 0;i != index-1;i++){
            p=p->next;
        }
        std::cout << p->item << std::endl;
    //Node *p = m_head;
    if(p!= nullptr){
        Node *killMe = p->next;
        p->next = killMe->next;
        killMe->next->prev =p;
        delete killMe;
        
    }
        m_size--;
    return true;
}
}
     
#endif // _X_XMMXX
