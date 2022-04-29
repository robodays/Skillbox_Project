#include <iostream>
#include <fstream>

#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs) {
    for (auto inputDoc : inputDocs) {

        std::ifstream docFile;

        docFile.open(inputDoc);

        if (docFile.is_open()) {
            std::cout << inputDoc << " open!";
        } else {
            std::cout << inputDoc << " not open!";
        }

        std::vector<std::string> words;
        std::string word;
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
/*

        for (std::string oneWord : words) {
            std::cout << oneWord << std::endl;
        }
*/

    }


}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    return std::vector<Entry>();
}
