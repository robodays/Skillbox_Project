#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <thread>
#include <mutex>


#include "../include/InvertedIndex.h"
//#include "InvertedIndex.h"


void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs) {
    std::vector<std::thread> threads;
    threads.reserve(inputDocs.size());
    for (int i = 0; i < inputDocs.size(); i++) {

        threads.emplace_back(&InvertedIndex::UpdateDocumentBaseOneFile, this, inputDocs[i], i);

/*

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
                auto itDoc_id = std::find_if(freqDictionary[word].begin(), freqDictionary[word].end(),[i](Entry const& e )
                {
                    return e.doc_id == i;
                });

                if (itDoc_id == freqDictionary[word].end()) {
                    freqDictionary[word].push_back({(size_t) i, 1});
                } else {
                    itDoc_id->count++;
                }
            }
        }
*/

    }


    for (auto & thread : threads) {
        thread.join();
    }

    //Test print dictionary
    for (const auto& dict : freqDictionary) {
        std::cout << dict.first << " = ";
        for(auto second : dict.second) {
            std::cout << "{" << second.doc_id << "," << second.count << "} ";
        }
        std::cout << std::endl;
    }

}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    auto wordCount = freqDictionary.find(word);
    if (wordCount != freqDictionary.end()) {
        return wordCount->second;
    }
    return {{}};
}

void InvertedIndex::UpdateDocumentBaseOneFile(std::string inputDoc, size_t docId) {

//    std::this_thread::sleep_for(std::chrono::seconds(5));

    //removing punctuation marks
    inputDoc.erase(std::remove_if(inputDoc.begin(), inputDoc.end(),
                                      [](unsigned char x){return std::ispunct(x);}),
                       inputDoc.end());

    //Converting a string to lowercase
    std::transform(inputDoc.begin(), inputDoc.end(), inputDoc.begin(),
                   [](unsigned char c) -> unsigned char { return std::tolower(c); });


    std::istringstream stringStream(inputDoc);
    std::string word;

    while(std::getline(stringStream, word, ' ')) {

        if (freqDictionary.find(word) == freqDictionary.end()) {
            std::vector<Entry> vec;
            Entry entry = {docId, 1};
            vec.push_back(entry);

            freqDictionary.insert({word, vec});
        } else {
            auto itDoc_id = std::find_if(freqDictionary[word].begin(), freqDictionary[word].end(),[docId](Entry const& e )
            {
                return e.doc_id == docId;
            });

            if (itDoc_id == freqDictionary[word].end()) {
                freqDictionary[word].push_back({(size_t) docId, 1});
            } else {
                itDoc_id->count++;
            }
        }
    }
}

std::map<std::string, std::vector<Entry>> InvertedIndex::GetFreqDictionary() {
    return freqDictionary;
}
