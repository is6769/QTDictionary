#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include <QFontDialog>
#include <QFileDialog>
#include <QStandardPaths>

SettingsDialog::SettingsDialog(Settings *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    appSettings(settings)
{
    ui->setupUi(this);
    
    // Setup theme dropdown
    ui->themeComboBox->addItem("Light", "light");
    ui->themeComboBox->addItem("Dark", "dark");
    
    // Connect signals
    connect(ui->fontButton, &QPushButton::clicked, this, &SettingsDialog::onSelectFont);
    connect(ui->autoSaveCheckBox, &QCheckBox::toggled, this, &SettingsDialog::onAutoSaveToggled);
    connect(ui->locationButton, &QPushButton::clicked, this, &SettingsDialog::onSelectAutoSaveLocation);
    connect(ui->themeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsDialog::onThemeChanged);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::onAccepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::onRejected);
    
    // Load settings
    loadCurrentSettings();
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::loadCurrentSettings() {
    // Font settings
    selectedFont = appSettings->getFont();
    updateFontPreview();
    
    // Theme settings
    QString theme = appSettings->getTheme();
    int themeIndex = ui->themeComboBox->findData(theme);
    if (themeIndex >= 0) {
        ui->themeComboBox->setCurrentIndex(themeIndex);
    } else {
        ui->themeComboBox->setCurrentIndex(0); // Default to light
    }
    selectedTheme = theme;
    
    // Auto-save settings
    autoSaveEnabled = appSettings->autoSaveEnabled();
    autoSaveInterval = appSettings->autoSaveInterval();
    autoSaveLocation = appSettings->autoSaveLocation();
    
    ui->autoSaveCheckBox->setChecked(autoSaveEnabled);
    ui->intervalSpinBox->setValue(autoSaveInterval);
    ui->locationLineEdit->setText(autoSaveLocation);
    
    ui->intervalSpinBox->setEnabled(autoSaveEnabled);
    ui->locationLineEdit->setEnabled(autoSaveEnabled);
    ui->locationButton->setEnabled(autoSaveEnabled);
    
    // Other settings
    confirmDeletion = appSettings->confirmDeletion();
    caseSensitiveSearch = appSettings->caseSensitiveSearch();
    maxRecentFiles = appSettings->maxRecentFiles();
    
    ui->confirmDeleteCheckBox->setChecked(confirmDeletion);
    ui->caseSensitiveCheckBox->setChecked(caseSensitiveSearch);
    ui->recentSpinBox->setValue(maxRecentFiles);
}

void SettingsDialog::onSelectFont() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, selectedFont, this, "Select Font");
    if (ok) {
        selectedFont = font;
        updateFontPreview();
    }
}

void SettingsDialog::updateFontPreview() {
    ui->fontPreviewLabel->setFont(selectedFont);
    ui->fontPreviewLabel->setText(QString("%1, %2pt").arg(selectedFont.family()).arg(selectedFont.pointSize()));
}

void SettingsDialog::onSelectAutoSaveLocation() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Auto-Save Location",
                                                  autoSaveLocation,
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        autoSaveLocation = dir;
        ui->locationLineEdit->setText(dir);
    }
}

void SettingsDialog::onAutoSaveToggled(bool checked) {
    ui->intervalSpinBox->setEnabled(checked);
    ui->locationLineEdit->setEnabled(checked);
    ui->locationButton->setEnabled(checked);
    autoSaveEnabled = checked;
}

void SettingsDialog::onThemeChanged(int index) {
    selectedTheme = ui->themeComboBox->itemData(index).toString();
}

void SettingsDialog::onAccepted() {
    // Apply font settings
    appSettings->setFont(selectedFont);
    
    // Apply theme settings
    appSettings->setTheme(selectedTheme);
    
    // Apply auto-save settings
    appSettings->setAutoSaveEnabled(autoSaveEnabled);
    appSettings->setAutoSaveInterval(ui->intervalSpinBox->value());
    appSettings->setAutoSaveLocation(autoSaveLocation);
    
    // Apply other settings
    appSettings->setConfirmDeletion(ui->confirmDeleteCheckBox->isChecked());
    appSettings->setCaseSensitiveSearch(ui->caseSensitiveCheckBox->isChecked());
    appSettings->setMaxRecentFiles(ui->recentSpinBox->value());
    
    // Save settings
    appSettings->saveSettings();
    
    accept();
}

void SettingsDialog::onRejected() {
    reject();
}
