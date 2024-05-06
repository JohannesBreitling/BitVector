#include<string>
#include<format>
#include "bitvector.h"

using namespace std;

const uint64_t ONE = 1;

BitVector constructFromString(string data) {
    BitVector result;

    
    uint64_t currentWord = 0;

    size_t i = 0;

    while (i < data.size()) {
        switch (data[i]) {
            case '0':
                currentWord = currentWord << 1;
                break;
            
            case '1':
                currentWord = currentWord << 1;
                currentWord = currentWord | ONE;
                break;
            
            default:
                string m = "Character ";
                m.push_back(data[i]);
                m += " not legal.";
                throw runtime_error(m);
        }

        if (i % 64 == 63) {
            cout << currentWord << endl;
            result.data.push_back(currentWord);
            currentWord = 0;
        }


        i++;
    }

    if (i % 64 == 0) {
        return result;
    }

    currentWord = currentWord << (64 - (i % 64));
    result.data.push_back(currentWord);

    return result;
}

int64_t accessBitVetor(BitVector v, size_t index) {
    
    size_t wordNumber = index / 64;
    cout << "WN " << wordNumber << endl;

    size_t offset = index % 64;
    cout << "OS " << wordNumber << endl;

    uint64_t word = v.data[wordNumber];
    cout << "WORD " << word << endl;

    uint64_t shifted = word >> (63 - offset);
    cout << "SHIFTED " << shifted << endl;

    return shifted & ONE;
}

int main() {
    //string input = "1000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    string input = "10000000000";
    BitVector v = constructFromString(input);

    uint64_t bit = accessBitVetor(v, 2);
    cout << "Access " << bit << endl;

    return 0;
}