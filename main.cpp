#include<string>
#include<format>
#include<chrono>
#include<cassert>
#include "bitvector.h"
#include "filereader.h"

using namespace std;

vector<uint64_t> computeOutputs(BitVector bv, vector<RSOperation> operations) {
    vector<uint64_t> result;

    for (vector<RSOperation>::iterator it = operations.begin(); it != operations.end(); it++) {
        cout << "Current Operation " << operationToString(*it) << endl;

        uint64_t currentResult;
        switch ((*it).query) {
            case ACCESS:
                currentResult = accessBitVetor(bv, (*it).arg1);
                break;
            case RANK:
                currentResult = scanRank(bv, (*it).arg1, (*it).arg2);
                break;
            case SELECT:
                currentResult = scanSelect(bv, (*it).arg1, (*it).arg2);
                break;
            default:
                currentResult = -1;
        }

        result.push_back(currentResult);
    }

    



    return result;
}

int main(int argc, char *argv[]) {

    // Read file names from programm parameters
    assert(argc == 3 && "Wrong number of arguemnts.");
    string inputfile, outputfile;
    inputfile = argv[1];
    outputfile = argv[2];

    // Read input from file into stringarray
    RSStringInput *input = readRSInput("input.txt");

    // Construct the bitvector from the input string
    BitVector bv = constructFromString((*input).bv);

    // TODO Compute the results
    vector<uint64_t> result = computeOutputs(bv, (*input).operations);

    for (vector<uint64_t>::iterator it = result.begin(); it != result.end(); it++) {
        cout << "RESULT : " << *it << endl;
    }

    // TODO Output the results






    //string input = "1000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    //string input = "10000000000";
    //BitVector v = constructFromString(input);

    //uint64_t bit = accessBitVetor(v, 2);
    //cout << "Access " << bit << endl;

    // RankSelectInput input;

    // input = readRSInputFromFile("input.txt");
    

    return 0;
}