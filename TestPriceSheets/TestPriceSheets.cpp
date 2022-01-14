// TestPriceSheets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "PriceCalulation.h"

using namespace std;
/*
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>

template<class T, char sep=','>
struct comma_sep { //type used for temporary input
    T t; //where data is temporarily read to
    operator const T&() const {return t;} //acts like an int in most cases
};
template<class T, char sep>
std::istream& operator>>(std::istream& in, comma_sep<T,sep>& t) 
{
    if (!(in >> t.t)) //if we failed to read the int
        return in; //return failure state
    if (in.peek()==sep) //if next character is a comma
        in.ignore(); //extract it from the stream and we're done
    else //if the next character is anything else
        in.clear(); //clear the EOF state, read was successful
    return in; //return 
}

int main() {
    typedef std::istream_iterator<comma_sep<int>> istrit;
    typedef std::ostream_iterator<int> ostrit;
    
    std::vector<int> vec(istrit(std::cin), istrit());
    std::copy(vec.begin(), vec.end(), ostrit(std::cout, ";"));
    return 0;
}*/

int main(int argc, char* argv[]) {

    PriceCalculation cal;

    string year;

    int menu0;

    bool run_program = true;

    //double *product_list_pointer;

    double pricePB, priceBB = 0, priceNB = 0, priceBTB, priceBD = 0, priceSC, priceCWC, priceWC, priceCP, priceLCP, priceMS,
        priceRGM,priceSB, priceST, priceTS, priceFD, priceTO, retailPercentage;

    double difPB_W, difBTB_W;

    // delivered prices Mulches
    double maxlp0, maxlp1, maxlp2, maxlp3, maxlp4, maxlp5, maxlp6, maxlp7, maxlp8;

    int maxl0, maxl1, maxl2, maxl3, maxl4, maxl5, maxl6, maxl7, maxl8;

    // Delivered Prices Soils
    double maxslp0, maxslp1, maxslp2, maxslp3, maxslp4;

    int maxsl0, maxsl1, maxsl2, maxsl3, maxsl4;

    cout << "Welcome to PriceSheet maker!\nPatent pending\n";

    cout << "Please Enter the year: ";

    cin >> year;

    cout << "Enter prices of products individualy (1) or just Premium and Beauty Bark? (2): ";

    cin >> menu0;

    while (run_program) {
    
        switch (menu0) {

            case 0: {

                cout << "Enter prices of products individualy (1) or just Premium and Beauty Bark? (2): ";

                cin >> menu0;

            }break;

            case 1: {


            }break;

            case 2: {
                /*
                    This calculates its prices by getting the base price (Wholesale 10+ yrds picked up price)
                    and calculating prices off of a percentage
                */

                cout << "Enter the wholesale picked up price of the following products: \n";

                cout << "Premium Bark:";

                cin >> pricePB;

                cout << "Beauty Bark:";

                cin >> priceBTB;

                cout << "What price diffrence do you want between products in concern with Premium Bark: ";

                cin >> difPB_W;

                cout << "What price diffrence do you want between products in concern with Beauty Bark: ";

                cin >> difBTB_W;

                cout << "Enter a percentage increase from wholesale to retail:";

                cin >> retailPercentage;

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

                // temp filling out of delivered vars
                maxl0 = 1; maxl1 = 6; maxl2 = 10; maxl3 = 15; maxl4 = 20; maxl5 = 25; maxl6 = 30; maxl7 = 40; maxl8 = 50;
                maxlp0 = 42.65; maxlp1 = 69.25; maxlp2 = 105.25; maxlp3 = 115.25; maxlp4 = 124.75; maxlp5 = 130; maxlp6 = 132.75; maxlp7 = 145.75; maxlp8 = 156;

                // Delivered Prices Soils
                maxsl0 = 1, maxsl1 = 3, maxsl2 = 8, maxsl3 = 15, maxsl4 = 20;
                maxslp0 = 47.25, maxslp1 = 61, maxslp2 = 105.75, maxslp3 = 131.75, maxslp4 = 150;


                cal.setdifPB_W(difPB_W);
                cal.setdifBTB_W(difBTB_W);

                cal.setYear(year);
                cal.setRetailPercentage(retailPercentage);

                //Setting up for calculating delivered prices Soil
                double maxload_Soil[5] = { maxsl0, maxsl1, maxsl2, maxsl3, maxsl4 };
                double* maxload_pointer_Soil = maxload_Soil;
                int n = sizeof(maxload_Soil) / sizeof(maxload_Soil[0]);
                cal.setTruckMaxLoadSoil(maxload_pointer_Soil, n);

                double maxloadprice_Soil[5] = { maxslp0, maxslp1, maxslp2, maxslp3, maxslp4 };
                double* maxloadprice_pointer_Soil = maxloadprice_Soil;
                n = sizeof(maxloadprice_Soil) / sizeof(maxloadprice_Soil[0]);
                cal.setTruckMaxLoadPriceSoil(maxloadprice_pointer_Soil, n);

                //Setting up for calculating delivered prices Mulch
                double maxload[9] = { maxl0, maxl1, maxl2, maxl3, maxl4, maxl5, maxl6, maxl7, maxl8 };
                double* maxload_pointer = maxload;
                n = sizeof(maxload) / sizeof(maxload[0]);
                cal.setTruckMaxLoad(maxload_pointer, n);

                double maxloadprice[9] = { maxlp0, maxlp1, maxlp2, maxlp3, maxlp4, maxlp5, maxlp6, maxlp7, maxlp8 };
                double* maxloadprice_pointer = maxloadprice;
                n = sizeof(maxloadprice) / sizeof(maxloadprice[0]);
                cal.setTruckMaxLoadPrice(maxloadprice_pointer, n);

                cal.calculateDeliveredPrices();

                //setting up to calculate picked up prices prices
                double product_list[17] = { pricePB, priceBB, priceNB, priceBTB, priceBD, priceSC, priceCWC, priceWC, priceCP, priceLCP, priceMS,
                    priceRGM, priceSB, priceST, priceTS, priceFD, priceTO, };

                double* product_list_pointer = product_list;
                n = sizeof(product_list) / sizeof(product_list[0]);
                cal.setProductStartPrice(product_list_pointer, n);

                cal.calculatePickedUpPrices();

                // Creating ABC formatted text file
                cal.calculateDeliveredProducts();

                cal.createABCFormatting();
                cal.createTempPBFile();

            }break;
        }
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
