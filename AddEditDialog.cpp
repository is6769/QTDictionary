#include "AddEditDialog.h"
#include "ui_AddEditDialog.h"
#include <QMessageBox>

AddEditDialog::AddEditDialog(QWidget* parent, WordDefinition* wordDefToEdit)
    : QDialog(parent),
      ui(new Ui::AddEditDialog),
      isEditMode(wordDefToEdit != nullptr)
{
    ui->setupUi(this);
    
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint);
    
    setAttribute(Qt::WA_DeleteOnClose, false);
    
    if (isEditMode) {
        setWindowTitle("Редактирование слова");
        
        wordDef = new WordDefinition(*wordDefToEdit);
    } else {
        setWindowTitle("Добавление нового слова");
        wordDef = new WordDefinition();
    }
    
    if (isEditMode) {
        fillFieldsFromWord();
    }
    
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddEditDialog::saveWord);

    setObjectName("AddEditDialog");
    setContentsMargins(10, 10, 10, 10);
}

AddEditDialog::~AddEditDialog() {
    delete ui;
    
    delete wordDef;
}

WordDefinition AddEditDialog::getWordDefinition() {
    return *wordDef;
}

void AddEditDialog::fillFieldsFromWord() {
    ui->wordInput->setText(wordDef->getWord());
    ui->definitionInput->setText(wordDef->getDefinition());
    
    QString examples;
    for (const QString& example : wordDef->getExamples()) {
        examples += example + "\n";
    }
    ui->examplesInput->setText(examples);
    
    ui->synonymsInput->setText(wordDef->getSynonyms().join(", "));
    
    ui->antonymsInput->setText(wordDef->getAntonyms().join(", "));
}

void AddEditDialog::saveWord() {
    if (ui->wordInput->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка проверки", "Слово не может быть пустым.");
        return;
    }
    
    if (ui->definitionInput->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка проверки", "Определение не может быть пустым.");
        return;
    }
    
    wordDef->setWord(ui->wordInput->text().trimmed());
    wordDef->setDefinition(ui->definitionInput->toPlainText().trimmed());
    
    wordDef->clearExamples();
    wordDef->clearSynonyms();
    wordDef->clearAntonyms();
    
    QStringList examplesList = ui->examplesInput->toPlainText().split("\n", Qt::SkipEmptyParts);
    for (const QString& example : examplesList) {
        if (!example.trimmed().isEmpty()) {
            wordDef->addExample(example.trimmed());
        }
    }
    
    QStringList synonymsList = ui->synonymsInput->text().split(",", Qt::SkipEmptyParts);
    for (const QString& synonym : synonymsList) {
        if (!synonym.trimmed().isEmpty()) {
            wordDef->addSynonym(synonym.trimmed());
        }
    }
    
    QStringList antonymsList = ui->antonymsInput->text().split(",", Qt::SkipEmptyParts);
    for (const QString& antonym : antonymsList) {
        if (!antonym.trimmed().isEmpty()) {
            wordDef->addAntonym(antonym.trimmed());
        }
    }
    
    accept();
}
