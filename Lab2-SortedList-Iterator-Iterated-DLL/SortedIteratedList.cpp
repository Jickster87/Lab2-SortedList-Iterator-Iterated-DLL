#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    head = tail = nullptr;
    listSize = 0;
    rel = r;
}

int SortedIteratedList::size() const {
    return listSize;
}

bool SortedIteratedList::isEmpty() const {
    return listSize == 0;
}

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
    if (!poz.valid()) {
        throw exception();
    }
    return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
    //check if the poz is ok
    if (!poz.valid()) {
        throw exception();
    }
    //node to remove
    Node * nodeToRemove = poz.currentElement;
    TComp removedVal = nodeToRemove->elem;
    
    // Case 1: Removing head node
     if (nodeToRemove == head) {
         head = head->next;
         if (head != nullptr) {
             head->prev = nullptr;
         } else { // List becomes empty
             tail = nullptr;
         }
     }
     // Case 2: Removing tail node
     else if (nodeToRemove == tail) {
         tail = tail->prev;
         if (tail != nullptr) {
             tail->next = nullptr;
         } else { // List becomes empty
             head = nullptr;
         }
     }
     // Case 3: Removing a middle node
     else {
         nodeToRemove->prev->next = nodeToRemove->next;
         nodeToRemove->next->prev = nodeToRemove->prev;
     }
     
     // Move iterator to next node
     poz.next();
     
     delete nodeToRemove;
     listSize--;
     
    return removedVal;
}

ListIterator SortedIteratedList::search(TComp e) const {
    ListIterator it = first();
    while (it.valid()) {
        if (it.getCurrent() == e) {
            return it;
        }
        it.next();
    }
    return ListIterator(*this);
}

void SortedIteratedList::add(TComp e) {
    Node * newNode = new Node(e);
    
    //list empty
    if (isEmpty()) {
        head = tail = newNode;
        listSize++;
        return;
    }
    
    //element is at head
    if (rel(e, head->elem)) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        listSize++;
        return;
    }
    
    //navigate to pos
    Node * nomad = head;
    while (nomad != nullptr && rel(nomad->elem, e)) {
        nomad = nomad->next;
    }
    
    //element is tail
    if (nomad == nullptr) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    //element is in between
    else{
        newNode->next = nomad;
        newNode->prev = nomad->prev;
        if (nomad->prev != nullptr) {
            nomad->prev->next = newNode;
        }
        nomad->prev = newNode;
             
         // Update head if needed
        if (nomad == head) {
             head = newNode;
        }
    }
    listSize++;
}

SortedIteratedList::~SortedIteratedList() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}
