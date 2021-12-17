// TestPriceSheets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

double calulateWholesalePickedUp(double product[17]) {
    return 0;
}



/*
double calculatePrices(double product) {

    static double r[19];

    for (int i = 0; i > sizeof(r); i++) {
        r[i] = product + i;
    }

    return *r;
}
*/
double createABC2(string year2, double retailPercentage2, double difPB, double difBTB, double pricePB2, double priceBTB2) {

    int f;
    double percent;
    double r[4], r2[4], w[5], w2[5];

    ofstream MyFile2("ABCPricing2_" + year2 + ".txt");
    double products2[5] = { pricePB2, 0, 0, priceBTB2, 0 };

    for (int j = 0; j < sizeof(products2) / sizeof(products2[0]); j++) {

        switch (j) {
        case 0: MyFile2 << "\n\nPremium Bark\n\n"; break;
        case 1: MyFile2 << "\n\nBark Blend\n\n"; break;
        case 2: MyFile2 << "\n\nNatures Blend\n\n"; break;
        case 3: MyFile2 << "\n\nBeauty Bark\n\n"; break;
        case 4: MyFile2 << "\n\nDyed Mulch\n\n"; break;
        }

        percent = .12;
        MyFile2 << "Wholesale Picked Up Price:\n";
        if (j == 0 || j == 3) {

            for (int i = 0; i < sizeof(r) / sizeof(r[0]); i++) {
                // 0 1 2 3 != 3 6 3 0 % -> 12 9 3 0 %
                percent = (percent - (i * .03));
                if (percent >= 0) r[i] = round((products2[j] * (1 + percent)) * 4) / 4; else r[i] = products2[j];
                MyFile2 << "," << 1 + (3 * i) << "*" << r[i] << "$";
            }

            percent = .015;
            f = 2;
            MyFile2 << "\n\nRetial Picked Up Price:\n";
            for (int i = 0; i < sizeof(w) / sizeof(w[0]); i++) {
                switch (i) {
                case 4: f = 6; break;
                default: break;
                }

                if (i != 4) {
                    w[i] = round(((products2[j] * (1 + retailPercentage2) * (1 + (.075 - (percent * i)))) * 4)) / 4;
                }
                else {
                    w[i] = round((products2[j] * (1 + retailPercentage2)) * 4) / 4;
                }

                if (i == 0) {
                    w[i] = round((w[i] / 1.06) * 100) / 100;
                }
                MyFile2 << "," << f + i << "*" << w[i] << "$";
            }
        }
        else {
            if (j < 3) {
                for (int i = 0; i < sizeof(r) / sizeof(r[0]); i++) {
                    r[i] -= difPB;
                    MyFile2 << "," << 1 + (3 * i) << "*" << r[i] << "$";
                }

            }
            if (j == 4) {
                for (int i = 0; i < sizeof(r) / sizeof(r[0]); i++) {
                    r[i] -= difBTB;
                    MyFile2 << "," << 1 + (3 * i) << "*" << r[i] << "$";
                }
            }
        }

        
    }

    MyFile2.close();
    return 0;
}


double createABC(string year, double retailPercentage, double pricePB, double priceBB, double priceNB, double priceBTB, double priceBD){/*,
    double priceSC, double priceCWC, double priceWC, double priceCP, double priceLCP, double priceMS, double priceRGM,
    double priceSB, double priceST, double priceTS, double priceFD, double priceTO) {*/
    //double p;
    //double calcPB = calculatePrices(pricePB);
    //float coeff = 4f;
    //p = calcPB();

    //array priceArrPB = calculatePrices(pricePB);
    double products[5]/*17*/ = { pricePB, priceBB, priceNB, priceBTB, priceBD };/*/, priceSC, priceCWC, priceWC, priceCP, priceLCP, priceMS,
        priceRGM, priceSB, priceST, priceTS, priceFD, priceTO };*/

    int f;
    double percent;
    double r[4], w[5];
    ofstream MyFile("ABCPricing_" + year + ".txt");

    //MyFile << "Premium Bark\n\n";

    //MyFile << "Wholesale:\n\n";


    //MyFile << "Picked Up:\n";

    for (int j = 0; j < sizeof(products) / sizeof(products[0]); j++) {
        
        switch (j) {
        case 0: MyFile << "\n\nPremium Bark\n\n"; break;
        case 1: MyFile << "\n\nBark Blend\n\n"; break;
        case 2: MyFile << "\n\nNatures Blend\n\n"; break;
        case 3: MyFile << "\n\nBeauty Bark\n\n"; break;
        case 4: MyFile << "\n\nDyed Mulch\n\n"; break;
            /*
        case 5: MyFile << "\n\nSafe Cover\n\n"; break;
        case 6: MyFile << "\n\nClean Wood Chips\n\n"; break;
        case 7: MyFile << "\n\nWood Chips\n\n"; break;
        case 8: MyFile << "\n\nCompost\n\n"; break;
        case 9: MyFile << "\n\nLeaf Compost\n\n"; break;
        case 10: MyFile << "\n\nMushroom Soil\n\n"; break;
        case 11: MyFile << "\n\nRain Garden Mix\n\n"; break;
        case 12: MyFile << "\n\nScreened Blend\n\n"; break;
        case 13: MyFile << "\n\nScreened Topsoil\n\n"; break;
        case 14: MyFile << "\n\nRegular Topsoil\n\n"; break;
        case 15: MyFile << "\n\nFill Dirt\n\n"; break;
        case 16: MyFile << "\n\nTopsoil Overs\n\n"; break;
        */
        }


        percent = .12;

        MyFile << "Wholesale Picked Up Price:\n";
        for (int i = 0; i < sizeof(r) / sizeof(r[0]); i++) {
            // 0 1 2 3 != 3 6 3 0 % -> 12 9 3 0 %
            percent = (percent - (i * .03));
            if (percent >= 0) r[i] = round((products[j] * (1 + percent)) * 4) / 4; else r[i] = products[j];
            MyFile << "," << 1 + (3 * i) << "*" << r[i] << "$";
        }
        
        percent = .015;
        f = 2;
        MyFile << "\n\nRetial Picked Up Price:\n";
        for (int i = 0; i < sizeof(w) / sizeof(w[0]); i++) {
            switch (i) {
            case 4: f = 6; break;
            default: break;
            }

            if (i != 4) {
                w[i] = round(((products[j] * (1 + retailPercentage) * (1 + (.075 - (percent * i)))) * 4)) / 4;
            }
            else {
                w[i] = round((products[j] * (1 + retailPercentage)) * 4) / 4;
            }

            if (i == 0) {
                w[i] = round((w[i] / 1.06)*100)/100;
            }
            MyFile << "," << f + i << "*" << w[i] << "$";
        }
        
    }

    /*
    MyFile << "\nDelivered:\n";
    double t[18];
    percent = .12;
    for (int i = 0; i < sizeof(r) / sizeof(r[0]); i++) {
        percent = (percent - (i * .03));
        if (percent >= 0) r[i] = round((pricePB * (1 + percent)) * 4) / 4; else r[i] = pricePB;
        MyFile << "," << 1 + (3 * i) << "*" << r[i] << "$";
    }
    */
    /*
    MyFile << "Retail:\n\n";


    MyFile << "Picked Up:\n";

    MyFile << "Delivered:\n";

    //Math.round(myFloat*4)/4f
    */

    MyFile.close();

    return 0;
}


int createExel() {




    return 0;
}

int main(int argc, char* argv[]) {

    string year;

    int menu0;

    double pricePB, priceBB, priceNB, priceBTB, priceBD, priceSC, priceCWC, priceWC, priceCP, priceLCP, priceMS,
        priceRGM,priceSB, priceST, priceTS, priceFD, priceTO, retailPercentage;

    double difPB, difBTB;

    cout << "Welcome to PriceSheet maker!\n Patten pending\n";

    cout << "Please Enter the year: ";

    cin >> year;
    
    cout << "Enter prices of products individualy (1) or just Premium and Beauty Bark? (2): ";

    cin >> menu0;
    
    switch (menu0) {

        case 1:{
            cout << "Enter the wholesale picked up price of the following; \n";

            cout << "Premium Bark:";

            cin >> pricePB;

            cout << "Bark Blend:";

            cin >> priceBB;

            cout << "Nature's Blend:";

            cin >> priceNB;

            cout << "Beauty Bark:";

            cin >> priceBTB;

            cout << "Dyed Mulches:";

            cin >> priceBD;

            cout << "Enter a percentage incress from wholesale to retail:";

            cin >> retailPercentage;

            /*
            cout << "Safe Cover:";

            cin >> priceSC;

            cout << "Clean Wood Chips:";

            cin >> priceCWC;

            cout << "Wood Chips:";

            cin >> priceWC;

            cout << "Compost:";

            cin >> priceCP;

            cout << "Leaf Compost:";

            cin >> priceLCP;

            cout << "Mushroom Soil:";

            cin >> priceMS;

            cout << "Rain Garden Mix:";

            cin >> priceRGM;

            cout << "Screened Blend:";

            cin >> priceSB;

            cout << "Screened Topsoil:";

            cin >> priceST;

            cout << "Topsoil:";

            cin >> priceTS;

            cout << "Fill Dirt:";

            cin >> priceFD;

            cout << "Topsoil Overs:";

            cin >> priceTO;
            */
            double ABC = createABC(year, retailPercentage, pricePB, priceBB, priceNB, priceBTB, priceBD);/*, priceSC, priceCWC, priceWC, priceCP,
                priceLCP, priceMS, priceRGM, priceSB, priceST, priceTS, priceFD, priceTO);*/
        
        }break;

        case 2: {
        
            cout << "Enter the wholesale picked up price of the following; \n";

            cout << "Premium Bark:";

            cin >> pricePB;
        
            cout << "Beauty Bark:";

            cin >> priceBTB;

            cout << "What price diffrence do you want between products in concern with Premium Bark: ";

            cin >> difPB;

            cout << "What price diffrence do you want between products in concern with Beauty Bark: ";

            cin >> difBTB;

            cout << "Enter a percentage incress from wholesale to retail:";

            cin >> retailPercentage;

            double ABC2 = createABC2(year, retailPercentage, difPB, difBTB, pricePB, priceBTB);
        }break;


    }


    

    

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
