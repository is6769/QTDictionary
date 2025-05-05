#include "AddEditDialog.h"
#include "ui_AddEditDialog.h"
#include <QMessageBox>

// Конструктор диалога добавления/редактирования слова
AddEditDialog::AddEditDialog(QWidget* parent, WordDefinition* wordDefToEdit)
    : QDialog(parent),
      ui(new Ui::AddEditDialog),
      isEditMode(wordDefToEdit != nullptr)
{
    ui->setupUi(this);
    
    // Установка флагов окна для обеспечения рамки и заголовка
    // Qt::WindowCloseButtonHint - кнопка закрытия, Qt::WindowTitleHint - заголовок окна
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint);
    
    // Отключаем автоматическое удаление диалога при закрытии
    setAttribute(Qt::WA_DeleteOnClose, false);
    
    // Настройка диалога в зависимости от режима работы (редактирование или создание)
    if (isEditMode) {
        // Режим редактирования - изменяем заголовок
        setWindowTitle("Редактирование слова");
        
        // Создаем копию объекта определения слова для редактирования
        // чтобы не изменить оригинал до подтверждения пользователем
        wordDef = new WordDefinition(*wordDefToEdit);
    } else {
        // Режим создания - устанавливаем заголовок и создаем новый пустой объект
        setWindowTitle("Добавление нового слова");
        wordDef = new WordDefinition();
    }
    
    // Если в режиме редактирования, заполняем поля данными из определения
    if (isEditMode) {
        fillFieldsFromWord();
    }
    
    // Отключение сигнала accepted() по умолчанию для предотвращения преждевременного принятия
    // так как нам нужна валидация перед закрытием
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    
    // Подключение нашего пользовательского метода сохранения с валидацией
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddEditDialog::saveWord);

    // Установка имени объекта для таргетирования в CSS и настройка отступов
    setObjectName("AddEditDialog");
    setContentsMargins(10, 10, 10, 10);
}

// Деструктор диалога - освобождает ресурсы
AddEditDialog::~AddEditDialog() {
    // Освобождаем память UI-компонентов
    delete ui;
    
    // Освобождаем память объекта определения слова
    delete wordDef;
}

// Метод для получения определения слова из диалога
WordDefinition AddEditDialog::getWordDefinition() {
    return *wordDef;
}

// Заполнение полей диалога данными из текущего определения слова
void AddEditDialog::fillFieldsFromWord() {
    // Заполняем основные поля
    ui->wordInput->setText(wordDef->getWord());
    ui->definitionInput->setText(wordDef->getDefinition());
    
    // Заполняем примеры, соединяя их с переносами строк
    QString examples;
    for (const QString& example : wordDef->getExamples()) {
        examples += example + "\n";
    }
    ui->examplesInput->setText(examples);
    
    // Заполняем синонимы, соединяя их запятыми
    ui->synonymsInput->setText(wordDef->getSynonyms().join(", "));
    
    // Заполняем антонимы, соединяя их запятыми
    ui->antonymsInput->setText(wordDef->getAntonyms().join(", "));
}

// Сохранение данных из полей диалога в объект определения слова
void AddEditDialog::saveWord() {
    // Проверка валидности ввода - слово не должно быть пустым
    if (ui->wordInput->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка проверки", "Слово не может быть пустым.");
        return;
    }
    
    // Проверка валидности ввода - определение не должно быть пустым
    if (ui->definitionInput->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка проверки", "Определение не может быть пустым.");
        return;
    }
    
    // Обновление объекта определения слова текстом из полей ввода
    wordDef->setWord(ui->wordInput->text().trimmed());
    wordDef->setDefinition(ui->definitionInput->toPlainText().trimmed());
    
    // Очистка существующих коллекций перед добавлением новых элементов
    QList<QString> existingExamples = wordDef->getExamples();
    while (!existingExamples.isEmpty()) {
        wordDef->getExamples().removeOne(existingExamples.takeFirst());
    }
    
    wordDef->getSynonyms().clear();
    wordDef->getAntonyms().clear();
    
    // Обработка примеров (строка за строкой)
    QStringList examplesList = ui->examplesInput->toPlainText().split("\n", Qt::SkipEmptyParts);
    for (const QString& example : examplesList) {
        if (!example.trimmed().isEmpty()) {
            wordDef->addExample(example.trimmed());
        }
    }
    
    // Обработка синонимов (через запятую)
    QStringList synonymsList = ui->synonymsInput->text().split(",", Qt::SkipEmptyParts);
    for (const QString& synonym : synonymsList) {
        if (!synonym.trimmed().isEmpty()) {
            wordDef->addSynonym(synonym.trimmed());
        }
    }
    
    // Обработка антонимов (через запятую)
    QStringList antonymsList = ui->antonymsInput->text().split(",", Qt::SkipEmptyParts);
    for (const QString& antonym : antonymsList) {
        if (!antonym.trimmed().isEmpty()) {
            wordDef->addAntonym(antonym.trimmed());
        }
    }
    
    // Принимаем диалог, что приводит к его закрытию с кодом QDialog::Accepted
    accept();
}
