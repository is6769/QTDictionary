/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *appearanceTab;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *themeLabel;
    QComboBox *themeComboBox;
    QLabel *fontLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *fontPreviewLabel;
    QPushButton *fontButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *autoSaveTab;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *autoSaveCheckBox;
    QFormLayout *formLayout_2;
    QLabel *intervalLabel;
    QSpinBox *intervalSpinBox;
    QLabel *locationLabel;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *locationLineEdit;
    QPushButton *locationButton;
    QSpacerItem *verticalSpacer;
    QWidget *otherTab;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *confirmDeleteCheckBox;
    QCheckBox *caseSensitiveCheckBox;
    QFormLayout *formLayout_3;
    QLabel *recentLabel;
    QSpinBox *recentSpinBox;
    QSpacerItem *verticalSpacer_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->resize(500, 450);
        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(SettingsDialog);
        tabWidget->setObjectName("tabWidget");
        appearanceTab = new QWidget();
        appearanceTab->setObjectName("appearanceTab");
        verticalLayout_2 = new QVBoxLayout(appearanceTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        themeLabel = new QLabel(appearanceTab);
        themeLabel->setObjectName("themeLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, themeLabel);

        themeComboBox = new QComboBox(appearanceTab);
        themeComboBox->setObjectName("themeComboBox");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, themeComboBox);

        fontLabel = new QLabel(appearanceTab);
        fontLabel->setObjectName("fontLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, fontLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        fontPreviewLabel = new QLabel(appearanceTab);
        fontPreviewLabel->setObjectName("fontPreviewLabel");
        fontPreviewLabel->setFrameShape(QFrame::Panel);
        fontPreviewLabel->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(fontPreviewLabel);

        fontButton = new QPushButton(appearanceTab);
        fontButton->setObjectName("fontButton");

        horizontalLayout->addWidget(fontButton);


        formLayout->setLayout(1, QFormLayout::ItemRole::FieldRole, horizontalLayout);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer_2 = new QSpacerItem(20, 250, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tabWidget->addTab(appearanceTab, QString());
        autoSaveTab = new QWidget();
        autoSaveTab->setObjectName("autoSaveTab");
        verticalLayout_3 = new QVBoxLayout(autoSaveTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        autoSaveCheckBox = new QCheckBox(autoSaveTab);
        autoSaveCheckBox->setObjectName("autoSaveCheckBox");

        verticalLayout_3->addWidget(autoSaveCheckBox);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        intervalLabel = new QLabel(autoSaveTab);
        intervalLabel->setObjectName("intervalLabel");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, intervalLabel);

        intervalSpinBox = new QSpinBox(autoSaveTab);
        intervalSpinBox->setObjectName("intervalSpinBox");
        intervalSpinBox->setMinimum(1);
        intervalSpinBox->setMaximum(60);
        intervalSpinBox->setValue(5);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, intervalSpinBox);

        locationLabel = new QLabel(autoSaveTab);
        locationLabel->setObjectName("locationLabel");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, locationLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        locationLineEdit = new QLineEdit(autoSaveTab);
        locationLineEdit->setObjectName("locationLineEdit");

        horizontalLayout_2->addWidget(locationLineEdit);

        locationButton = new QPushButton(autoSaveTab);
        locationButton->setObjectName("locationButton");

        horizontalLayout_2->addWidget(locationButton);


        formLayout_2->setLayout(1, QFormLayout::ItemRole::FieldRole, horizontalLayout_2);


        verticalLayout_3->addLayout(formLayout_2);

        verticalSpacer = new QSpacerItem(20, 250, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(autoSaveTab, QString());
        otherTab = new QWidget();
        otherTab->setObjectName("otherTab");
        verticalLayout_4 = new QVBoxLayout(otherTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        confirmDeleteCheckBox = new QCheckBox(otherTab);
        confirmDeleteCheckBox->setObjectName("confirmDeleteCheckBox");

        verticalLayout_4->addWidget(confirmDeleteCheckBox);

        caseSensitiveCheckBox = new QCheckBox(otherTab);
        caseSensitiveCheckBox->setObjectName("caseSensitiveCheckBox");

        verticalLayout_4->addWidget(caseSensitiveCheckBox);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        recentLabel = new QLabel(otherTab);
        recentLabel->setObjectName("recentLabel");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, recentLabel);

        recentSpinBox = new QSpinBox(otherTab);
        recentSpinBox->setObjectName("recentSpinBox");
        recentSpinBox->setMinimum(0);
        recentSpinBox->setMaximum(20);
        recentSpinBox->setValue(5);

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, recentSpinBox);


        verticalLayout_4->addLayout(formLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 250, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        tabWidget->addTab(otherTab, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SettingsDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dictionary Settings", nullptr));
        themeLabel->setText(QCoreApplication::translate("SettingsDialog", "Theme:", nullptr));
        fontLabel->setText(QCoreApplication::translate("SettingsDialog", "Font:", nullptr));
        fontPreviewLabel->setText(QCoreApplication::translate("SettingsDialog", "Font Preview", nullptr));
        fontButton->setText(QCoreApplication::translate("SettingsDialog", "Change Font...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(appearanceTab), QCoreApplication::translate("SettingsDialog", "Appearance", nullptr));
        autoSaveCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Enable auto-save", nullptr));
        intervalLabel->setText(QCoreApplication::translate("SettingsDialog", "Auto-save interval (minutes):", nullptr));
        locationLabel->setText(QCoreApplication::translate("SettingsDialog", "Auto-save location:", nullptr));
        locationButton->setText(QCoreApplication::translate("SettingsDialog", "Browse...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(autoSaveTab), QCoreApplication::translate("SettingsDialog", "Auto-Save", nullptr));
        confirmDeleteCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Confirm word deletion", nullptr));
        caseSensitiveCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Case sensitive search", nullptr));
        recentLabel->setText(QCoreApplication::translate("SettingsDialog", "Maximum recent files:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(otherTab), QCoreApplication::translate("SettingsDialog", "Other", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
