#include "WordDefinition.h"

// Конструктор по умолчанию для создания пустого определения
WordDefinition::WordDefinition() {}

// Конструктор с параметрами для создания определения с базовыми полями
WordDefinition::WordDefinition(QString word, QString definition) 
    : word(word), definition(definition) {}

// Установка слова для текущего определения
void WordDefinition::setWord(QString word) {
    this->word = word;
}

// Получение текущего слова
QString WordDefinition::getWord() const {
    return word;
}

// Установка определения для текущего слова
void WordDefinition::setDefinition(QString definition) {
    this->definition = definition;
}

// Получение текущего определения
QString WordDefinition::getDefinition() const {
    return definition;
}

// Добавление примера использования слова
void WordDefinition::addExample(QString example) {
    examples.append(example);
}

// Получение списка всех примеров использования
QList<QString> WordDefinition::getExamples() const {
    return examples;
}

// Добавление синонима к текущему слову
void WordDefinition::addSynonym(QString synonym) {
    synonyms.append(synonym);
}

// Получение списка всех синонимов
QStringList WordDefinition::getSynonyms() const {
    return synonyms;
}

// Добавление антонима к текущему слову
void WordDefinition::addAntonym(QString antonym) {
    antonyms.append(antonym);
}

// Получение списка всех антонимов
QStringList WordDefinition::getAntonyms() const {
    return antonyms;
}
