#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
    currentElement = list.head;
}

void ListIterator::first(){
    currentElement = list.head;
}

void ListIterator::next(){
    if (!valid()) {
        throw exception();
    }
    currentElement = currentElement->next;
}

bool ListIterator::valid() const{
    return currentElement != nullptr;
}

TComp ListIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }
    return currentElement->elem;
}


