/*
#include "gtest/gtest.h"

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
    int i = 0;
}
*/



#include <iostream>
#include <vector>

//#include <nlohmann/json.hpp>
//#include <fstream>
//#include "config.h"

#include "ConverterJSON.h"
#include "SearchServer.h"
#include "InvertedIndex.h"



int main() {

    ConverterJSON converterJson;

    std::vector<std::string> textDocuments = converterJson.GetTextDocuments();
    int responsesLimit = converterJson.GetResponsesLimit();
    std::cout << "max_responses: " << responsesLimit << std::endl;

//    std::vector<std::string> requests = converterJson.GetRequests();



    InvertedIndex invertedIndex;
    invertedIndex.UpdateDocumentBase(textDocuments);



    SearchServer searchServer(invertedIndex);

    auto relevantAnswers = searchServer.search(converterJson.GetRequests());

    converterJson.putAnswers(relevantAnswers);

    std::cout << "END" << std::endl;

        //fileConfigJSON >> configData;
        //std::cout << configData.contains("config");

        /*for (auto itFilms = films.begin(); itFilms != films.end(); ++itFilms) {
            for (auto itActors = films[itFilms.key()]["actors"].begin();
                 itActors != films[itFilms.key()]["actors"].end(); ++itActors) {
                std::string str = (*itActors)["actor"];
                if (str.find(actor) != -1) {
                    std::cout << "Found:" << std::endl;
                    std::cout << "\tFilm: " << films[itFilms.key()]["title"] << std::endl;
                    std::cout << "\tActor name: " << (*itActors)["actor"] << std::endl;
                    std::cout << "\tCharacter: " << (*itActors)["character"] << std::endl;
                    std::cout << "+++++++++++++++++++++++++" << std::endl;
                }
            }
        }
*/
/*    } else {
        std::cout << "File config.json no open!" << std::endl;
        std::cout << "Search Engine is closed!" << std::endl;
    }*/

/*

    nlohmann::json films;

    std::ifstream file2("../films.json");
//    std::ifstream file2("E:\\GitHub\\Skillbox_Project\\films.json");

    file2 >> films;
    file2.close();

    //Anthony
    //Olivia
    std::cout << "Enter actor name: " << std::endl;
    std::string actor;
    std::cin >> actor;

    for (auto itFilms = films.begin(); itFilms != films.end(); ++itFilms) {
        for (auto itActors = films[itFilms.key()]["actors"].begin();
             itActors != films[itFilms.key()]["actors"].end(); ++itActors) {
            std::string str = (*itActors)["actor"];
            if (str.find(actor) != -1) {
                std::cout << "Found:" << std::endl;
                std::cout << "\tFilm: " << films[itFilms.key()]["title"] << std::endl;
                std::cout << "\tActor name: " << (*itActors)["actor"] << std::endl;
                std::cout << "\tCharacter: " << (*itActors)["character"] << std::endl;
                std::cout << "+++++++++++++++++++++++++" << std::endl;
            }
        }
    }
*/


/*
//Information about film film.json (write file)

    std::cout << "Information about film" << std::endl;

    nlohmann::json film{
            {"title",         "The Shawshank Redemption"},
            {"country",       "United States"},
            {"release-date",  "1994"},
            {"studio",        "Castle Rock Entertainment"},
            {"script-writer", "Frank Darabont"},
            {"director",      "Frank Darabont"},
            {"producer",      "Liz Glotzer"},
            {"actors",        {
                                      {"Andy-Dufresne", "Tim Robbins"},
                                      {"Ellis-Boyd", "Morgan Freeman"}}
            }
    };

    std::ofstream file("../film.json");
    file << film;
    file.close();


//Films Data Analysis films.json (read file)



    std::cout << "Films Data Analysis" << std::endl;

    nlohmann::json films;

    std::ifstream file2("../films.json");
//    std::ifstream file2("E:\\GitHub\\Skillbox_Project\\films.json");

    file2 >> films;
    file2.close();

    //Anthony
    //Olivia
    std::cout << "Enter actor name: " << std::endl;
    std::string actor;
    std::cin >> actor;

    for (auto itFilms = films.begin(); itFilms != films.end(); ++itFilms) {
        for (auto itActors = films[itFilms.key()]["actors"].begin();
             itActors != films[itFilms.key()]["actors"].end(); ++itActors) {
            std::string str = (*itActors)["actor"];
            if (str.find(actor) != -1) {
                std::cout << "Found:" << std::endl;
                std::cout << "\tFilm: " << films[itFilms.key()]["title"] << std::endl;
                std::cout << "\tActor name: " << (*itActors)["actor"] << std::endl;
                std::cout << "\tCharacter: " << (*itActors)["character"] << std::endl;
                std::cout << "+++++++++++++++++++++++++" << std::endl;
            }
        }
    }



    return 0;

*/

}

