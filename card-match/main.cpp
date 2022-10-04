// CS315 Joey hurley
// I recieved help from online documentation

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}

