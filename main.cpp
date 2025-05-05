#include <QApplication>
#include "MainWindow.h"
#include "Settings.h"

int main(int argc, char *argv[]) {
    // Создание экземпляра приложения Qt
    QApplication app(argc, argv);
    
    // Установка имени и организации приложения для правильного хранения настроек
    app.setApplicationName("Dictionary Application");
    app.setOrganizationName("Dictionary Project");
    
    // Инициализация настроек приложения на раннем этапе
    // для правильного применения темы и других параметров
    Settings appSettings;
    
    // Применение выбранной темы перед отображением любых виджетов
    appSettings.applyTheme();
    
    // Применение настроек шрифта ко всему приложению
    QFont appFont = appSettings.getFont();
    QApplication::setFont(appFont);
    
    // Создание и отображение главного окна приложения
    MainWindow mainWindow;
    mainWindow.show();
    
    // Запуск главного цикла обработки событий приложения
    // и возврат кода завершения при выходе
    return app.exec();
}
