#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QString>
#include <QJsonObject>
#include "WordDefinition.h"

class Dictionary;

class JsonHandler {
public:
    static bool exportToFile(Dictionary* dict, QString filePath);
    static bool importFromFile(Dictionary* dict, QString filePath, bool merge);

private:
    static QJsonObject wordToJson(WordDefinition* word);
    static WordDefinition jsonToWord(QJsonObject json);
};

#endif
