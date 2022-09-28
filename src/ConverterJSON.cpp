#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "ConverterJSON.h"
#include "config.h"

std::vector<std::string> ConverterJSON::GetTextDocuments() {

    std::ifstream fileConfigJSON;
    fileConfigJSON.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        fileConfigJSON.open("../config.json");
        std::cout << "File config.json open!" << std::endl;
    } catch (std::exception& e) {
        //std::cout << e.what() << std::endl;
        std::cout << "ERROR: config file is missing!" << std::endl;
        std::cout << "Search Engine is closed!" << std::endl;
    }

    nlohmann::json configData;
    fileConfigJSON >> configData;
    fileConfigJSON.close();

    try {
        configData.at("config");
        std::cout << "File config.json correct!" << std::endl;
    } catch (nlohmann::json::exception& e) {
        //std::cout << e.what() << std::endl;
        std::cout << "ERROR: config file is empty!" << std::endl;
        std::cout << "Search Engine is closed!" << std::endl;
        exit(1);
    }

    std::cout << "Starting " << configData["config"]["name"] << std::endl;

    if (configData["config"]["version"] == PROJECT_VER) {
        std::cout << "Version: " << PROJECT_VER << std::endl;
    } else {
        std::cout << "ERROR: config.json has incorrect file version" << std::endl;
        std::cout << "Version engine: " << PROJECT_VER << " does not match with version config.json: " << configData["config"]["version"] << std::endl;
        exit(1);
    }

    std::vector<std::string> textDocuments;

    for (auto & itFiles : configData["files"]) {
        std::string pathFile = itFiles;
        std::ifstream docFile(pathFile);
        if (docFile.is_open()) {
            std::cout << pathFile << " open!" << std::endl;

            std::string str, str2;

            while (std::getline(docFile, str2)) {
                str += str2;
            }
            textDocuments.push_back(str);
        } else {
            std::cout << pathFile << " not open!" << std::endl;
        }

    }

    return textDocuments;
}

int ConverterJSON::GetResponsesLimit() {

    std::ifstream fileConfigJSON("../config.json");

    nlohmann::json configData;

    fileConfigJSON >> configData;
    fileConfigJSON.close();

    try {
        configData["config"].at("max_responses");
        return configData["config"]["max_responses"];
    } catch (nlohmann::json::exception& e) {
        return 5;
    }
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream fileRequestsJSON;
    fileRequestsJSON.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // open requests.json
    try {
        fileRequestsJSON.open("../requests.json");
        std::cout << "File requests.json open!" << std::endl;
    } catch (std::exception& e) {
        std::cout << "ERROR: config file is missing!" << std::endl;
        std::cout << "Search Engine is closed!" << std::endl;
    }

    nlohmann::json requestsData;

    fileRequestsJSON >> requestsData;

    fileRequestsJSON.close();

    try {
        requestsData.at("requests");
        std::cout << "File requests.json correct!" << std::endl;
    } catch (nlohmann::json::exception& e) {
        std::cout << "ERROR: requests file is empty!" << std::endl;
        std::cout << "Search Engine is closed!" << std::endl;
        exit(1);
    }

    // save requests in vector
    std::vector<std::string> requests;

    for (auto & itRequests : requestsData["requests"]) {
        requests.push_back(itRequests);
    }

    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {

    nlohmann::json answersJSON;
    nlohmann::json request;

    for (int i = 0; i < answers.size(); i++) {

        // setting the request id-name
        std::string numberWithZeros;
        if (i + 1 < 10) numberWithZeros = "00" + std::to_string(i + 1);
        else if (i + 1 >= 100) numberWithZeros = std::to_string(i + 1);
        else numberWithZeros = "0" + std::to_string(i + 1);

        // record requests results
        if (!answers[i].empty()) {
            request["request" + numberWithZeros]["result"] = "true";

            nlohmann::json relevance;
            int responsesLimit = GetResponsesLimit();
            for (auto & answer : answers[i]) {
                if (responsesLimit == 0) {
                    break;
                }
                responsesLimit--;
                relevance["docid"] = answer.doc_id;
                relevance["rank"] = answer.rank;
                request["request" + numberWithZeros]["relevance"] += relevance;
            }
        } else {
            request["request" + numberWithZeros]["result"] =  "false";
        }
    }
    answersJSON["answers"] = request;

    std::ofstream file("../answers.json");
    std::cout << "Writing requests results to a file answers.json!" << std::endl;
    file << answersJSON.dump(4);
    file.close();
}
