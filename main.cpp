#include <QApplication>
#include "MainWindow.h"
#include "Settings.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setApplicationName("Dictionary Application");
    app.setOrganizationName("Dictionary Project");
    
    Settings appSettings;
    
    appSettings.applyTheme();
    
    QFont appFont = appSettings.getFont();
    QApplication::setFont(appFont);
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}
