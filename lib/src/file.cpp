#include "file.h"

namespace mylib {

LinkedList::LinkedList() : head_(nullptr), size_(0) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insertAtHead(int value) {
    Node* newNode = new Node{value, head_};
    head_ = newNode;
    size_++;
}

void LinkedList::insertAtTail(int value) {
    Node* newNode = new Node{value, nullptr};
    if (!head_) {
        head_ = newNode;
    } else {
        Node* current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size_++;
}

void LinkedList::insertAtIndex(int index, int value) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0) {
        insertAtHead(value);
        return;
    }

    Node* current = head_;
    for (int i = 0; i < index - 1; ++i) {
        current = current->next;
    }

    Node* newNode = new Node{value, current->next};
    current->next = newNode;
    size_++;
}

bool LinkedList::removeByValue(int value) {
    if (!head_) return false;

    if (head_->data == value) {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
        size_--;
        return true;
    }

    Node* current = head_;
    while (current->next) {
        if (current->next->data == value) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size_--;
            return true;
        }
        current = current->next;
    }
    return false;
}

int LinkedList::get(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    Node* current = head_;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

int LinkedList::indexOf(int value) const {
    Node* current = head_;
    int index = 0;
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int LinkedList::size() const {
    return size_;
}

void LinkedList::clear() {
    Node* current = head_;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head_ = nullptr;
    size_ = 0;
}

} // namespace mylib