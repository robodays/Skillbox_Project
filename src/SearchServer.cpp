//
// Created by Zver on 20.04.2022.
//

#include "SearchServer.h"
#include <algorithm>
#include <sstream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    for (int i = 0; i = queries_input.size(); i++) {

        std::string query_one = queries_input[i];

        //removing punctuation marks
        query_one.erase(std::remove_if(query_one.begin(), query_one.end(),
                                      [](unsigned char x){return std::ispunct(x);}),
                        query_one.end());

        //Converting a string to lowercase
        std::transform(query_one.begin(), query_one.end(), query_one.begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });

        std::map<std::string,size_t> queryMap;

        std::istringstream stringStream(query_one);
        std::string word;

        while(std::getline(stringStream, word, ' ')) {

            if (queryMap.find(word) == queryMap.end()) {
                queryMap.insert({word, 1});
            } else {
                queryMap[word]++;
            }
        }





    }

    return std::vector<std::vector<RelativeIndex>>();
}
