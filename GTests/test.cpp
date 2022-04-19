
#include "gtest/gtest.h"

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}


/*


#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

int main() {


//Information about film film.json
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

    std::ofstream file("film.json");
    file << film;
    file.close();

//Films Data Analysis films.json


    std::cout << "Films Data Analysis" << std::endl;

    nlohmann::json films;

    std::ifstream file2("films.json");

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


}
*/

