#include "Cargo.h"


void Cargo::add(string newdata, string newdata2) {
    Node *last = new Node;

    if (head == NULL) {
        last->data = newdata;
        last->data2 = newdata2;
        last->next = NULL;
        last->prev = NULL;
        head = last;
        sizeOfCargo++;
        return;
    }

    last = head;
    Node *temp = new Node;
    while (last->next != NULL) {
        last = last->next;
    }

    temp->data = newdata;
    temp->data2 = newdata2;
    last->next = temp;
    temp->next = NULL;
    temp->prev = last;
    sizeOfCargo++;

}

void Cargo::deleteLastNode() {
    struct Node *last = head;
    if (last != NULL) {
        if (last->next == NULL && last->prev == NULL) {
            head = NULL;
            sizeOfCargo--;
            return;
        }
        if (last != NULL) {
            while (last->next->next != NULL) {
                last = last->next;
            }
            last->next = NULL;

        }
        sizeOfCargo--;
    }


}

string Cargo::lastNode() {
    struct Node *last = head;
    if (last != NULL) {
        while (last->next != NULL) {
            last = last->next;
        }
        return last->data;
    }
}

string Cargo::lastNode2() {
    struct Node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    return last->data2;
}

int Cargo::lenghtCargo() {
    return sizeOfCargo;
}

Cargo::Cargo() {};

Cargo::~Cargo() {};