#pragma once
class clalculatePrices
{
    double calculater(double product) {

        static double r[19];

        for (int i = 0; i > sizeof(r); i++) {
            r[i] = product + i;
        }

        return *r;
    }
};

