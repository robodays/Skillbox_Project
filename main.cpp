#include <iostream>
#include <vector>

#include "ConverterJSON.h"
#include "SearchServer.h"
#include "InvertedIndex.h"


int main() {

    ConverterJSON converterJson;
    std::vector<std::string> textDocuments = converterJson.GetTextDocuments(); // getting the contents of the files

    InvertedIndex invertedIndex;
    invertedIndex.UpdateDocumentBase(textDocuments); // filling in the database

    SearchServer searchServer(invertedIndex);
    auto relevantAnswers = searchServer.search(converterJson.GetRequests()); // search results

    converterJson.putAnswers(relevantAnswers); // putting the results in JSON file

    std::cout << "END" << std::endl;

}

