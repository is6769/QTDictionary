#ifndef ADDEDITDIALOG_H
#define ADDEDITDIALOG_H

#include <QDialog>
#include "WordDefinition.h"

namespace Ui {
class AddEditDialog;
}

class AddEditDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddEditDialog(QWidget* parent = nullptr, WordDefinition* wordDefToEdit = nullptr);
    ~AddEditDialog();
    WordDefinition getWordDefinition();

private slots:
    void saveWord();

private:
    Ui::AddEditDialog *ui;
    WordDefinition* wordDef;
    bool isEditMode;

    void fillFieldsFromWord();
};

#endif // ADDEDITDIALOG_H
