#include <iostream>
#include <vector>

#include "ConverterJSON.h"
#include "SearchServer.h"
#include "InvertedIndex.h"


int main() {

    ConverterJSON converterJson;

    std::vector<std::string> textDocuments = converterJson.GetTextDocuments();
    int responsesLimit = converterJson.GetResponsesLimit();
    std::cout << "max_responses: " << responsesLimit << std::endl;

    InvertedIndex invertedIndex;
    invertedIndex.UpdateDocumentBase(textDocuments);

    SearchServer searchServer(invertedIndex);
    auto relevantAnswers = searchServer.search(converterJson.GetRequests());

    converterJson.putAnswers(relevantAnswers);

    std::cout << "END" << std::endl;

}

