// FILE: sequence.cpp

#include "sequence.h"
#include <stdexcept>
// Constructor: Creates an empty sequence or a sequence of size 'sz'
Sequence::Sequence(int sz) : head(nullptr), tail(nullptr), numElts(0) {
    for (int i = 0; i < sz; ++i) {
        push_back(0);
    }
}
// Destructor: Destroys the sequence and releases the memory
Sequence::Sequence(const Sequence& s) : head(nullptr), tail(nullptr), numElts(0) {
    SequenceNode* current = s.head;
    while (current) {
        push_back(current->elt);
        current = current->next;
    }
}
// Assignment operator: Releases current sequence and copies from 's'
Sequence& Sequence::operator=(const Sequence& s) {
    if (this != &s) {
        clear();
        SequenceNode* current = s.head;
        while (current) {
            push_back(current->elt);
            current = current->next;
        }
    }
    return *this;
}

Sequence::~Sequence() {
    clear();
}
// Index operator: Accesses the element at 'position'
int& Sequence::operator[](int position) {
    if (position < 0 || position >= numElts) {
        throw out_of_range("Index out of bounds");
    }
    SequenceNode* current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->elt;
}

// Adds 'value' to the end of the sequence
void Sequence::push_back(const int& value) {
    SequenceNode* newNode = new SequenceNode(value);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    ++numElts;
}

// Removes the last element from the sequence
void Sequence::pop_back() {
    if (!tail) {
        throw out_of_range("Sequence is empty");
    }
    SequenceNode* oldTail = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete oldTail;
    --numElts;
}
// Inserts 'value' at 'position' in the sequence
void Sequence::insert(int position, int value) {
    if (position < 0 || position > numElts) {
        throw out_of_range("Index out of bounds");
    }
    SequenceNode* newNode = new SequenceNode(value);
    if (position == 0) {  // Insert at the head
        newNode->next = head;
        if (head) {
            head->prev = newNode;
        }
        head = newNode;
        if (!tail) {
            tail = newNode;
        }
    } else if (position == numElts) {  // Insert at the tail
        push_back(value);
    } else {
        SequenceNode* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev) {
            current->prev->next = newNode;
        }
        current->prev = newNode;
    }
    ++numElts;
}
// Returns the first element in the sequence
const int& Sequence::front() const {
    if (!head) {
        throw out_of_range("Sequence is empty");
    }
    return head->elt;
}
// Returns the last element in the sequence
const int& Sequence::back() const {
    if (!tail) {
        throw out_of_range("Sequence is empty");
    }
    return tail->elt;
}

bool Sequence::empty() const {
    return numElts == 0;
}

int Sequence::size() const {
    return numElts;
}

// Clears the sequence and releases memory
void Sequence::clear() {
    while (head) {
        SequenceNode* oldHead = head;
        head = head->next;
        delete oldHead;
    }
    head = tail = nullptr;
    numElts = 0;
}
// Erases 'count' elements starting from 'position'
void Sequence::erase(int position, int count) {
    if (position < 0 || position >= numElts || position + count > numElts) {
        throw out_of_range("Index out of bounds");
    }
   
    SequenceNode* current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    for (int i = 0; i < count; ++i) {
        SequenceNode* toDelete = current;
        current = current->next;
        if (toDelete->prev) {
            toDelete->prev->next = toDelete->next;
        } else {
            head = toDelete->next;
        }
        if (toDelete->next) {
            toDelete->next->prev = toDelete->prev;
        } else {
            tail = toDelete->prev;
        }
        delete toDelete;
    }
    numElts -= count;
}
// Outputs the sequence elements
ostream& operator<<(ostream& os, const Sequence& s) {
    os << "<";
    Sequence::SequenceNode* current = s.head;
    while (current) {
        os << current->elt;
        if (current->next) {
            os << ", ";
        }
        current = current->next;
    }
    os << ">";
    return os;
}
