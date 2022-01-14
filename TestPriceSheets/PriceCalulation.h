#pragma once
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>

class PriceCalculation {

    double Pickup_Wholesale_products[17][4], Pickup_Wholesale_products_Rounded[17][4];
    // [Product] [Price] 0 = PB, 1 = BB, 2 = NB, 3 = BTB, 4 = Dyed Mulch, 5 = SC, 6 = CWC, 7 = WC, 8 = CP, 9 = LCP, 10 = MS, 
    // 11 = RGM, 12 = SB, 13 = ST, 14 = TS, 15 = FD, 16 = TO;
    double Pickup_Retail_products[17][5], Pickup_Retail_products_Rounded[17][5];
    double retailPercentage;
    double productPrice[17];
    double difPB_W, difBTB_W, difPB_R, difBTB_R;

    //  Mulch Delivered Pricings
    double arr_TruckMaxLoad[9], arr_TruckMaxLoadPrice[9], deliveredPricing[26],
        deliveredPricing_Wholesale_Rounded[17][26], deliveredPricing_Retail_Rounded[17][26];

    // Soil Delivered Pricing
    double arr_TruckMaxLoad_Soil[5], arr_TruckMaxLoadPrice_Soil[5], deliveredPricing_Soil[15];

    double priceBetween, pricePerYardBetween;
    int difYardageDelivered_W, yardsBetween;

    std::string year;

public:

    void calculatePickedUpPrices() {
        double percent;
        int PW_array_length = sizeof(Pickup_Wholesale_products[0]) / sizeof(double);
        int PR_array_length = sizeof(Pickup_Retail_products[0]) / sizeof(double);

        // Calculating the wholesale to retail price diffrence to the change between products
        difPB_R = round(difPB_W * (1 + retailPercentage) * 4) / 4;
        difBTB_R = round(difBTB_W * (1 + retailPercentage) * 4) / 4;
        //std::cout << difPB_R;
        for (int j = 0; j < sizeof(productPrice) / sizeof(productPrice[0]); j++) {

            /*  Whole sale Price calcuation
                i = 0   1 - 3 yrds 12%  > 10+ yrds
                i = 1   4 - 6 yrds 9%   > 10+ yrds
                i = 2   7 - 9 yrds 3%   > 10+ yrds
                i = 3   10+ yrds        = productPrice[j]
            */

            /*  Retail Price Calculation
                i = 4   1 - 2 yrds 21% > 10+ yrds
                i = 3   3 yrds 12% > 10+ yrds
                i = 2   4 yrds 9% > 10+ yrds
                i = 1   5 - 9 yrds  3% > 10+ yrds
                i = 0   10+ yrds "retailPercentage" > wholesale price
            */

            switch (j) {
            case 1: case 2: { // 1 = Bark Blend, 2 = Nature's Blend
                // Wholesale
                for (int i = 0; i < PW_array_length; i++) {
                    Pickup_Wholesale_products[j][i] = Pickup_Wholesale_products[(j - 1)][i] - difPB_W;
                }

                // Retail
                for (int i = 0; i < PR_array_length; i++) {
                    Pickup_Retail_products[j][i] = Pickup_Retail_products[(j - 1)][i] - difPB_R;
                }
            }break;
            case 4: { // 4 = Dyed Mulches
                for (int i = 0; i < PW_array_length; i++) {
                    Pickup_Wholesale_products[j][i] = Pickup_Wholesale_products[(j - 1)][i] - difBTB_W;
                }

                // Retail
                for (int i = 0; i < PR_array_length; i++) {
                    Pickup_Retail_products[j][i] = Pickup_Retail_products[(j - 1)][i] - difBTB_R;
                }
            }break;
            default: {
                percent = .12;

                // Wholesale Picked Up Price
                for (int i = 0; i < PW_array_length; i++) {
                    // 0 1 2 3 != 3 6 3 0 % -> 12 9 3 0 %
                    percent = (percent - (i * .03));
                    if (percent >= 0) {
                        Pickup_Wholesale_products[j][i] = productPrice[j] * (1 + percent);
                    }
                    else {
                        Pickup_Wholesale_products[j][i] = productPrice[j];
                    }
                }

                // Retial Picked Up Price
                for (int i = (PR_array_length - 1); i >= 0; i--) {
                    // 4 3 2 1 0 != 0 3 6 3 9 % -> 0 3 9 12 15 %
                    if (i != (PR_array_length - 1)) {
                        switch (i) {
                        case 1: case 3: percent = .03; break;
                        case 2: percent = .06; break;
                        case 0: percent = .09; break;
                        }
                        Pickup_Retail_products[j][i] = Pickup_Retail_products[j][(i + 1)] * (1 + percent);
                    }
                    else {
                        Pickup_Retail_products[j][i] = Pickup_Wholesale_products[j][(i - 1)] * (1 + retailPercentage);
                    }
                }
            }break;
            }

            // Round all prices to a quarter
        }
        for (int j = 0; j < sizeof(productPrice) / sizeof(productPrice[0]); j++) {

            // Wholesale
            for (int i = 0; i < PW_array_length; i++) {
                Pickup_Wholesale_products_Rounded[j][i] = round(Pickup_Wholesale_products[j][i] * 4) / 4;
            }

            // Retail
            for (int i = 0; i < PR_array_length; i++) {
                if (i != 0) {
                    Pickup_Retail_products_Rounded[j][i] = round(Pickup_Retail_products[j][i] * 4) / 4;
                }
                else {
                    Pickup_Retail_products_Rounded[j][i] = (round(Pickup_Retail_products[j][i] * 4) / 1.06) / 4; // Rounds to a quarter
                    Pickup_Retail_products_Rounded[j][i] = round(Pickup_Retail_products_Rounded[j][i] * 100) / 100;
                }
            }
        }
    }

    void calculateDeliveredPrices() {

        // Delivered Pricing Mulch
        int size_deliveredpricing = sizeof(deliveredPricing) / sizeof(deliveredPricing[0]);

        int j = 0, k = 0;

        for (int i = 0; i < size_deliveredpricing; i++) {
            
            if (i < 19) k = i + 1; else k = ((i - 19) * 5) + 20;

            if (k == arr_TruckMaxLoad[j]) {
                
                deliveredPricing[i] = arr_TruckMaxLoadPrice[j];

                yardsBetween = arr_TruckMaxLoad[j] - arr_TruckMaxLoad[(j + 1)];

                priceBetween = arr_TruckMaxLoadPrice[j] - arr_TruckMaxLoadPrice[(j + 1)];

                // if under twenty calulate each yard, otherwise only calculate multiplies of 5
                if (i < 19) {
                    pricePerYardBetween = priceBetween / yardsBetween;
                }
                else {
                    pricePerYardBetween = abs(priceBetween / 2);
                }

                j++;
            }
            else {
                deliveredPricing[i] = deliveredPricing[(i - 1)] + pricePerYardBetween;
            }
        }

        // Delivered Pricing Soil
        int size_deliveredpricing_Soil = sizeof(deliveredPricing_Soil) / sizeof(deliveredPricing_Soil[0]);

        j = 0, k = 0;

        for (int i = 0; i < size_deliveredpricing_Soil; i++) { // Need to Change this so that 1 - 12, 13-14, 15-19, 20

            switch (i) { // 0 - 7 = 1 - 8, 8 = 9 - 15, 9 = 16 - 20,
            default: k = i + 1; break;
            case 13: k = 15; break;
            case 14: k = 20; break;
            }

            if (k == arr_TruckMaxLoad_Soil[j]) {

                deliveredPricing_Soil[i] = arr_TruckMaxLoadPrice_Soil[j];

                yardsBetween = arr_TruckMaxLoad_Soil[j] - arr_TruckMaxLoad_Soil[(j + 1)];

                priceBetween = arr_TruckMaxLoadPrice_Soil[j] - arr_TruckMaxLoadPrice_Soil[(j + 1)];

                // if under thirteen calulate each yard, otherwise only calculate multiplies of 5
                
                if (i < 11) {
                    pricePerYardBetween = abs(priceBetween / yardsBetween);
                }
                else {
                    pricePerYardBetween = abs(priceBetween / 2);
                }
                
                j++;
            }
            else {
                deliveredPricing_Soil[i] = deliveredPricing_Soil[(i - 1)] + pricePerYardBetween;
            }
            //std::cout << deliveredPricing_Soil[i];
        }
    }

    void calculateDeliveredProducts() {

        double price_product;
        int k;
        // Wholesale Prices
        for (int i = 0; i < sizeof(deliveredPricing_Wholesale_Rounded) / sizeof(deliveredPricing_Wholesale_Rounded[0]); i++) {

            for (int j = 0; j < sizeof(deliveredPricing_Wholesale_Rounded[0]) / sizeof(double); j++) {
                if (i < 11) {
                    if (j < 19) k = j + 1; else k = ((j - 19) * 5) + 20;
                }
                else {
                    switch (j) { // 0 - 7 = 1 - 8, 8 = 9 - 15, 9 = 16 - 20,
                    default: k = j + 1; break;
                    case 13: k = 15; break;
                    case 14: k = 20; break;
                    }
                    if (j > 14) continue;
                }
                switch (j) {
                case 0: case 1: case 2: { price_product = Pickup_Wholesale_products[i][0] * k; } break;
                case 3: case 4: case 5: { price_product = Pickup_Wholesale_products[i][1] * k; } break;
                case 6: case 7: case 8: { price_product = Pickup_Wholesale_products[i][2] * k; } break;
                default: { price_product = Pickup_Wholesale_products[i][3] * k; } break;
                }
                //std::cout << price_product;
                if (i < 11) {
                    deliveredPricing_Wholesale_Rounded[i][j] = round(((price_product + deliveredPricing[j]) / k) * 4) / 4;
                }
                else {
                    deliveredPricing_Wholesale_Rounded[i][j] = round(((price_product + deliveredPricing_Soil[j]) / k) * 4) / 4;
                }
            }
        }

        // Retail Pricing
        for (int i = 0; i < sizeof(deliveredPricing_Retail_Rounded) / sizeof(deliveredPricing_Retail_Rounded[0]); i++) {

            for (int j = 0; j < sizeof(deliveredPricing_Retail_Rounded[0]) / sizeof(double); j++) {
                if (i < 11) {
                    if (j < 19) k = j + 1; else k = ((j - 19) * 5) + 20;
                }
                else {
                    switch (j) { // 0 - 7 = 1 - 8, 8 = 9 - 15, 9 = 16 - 20,
                    default: k = j + 1; break;
                    case 13: k = 15; break;
                    case 14: k = 20; break;
                    }
                    if (j > 14) continue;
                }
                switch (j) {
                case 0: case 1: { price_product = Pickup_Retail_products[i][0] * k; } break;
                case 2: { price_product = Pickup_Retail_products[i][1] * k; } break;
                case 3: { price_product = Pickup_Retail_products[i][2] * k; } break;
                case 4: case 5: case 6: case 7: case 8: { price_product = Pickup_Retail_products[i][3] * k; } break;
                default: { price_product = Pickup_Retail_products[i][4] * k; } break;
                }

                if (i < 11) {
                    deliveredPricing_Retail_Rounded[i][j] = round(((price_product + deliveredPricing[j]) / k) * 4) / 4;
                }
                else {
                    deliveredPricing_Retail_Rounded[i][j] = round(((price_product + deliveredPricing_Soil[j]) / k) * 4) / 4;
                }
            }
        }
    }

    void setTruckMaxLoadSoil(double* maxLoad, int n) {
        for (int i = 0; i < n; i++) {
            this->arr_TruckMaxLoad_Soil[i] = maxLoad[i];
        }
    }

    void setTruckMaxLoadPriceSoil(double* maxLoadPrice, int n) {
        for (int i = 0; i < n; i++) {
            this->arr_TruckMaxLoadPrice_Soil[i] = maxLoadPrice[i];
        }
    }

    void setTruckMaxLoad(double *maxLoad, int n) {
        for (int i = 0; i < n; i++) {
            this->arr_TruckMaxLoad[i] = maxLoad[i];
        }
    }

    void setTruckMaxLoadPrice(double *maxLoadPrice, int n) {
        for (int i = 0; i < n; i++) {
            this->arr_TruckMaxLoadPrice[i] = maxLoadPrice[i];
        }
    }

    void setRetailPercentage(double percentage) {
        this->retailPercentage = percentage;
    }

    void setProductStartPrice(double *product, int n) {
        for (int i = 0; i < n; i++) {
            this->productPrice[i] = product[i];
        }
    }

    void setYear(std::string year) {
        this->year = year;
    }

    void setdifPB_W(double difPB) {
        this->difPB_W = difPB;
    }

    void setdifBTB_W(double difBTB) {
        this->difBTB_W = difBTB;
    }

    void createABCFormatting() {
        int f;
        std::ofstream MyFile("ABCPricing_" + year + ".txt");

        for (int i = 0; i < sizeof(Pickup_Wholesale_products) / sizeof(Pickup_Wholesale_products[0]); i++) { // Amount of products (rows)

            switch (i) {
            case 0: MyFile << "\n\nPremium Bark\n"; break;
            case 1: MyFile << "\n\n\nBark Blend\n"; break;
            case 2: MyFile << "\n\n\nNatures Blend\n"; break;
            case 3: MyFile << "\n\n\nBeauty Bark\n"; break;
            case 4: MyFile << "\n\n\nDyed Mulch\n"; break;
            case 5: MyFile << "\n\n\nSafe Cover\n"; break;
            case 6: MyFile << "\n\n\nClean Wood Chips\n"; break;
            case 7: MyFile << "\n\n\nWood Chips\n"; break;
            case 8: MyFile << "\n\n\nCompost\n"; break;
            case 9: MyFile << "\n\n\nLeaf Compost\n"; break;
            case 10: MyFile << "\n\n\nMushroom Soil\n"; break;
            case 11: MyFile << "\n\n\nRain Garden Mix\n"; break;
            case 12: MyFile << "\n\n\nScreened Blend\n"; break;
            case 13: MyFile << "\n\n\nScreened Topsoil\n"; break;
            case 14: MyFile << "\n\n\nTopsoil\n"; break;
            case 15: MyFile << "\n\n\nFill Dirt\n"; break;
            case 16: MyFile << "\n\n\nTopsoil Overs\n"; break;
        };

            MyFile << "\nWholesale:\n";
            // Wholesale Prices

            MyFile << "\nPicked Up Price:\n";
            // Picked Up Price
            for (int j = 0; j < sizeof(Pickup_Wholesale_products[0]) / sizeof(double); j++) { // Price per yardage (columns)
                MyFile << "," << 1 + (3 * j) << "*" << Pickup_Wholesale_products_Rounded[i][j] << "$";
            }

            MyFile << "\n\nDelivered Price:\n";
            // Delivered Price
            for (int p = 0; p < sizeof(deliveredPricing_Wholesale_Rounded[0]) / sizeof(double); p++) {

                if (i < 11) {
                    if (p < 19) f = p + 1; else f = ((p - 19) * 5) + 20;
                }
                else {
                    switch (p) { // 0 - 7 = 1 - 8, 8 = 9 - 15, 9 = 16 - 20,
                        default: f = p + 1; break;
                        case 13: f = 15; break;
                        case 14: f = 20; break;
                    }
                    if (p > 14) continue;
                }
                
                MyFile << "," << (f) << "*" << deliveredPricing_Wholesale_Rounded[i][p] << "$";
            }

            MyFile << "\n\nRetail:\n";
            // Retail Prices

            MyFile << "\nPicked Up Price:\n";
            // Picked Up Price
            for (int k = 0; k < sizeof(Pickup_Retail_products[0]) / sizeof(double); k++) { // Price per yardage (columns)
                switch (k) {
                case 0: f = 1; break;
                case 1: f = 2; break;
                case 4: f = 6; break;
                default: break;
                }
                MyFile << "," << f + k << "*" << Pickup_Retail_products_Rounded[i][k] << "$";
            }

            MyFile << "\n\nDelivered Prce:\n";
            // Delivered Price
            for (int p = 0; p < sizeof(deliveredPricing_Retail_Rounded[0]) / sizeof(double); p++) {
                
                if (i < 11) {
                    if (p < 19) f = p + 1; else f = ((p - 19) * 5) + 20;
                }
                else {
                    switch (p) { // 0-7 = 1-8, 8 = 9-15, 9 = 16-20,
                    default: f = p + 1; break;
                    case 13: f = 15; break;
                    case 14: f = 20; break;
                    }
                    if (p > 14) continue;
                }
                MyFile << "," << (f) << "*" << deliveredPricing_Retail_Rounded[i][p] << "$";
            }
        }

        // Delivery Price Mulch
        MyFile << "\n\nDelivery Price Mulch\n";
        for (int t = 0; t < sizeof(deliveredPricing) / sizeof(deliveredPricing[0]); t++) {
            if (t < 19) f = t + 1; else f = ((t - 19) * 5) + 20;
            MyFile << (f) << " = " << deliveredPricing[t] << ",  ";
        }

        // Delivery Price Soil
        MyFile << "\n\nDelivery Price Soil\n";
        for (int t = 0; t < sizeof(deliveredPricing_Soil) / sizeof(deliveredPricing_Soil[0]); t++) {
            // 0 - 7 = 1 - 8, 8 = 9 - 15, 9 = 16 - 20,
            switch (t) {
            default: f = t + 1; break;
            case 13: f = 15; break;
            case 14: f = 20; break;
            }
            MyFile << (f) << " = " << deliveredPricing_Soil[t] << ",  ";
        }

        /*
        MyFile << "\n\n";

        for (int y = 0; y < sizeof(deliveredPricing_Wholesale_Rounded) / sizeof(deliveredPricing_Wholesale_Rounded[0]); y++) {
            
            switch (y) {
            case 0: MyFile << "\n\nPremium Bark\n"; break;
            case 1: MyFile << "\n\n\nBark Blend\n"; break; 
            case 2: MyFile << "\n\n\nNatures Blend\n"; break;
            case 3: MyFile << "\n\n\nBeauty Bark\n"; break;
            case 4: MyFile << "\n\n\nDyed Mulch\n"; break;
            }

            for (int p = 0; p < sizeof(deliveredPricing_Wholesale_Rounded[0]) / sizeof(double); p++) {
                MyFile << (p + 1) << " = " << deliveredPricing_Wholesale_Rounded[y][p] << ", ";
            }

        }
        */

        MyFile.close();
    }

    void createTempPBFile() {
        std::ofstream TestPB("TestPB.txt");

        // Input Delivered Pricing Mulch
        TestPB << "DPM,";
        for (int k = 0; k < sizeof(deliveredPricing) / sizeof(deliveredPricing[0]); k++) {
            switch (k) {
            default: TestPB << deliveredPricing[k] << ","; break;
            case 16: case 17: case 18: case 22: case 24: break; // Removes 17-19, 35, 45
            }
        }

        // Input Delivered Pricing Soil
        TestPB << "DPS,";
        for (int b = 0; b < sizeof(deliveredPricing_Soil) / sizeof(deliveredPricing_Soil[0]); b++) {
            TestPB << deliveredPricing_Soil[b] << ",";
        }

        // Input Pricing of Delivered Products
        for (int i = 0; i < sizeof(deliveredPricing_Wholesale_Rounded) / sizeof(deliveredPricing_Wholesale_Rounded[0]); i++) {

            switch (i) {
            case 0: TestPB << "PB,"; break;
            case 1: TestPB << "BB,"; break;
            case 2: TestPB << "NB,"; break;
            case 3: TestPB << "BBT,"; break;
            case 4: TestPB << "BD,"; break;
            case 5: TestPB << "SC,"; break;
            case 6: TestPB << "CWC,"; break;
            case 7: TestPB << "WC,"; break;
            case 8: TestPB << "CP,"; break;
            case 9: TestPB << "LCP,"; break;
            case 10: TestPB << "MS,"; break;
            case 11: TestPB << "RGM,"; break;
            case 12: TestPB << "SB,"; break;
            case 13: TestPB << "ST,"; break;
            case 14: TestPB << "TS,"; break;
            case 15: TestPB << "FD,"; break;
            case 16: TestPB << "TO,"; break;
            };

            for (int p = 0; p < sizeof(deliveredPricing_Wholesale_Rounded[0]) / sizeof(double); p++) {

                if (i < 11) {
                    switch (p) {
                    default: TestPB << deliveredPricing_Wholesale_Rounded[i][p] << ","; break;
                    case 16: case 17: case 18: case 22: case 24: break; // Removes 17-19, 35, 45
                    }
                }
                else {
                    if (p < 15){
                        TestPB << deliveredPricing_Wholesale_Rounded[i][p] << ",";
                    }
                }
                
            }
        }

        TestPB.close();
    }
};


