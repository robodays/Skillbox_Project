#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include <vector>
//#include "InvertedIndex.h"
#include "../include/InvertedIndex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx) : _index(idx){ };

/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);


private:
/**
* Метод ищет относительную релевантность для одного запроса
* @param queryWordsVec вектор слов запроса отсортированный по количеству встречающихся слов во всех документов
* @return возвращает вектор относительной релевантности для одного запроса
*/
    std::vector<RelativeIndex> SearchRelativeIndex(std::vector<std::pair<std::string, size_t>> &queryWordsVec);

    InvertedIndex& _index;


};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
