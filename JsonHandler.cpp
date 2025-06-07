#include "JsonHandler.h"
#include "Dictionary.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

bool JsonHandler::exportToFile(Dictionary* dict, QString filePath) {
    QJsonArray wordArray;
    
    QList<QString> allWords = dict->getAllWords();
    for (const QString& wordStr : allWords) {
        WordDefinition* word = dict->findWord(wordStr);
        if (word) {
            wordArray.append(wordToJson(word));
        }
    }
    
    QJsonDocument document(wordArray);
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    file.write(document.toJson());
    file.close();
    
    return true;
}

bool JsonHandler::importFromFile(Dictionary* dict, QString filePath, bool merge) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument document = QJsonDocument::fromJson(data);
    if (document.isNull() || !document.isArray()) {
        return false;
    }
    
    if (!merge) {
        QList<QString> allWords = dict->getAllWords();
        for (const QString& word : allWords) {
            dict->removeWord(word);
        }
    }
    
    QJsonArray wordArray = document.array();
    for (const QJsonValue& value : wordArray) {
        if (value.isObject()) {
            WordDefinition word = jsonToWord(value.toObject());
            dict->addWord(word.getWord(), word);
        }
    }
    
    return true;
}

QJsonObject JsonHandler::wordToJson(WordDefinition* word) {
    QJsonObject wordObject;
    
    wordObject["word"] = word->getWord();
    wordObject["definition"] = word->getDefinition();
    
    QJsonArray examplesArray;
    for (const QString& example : word->getExamples()) {
        examplesArray.append(example);
    }
    wordObject["examples"] = examplesArray;
    
    QJsonArray synonymsArray;
    for (const QString& synonym : word->getSynonyms()) {
        synonymsArray.append(synonym);
    }
    wordObject["synonyms"] = synonymsArray;
    
    QJsonArray antonymsArray;
    for (const QString& antonym : word->getAntonyms()) {
        antonymsArray.append(antonym);
    }
    wordObject["antonyms"] = antonymsArray;
    
    return wordObject;
}

WordDefinition JsonHandler::jsonToWord(QJsonObject json) {
    WordDefinition word;
    
    word.setWord(json["word"].toString());
    word.setDefinition(json["definition"].toString());
    
    QJsonArray examplesArray = json["examples"].toArray();
    for (const QJsonValue& example : examplesArray) {
        word.addExample(example.toString());
    }
    
    QJsonArray synonymsArray = json["synonyms"].toArray();
    for (const QJsonValue& synonym : synonymsArray) {
        word.addSynonym(synonym.toString());
    }
    
    QJsonArray antonymsArray = json["antonyms"].toArray();
    for (const QJsonValue& antonym : antonymsArray) {
        word.addAntonym(antonym.toString());
    }
    
    return word;
}
