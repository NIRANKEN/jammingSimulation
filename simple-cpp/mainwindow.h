#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FIREVV3D.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  FIREVV3D *show_FIREVV3D();
 signals:
  void quit();
  void repaintEIG();
  private slots:
    void on_inputButton_clicked();

    void on_lineEdit_num_returnPressed();

    void on_eigvecButton_clicked();

    void on_zahyoButton_clicked();

    void on_exitButton_clicked();

 private:
    Ui::MainWindow *ui;
    FIREVV3D *fire3d_obj;

};

#endif // MAINWINDOW_H
