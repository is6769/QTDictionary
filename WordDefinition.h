#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H

#include <QString>
#include <QList>
#include <QStringList>

class WordDefinition {
private:
    QString word;
    QString definition;
    QList<QString> examples;
    QStringList synonyms;
    QStringList antonyms;

public:
    WordDefinition();
    WordDefinition(QString word, QString definition);
    
    void setWord(QString word);
    QString getWord() const;
    
    void setDefinition(QString definition);
    QString getDefinition() const;
    
    void addExample(QString example);
    QList<QString> getExamples() const;
    void clearExamples(); 
    
    void addSynonym(QString synonym);
    QStringList getSynonyms() const;
    void clearSynonyms(); 
    
    void addAntonym(QString antonym);
    QStringList getAntonyms() const;
    void clearAntonyms(); 
};

#endif // WORDDEFINITION_H
