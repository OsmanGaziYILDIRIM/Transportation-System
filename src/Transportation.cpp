#include <iostream>
#include "Stack.cpp"
#include "Queue.cpp"
#include <fstream>
#include "City.h"
#include <bits/stdc++.h>
#include "Cargo.cpp"

using namespace std;


vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}


void work(string dests, string packages, string trucks, string mission, string result) {
    ifstream destsFile;
    destsFile.open(dests);
    string list[50];
    string row;
    int countCity = 0;
    while (getline(destsFile, row)) {
        list[countCity] = row;
        countCity++;
    }
    string destsList[countCity];
    int i = 0;
    while (true) {
        destsList[i] = list[i];
        i++;
        if (i == countCity) {
            break;
        }
    }
    destsFile.close();

    ifstream packagesFile;
    packagesFile.open(packages);
    string matris[20][2];
    int countPackage = 0;
    while (getline(packagesFile, row)) {
        vector<string> v = split(row, " ");
        matris[countPackage][0] = v[0];
        matris[countPackage][1] = v[1];
        countPackage++;
    }
    string packageList[countPackage][2];
    int j = 0;
    while (true) {
        packageList[j][0] = matris[j][0];
        packageList[j][1] = matris[j][1];
        j++;
        if (j == countPackage) {
            break;
        }
    }
    packagesFile.close();

    ifstream trucksFile;
    trucksFile.open(trucks);
    string matris2[20][3];
    int countTruck = 0;
    while (getline(trucksFile, row)) {
        vector<string> v = split(row, " ");
        matris2[countTruck][0] = v[0];
        matris2[countTruck][1] = v[1];
        matris2[countTruck][2] = v[2];
        countTruck++;
    }
    string truckList[countTruck][3];
    int k = 0;
    while (true) {
        truckList[k][0] = matris2[k][0];
        truckList[k][1] = matris2[k][1];
        truckList[k][2] = matris2[k][2];
        k++;
        if (k == countTruck) {
            break;
        }
    }
    trucksFile.close();


    City cityList[countCity];
    int mervi = 0;
    for (int i = 0; i < countCity; i++) {
        City *city = new City;
        city->name = destsList[i];
        for (int l = 0; l < countPackage; l++) {
            if (city->name == packageList[l][1]) {
                Packages packages1;                 // add package to stack
                packages1.numberPackage = packageList[l][0];
                city->stack.push(packages1);
            }
        }
        for (int m = 0; m < countTruck; m++) {
            if (city->name == truckList[m][1]) {
                Trucks trucks1;                       // add truck to queue
                trucks1.numberTruck = truckList[m][0];
                trucks1.power = truckList[m][2];
                city->queue.enqueue(trucks1);
            }
        }
        cityList[mervi] = *city;
        mervi++;
    }
    fstream output;
    output.open(result, ios::out);
    ifstream missionFile;
    missionFile.open(mission);
    while (getline(missionFile, row)) {
        vector<string> mission = split(row, "-");

        for (int l = 0; l < countCity; l++) {
            City city = cityList[l];
            if (mission[0] == city.name) {
                Cargo cargo;
                if (!city.queue.isEmpty()) {                          //take truck
                    Trucks trucks1;
                    city.queue.getFront(trucks1);
                    cargo.add(trucks1.numberTruck, trucks1.power);
                    city.queue.dequeue();
                    cityList[l]=city;
                }
                int firstPackage = 0;
                stringstream geek(mission[3]);
                geek >> firstPackage;
                for (int m = 0; m < firstPackage; m++) {               //take package of first city
                    if (!city.stack.isEmpty()) {
                        Packages packages1;
                        city.stack.getTop(packages1);
                        cargo.add(packages1.numberPackage, "0");
                        city.stack.pop();
                        cityList[l]=city;
                    }
                }
                for (int m = 0; m < countCity; m++) {
                    City city2 = cityList[m];
                    if (mission[1] == city2.name) {                    //take package of second city
                        int secondPackage = 0;
                        stringstream geek2(mission[4]);
                        geek2 >> secondPackage;
                        Packages secondCity[secondPackage];
                        for (int n = 0; n < secondPackage; ++n) {
                            if (!city2.stack.isEmpty()) {
                                Packages packages1;
                                city2.stack.getTop(packages1);
                                secondCity[n] = packages1;
                                city2.stack.pop();
                                cityList[m]=city2;
                            }
                        }


                        vector<string> takePackage = split(mission[5], ",");
                        int lenght = takePackage.size();
                        string putPackage[lenght];
                        for (int i1 = 0; i1 < lenght; i1++) {
                            putPackage[i1] = cargo.lastNode();            // put package to second city
                            cargo.deleteLastNode();
                        }

                        for (int k1 = 0; k1 < lenght; k1++) {
                            int a = 0;
                            stringstream geek2(takePackage[k1]);
                            geek2 >> a;
                            Packages packages1;
                            packages1.numberPackage = putPackage[a];
                            city2.stack.push(packages1);
                            cityList[m]=city2;
                        }
                        for (int l1 = 0; l1 < secondPackage; ++l1) {
                            cargo.add(secondCity[l1].numberPackage, "0");

                        }

                        for (int m1 = 0; m1 < countCity; m1++) {       // put package to last city
                            City city1 = cityList[m1];
                            if (mission[2] == city1.name) {
                                while (cargo.lenghtCargo() > 1) {
                                    Packages packages1;
                                    packages1.numberPackage = cargo.lastNode();
                                    city1.stack.push(packages1);
                                    cargo.deleteLastNode();
                                    cityList[m1]=city1;
                                }
                                if (cargo.lenghtCargo() == 1) {
                                    Trucks trucks1;
                                    trucks1.numberTruck = cargo.lastNode();
                                    trucks1.power = cargo.lastNode2();
                                    city1.queue.enqueue(trucks1);
                                    cargo.deleteLastNode();
                                    cityList[m1]=city1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    missionFile.close();
    for (int n1 = 0; n1 < countCity; n1++) {
        output << cityList[n1].name << "\n" << "Packages:\n";
        while (!cityList[n1].stack.isEmpty()) {
            Packages *packages1 = new Packages;
            cityList[n1].stack.getTop(*packages1);
            cityList[n1].stack.pop();
            output << packages1->numberPackage << "\n";
        }
        output << "Trucks:\n";
        while (!cityList[n1].queue.isEmpty()) {
            Trucks *trucks1 = new Trucks;
            cityList[n1].queue.getFront(*trucks1);
            cityList[n1].queue.dequeue();
            output << trucks1->numberTruck << "\n";
        }
        output << "-------------\n";
    }

    output.close();

}