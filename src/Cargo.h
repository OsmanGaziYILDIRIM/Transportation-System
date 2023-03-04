#ifndef ASSIGMENT3_CARGO_H
#define ASSIGMENT3_CARGO_H

#include "Trucks.h"
#include "Packages.h"

class Cargo {
public:
    Cargo();

    ~Cargo();

    struct Node {
        string data;
        string data2;
        struct Node *prev;
        struct Node *next;
    };
    struct Node *head = NULL;
    int sizeOfCargo = 0;

    void add(string newdata, string newdata2);

    void deleteLastNode();

    string lastNode();

    string lastNode2();


    void display();

    int lenghtCargo();
};


#endif //ASSIGMENT3_CARGO_H
