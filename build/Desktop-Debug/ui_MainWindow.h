/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *addAction;
    QAction *editAction;
    QAction *deleteAction;
    QAction *exportAction;
    QAction *importAction;
    QAction *exitAction;
    QAction *settingsAction;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *aboutAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *searchLayout;
    QLabel *label;
    QLineEdit *searchBar;
    QPushButton *searchButton;
    QSplitter *splitter;
    QListWidget *wordListWidget;
    QTextEdit *resultDisplay;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        addAction = new QAction(MainWindow);
        addAction->setObjectName("addAction");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("list-add")));
        addAction->setIcon(icon);
        editAction = new QAction(MainWindow);
        editAction->setObjectName("editAction");
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("document-edit")));
        editAction->setIcon(icon1);
        deleteAction = new QAction(MainWindow);
        deleteAction->setObjectName("deleteAction");
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("edit-delete")));
        deleteAction->setIcon(icon2);
        exportAction = new QAction(MainWindow);
        exportAction->setObjectName("exportAction");
        importAction = new QAction(MainWindow);
        importAction->setObjectName("importAction");
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName("exitAction");
        settingsAction = new QAction(MainWindow);
        settingsAction->setObjectName("settingsAction");
        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("preferences-system")));
        settingsAction->setIcon(icon3);
        newAction = new QAction(MainWindow);
        newAction->setObjectName("newAction");
        QIcon icon4(QIcon::fromTheme(QString::fromUtf8("document-new")));
        newAction->setIcon(icon4);
        openAction = new QAction(MainWindow);
        openAction->setObjectName("openAction");
        QIcon icon5(QIcon::fromTheme(QString::fromUtf8("document-open")));
        openAction->setIcon(icon5);
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName("saveAction");
        QIcon icon6(QIcon::fromTheme(QString::fromUtf8("document-save")));
        saveAction->setIcon(icon6);
        saveAsAction = new QAction(MainWindow);
        saveAsAction->setObjectName("saveAsAction");
        QIcon icon7(QIcon::fromTheme(QString::fromUtf8("document-save-as")));
        saveAsAction->setIcon(icon7);
        aboutAction = new QAction(MainWindow);
        aboutAction->setObjectName("aboutAction");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(10);
        searchLayout->setObjectName("searchLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        searchLayout->addWidget(label);

        searchBar = new QLineEdit(centralwidget);
        searchBar->setObjectName("searchBar");
        searchBar->setClearButtonEnabled(true);

        searchLayout->addWidget(searchBar);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        QIcon icon8(QIcon::fromTheme(QString::fromUtf8("search")));
        searchButton->setIcon(icon8);

        searchLayout->addWidget(searchButton);


        verticalLayout->addLayout(searchLayout);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        wordListWidget = new QListWidget(splitter);
        wordListWidget->setObjectName("wordListWidget");
        wordListWidget->setMinimumSize(QSize(200, 0));
        wordListWidget->setAlternatingRowColors(true);
        wordListWidget->setSortingEnabled(true);
        splitter->addWidget(wordListWidget);
        resultDisplay = new QTextEdit(splitter);
        resultDisplay->setObjectName("resultDisplay");
        resultDisplay->setReadOnly(true);
        splitter->addWidget(resultDisplay);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(newAction);
        menuFile->addAction(openAction);
        menuFile->addAction(saveAction);
        menuFile->addAction(saveAsAction);
        menuFile->addSeparator();
        menuFile->addAction(addAction);
        menuFile->addAction(editAction);
        menuFile->addAction(deleteAction);
        menuFile->addSeparator();
        menuFile->addAction(exportAction);
        menuFile->addAction(importAction);
        menuFile->addSeparator();
        menuFile->addAction(exitAction);
        menuSettings->addAction(settingsAction);
        menuHelp->addAction(aboutAction);
        toolBar->addAction(newAction);
        toolBar->addAction(openAction);
        toolBar->addAction(saveAction);
        toolBar->addSeparator();
        toolBar->addAction(addAction);
        toolBar->addAction(editAction);
        toolBar->addAction(deleteAction);
        toolBar->addSeparator();
        toolBar->addAction(settingsAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Dictionary Application", nullptr));
        addAction->setText(QCoreApplication::translate("MainWindow", "&Add Word", nullptr));
#if QT_CONFIG(shortcut)
        addAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        editAction->setText(QCoreApplication::translate("MainWindow", "&Edit Word", nullptr));
#if QT_CONFIG(shortcut)
        editAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        deleteAction->setText(QCoreApplication::translate("MainWindow", "&Delete Word", nullptr));
#if QT_CONFIG(shortcut)
        deleteAction->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        exportAction->setText(QCoreApplication::translate("MainWindow", "E&xport Dictionary", nullptr));
#if QT_CONFIG(shortcut)
        exportAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+X", nullptr));
#endif // QT_CONFIG(shortcut)
        importAction->setText(QCoreApplication::translate("MainWindow", "&Import Dictionary", nullptr));
#if QT_CONFIG(shortcut)
        importAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+I", nullptr));
#endif // QT_CONFIG(shortcut)
        exitAction->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
#if QT_CONFIG(shortcut)
        exitAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        settingsAction->setText(QCoreApplication::translate("MainWindow", "&Settings...", nullptr));
        newAction->setText(QCoreApplication::translate("MainWindow", "&New Dictionary", nullptr));
#if QT_CONFIG(shortcut)
        newAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        openAction->setText(QCoreApplication::translate("MainWindow", "&Open Dictionary...", nullptr));
#if QT_CONFIG(shortcut)
        openAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        saveAction->setText(QCoreApplication::translate("MainWindow", "&Save Dictionary", nullptr));
#if QT_CONFIG(shortcut)
        saveAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        saveAsAction->setText(QCoreApplication::translate("MainWindow", "Save Dictionary &As...", nullptr));
#if QT_CONFIG(shortcut)
        saveAsAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        aboutAction->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Search:", nullptr));
        searchBar->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter a word to search...", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        resultDisplay->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"h2 { color: #2c3e50; }\n"
"b { color: #34495e; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Search for a word or select one from the list.</p></body></html>", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "&Settings", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "&Help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
