#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <stdexcept>
#include <string.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

const int permSize = 10;

void printPerm(int* perm, int curr_index) {
    for(int r = 0; r < curr_index; ++r) {
        std::cout << perm[r] << " ";
    }
    std::cout << std::endl;
}


// curr_index is the index of the item that is going to be appended
bool backtrack(int* perm, int curr_index, int curr_sum, const int* const input, int K) { 
    if(curr_index > permSize) 
        return false;

    //printPerm(perm, curr_index);

    // don't build the whole tree. cut off as soon as we get bigger than K
    if(curr_sum > K)
        return false;

    if(curr_index == permSize) {
        // GOT THE SOLUTION
        printPerm(perm, curr_index);
        return true;
    }

    for(int j = 0; j < 10; ++j) {

        // TODO. this is shitty
        bool ok = true;
        for(int b = 0; b < curr_index; ++b) {
            if(perm[b] == j) {
                ok = false;
                break;
            }
        }
        if(!ok) {
            continue;
        }

        perm[curr_index] = j;
        int sum_after_appending = curr_sum + j * input[curr_index];
        if(backtrack(perm, curr_index + 1, sum_after_appending, input, K))
            return true;
    } 

    return false;
}

/////////////////////////////////////////////////////

void readTestInput(int* input, int& K) {

    std::string currLine;
    std::getline(std::cin, currLine);
    stringstream stream(currLine);
    for(int i = 0; i < permSize; ++i) {
        if(!(stream >> input[i])) {
            throw std::runtime_error("fuck: invalid input"); 
        }
    }

    std::getline(std::cin, currLine);
    K = std::stoi(currLine);
}


int main(int argc, char* argv[]) {

    unsigned testsCount;

    std::string currLine;
    std::getline(std::cin, currLine);
    testsCount = std::stoi(currLine);
    if(testsCount == 0)
        return 0;

    for(int i = 0; i < testsCount; i++) {
        int input[permSize];
        int K;
        readTestInput(input, K);

        int perm[permSize + 1];
        if(!backtrack(perm, 0, 0, input, K)) 
            std::cout << "-1" << std::endl;
    }

    return 0;
}
