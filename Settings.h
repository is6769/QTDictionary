#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFont>
#include <QColor>
#include <QString>
#include <QTimer>

class Settings : public QObject {
    Q_OBJECT

public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings();

    // Theme settings
    QString getTheme() const;
    void setTheme(const QString &theme);

    // Font settings
    QFont getFont() const;
    void setFont(const QFont &font);

    // Auto-save settings
    bool autoSaveEnabled() const;
    void setAutoSaveEnabled(bool enabled);
    
    int autoSaveInterval() const;
    void setAutoSaveInterval(int minutes);
    
    QString autoSaveLocation() const;
    void setAutoSaveLocation(const QString &location);

    // Other settings
    bool confirmDeletion() const;
    void setConfirmDeletion(bool confirm);
    
    bool caseSensitiveSearch() const;
    void setCaseSensitiveSearch(bool sensitive);
    
    int maxRecentFiles() const;
    void setMaxRecentFiles(int max);
    
    QStringList recentFiles() const;
    void addRecentFile(const QString &filePath);
    void clearRecentFiles();

    // Load/save settings
    void loadSettings();
    void saveSettings();
    
    // Apply theme
    void applyTheme();

signals:
    void themeChanged(const QString &theme);
    void fontChanged(const QFont &font);
    void autoSaveSettingsChanged();
    void autoSaveNow();

private:
    QSettings *settings;
    QString themeName;
    QFont appFont;
    bool autoSave;
    int saveInterval;
    QString saveLocation;
    bool confirmDelete;
    bool caseSensitive;
    int maxRecent;
    QStringList recentFilesList;
    QTimer *autoSaveTimer;

    void setupDefaults();
    void startAutoSaveTimer();
};

#endif // SETTINGS_H
