#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Dictionary.h"
#include "Settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Dictionary* dictionary;
    Settings* appSettings;
    QString currentFilePath;
    bool dictionaryModified;
    QTimer *statusClearTimer;
    QMenu *recentFilesMenu;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void updateWordList();
    void connectSignals();
    void createRecentFilesMenu();
    void updateRecentFilesMenu();
    bool maybeSave();
    void setCurrentFile(const QString &filePath);
    bool saveFile(const QString &filePath);
    void setModified(bool modified);
    void loadRecentFile(const QString &filePath);

private slots:
    void searchWord();
    void addNewWord();
    void editWord();
    void deleteWord();
    void exportDictionary();
    void importDictionary();
    void clearResults();
    void wordSelected(const QString& word);
    void showSettingsDialog();
    void onFontChanged(const QFont &font);
    void onAutoSaveNow();
    void clearStatusMessage();
    void newDictionary();
    bool saveCurrentDictionary();
    bool saveAsDictionary();
    void openDictionary();
};

#endif // MAINWINDOW_H
