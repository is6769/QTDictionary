#include "Dictionary.h"
#include "JsonHandler.h"

// Конструктор класса словаря - инициализирует пустой словарь
Dictionary::Dictionary() {}

// Добавление слова в словарь
void Dictionary::addWord(QString word, WordDefinition definition) {
    // Добавление слова в словарь с преобразованием к нижнему регистру для ключа,
    // что обеспечивает регистронезависимый поиск
    words[word.toLower()] = definition;
}

// Удаление слова из словаря по ключу
bool Dictionary::removeWord(QString word) {
    // Удаление слова из словаря по ключу в нижнем регистре
    // Возвращает true, если слово было найдено и удалено
    return words.remove(word.toLower()) > 0;
}

// Поиск слова в словаре и возврат указателя на его определение
WordDefinition* Dictionary::findWord(QString word) {
    // Поиск слова в словаре по ключу в нижнем регистре
    // для обеспечения регистронезависимого поиска
    if (words.contains(word.toLower())) {
        // Возвращаем указатель на найденное определение
        return &words[word.toLower()];
    }
    // Если слово не найдено, возвращаем nullptr
    return nullptr;
}

// Получение списка всех слов в словаре
QList<QString> Dictionary::getAllWords() {
    // Получение списка всех ключей (слов) из словаря
    return words.keys();
}

// Получение количества слов в словаре
int Dictionary::getWordCount() {
    // Возвращает количество слов в словаре
    return words.size();
}

// Экспорт словаря в JSON-файл
bool Dictionary::exportToJson(QString filePath) {
    // Использование статического метода JsonHandler для экспорта
    return JsonHandler::exportToFile(this, filePath);
}

// Импорт словаря из JSON-файла с возможностью слияния
bool Dictionary::importFromJson(QString filePath, bool mergeWithExisting) {
    // Использование статического метода JsonHandler для импорта
    // mergeWithExisting определяет, сливать ли новые данные с существующими
    // или полностью заменять имеющийся словарь
    return JsonHandler::importFromFile(this, filePath, mergeWithExisting);
}
