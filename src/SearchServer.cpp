#include "SearchServer.h"
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    for (int i = 0; i = queries_input.size(); i++) {

        std::string query_one = queries_input[i];


        //removing punctuation marks
        query_one.erase(std::remove_if(query_one.begin(), query_one.end(),
                                      [](unsigned char x){return std::ispunct(x);}),
                        query_one.end());



/*
        //Converting a string to lowercase
        std::transform(query_one.begin(), query_one.end(), query_one.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });

*/







        std::map<std::string,size_t> queryWordsMap;

        std::istringstream stringStream(query_one);
        std::string word;

        while(std::getline(stringStream, word, ' ')) {
            std::cout << "WSearch = " << word << std::endl;
            //std::cout << "search = " << word << std::endl;
            /* if (queryWordsMap.find(word) == queryWordsMap.end()) {
                 queryWordsMap.insert({word, 1});
             } else {
                 queryWordsMap[word]++;
            }*/
        }

/*        std::vector<std::pair<std::string,size_t>> queryWordsVec(queryWordsMap.begin(),queryWordsMap.end());

        for (auto word : queryWordsVec) {
            std::cout << word.first << " count = " << word.second << std::endl;
        }*/





    }
    std::vector<std::vector<RelativeIndex>> returnData;
   // return std::vector<std::vector<RelativeIndex>>();
    return returnData;
}
