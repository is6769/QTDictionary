#include "JsonHandler.h"
#include "Dictionary.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

// Экспорт словаря в JSON-файл
bool JsonHandler::exportToFile(Dictionary* dict, QString filePath) {
    // Создаем JSON-массив для хранения всех слов
    QJsonArray wordArray;
    
    // Получение всех слов из словаря
    QList<QString> allWords = dict->getAllWords();
    for (const QString& wordStr : allWords) {
        // Преобразование каждого определения слова в JSON-объект
        WordDefinition* word = dict->findWord(wordStr);
        if (word) {
            wordArray.append(wordToJson(word));
        }
    }
    
    // Создание JSON-документа из массива слов
    QJsonDocument document(wordArray);
    
    // Открытие файла для записи
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        // Возвращаем false, если не удалось открыть файл
        return false;
    }
    
    // Запись JSON-документа в файл
    file.write(document.toJson());
    file.close();
    
    // Возвращаем true, если экспорт выполнен успешно
    return true;
}

// Импорт словаря из JSON-файла
bool JsonHandler::importFromFile(Dictionary* dict, QString filePath, bool merge) {
    // Открытие файла для чтения
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        // Возвращаем false, если не удалось открыть файл
        return false;
    }
    
    // Считывание всего содержимого файла
    QByteArray data = file.readAll();
    file.close();
    
    // Разбор JSON-документа
    QJsonDocument document = QJsonDocument::fromJson(data);
    if (document.isNull() || !document.isArray()) {
        // Возвращаем false, если документ не в формате JSON или не является массивом
        return false;
    }
    
    // Если не требуется слияние, то очищаем существующий словарь
    if (!merge) {
        // Очистка существующего словаря, если не производится слияние
        QList<QString> allWords = dict->getAllWords();
        for (const QString& word : allWords) {
            dict->removeWord(word);
        }
    }
    
    // Добавление слов из JSON-документа в словарь
    QJsonArray wordArray = document.array();
    for (const QJsonValue& value : wordArray) {
        if (value.isObject()) {
            // Преобразование JSON-объекта в определение слова
            WordDefinition word = jsonToWord(value.toObject());
            dict->addWord(word.getWord(), word);
        }
    }
    
    // Возвращаем true, если импорт выполнен успешно
    return true;
}

// Преобразование определения слова в JSON-объект
QJsonObject JsonHandler::wordToJson(WordDefinition* word) {
    // Создаем JSON-объект для представления слова
    QJsonObject wordObject;
    
    // Преобразование свойств определения слова в поля JSON-объекта
    wordObject["word"] = word->getWord();
    wordObject["definition"] = word->getDefinition();
    
    // Преобразование примеров в JSON-массив
    QJsonArray examplesArray;
    for (const QString& example : word->getExamples()) {
        examplesArray.append(example);
    }
    wordObject["examples"] = examplesArray;
    
    // Преобразование синонимов в JSON-массив
    QJsonArray synonymsArray;
    for (const QString& synonym : word->getSynonyms()) {
        synonymsArray.append(synonym);
    }
    wordObject["synonyms"] = synonymsArray;
    
    // Преобразование антонимов в JSON-массив
    QJsonArray antonymsArray;
    for (const QString& antonym : word->getAntonyms()) {
        antonymsArray.append(antonym);
    }
    wordObject["antonyms"] = antonymsArray;
    
    // Возвращаем готовый JSON-объект
    return wordObject;
}

// Преобразование JSON-объекта в определение слова
WordDefinition JsonHandler::jsonToWord(QJsonObject json) {
    // Создаем новый объект определения слова
    WordDefinition word;
    
    // Заполнение объекта определения слова данными из JSON-объекта
    word.setWord(json["word"].toString());
    word.setDefinition(json["definition"].toString());
    
    // Добавление примеров из JSON-массива
    QJsonArray examplesArray = json["examples"].toArray();
    for (const QJsonValue& example : examplesArray) {
        word.addExample(example.toString());
    }
    
    // Добавление синонимов из JSON-массива
    QJsonArray synonymsArray = json["synonyms"].toArray();
    for (const QJsonValue& synonym : synonymsArray) {
        word.addSynonym(synonym.toString());
    }
    
    // Добавление антонимов из JSON-массива
    QJsonArray antonymsArray = json["antonyms"].toArray();
    for (const QJsonValue& antonym : antonymsArray) {
        word.addAntonym(antonym.toString());
    }
    
    // Возвращаем заполненный объект определения слова
    return word;
}
