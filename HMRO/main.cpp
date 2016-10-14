#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <stdexcept>

using namespace std;

struct TestData {
    unsigned recrCountBef;
    unsigned recrCountAft;
    unsigned mroDownCount;
    unordered_map<string, string> recrutesBefore;
    unordered_map<string, string> mroTransf;

    void clear() {
        recrutesBefore.clear();
        mroTransf.clear();
        recrCountBef = 0;
        recrCountAft = 0;
        mroDownCount = 0;
    }
};

unordered_map<string, string> chainCache;
const string& unwindEncodingChain(const TestData& testData, const string& mor) {
    auto it = chainCache.find(mor);
    if(it != chainCache.end()) {
        return it->second; 
    } else { 
        string res = mor;
        auto it = testData.mroTransf.find(res);
        while(it != testData.mroTransf.end()) {
            res = it->second;
            it = testData.mroTransf.find(res);
        }

        chainCache[mor] = res;
        return chainCache[mor];
    } 
}

int main(int argc, char* argv[]) {

    unsigned testsCount;

    std::string currLine;
    std::getline(std::cin, currLine);
    testsCount = std::stoi(currLine);
    if(testsCount == 0)
        return 0;

    TestData test;
    for(int i = 0; i < testsCount; i++) {
        test.clear();
        chainCache.clear();

        // recruits before
        std::getline(std::cin, currLine);
        test.recrCountBef = std::stoi(currLine);
        for(int j = 0; j < test.recrCountBef; j++) {
            std::getline(std::cin, currLine);
            size_t pos = currLine.find_first_of(" ");
            if (pos != std::string::npos) {
                test.recrutesBefore[currLine.substr(0, pos)] = currLine.substr(pos + 1);
            } else {
                throw std::runtime_error("fuck"); 
            };
        }

        // new mro encoding
        std::getline(std::cin, currLine);
        int mroEncCount = std::stoi(currLine);
        for(int j = 0; j < mroEncCount; j++) {
            std::getline(std::cin, currLine);
            size_t pos = currLine.find_first_of(" ");
            if (pos != std::string::npos) {
                test.mroTransf[currLine.substr(0, pos)] = currLine.substr(pos + 1);
            } else {
                throw std::runtime_error("fuck"); 
            };
        }

        // recruits after
        std::getline(std::cin, currLine);
        test.recrCountAft = std::stoi(currLine);
        for(int j = 0; j < test.recrCountAft; j++) {
            std::getline(std::cin, currLine);
            const string& currRecrut = currLine;
            const auto& it = test.recrutesBefore.find(currRecrut);
            if(it == test.recrutesBefore.end()) {
                throw std::runtime_error("fuck"); 
            } else {
                const string& originalMOR = it->second;
                std::cout << currRecrut << " " << unwindEncodingChain(test, originalMOR) << std::endl;
            }
        }

        std::getline(std::cin, currLine);
        std::cout << std::endl;
    }

    return 0;
}
