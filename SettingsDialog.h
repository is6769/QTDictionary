#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFont>
#include "Settings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(Settings *settings, QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void onAccepted();
    void onRejected();
    void onSelectFont();
    void onSelectAutoSaveLocation();
    void onAutoSaveToggled(bool checked);
    void onThemeChanged(int index);
    void updateFontPreview();

private:
    Ui::SettingsDialog *ui;
    Settings *appSettings;
    QFont selectedFont;
    QString selectedTheme;
    bool autoSaveEnabled;
    int autoSaveInterval;
    QString autoSaveLocation;
    bool confirmDeletion;
    bool caseSensitiveSearch;
    int maxRecentFiles;
    
    void loadCurrentSettings();
};

#endif // SETTINGSDIALOG_H
