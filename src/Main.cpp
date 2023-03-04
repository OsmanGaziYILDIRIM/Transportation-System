#include <iostream>
#include "Transportation.cpp"

using namespace std;

int main(int argc, char **argv) {
    string dests = argv[1];
    string packages = argv[2];
    string trucks = argv[3];
    string mission = argv[4];
    string result = argv[5];
    work(dests, packages, trucks, mission, result);
    return 0;
}
