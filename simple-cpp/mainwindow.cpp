#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  fire3d_obj=new FIREVV3D();

  ui->setupUi(this);
  this->show();
}

MainWindow::~MainWindow()
{
  delete fire3d_obj;
  delete ui;
}

FIREVV3D* MainWindow::show_FIREVV3D()
{
  return fire3d_obj;
}

void MainWindow::on_inputButton_clicked()
{
  fire3d_obj->inputZahyoData3D();
}

void MainWindow::on_lineEdit_num_returnPressed()
{
  int n=ui->lineEdit_num->text().toInt();
  fire3d_obj->set_EigNum(n);
  emit repaintEIG();
}

void MainWindow::on_eigvecButton_clicked()
{
  fire3d_obj->calculateEigData3D();
}

void MainWindow::on_zahyoButton_clicked()
{
  fire3d_obj->set_CalculatedEigMode(false);
}

void MainWindow::on_exitButton_clicked()
{
  emit quit();
}
