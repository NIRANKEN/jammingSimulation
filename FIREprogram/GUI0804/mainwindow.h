#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
//#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initialSetParameters();
    void initialSetParameter(int val,QLineEdit *le,QLabel *lb);
    void initialSetParameter(double val,QLineEdit *le,QLabel *lb);
    inline void modifyStatus();
    inline void startMethod();

public slots:
    void calculatedVV();
    void calculateVV();

    signals:
   void startSim();
    void stopSim();
    void calculatedSim();
    void quitApp();

private slots:

    void on_seed_in_returnPressed();

    void on_phi_in_returnPressed();

    void on_crrate_in_returnPressed();

    void on_N_in_returnPressed();

    void on_pex_in_returnPressed();

    void on_mix2_in_returnPressed();

    void on_lx_in_returnPressed();

    void on_ly_in_returnPressed();

    void on_sr_in_returnPressed();

    void on_mix1_in_returnPressed();

    void on_tstep_in_returnPressed();

    void on_damp_in_returnPressed();

    void on_IFT_in_returnPressed();

    void on_DFT_in_returnPressed();

    void on_DFDT_in_returnPressed();

    void on_DTinit_in_returnPressed();

    void on_maxT_in_returnPressed();

    void on_delayFIRE_in_returnPressed();

    void on_sysdefBt_clicked();

    void on_MDdefBt_clicked();

    void on_startBt_clicked();

    void on_noiseBt_clicked();

    void on_repBt_clicked();

    void on_resetPtBt_clicked();

    void on_burnBt_clicked();

    void on_readBt_clicked();

    void on_calcmodeBt_clicked();

    void on_writeeigBt_clicked();

    void on_ccgBt_clicked();

    void on_pushButton_clicked();

    void on_exit_bt_clicked();

    void on_startBt_2_clicked();

    void on_eignum_le_returnPressed();

private:
    Ui::MainWindow *ui;
    bool isSimulated;
    QTimer *tim;
};

#endif // MAINWINDOW_H
