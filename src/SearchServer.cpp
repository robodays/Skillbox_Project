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

        std::vector<std::pair<std::string,size_t>> queryWordsVec;

        std::istringstream stringStream(queryOne);
        std::string word;

        while(std::getline(stringStream, word, ' ')) {
            //auto freqDictionary = _index.GetFreqDictionary();
            auto freqWord = _index.GetWordCount(word);
            if (freqWord.empty()) {
//todo
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
        queryWordsVec.resize(queryWordsMap.size());
        std::copy(queryWordsMap.begin(), queryWordsMap.end(), queryWordsVec.begin());

        std::sort(queryWordsVec.begin(), queryWordsVec.end(), [](const std::pair<std::string,int> &left, const std::pair<std::string,int> &right) {
            return left.second < right.second;
        });

//print test
        for (auto wordTest : queryWordsVec) {
            std::cout << wordTest.first << " count = " << wordTest.second << std::endl;
        }
        std::cout << "--------------" << std::endl;


        std::vector<size_t> docIdVec;
        std::vector<size_t> rareDocIdVec;
        if (queryWordsVec[0].second != 0) {
            for (auto wordCount: _index.GetWordCount(queryWordsVec[0].first)) {
                docIdVec.push_back(wordCount.doc_id);
            }
            for (int i = 1; i < queryWordsVec.size(); i++) {
                rareDocIdVec.clear();

                for (auto wordCount: _index.GetWordCount(queryWordsVec[i].first)) {
                    if (std::find(docIdVec.begin(), docIdVec.end(), wordCount.doc_id) != docIdVec.end()) {
                        rareDocIdVec.push_back(wordCount.doc_id);
                    }
                }

                docIdVec.clear();
                docIdVec.resize(rareDocIdVec.size());
                std::copy(rareDocIdVec.begin(), rareDocIdVec.end(), docIdVec.begin());
            }
        } else {
//todo            // не найдено
        }
// test print
        for (auto docId : rareDocIdVec) {
            std::cout << "unique docId: " << docId << std::endl;
        }
        std::cout << "++++++++++" << std::endl;

        //Absolute relevance
        size_t maxAbsoluteRelevance = 0;
        std::vector<size_t> absoluteRelevance;
        absoluteRelevance.resize(rareDocIdVec.size());
        for (const auto& queryWord : queryWordsVec) {
            for (auto wordCount : _index.GetWordCount(queryWord.first)) {
                auto itDocId = std::find(rareDocIdVec.begin(), rareDocIdVec.end(), wordCount.doc_id);
                if (itDocId != rareDocIdVec.end()) {

                    int index;
                    index = std::distance(rareDocIdVec.begin(), itDocId);
                    absoluteRelevance[index] += wordCount.count;

                    if (absoluteRelevance[index] > maxAbsoluteRelevance) {
                        maxAbsoluteRelevance = absoluteRelevance[index];
                    }
                }
            }


        }
// test print
        for (auto ab : absoluteRelevance) {
            std::cout << "absoluteRelevance " << ab << std::endl;
        }
        std::cout << "maxAbsoluteRelevance " << maxAbsoluteRelevance << std::endl;
        std::cout << "++++++++++" << std::endl;


        //Relative relevance


    }





    std::vector<std::vector<RelativeIndex>> returnData;
   // return std::vector<std::vector<RelativeIndex>>();
    return returnData;
}
