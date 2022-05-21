#include "SearchServer.h"
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    for (int i = 0; i < queries_input.size(); i++) {

        std::string queryOne = queries_input[i];

        //removing punctuation marks
        queryOne.erase(std::remove_if(queryOne.begin(), queryOne.end(),
                                      [](unsigned char x){return std::ispunct(x);}),
                       queryOne.end());

        //Converting a string to lowercase
        std::transform(queryOne.begin(), queryOne.end(), queryOne.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });


        std::map<std::string,size_t> queryWordsMap;

        std::istringstream stringStream(queryOne);
        std::string word;

        while(std::getline(stringStream, word, ' ')) {
            auto freqDictionary = _index.GetFreqDictionary();
            auto freqWord = _index.GetWordCount(word);
            if (freqWord.empty()) {
                queryWordsMap.insert({word, 0});
            } else {
                size_t countInAllDoc = 0;
                for (auto docId : freqWord) {
                    countInAllDoc += docId.count;
                }

                queryWordsMap.insert({word, countInAllDoc});
            }
/*            if (freqDictionary.find(word) == freqDictionary.end()) {
                queryWordsMap.insert({word, 0});
            } else {

                //queryWordsMap.insert({word, _index.GetFreqDictionary().find(word)->second.});;
            }*/
        }

        std::vector<std::pair<std::string,size_t>> queryWordsVec(queryWordsMap.begin(),queryWordsMap.end());

        std::sort(queryWordsVec.begin(), queryWordsVec.end(), [](const std::pair<std::string,int> &left, const std::pair<std::string,int> &right) {
            return left.second < right.second;
        });

        for (auto wordTest : queryWordsVec) {
            std::cout << wordTest.first << " count = " << wordTest.second << std::endl;
        }
        std::cout << "--------------" << std::endl;





    }
    std::vector<std::vector<RelativeIndex>> returnData;
   // return std::vector<std::vector<RelativeIndex>>();
    return returnData;
}
