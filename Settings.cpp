#include "Settings.h"
#include <QDir>
#include <QStandardPaths>
#include <QApplication>
#include <QFile>
#include <QFontDatabase>

// Конструктор класса настроек, инициализирует базовые параметры и загружает сохраненные настройки
Settings::Settings(QObject *parent) : QObject(parent) {
    // Инициализация объекта настроек Qt для хранения параметров приложения
    settings = new QSettings("Dictionary Project", "Dictionary", this);
    
    // Создание таймера автосохранения
    autoSaveTimer = new QTimer(this);
    
    // Подключение сигнала таймера к слоту автосохранения
    connect(autoSaveTimer, &QTimer::timeout, this, &Settings::autoSaveNow);
    
    // Установка значений по умолчанию и загрузка настроек из хранилища
    setupDefaults();
    loadSettings();
}

// Деструктор класса настроек, сохраняет текущие настройки перед уничтожением объекта
Settings::~Settings() {
    // Сохранение текущих настроек перед выходом
    saveSettings();
    
    // Освобождение ресурсов, занятых объектом настроек
    delete settings;
}

// Инициализация настроек значениями по умолчанию
void Settings::setupDefaults() {
    // По умолчанию используется светлая тема
    themeName = "light";
    
    // Используем системный шрифт приложения
    appFont = QApplication::font();
    
    // Автосохранение по умолчанию отключено
    autoSave = false;
    
    // Интервал автосохранения - 5 минут
    saveInterval = 5;
    
    // Расположение файлов автосохранения - папка документов пользователя
    saveLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    
    // Дополнительные настройки
    confirmDelete = true;      // Подтверждение удаления включено
    caseSensitive = false;     // Поиск без учета регистра
    maxRecent = 5;             // Количество отображаемых недавних файлов
}

// Загрузка сохраненных настроек из QSettings
void Settings::loadSettings() {
    // Загрузка темы, по умолчанию - светлая
    themeName = settings->value("theme", "light").toString();
    
    // Загрузка шрифта, если он был сохранен
    if (settings->contains("font")) {
        appFont.fromString(settings->value("font").toString());
    }
    
    // Загрузка настроек автосохранения
    autoSave = settings->value("autoSave/enabled", false).toBool();
    saveInterval = settings->value("autoSave/interval", 5).toInt();
    saveLocation = settings->value("autoSave/location", 
                                   QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
    
    // Загрузка прочих настроек
    confirmDelete = settings->value("confirmDeletion", true).toBool();
    caseSensitive = settings->value("caseSensitiveSearch", false).toBool();
    maxRecent = settings->value("maxRecentFiles", 5).toInt();
    recentFilesList = settings->value("recentFiles").toStringList();
    
    // Если автосохранение включено, запускаем таймер
    if (autoSave) {
        startAutoSaveTimer();
    }
}

// Сохранение текущих настроек в постоянное хранилище
void Settings::saveSettings() {
    // Сохранение основных настроек
    settings->setValue("theme", themeName);
    settings->setValue("font", appFont.toString());
    
    // Сохранение настроек автосохранения
    settings->setValue("autoSave/enabled", autoSave);
    settings->setValue("autoSave/interval", saveInterval);
    settings->setValue("autoSave/location", saveLocation);
    
    // Сохранение прочих настроек
    settings->setValue("confirmDeletion", confirmDelete);
    settings->setValue("caseSensitiveSearch", caseSensitive);
    settings->setValue("maxRecentFiles", maxRecent);
    settings->setValue("recentFiles", recentFilesList);
    
    // Синхронизация с файловой системой
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
        // Trim list if needed
        while (recentFilesList.size() > maxRecent && !recentFilesList.isEmpty()) {
            recentFilesList.removeLast();
        }
    }
}

QStringList Settings::recentFiles() const {
    return recentFilesList;
}

void Settings::addRecentFile(const QString &filePath) {
    // Remove if already exists (to move it to top)
    recentFilesList.removeAll(filePath);
    
    // Add to beginning
    recentFilesList.prepend(filePath);
    
    // Trim list if needed
    while (recentFilesList.size() > maxRecent && !recentFilesList.isEmpty()) {
        recentFilesList.removeLast();
    }
}

void Settings::clearRecentFiles() {
    recentFilesList.clear();
}

// Применение выбранной темы к приложению
void Settings::applyTheme() {
    QString themeFile;
    
    // Выбор файла темы в зависимости от текущих настроек
    if (themeName == "dark") {
        themeFile = ":/themes/dark.qss";
    } else { // По умолчанию используется светлая тема
        themeFile = ":/themes/light.qss";
    }
    
    // Загрузка и применение файла таблицы стилей
    QFile file(themeFile);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        
        // Применение таблицы стилей ко всему приложению
        qApp->setStyleSheet(styleSheet);
        
        // Сохранение имени темы для постоянства
        settings->setValue("theme", themeName);
        settings->sync();
        
        // Уведомление о смене темы (для компонентов, которым нужно реагировать)
        emit themeChanged(themeName);
    } else {
        qWarning("Не удалось открыть файл темы: %s", qPrintable(themeFile));
    }
}

// Запуск таймера автосохранения с учетом установленного интервала
void Settings::startAutoSaveTimer() {
    // Останавливаем предыдущий таймер
    autoSaveTimer->stop();
    
    // Устанавливаем интервал в миллисекундах (из минут)
    autoSaveTimer->setInterval(saveInterval * 60 * 1000);
    
    // Запускаем таймер
    autoSaveTimer->start();
}
