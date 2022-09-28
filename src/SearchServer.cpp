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


        relativeIndexVec.push_back(searchRelativeIndex(queryWordsVec));
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


std::vector<RelativeIndex> SearchServer::searchRelativeIndex(std::vector<std::pair<std::string,size_t>> &queryWordsVec) {

    std::vector<RelativeIndex> relativeIndex;

    //Absolute relevance
    size_t maxAbsoluteRelevance = 0;
    std::map<size_t,size_t> absoluteRelevance;
    for (const auto& queryWord : queryWordsVec) {
        for (auto wordCount : _index.GetWordCount(queryWord.first)) {
            if (absoluteRelevance.find(wordCount.doc_id) == absoluteRelevance.end()) {
                absoluteRelevance[wordCount.doc_id] = 0;
            }

            absoluteRelevance[wordCount.doc_id] += wordCount.count;

            if (absoluteRelevance[wordCount.doc_id] > maxAbsoluteRelevance) {
                maxAbsoluteRelevance = absoluteRelevance[wordCount.doc_id];

            }
        }
    }

    //Relative relevance
    std::multimap<size_t,size_t> absoluteRelevanceMultimap;
    for(auto & it : absoluteRelevance) {
        absoluteRelevanceMultimap.insert(std::pair<size_t,size_t> (it.second, it.first));
    }

    for(auto & it : absoluteRelevanceMultimap) {
        float rank = (float) it.first / (float) maxAbsoluteRelevance;
        relativeIndex.push_back({it.second, rank});
    }

    std::sort(relativeIndex.begin(),relativeIndex.end(), [](const RelativeIndex &left, const RelativeIndex &right) {
        return ((left.rank > right.rank) || (left.doc_id < right.doc_id));
    });

    return relativeIndex;
}
