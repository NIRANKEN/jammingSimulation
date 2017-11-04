#include "FIREVV.h"
#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
//#include "ENTERev.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  //QWidget* window =new QWidget;
  MainWindow *mw = new MainWindow;
  QObject::connect(mw,SIGNAL(quitApp()),&app,SLOT(quit()));
  return app.exec();
}
