#include "Settings.h"
#include <QDir>
#include <QStandardPaths>
#include <QApplication>
#include <QFile>
#include <QFontDatabase>

Settings::Settings(QObject *parent) : QObject(parent) {
    settings = new QSettings("Dictionary Project", "Dictionary", this);
    
    autoSaveTimer = new QTimer(this);
    
    connect(autoSaveTimer, &QTimer::timeout, this, &Settings::autoSaveNow);
    
    setupDefaults();
    loadSettings();
}

Settings::~Settings() {
    saveSettings();
    
    delete settings;
}

void Settings::setupDefaults() {
    themeName = "light";
    
    appFont = QApplication::font();
    
    autoSave = false;
    
    saveInterval = 5;
    
    saveLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    
    confirmDelete = true;
    caseSensitive = false;
    maxRecent = 5;
}

void Settings::loadSettings() {
    themeName = settings->value("theme", "light").toString();
    
    if (settings->contains("font")) {
        appFont.fromString(settings->value("font").toString());
    }
    
    autoSave = settings->value("autoSave/enabled", false).toBool();
    saveInterval = settings->value("autoSave/interval", 5).toInt();
    saveLocation = settings->value("autoSave/location", 
                                   QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
    
    confirmDelete = settings->value("confirmDeletion", true).toBool();
    caseSensitive = settings->value("caseSensitiveSearch", false).toBool();
    maxRecent = settings->value("maxRecentFiles", 5).toInt();
    recentFilesList = settings->value("recentFiles").toStringList();
    
    if (autoSave) {
        startAutoSaveTimer();
    }
}

void Settings::saveSettings() {
    settings->setValue("theme", themeName);
    settings->setValue("font", appFont.toString());
    
    settings->setValue("autoSave/enabled", autoSave);
    settings->setValue("autoSave/interval", saveInterval);
    settings->setValue("autoSave/location", saveLocation);
    
    settings->setValue("confirmDeletion", confirmDelete);
    settings->setValue("caseSensitiveSearch", caseSensitive);
    settings->setValue("maxRecentFiles", maxRecent);
    settings->setValue("recentFiles", recentFilesList);
    
    settings->sync();
}

QString Settings::getTheme() const {
    return themeName;
}

void Settings::setTheme(const QString &theme) {
    if (themeName != theme) {
        themeName = theme;
        applyTheme();
        emit themeChanged(theme);
    }
}

QFont Settings::getFont() const {
    return appFont;
}

void Settings::setFont(const QFont &font) {
    if (appFont != font) {
        appFont = font;
        emit fontChanged(font);
    }
}

bool Settings::autoSaveEnabled() const {
    return autoSave;
}

void Settings::setAutoSaveEnabled(bool enabled) {
    if (autoSave != enabled) {
        autoSave = enabled;
        if (enabled) {
            startAutoSaveTimer();
        } else {
            autoSaveTimer->stop();
        }
        emit autoSaveSettingsChanged();
    }
}

int Settings::autoSaveInterval() const {
    return saveInterval;
}

void Settings::setAutoSaveInterval(int minutes) {
    if (saveInterval != minutes && minutes > 0) {
        saveInterval = minutes;
        if (autoSave) {
            startAutoSaveTimer();
        }
        emit autoSaveSettingsChanged();
    }
}

QString Settings::autoSaveLocation() const {
    return saveLocation;
}

void Settings::setAutoSaveLocation(const QString &location) {
    if (saveLocation != location) {
        saveLocation = location;
        emit autoSaveSettingsChanged();
    }
}

bool Settings::confirmDeletion() const {
    return confirmDelete;
}

void Settings::setConfirmDeletion(bool confirm) {
    confirmDelete = confirm;
}

bool Settings::caseSensitiveSearch() const {
    return caseSensitive;
}

void Settings::setCaseSensitiveSearch(bool sensitive) {
    caseSensitive = sensitive;
}

int Settings::maxRecentFiles() const {
    return maxRecent;
}

void Settings::setMaxRecentFiles(int max) {
    if (maxRecent != max && max >= 0) {
        maxRecent = max;
        while (recentFilesList.size() > maxRecent && !recentFilesList.isEmpty()) {
            recentFilesList.removeLast();
        }
    }
}

QStringList Settings::recentFiles() const {
    return recentFilesList;
}

void Settings::addRecentFile(const QString &filePath) {
    recentFilesList.removeAll(filePath);
    
    recentFilesList.prepend(filePath);
    
    while (recentFilesList.size() > maxRecent && !recentFilesList.isEmpty()) {
        recentFilesList.removeLast();
    }
}

void Settings::clearRecentFiles() {
    recentFilesList.clear();
}

void Settings::applyTheme() {
    QString themeFile;
    
    if (themeName == "dark") {
        themeFile = ":/themes/dark.qss";
    } else {
        themeFile = ":/themes/light.qss";
    }
    
    QFile file(themeFile);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        
        qApp->setStyleSheet(styleSheet);
        
        settings->setValue("theme", themeName);
        settings->sync();
        
        emit themeChanged(themeName);
    } else {
        qWarning("Не удалось открыть файл темы: %s", qPrintable(themeFile));
    }
}

void Settings::startAutoSaveTimer() {
    autoSaveTimer->stop();
    
    autoSaveTimer->setInterval(saveInterval * 60 * 1000);
    
    autoSaveTimer->start();
}
