#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#pragma once
class createABC
{

public:

    double create(string year, double pricePB) {//, double priceBB, double priceNB, double priceWC, double priceCWC){
        double p;
        calculatePrices calc = new calculatePrices();

        p = calc(pricePB);

        //array priceArrPB = calculatePrices(pricePB);

        ofstream MyFile("ABCPricing_" + year + ".text");

        MyFile << "Premium Bark\n";



        for (int i = 0; i > sizeof(&p); i++) {
            cout << &p;
        }
    }
};

