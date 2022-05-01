#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs) {
    for (int i = 0; i < inputDocs.size(); i++) {
 //       for (auto inputDoc : inputDocs) {

        //removing punctuation marks
        inputDocs[i].erase(std::remove_if(inputDocs[i].begin(), inputDocs[i].end(),
                                      [](unsigned char x){return std::ispunct(x);}),
                           inputDocs[i].end());

        //Converting a string to lowercase
        std::transform(inputDocs[i].begin(), inputDocs[i].end(), inputDocs[i].begin(),
                       [](unsigned char c) -> unsigned char { return std::tolower(c); });


        std::istringstream ss(inputDocs[i]);
        std::string word;

        while(std::getline(ss, word, ' ')) {

            if (freqDictionary.find(word) == freqDictionary.end()) {
                std::vector<Entry> vec;
                Entry entry = {(size_t) i, 1};
                vec.push_back(entry);
                freqDictionary.insert({word, vec});
            } else {
                //Entry entry = {(size_t) i, 1};
                auto itDoc_id = std::find_if(freqDictionary[word].begin(), freqDictionary[word].end(),[i](Entry const& e )
                {
                    return e.doc_id == i;
                });
                if (itDoc_id == freqDictionary[word].end()) {
                    freqDictionary[word].push_back({(size_t) i, 1});
                } else {
                    //freqDictionary[word][i].doc_id = i;
                    //freqDictionary[word][i].count++;
                    //int id = (int)(*itDoc_id).;
                    //freqDictionary[word][id].count;
                    (*itDoc_id).count++;
                }

            }
            //std::cout << word << std::endl;
        }

        std::vector<std::string> words;
        words.push_back(word);

/*        std::ifstream docFile;

        docFile.open(inputDoc);

        if (docFile.is_open()) {
            std::cout << inputDoc << " open!";
        } else {
            std::cout << inputDoc << " not open!";
        }

        std::vector<std::string> words;*/
/*        std::string word;
        while (!docFile.eof()) {
            docFile >> word;
            if (freqDictionary.find(word) == freqDictionary.end()) {
                std::vector vec =
                Entry entry;
                entry =
                freqDictionary.insert(word,)
            }
           words.push_back(word);
        }
    */

/*
*/



    }

    for (auto dict : freqDictionary) {
        std::cout << dict.first << " = ";
        for(auto second : dict.second) {
            std::cout << "{" << second.doc_id << "," << second.count << "} ";
        }
        std::cout << std::endl;
    }

}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    return std::vector<Entry>();
}
