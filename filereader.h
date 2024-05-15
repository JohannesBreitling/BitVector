#include <iostream>
#include <fstream>
#include <vector>
#include<sstream>

using namespace::std;

// TODO Möglicherweise ist 64 Bit besser wegen Padding
enum RSQuery : char {
    ACCESS = 'A', RANK = 'R', SELECT = 'S'
};

struct RSOperation {
    RSQuery query;
    uint64_t arg1;
    uint64_t arg2;
};

struct RSStringInput {
    string bv;
    vector<RSOperation> operations;
};

string operationToString(RSOperation op) {
    string result;
    
    switch (op.query) {
        case ACCESS:
            result = "ACESS<" + to_string(op.arg1) + ">";
            break;
        case RANK:
            result = "RANK< " + to_string(op.arg1) + ", " + to_string(op.arg2) + ">";
            break;
        case SELECT:
            result = "SELECT<" + to_string(op.arg1) + ", " + to_string(op.arg2) + ">";
            break;
        default:
            result = "error in operationToString method";
    }

    return result;
}

RSOperation getOperation(string s) {
    RSOperation result;

    stringstream words(s);

    string operation;
    if (!(words >> operation)) {
        throw runtime_error("Empty Line in input file");
    }

    if (!(operation == "access" || operation == "rank" || operation == "select")) {
        throw runtime_error("Illegal Operation: " + operation);
    }

    string arg1;
    if (!(words >> arg1)) {
        throw runtime_error("First Argument Missing");
    }
    result.arg1 = stoi(arg1);

    string arg2;
    if (operation != "access") {
        if (!(words >> arg2)) {
            throw runtime_error("Second Argument Missing");
        }
        result.arg2 = stoi(arg2);
    }

    if (words >> operation) {
        throw runtime_error("Additional argument found: " + operation);
    }
    
    if (operation == "access") {
        result.query = ACCESS;
        return result;
    }

    if (operation == "rank") {
        result.query = RANK;
        return result;
    }

    result.query = SELECT;
    return result;
}

RSStringInput *readRSInput(string filepath) {
    RSStringInput *result = new RSStringInput;

    ifstream InputFile(filepath);

    string queryNumberString;

    if (!getline(InputFile, queryNumberString)) {
        throw runtime_error("Input File is Empty");
    }

    uint64_t queryNumber = stoi(queryNumberString);

    if (!getline(InputFile, (*result).bv)) {
        throw runtime_error("Bit Vector missing in Input File");
    }

    string currentLine;
    for (uint64_t i = 0; i < queryNumber; i++) {
        getline(InputFile, currentLine);
        RSOperation operation = getOperation(currentLine);
        (*result).operations.push_back(operation);
    }

    return result;
}