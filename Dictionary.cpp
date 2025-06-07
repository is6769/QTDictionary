#include "Dictionary.h"
#include "JsonHandler.h"

Dictionary::Dictionary() {}

void Dictionary::addWord(QString word, WordDefinition definition) {
    words[word.toLower()] = definition;
}

bool Dictionary::removeWord(QString word) {
    return words.remove(word.toLower()) > 0;
}

WordDefinition* Dictionary::findWord(QString word) {
    if (words.contains(word.toLower())) {
        return &words[word.toLower()];
    }
    return nullptr;
}

QList<QString> Dictionary::getAllWords() {
    return words.keys();
}

int Dictionary::getWordCount() {
    return words.size();
}

bool Dictionary::exportToJson(QString filePath) {
    return JsonHandler::exportToFile(this, filePath);
}

bool Dictionary::importFromJson(QString filePath, bool mergeWithExisting) {
    return JsonHandler::importFromFile(this, filePath, mergeWithExisting);
}
