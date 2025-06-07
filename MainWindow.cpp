#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddEditDialog.h"
#include "SettingsDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QCloseEvent>
#include <QDateTime>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <QToolTip>
#include <QAction>
#include <QList>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    dictionary(new Dictionary()),
    appSettings(new Settings(this)),
    dictionaryModified(false)
{
    ui->setupUi(this);
    
    setObjectName("MainWindow");
    ui->resultDisplay->setObjectName("resultDisplay");
    ui->wordListWidget->setObjectName("wordListWidget");
    ui->searchBar->setObjectName("searchBar");
    ui->searchButton->setObjectName("searchButton");
    
    statusClearTimer = new QTimer(this);
    statusClearTimer->setSingleShot(true);
    connect(statusClearTimer, &QTimer::timeout, this, &MainWindow::clearStatusMessage);
    
    createRecentFilesMenu();
    
    connectSignals();
    
    appSettings->applyTheme();
    onFontChanged(appSettings->getFont());
    
    setWindowTitle("Словарное Приложение - [Не сохранено]");
    
    ui->statusBar->showMessage("Готово");
    
    ui->addAction->setShortcut(QKeySequence("Ctrl+A")); 
    
    QDir autoSaveDir(appSettings->autoSaveLocation());
    if (!autoSaveDir.exists()) {
        autoSaveDir.mkpath(".");
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete dictionary;
}

void MainWindow::connectSignals() {
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchWord);
    connect(ui->searchBar, &QLineEdit::returnPressed, this, &MainWindow::searchWord);
    connect(ui->wordListWidget, &QListWidget::itemClicked, [this](QListWidgetItem* item) {
        if (item) wordSelected(item->text());
    });
    
    connect(ui->addAction, &QAction::triggered, this, &MainWindow::addNewWord);
    connect(ui->editAction, &QAction::triggered, this, &MainWindow::editWord);
    connect(ui->deleteAction, &QAction::triggered, this, &MainWindow::deleteWord);
    connect(ui->exportAction, &QAction::triggered, this, &MainWindow::exportDictionary);
    connect(ui->importAction, &QAction::triggered, this, &MainWindow::importDictionary);
    connect(ui->exitAction, &QAction::triggered, qApp, &QApplication::quit);
    
    connect(ui->settingsAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);
    
    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newDictionary);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openDictionary);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveCurrentDictionary);
    connect(ui->saveAsAction, &QAction::triggered, this, &MainWindow::saveAsDictionary);
    
    connect(ui->aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "О Словарном Приложении",
                          "Словарное Приложение\n\n"
                          "Простое приложение для управления словарными определениями.\n\n"
                          "Возможности:\n"
                          "- Добавление, редактирование и удаление словарных определений\n"
                          "- Поиск слов\n"
                          "- Импорт и экспорт словарей\n"
                          "- Настраиваемые темы и шрифты\n"
                          "- Функция автосохранения");
    });
    
    connect(appSettings, &Settings::fontChanged, this, &MainWindow::onFontChanged);
    connect(appSettings, &Settings::autoSaveNow, this, &MainWindow::onAutoSaveNow);
}

void MainWindow::createRecentFilesMenu() {
    recentFilesMenu = new QMenu("Recent Files", this);
    ui->menuFile->insertMenu(ui->exitAction, recentFilesMenu);
    ui->menuFile->insertSeparator(ui->exitAction);
    
    updateRecentFilesMenu();
}

void MainWindow::updateRecentFilesMenu() {
    recentFilesMenu->clear();
    
    QStringList recentFiles = appSettings->recentFiles();
    for (const QString &filePath : recentFiles) {
        QAction *action = recentFilesMenu->addAction(QFileInfo(filePath).fileName());
        action->setData(filePath);
        action->setStatusTip(filePath);
        connect(action, &QAction::triggered, [this, filePath]() {
            loadRecentFile(filePath);
        });
    }
    
    if (recentFiles.isEmpty()) {
        QAction *noRecentAction = recentFilesMenu->addAction("No recent files");
        noRecentAction->setEnabled(false);
    } else {
        recentFilesMenu->addSeparator();
        QAction *clearAction = recentFilesMenu->addAction("Clear Recent Files");
        connect(clearAction, &QAction::triggered, [this]() {
            appSettings->clearRecentFiles();
            updateRecentFilesMenu();
        });
    }
}

void MainWindow::updateWordList() {
    ui->wordListWidget->clear();
    QList<QString> words = dictionary->getAllWords();
    
    if (appSettings->caseSensitiveSearch()) {
        std::sort(words.begin(), words.end());
    } else {
        std::sort(words.begin(), words.end(), [](const QString &a, const QString &b) {
            return a.toLower() < b.toLower();
        });
    }
    
    ui->wordListWidget->addItems(words);
    
    ui->statusBar->showMessage(QString("Словарь содержит %1 слов").arg(dictionary->getWordCount()));
    statusClearTimer->start(3000);
}

void MainWindow::searchWord() {
    QString searchText = ui->searchBar->text().trimmed();
    if (searchText.isEmpty()) {
        clearResults();
        return;
    }
    
    WordDefinition* word = dictionary->findWord(searchText);
    if (word) {
        QString result = "<h2>" + word->getWord() + "</h2>";
        result += "<p><b>Определение:</b> " + word->getDefinition() + "</p>";
        
        if (!word->getExamples().isEmpty()) {
            result += "<p><b>Примеры:</b></p><ul>";
            for (const QString& example : word->getExamples()) {
                result += "<li>" + example + "</li>";
            }
            result += "</ul>";
        }
        
        if (!word->getSynonyms().isEmpty()) {
            result += "<p><b>Синонимы:</b> " + word->getSynonyms().join(", ") + "</p>";
        }
        
        if (!word->getAntonyms().isEmpty()) {
            result += "<p><b>Антонимы:</b> " + word->getAntonyms().join(", ") + "</p>";
        }
        
        ui->resultDisplay->setHtml(result);
        ui->statusBar->showMessage("Слово найдено");
        statusClearTimer->start(3000);
    } else {
        ui->resultDisplay->setHtml("<p>Слово <b>'" + searchText + "'</b> не найдено в словаре.</p>");
        ui->statusBar->showMessage("Слово не найдено");
        statusClearTimer->start(3000);
    }
}

void MainWindow::wordSelected(const QString& word) {
    ui->searchBar->setText(word);
    searchWord();
}

void MainWindow::addNewWord() {
    AddEditDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        WordDefinition newWord = dialog.getWordDefinition();
        dictionary->addWord(newWord.getWord(), newWord);
        setModified(true);
        updateWordList();
        
        ui->searchBar->setText(newWord.getWord());
        searchWord();
        
        ui->statusBar->showMessage("Слово успешно добавлено");
        statusClearTimer->start(3000);
    }
}

void MainWindow::editWord() {
    QString currentWord = ui->searchBar->text().trimmed();
    if (currentWord.isEmpty()) {
        QMessageBox::information(this, "Редактировать слово", "Пожалуйста, сначала найдите слово для редактирования.");
        return;
    }
    
    WordDefinition* word = dictionary->findWord(currentWord);
    if (!word) {
        QMessageBox::warning(this, "Редактировать слово", "Слово не найдено в словаре.");
        return;
    }
    
    AddEditDialog dialog(this, word);
    if (dialog.exec() == QDialog::Accepted) {
        WordDefinition updatedWord = dialog.getWordDefinition();
        
        if (updatedWord.getWord().toLower() != currentWord.toLower()) {
            dictionary->removeWord(currentWord);
        }
        
        dictionary->addWord(updatedWord.getWord(), updatedWord);
        setModified(true);
        updateWordList();
        
        ui->searchBar->setText(updatedWord.getWord());
        searchWord();
        
        ui->statusBar->showMessage("Слово успешно обновлено");
        statusClearTimer->start(3000);
    }
}

void MainWindow::deleteWord() {
    QString currentWord = ui->searchBar->text().trimmed();
    if (currentWord.isEmpty()) {
        QMessageBox::information(this, "Удалить слово", "Пожалуйста, сначала найдите слово для удаления.");
        return;
    }
    
    WordDefinition* word = dictionary->findWord(currentWord);
    if (!word) {
        QMessageBox::warning(this, "Удалить слово", "Слово не найдено в словаре.");
        return;
    }
    
    bool shouldDelete = true;
    
    if (appSettings->confirmDeletion()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Подтвердить удаление",
            "Вы уверены, что хотите удалить слово '" + currentWord + "'?",
            QMessageBox::Yes | QMessageBox::No
        );
        
        shouldDelete = (reply == QMessageBox::Yes);
    }
    
    if (shouldDelete) {
        dictionary->removeWord(currentWord);
        setModified(true);
        updateWordList();
        clearResults();
        ui->searchBar->clear();
        ui->statusBar->showMessage("Слово успешно удалено");
        statusClearTimer->start(3000);
    }
}

void MainWindow::exportDictionary() {
    QString filePath = QFileDialog::getSaveFileName(
        this, "Экспортировать словарь", "", "JSON файлы (*.json)"
    );
    
    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".json", Qt::CaseInsensitive)) {
            filePath += ".json";
        }
        
        if (dictionary->exportToJson(filePath)) {
            QMessageBox::information(this, "Экспорт успешен", 
                "Словарь успешно экспортирован в " + filePath);
            ui->statusBar->showMessage("Словарь успешно экспортирован");
            statusClearTimer->start(3000);
        } else {
            QMessageBox::critical(this, "Ошибка экспорта", 
                "Не удалось экспортировать словарь в " + filePath);
            ui->statusBar->showMessage("Ошибка экспорта словаря");
            statusClearTimer->start(3000);
        }
    }
}

void MainWindow::importDictionary() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Импортировать словарь", "", "JSON файлы (*.json)"
    );
    
    if (!filePath.isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Опции импорта",
            "Вы хотите объединить с существующим словарем?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );
        
        if (reply == QMessageBox::Cancel) {
            return;
        }
        
        bool merge = (reply == QMessageBox::Yes);
        
        if (dictionary->importFromJson(filePath, merge)) {
            setModified(true);
            updateWordList();
            QMessageBox::information(this, "Импорт успешен", 
                QString("Словарь успешно импортирован из %1.\n%2 слов в словаре сейчас.")
                .arg(filePath).arg(dictionary->getWordCount()));
            ui->statusBar->showMessage("Словарь успешно импортирован");
            statusClearTimer->start(3000);
        } else {
            QMessageBox::critical(this, "Ошибка импорта", 
                "Не удалось импортировать словарь из " + filePath);
            ui->statusBar->showMessage("Ошибка импорта словаря");
            statusClearTimer->start(3000);
        }
    }
}

void MainWindow::clearResults() {
    ui->resultDisplay->clear();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        appSettings->saveSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::maybeSave() {
    if (!dictionaryModified) {
        return true;
    }
    
    const QMessageBox::StandardButton ret = QMessageBox::warning(
        this, 
        "Словарное Приложение", 
        "Словарь был изменен.\n"
        "Вы хотите сохранить изменения?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
    );
    
    switch (ret) {
        case QMessageBox::Save:
            return saveCurrentDictionary();
        case QMessageBox::Discard:
            return true;
        case QMessageBox::Cancel:
            return false;
        default:
            return false;
    }
}

void MainWindow::setCurrentFile(const QString &filePath) {
    currentFilePath = filePath;
    
    QString displayName = currentFilePath.isEmpty() ? 
                          "Не сохранено" : QFileInfo(currentFilePath).fileName();
    
    setWindowTitle(QString("Словарное Приложение - [%1]").arg(displayName));
    
    if (!currentFilePath.isEmpty()) {
        appSettings->addRecentFile(currentFilePath);
        updateRecentFilesMenu();
    }
}

bool MainWindow::saveFile(const QString &filePath) {
    QString actualFilePath = filePath;
    if (!actualFilePath.endsWith(".json", Qt::CaseInsensitive)) {
        actualFilePath += ".json";
    }
    
    if (dictionary->exportToJson(actualFilePath)) {
        setCurrentFile(actualFilePath);
        setModified(false);
        ui->statusBar->showMessage(QString("Словарь сохранен в %1").arg(actualFilePath), 3000);
        return true;
    }
    
    QMessageBox::warning(this, "Ошибка сохранения",
                        QString("Не удалось сохранить словарь в файл %1").arg(actualFilePath));
    return false;
}

void MainWindow::setModified(bool modified) {
    if (dictionaryModified != modified) {
        dictionaryModified = modified;
        
        QString title = windowTitle();
        if (modified && !title.endsWith('*')) {
            setWindowTitle(title + '*');
        } else if (!modified && title.endsWith('*')) {
            setWindowTitle(title.left(title.length() - 1));
        }
    }
}

void MainWindow::loadRecentFile(const QString &filePath) {
    if (maybeSave()) {
        if (QFile::exists(filePath)) {
            if (dictionary->importFromJson(filePath, false)) {
                setCurrentFile(filePath);
                setModified(false);
                updateWordList();
                ui->statusBar->showMessage(QString("Загружен словарь из %1").arg(filePath), 3000);
            } else {
                QMessageBox::warning(this, "Ошибка открытия",
                                    QString("Не удалось открыть словарь из файла %1").arg(filePath));
            }
        } else {
            QMessageBox::warning(this, "Файл не найден",
                                QString("Файл %1 не существует").arg(filePath));
            
            appSettings->recentFiles().removeOne(filePath);
            updateRecentFilesMenu();
        }
    }
}

void MainWindow::showSettingsDialog() {
    SettingsDialog dialog(appSettings, this);
    dialog.exec();
    
    updateWordList();
}

void MainWindow::onFontChanged(const QFont &font) {
    QApplication::setFont(font);
    
    ui->wordListWidget->setFont(font);
    ui->resultDisplay->setFont(font);
    ui->searchBar->setFont(font);
}

void MainWindow::onAutoSaveNow() {
    if (!dictionaryModified) {
        return;
    }

    if (!currentFilePath.isEmpty()) {
        if (saveFile(currentFilePath)) {
        } else {
        }
    } else {
        QDir autoSaveDir(appSettings->autoSaveLocation());
        if (!autoSaveDir.exists()) {
            if (!autoSaveDir.mkpath(".")) {
                qWarning() << "Не удалось создать директорию автосохранения:" << appSettings->autoSaveLocation();
                ui->statusBar->showMessage("Ошибка автосохранения: не удалось создать директорию.", 5000);
                statusClearTimer->start(5000);
                return;
            }
        }
        
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
        QString autoSavePath = QString("%1/dictionary_autosave_%2.json")
                                  .arg(appSettings->autoSaveLocation())
                                  .arg(timestamp);

        if (dictionary->exportToJson(autoSavePath)) {
            setModified(false); 
            ui->statusBar->showMessage(QString("Автосохранение в %1").arg(QFileInfo(autoSavePath).fileName()), 5000);
            statusClearTimer->start(5000);
        } else {
            qWarning() << "Не удалось выполнить автосохранение в" << autoSavePath;
            ui->statusBar->showMessage(QString("Ошибка автосохранения в %1").arg(QFileInfo(autoSavePath).fileName()), 5000);
            statusClearTimer->start(5000);
        }
    }
}

void MainWindow::clearStatusMessage() {
    if (ui->statusBar->currentMessage().startsWith("Ошибка автосохранения:") || 
        ui->statusBar->currentMessage().startsWith("Автосохранение в")) {
    } else {
        ui->statusBar->clearMessage();
    }
}

void MainWindow::newDictionary() {
    if (maybeSave()) {
        dictionary = new Dictionary();
        setCurrentFile("");
        setModified(false);
        updateWordList();
        clearResults();
        ui->searchBar->clear();
        ui->statusBar->showMessage("Создан новый словарь");
        statusClearTimer->start(3000);
    }
}

bool MainWindow::saveCurrentDictionary() {
    if (currentFilePath.isEmpty()) {
        return saveAsDictionary();
    } else {
        return saveFile(currentFilePath);
    }
}

bool MainWindow::saveAsDictionary() {
    QString filePath = QFileDialog::getSaveFileName(
        this, "Сохранить словарь", "", "JSON файлы (*.json)"
    );
    
    if (!filePath.isEmpty()) {
        return saveFile(filePath);
    }
    return false;
}

void MainWindow::openDictionary() {
    if (maybeSave()) {
        QString filePath = QFileDialog::getOpenFileName(
            this, "Открыть словарь", "", "JSON файлы (*.json)"
        );
        
        if (!filePath.isEmpty()) {
            if (dictionary->importFromJson(filePath, false)) {
                setCurrentFile(filePath);
                setModified(false);
                updateWordList();
                ui->statusBar->showMessage(QString("Загружен словарь из %1").arg(filePath));
                statusClearTimer->start(3000);
            } else {
                QMessageBox::critical(this, "Ошибка открытия", 
                    "Не удалось открыть словарь из " + filePath);
            }
        }
    }
}
