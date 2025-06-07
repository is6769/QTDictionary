#include "WordDefinition.h"

WordDefinition::WordDefinition() {}

WordDefinition::WordDefinition(QString word, QString definition) 
    : word(word), definition(definition) {}

void WordDefinition::setWord(QString word) {
    this->word = word;
}

QString WordDefinition::getWord() const {
    return word;
}

void WordDefinition::setDefinition(QString definition) {
    this->definition = definition;
}

QString WordDefinition::getDefinition() const {
    return definition;
}

void WordDefinition::addExample(QString example) {
    examples.append(example);
}

QList<QString> WordDefinition::getExamples() const {
    return examples;
}

void WordDefinition::clearExamples() {
    examples.clear();
}

void WordDefinition::addSynonym(QString synonym) {
    synonyms.append(synonym);
}

QStringList WordDefinition::getSynonyms() const {
    return synonyms;
}

void WordDefinition::clearSynonyms() {
    synonyms.clear();
}

void WordDefinition::addAntonym(QString antonym) {
    antonyms.append(antonym);
}

QStringList WordDefinition::getAntonyms() const {
    return antonyms;
}

void WordDefinition::clearAntonyms() {
    antonyms.clear();
}
