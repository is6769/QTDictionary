/********************************************************************************
** Form generated from reading UI file 'AddEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEDITDIALOG_H
#define UI_ADDEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *wordLabel;
    QLineEdit *wordInput;
    QLabel *definitionLabel;
    QTextEdit *definitionInput;
    QLabel *examplesLabel;
    QTextEdit *examplesInput;
    QLabel *synonymsLabel;
    QLineEdit *synonymsInput;
    QLabel *antonymsLabel;
    QLineEdit *antonymsInput;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddEditDialog)
    {
        if (AddEditDialog->objectName().isEmpty())
            AddEditDialog->setObjectName("AddEditDialog");
        AddEditDialog->resize(450, 500);
        verticalLayout = new QVBoxLayout(AddEditDialog);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(15, 15, 15, 15);
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(10);
        wordLabel = new QLabel(AddEditDialog);
        wordLabel->setObjectName("wordLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, wordLabel);

        wordInput = new QLineEdit(AddEditDialog);
        wordInput->setObjectName("wordInput");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, wordInput);

        definitionLabel = new QLabel(AddEditDialog);
        definitionLabel->setObjectName("definitionLabel");
        definitionLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, definitionLabel);

        definitionInput = new QTextEdit(AddEditDialog);
        definitionInput->setObjectName("definitionInput");
        definitionInput->setMinimumSize(QSize(0, 100));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, definitionInput);

        examplesLabel = new QLabel(AddEditDialog);
        examplesLabel->setObjectName("examplesLabel");
        examplesLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, examplesLabel);

        examplesInput = new QTextEdit(AddEditDialog);
        examplesInput->setObjectName("examplesInput");
        examplesInput->setMinimumSize(QSize(0, 100));

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, examplesInput);

        synonymsLabel = new QLabel(AddEditDialog);
        synonymsLabel->setObjectName("synonymsLabel");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, synonymsLabel);

        synonymsInput = new QLineEdit(AddEditDialog);
        synonymsInput->setObjectName("synonymsInput");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, synonymsInput);

        antonymsLabel = new QLabel(AddEditDialog);
        antonymsLabel->setObjectName("antonymsLabel");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, antonymsLabel);

        antonymsInput = new QLineEdit(AddEditDialog);
        antonymsInput->setObjectName("antonymsInput");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, antonymsInput);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(AddEditDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AddEditDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AddEditDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AddEditDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AddEditDialog);
    } // setupUi

    void retranslateUi(QDialog *AddEditDialog)
    {
        AddEditDialog->setWindowTitle(QCoreApplication::translate("AddEditDialog", "Dialog", nullptr));
        wordLabel->setText(QCoreApplication::translate("AddEditDialog", "Word:", nullptr));
        definitionLabel->setText(QCoreApplication::translate("AddEditDialog", "Definition:", nullptr));
        examplesLabel->setText(QCoreApplication::translate("AddEditDialog", "Examples:", nullptr));
        examplesInput->setPlaceholderText(QCoreApplication::translate("AddEditDialog", "Enter examples (one per line)", nullptr));
        synonymsLabel->setText(QCoreApplication::translate("AddEditDialog", "Synonyms:", nullptr));
        synonymsInput->setPlaceholderText(QCoreApplication::translate("AddEditDialog", "Enter synonyms (comma separated)", nullptr));
        antonymsLabel->setText(QCoreApplication::translate("AddEditDialog", "Antonyms:", nullptr));
        antonymsInput->setPlaceholderText(QCoreApplication::translate("AddEditDialog", "Enter antonyms (comma separated)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddEditDialog: public Ui_AddEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEDITDIALOG_H
