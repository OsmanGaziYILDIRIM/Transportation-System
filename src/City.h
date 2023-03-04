#ifndef ASSIGMENT3_CITY_H
#define ASSIGMENT3_CITY_H

#include "Packages.h"
#include "Trucks.h"

class City {
public:
    string name;
    Stack<Packages> stack;
    Queue<Trucks> queue;

};


#endif //ASSIGMENT3_CITY_H
