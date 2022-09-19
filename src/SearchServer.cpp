#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include "../include/SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    std::vector<std::vector<RelativeIndex>> relativeIndexVec;

    for (auto queryOne : queries_input) {

        // removing punctuation marks
        queryOne.erase(std::remove_if(queryOne.begin(), queryOne.end(),
                                      [](unsigned char x){return std::ispunct(x);}),
                       queryOne.end());

        // converting a string to lowercase
        std::transform(queryOne.begin(), queryOne.end(), queryOne.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });


        std::map<std::string,size_t> queryWordsMap;
        std::vector<std::pair<std::string,size_t>> queryWordsVec;

        std::istringstream stringStream(queryOne);
        std::string word;

        while(std::getline(stringStream, word, ' ')) {
            auto freqWord = _index.GetWordCount(word);
            if (freqWord.empty()) {
                //todo: А есть смысл дальше перебирать, если по данному запросу результат будет пустой? Пока оставим так.
                queryWordsMap.insert({word, 0});
            } else {
                size_t countInAllDoc = 0;
                for (auto docId : freqWord) {
                    countInAllDoc += docId.count;
                }

                queryWordsMap.insert({word, countInAllDoc});
            }

        }

        // copy map in vector
        queryWordsVec.resize(queryWordsMap.size());
        std::copy(queryWordsMap.begin(), queryWordsMap.end(), queryWordsVec.begin());

        // sorting by rarity of words
        std::sort(queryWordsVec.begin(), queryWordsVec.end(), [](const std::pair<std::string,int> &left, const std::pair<std::string,int> &right) {
            return left.second < right.second;
        });

//print test
/*        for (auto wordTest : queryWordsVec) {
            std::cout << wordTest.first << " count = " << wordTest.second << std::endl;
        }
        std::cout << "--------------" << std::endl;*/


        relativeIndexVec.push_back(SearchRelativeIndex(queryWordsVec));
    }

// test print
    for (const auto& r : relativeIndexVec) {
        for (auto re : r) {
            std::cout << "relativeIndexVec docId " << re.doc_id << " rank "<< re.rank << std::endl;
        }
        std::cout << "------------" << std::endl;
    }
    std::cout << "======++++++++++" << std::endl;

    return relativeIndexVec;
}


std::vector<RelativeIndex> SearchServer::SearchRelativeIndex(std::vector<std::pair<std::string,size_t>> &queryWordsVec) {

    std::vector<size_t> docIdVec;
    std::vector<size_t> tmpDocIdVec;


    std::vector<RelativeIndex> relativeIndex;

    if (queryWordsVec[0].second != 0) {
        for (auto wordCount: _index.GetWordCount(queryWordsVec[0].first)) {
            docIdVec.push_back(wordCount.doc_id);
        }

        for (int i = 1; i < queryWordsVec.size(); i++) {
            for (auto wordCount: _index.GetWordCount(queryWordsVec[i].first)) {
                if (std::find(docIdVec.begin(), docIdVec.end(), wordCount.doc_id) != docIdVec.end()) {
                    tmpDocIdVec.push_back(wordCount.doc_id);
                }
            }

            docIdVec.clear();
            docIdVec.resize(tmpDocIdVec.size());
            std::copy(tmpDocIdVec.begin(), tmpDocIdVec.end(), docIdVec.begin());
            tmpDocIdVec.clear();
        }

// test print
        /*for (auto docId : docIdVec) {
            std::cout << "unique docId: " << docId << std::endl;
        }
        std::cout << "++++++++++" << std::endl;*/

        //Absolute relevance
        size_t maxAbsoluteRelevance = 0;
        std::vector<size_t> absoluteRelevance;
        absoluteRelevance.resize(docIdVec.size());
        for (const auto& queryWord : queryWordsVec) {
            for (auto wordCount : _index.GetWordCount(queryWord.first)) {
                auto itDocId = std::find(docIdVec.begin(), docIdVec.end(), wordCount.doc_id);
                if (itDocId != docIdVec.end()) {

                    int index;
                    index = std::distance(docIdVec.begin(), itDocId);
                    absoluteRelevance[index] += wordCount.count;

                    if (absoluteRelevance[index] > maxAbsoluteRelevance) {
                        maxAbsoluteRelevance = absoluteRelevance[index];
                    }
                }
            }
        }
// test print
/*            for (auto ab : absoluteRelevance) {
                std::cout << "absoluteRelevance " << ab << std::endl;
            }
            std::cout << "maxAbsoluteRelevance " << maxAbsoluteRelevance << std::endl;
            std::cout << "++++++++++" << std::endl;*/


        //Relative relevance

        for (int i = 0; i < docIdVec.size(); i++) {
            float rank = (float) absoluteRelevance[i] / (float) maxAbsoluteRelevance;
            relativeIndex.push_back({docIdVec[i], rank});
        }

        std::sort(relativeIndex.begin(),relativeIndex.end(), [](const RelativeIndex &left, const RelativeIndex &right) {
            return left.rank > right.rank;
        });
    }

    return relativeIndex;
}