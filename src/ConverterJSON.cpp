#include "ConverterJSON.h"
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

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

    for (auto itFiles = configData["files"].begin(); itFiles != configData["files"].end(); ++itFiles) {
        textDocuments.push_back(*itFiles);
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

    std::vector<std::string> requests;

    for (auto itRequests = requestsData["requests"].begin(); itRequests != requestsData["requests"].end(); ++itRequests) {
        requests.push_back(*itRequests);
    }


    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

}
