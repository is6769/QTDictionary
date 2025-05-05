#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QMap>
#include <QString>
#include <QList>
#include "WordDefinition.h"

class Dictionary {
private:
    QMap<QString, WordDefinition> words;

public:
    Dictionary();
    
    void addWord(QString word, WordDefinition definition);
    bool removeWord(QString word);
    WordDefinition* findWord(QString word);
    QList<QString> getAllWords();
    int getWordCount();
    bool exportToJson(QString filePath);
    bool importFromJson(QString filePath, bool mergeWithExisting);
};

#endif // DICTIONARY_H
