#include <vector>
#include <string>
#include <iostream>

using namespace std;

const uint64_t ONE = 1;

struct BitVector {
    uint64_t length;
    vector<uint64_t> data;
};

int64_t accessBitVetor(BitVector v, size_t index) {
    size_t wordNumber = index / 64;
    size_t offset = index % 64;

    uint64_t word = v.data[wordNumber];

    uint64_t shifted = word >> (63 - offset);

    return shifted & ONE;
};

BitVector constructFromString(string data) {
    BitVector result;
    uint64_t currentWord = 0;
    result.length = 0;

    size_t i = 0;

    while (i < data.size()) {
        result.length++;
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

uint64_t scanRank(BitVector bv, uint64_t b, uint64_t i) {
    uint64_t count = 0;
    
    for (uint64_t j = 0; j < i; j++) {
        if (accessBitVetor(bv, j) == b) {
            count++;
        }
    }

    return count;
}

uint64_t scanSelect(BitVector bv, uint64_t b, uint64_t i) {
    uint64_t count = i;
    
    for (uint64_t j = 0; j < bv.length; j++) {
        if (accessBitVetor(bv, j) == b) {
            count--;
        }

        if (count == 0) {
            return j;
        }
    }

    return count;
}
