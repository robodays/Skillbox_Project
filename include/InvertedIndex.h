#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <string>
#include <vector>
#include <map>
#include <mutex>


struct Entry {
    size_t doc_id, count;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;

/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск*
@param inputDocs содержимое документов
*/
    void UpdateDocumentBase(std::vector<std::string> inputDocs);

/**
* Обновить или заполнить базу одного документа (для отдельного потока)
@param inputDocs содержимое одного документа
@param docId id документа
*/
    void UpdateDocumentBaseOneFile(std::string inputDoc, size_t docId);

/**
* Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freqDictionary; // частотный словарь
    std::mutex m_freqDictionary;
};


#endif //SEARCH_ENGINE_INVERTEDINDEX_H
