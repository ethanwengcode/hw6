#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5]{0,0,0,0,0}; 
        int groupNum = 4;
        size_t len = k.length();
        int index = static_cast<int>(len);

        // start at the end of string; groups of 6
        while( index > 0 && groupNum >= 0) {
            int x = std::max(0, index-6);
            unsigned long long base = 1;
            unsigned long long val = 0;

            // convert from base-36 to decimal
            for(int i = index -1; i >= x; i--) {
                val += letterDigitToNumber(k[i]) * base;
                base *= 36;
            }

            w[groupNum] = val; // store value
            groupNum--; // next groupNum
            index -= 6; 
        }

        // hash 
        unsigned long long hashVal = 0;
        for(int i = 0; i <5; i++) {
            hashVal += rValues[i] * w[i];
        }
        return static_cast<HASH_INDEX_T>(hashVal); 

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(std::isdigit(letter)) { // digit
            return static_cast<HASH_INDEX_T>(letter - '0' + 26);
        }
        else if(std::isalpha(letter)) { // letter
            return static_cast<HASH_INDEX_T>(std::tolower(letter) - 'a');
        }
        return 0; // invalid input
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
