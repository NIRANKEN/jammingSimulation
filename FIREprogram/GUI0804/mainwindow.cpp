#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),isSimulated(false),tim(new QTimer())
{
    //qDebug()<<"timer:"<<tim->remainingTime()<<"ms"<<endl;
    ui->setupUi(this);
    tim->setSingleShot(true);
   // QObject::connect(this,SIGNAL(startSim()),tim,SLOT(start(1)));
    QObject::connect(this,SIGNAL(stopSim()),tim,SLOT(stop()));
    QObject::connect(this,SIGNAL(startSim()),ui->Grp,SLOT(VerletDO()));
    QObject::connect(ui->Grp,&FIREVV::VVfin,[this](){tim->start(1);});
    QObject::connect(ui->Grp,SIGNAL(created()),tim,SLOT(stop()));
    QObject::connect(tim,SIGNAL(timeout()),ui->Grp,SLOT(VerletDO()));
    //QObject::connect(tim,&QTimer::timeout,[this](){ui->repBt->setText("Hello World!");});
    modifyStatus();
    this->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initialSetParameters()
{
    initialSetParameter(ui->Grp->Show_alpha(),ui->pex_in,ui->pex_v);
    initialSetParameter(ui->Grp->Show_Lengx(),ui->lx_in,ui->lx_v);
    initialSetParameter(ui->Grp->Show_Lengy(),ui->ly_in,ui->ly_v);
    initialSetParameter(ui->Grp->Show_PHI(),ui->phi_in,ui->phi_v);
    initialSetParameter(ui->Grp->Show_PN(),ui->N_in,ui->N_v);
    initialSetParameter(ui->Grp->Show_ratio(),ui->sr_in,ui->sr_v);
    initialSetParameter(ui->Grp->Show_Pratio1(),ui->mix1_in,ui->mix1_v);
    initialSetParameter(ui->Grp->Show_Pratio2(),ui->mix2_in,ui->mix2_v);

    initialSetParameter(ui->Grp->Show_Tstep(),ui->tstep_in,ui->tstep_v);
    initialSetParameter(ui->Grp->Show_TstepM(),ui->maxT_in,ui->maxT_v);
    initialSetParameter(ui->Grp->Show_DMPt()/ui->Grp->Show_Tstep(),ui->damp_in,ui->damp_v);
    initialSetParameter(ui->Grp->Show_dmptI(),ui->DTinit_in,ui->DTinit_v);
    initialSetParameter(ui->Grp->Show_fraI(),ui->IFT_in,ui->IFT_v);
    initialSetParameter(ui->Grp->Show_fraD(),ui->DFT_in,ui->DFT_v);
    initialSetParameter(ui->Grp->Show_fraA(),ui->DFDT_in,ui->DFDT_v);
    initialSetParameter(ui->Grp->Show_ITFIRE(),ui->delayFIRE_in,ui->delayFIRE_v);
}

void MainWindow::initialSetParameter(int val,QLineEdit *le,QLabel *lb)
{
    le->setText(QString::number(val));
    lb->setText("("+QString::number(val)+")");
}
void MainWindow::initialSetParameter(double val,QLineEdit *le,QLabel *lb)
{
    le->setText(QString::number(val));
    lb->setText("("+QString::number(val)+")");
}
inline void MainWindow::modifyStatus()
{
    QObject::connect(this,&MainWindow::startSim,[this](){
        ui->state_lb->setText("mechanical unstable><");
        ui->eng_lb->setText(QString::number(ui->Grp->Show_func()));
        ui->phi_lb->setText(QString::number(ui->Grp->Show_PHI()));
        if(ui->Grp->Show_func()==0.0){

            QFont status_font=QFont("Arial",15,QFont::Bold);
            QPalette status_palette=ui->status_lb->palette();
            status_palette.setColor(QPalette::Foreground,QColor(Qt::blue));
            ui->status_lb->setFont(status_font);
            ui->status_lb->setPalette(status_palette);
            ui->status_lb->setText("UNJAMMED STATE");
        }
        else{

            QFont status_font=QFont("Arial",15,QFont::Bold);
            QPalette status_palette=ui->status_lb->palette();
            status_palette.setColor(QPalette::Foreground,QColor(Qt::red));
            ui->status_lb->setFont(status_font);
            ui->status_lb->setPalette(status_palette);
            ui->status_lb->setText("JAMMED STATE");
        }
        ui->eignum_lb->setText("???");
        ui->cvc_lb->setText("???");
        ui->mode_lb->setText("???");
    });
    QObject::connect(ui->Grp,&FIREVV::VVfin,[this](){
        ui->eng_lb->setText(QString::number(ui->Grp->Show_func()));

    });
    QObject::connect(ui->Grp,&FIREVV::minfunc,[this]()
    {
        ui->state_lb->setText("mechanical stable^^");
        if(ui->Grp->Show_func()==0.0){

            QFont status_font=QFont("Arial",15,QFont::Bold);
            QPalette status_palette=ui->status_lb->palette();
            status_palette.setColor(QPalette::Foreground,QColor(Qt::blue));

            ui->status_lb->setFont(status_font);
            ui->status_lb->setPalette(status_palette);
            ui->status_lb->setText("UNJAMMED STATE");
        }
        else{

            QFont status_font=QFont("Arial",15,QFont::Bold);
            QPalette status_palette=ui->status_lb->palette();
            status_palette.setColor(QPalette::Foreground,QColor(Qt::red));
            ui->status_lb->setFont(status_font);
            ui->status_lb->setPalette(status_palette);
            ui->status_lb->setText("JAMMED STATE");
        }
    });
}

inline void MainWindow::startMethod()
{
    if(isSimulated) {
        isSimulated=false;
        ui->startBt->setText("START");
        ui->startBt_2->setText("START");
        //tim->stop();
        emit stopSim();
    }
    else {
        isSimulated=true;
        //tim->start(1);
        ui->startBt->setText("STOP");
        ui->startBt_2->setText("STOP");
        emit startSim();
        /*
        while(isSimulated) {
            ttt->setSingleShot(true);
            QObject::connect(ttt,SIGNAL(timeout()),ui->Grp,SLOT(VerletDO()));
            QObject::connect(ui->Grp,SIGNAL(VVfin()),ttt,SLOT(start(0.2)));
            QObject::connect(ui->startBt,&QPushButton::clicked,[this](){isSimulated=false;ui->startBt->setText("START");});
        }
        */
   //     emit startSimulation();
    }
}

void MainWindow::calculatedVV()
{
    emit calculatedSim();
}
void MainWindow::calculateVV()
{
    ui->Grp->VerletDO();
}

void MainWindow::on_seed_in_returnPressed()
{
ui->Grp->Gen_zahyo(ui->seed_in->text().toInt(),ui->Grp->Show_PN());
ui->seed_v->setText("("+ui->seed_in->text()+")");
}

void MainWindow::on_phi_in_returnPressed()
{
    ui->Grp->Gen_PHI(ui->phi_in->text().toDouble(),ui->Grp->Show_Lengx(),ui->Grp->Show_Lengy(),ui->Grp->Show_PN());
    ui->phi_v->setText("("+QString::number(ui->Grp->Show_PHI())+")");

}

void MainWindow::on_crrate_in_returnPressed()
{
ui->Grp->Inc_PHI(ui->crrate_in->text().toDouble(),ui->Grp->Show_PN());
ui->phi_v->setText("("+QString::number(ui->Grp->Show_PHI())+")");
}

void MainWindow::on_N_in_returnPressed()
{
ui->Grp->Set_PN(ui->N_in->text().toInt());
ui->N_v->setText("("+QString::number(ui->Grp->Show_PN())+")");
}

void MainWindow::on_pex_in_returnPressed()
{
    ui->Grp->Set_alpha(ui->pex_in->text().toDouble());
    ui->pex_v->setText("("+QString::number(ui->Grp->Show_alpha())+")");
}

void MainWindow::on_lx_in_returnPressed()
{
    ui->Grp->Set_Lengx(ui->lx_in->text().toDouble());
    ui->lx_v->setText("("+QString::number(ui->Grp->Show_Lengx())+")");
}

void MainWindow::on_ly_in_returnPressed()
{
    ui->Grp->Set_Lengy(ui->ly_in->text().toDouble());
    ui->ly_v->setText("("+QString::number(ui->Grp->Show_Lengy())+")");
}

void MainWindow::on_sr_in_returnPressed()
{
ui->Grp->Set_ratio(ui->sr_in->text().toDouble());
ui->sr_v->setText("("+QString::number(ui->Grp->Show_ratio())+")");
}

void MainWindow::on_mix1_in_returnPressed()
{
    ui->Grp->Set_Pratio1(ui->mix1_in->text().toInt());
    ui->mix1_v->setText("("+QString::number(ui->Grp->Show_Pratio1())+")");
}

void MainWindow::on_mix2_in_returnPressed()
{
    ui->Grp->Set_Pratio2(ui->mix2_in->text().toInt());
    ui->mix2_v->setText("("+QString::number(ui->Grp->Show_Pratio2())+")");
}

void MainWindow::on_tstep_in_returnPressed()
{
    ui->Grp->Set_Tstep(ui->tstep_in->text().toDouble());
    ui->tstep_v->setText("("+QString::number(ui->Grp->Show_Tstep())+")");
}

void MainWindow::on_damp_in_returnPressed()
{
    ui->Grp->Set_DMPt(ui->damp_in->text().toDouble()*ui->Grp->Show_Tstep());
    ui->damp_in->setText("("+QString::number(ui->Grp->Show_DMPt()/ui->Grp->Show_Tstep())+")");
}

void MainWindow::on_IFT_in_returnPressed()
{
    ui->Grp->Set_fraI(ui->IFT_in->text().toDouble());
    ui->IFT_v->setText("("+QString::number(ui->Grp->Show_fraI())+")");
}

void MainWindow::on_DFT_in_returnPressed()
{
    ui->Grp->Set_fraD(ui->DFT_in->text().toDouble());
    ui->DFT_v->setText("("+QString::number(ui->Grp->Show_fraD())+")");
}

void MainWindow::on_DFDT_in_returnPressed()
{
    ui->Grp->Set_fraA(ui->DFDT_in->text().toDouble());
    ui->DFDT_v->setText("("+QString::number(ui->Grp->Show_fraA())+")");
}

void MainWindow::on_DTinit_in_returnPressed()
{
    ui->Grp->Set_dmptI(ui->DTinit_in->text().toDouble());
    ui->DTinit_v->setText("("+QString::number(ui->Grp->Show_dmptI())+")");
}

void MainWindow::on_maxT_in_returnPressed()
{
    ui->Grp->Set_TstepM(ui->maxT_in->text().toDouble());
    ui->maxT_v->setText("("+QString::number(ui->Grp->Show_TstepM())+")");
}

void MainWindow::on_delayFIRE_in_returnPressed()
{
    ui->Grp->Set_ITFIRE(ui->delayFIRE_in->text().toInt());
    ui->delayFIRE_v->setText("("+QString::number(ui->Grp->Show_ITFIRE())+")");
}

void MainWindow::on_sysdefBt_clicked()
{
    //modify initial value...

    //Grp wo init state ni suru

    initialSetParameter(ui->Grp->Show_alpha(),ui->pex_in,ui->pex_v);
    initialSetParameter(ui->Grp->Show_Lengx(),ui->lx_in,ui->lx_v);
    initialSetParameter(ui->Grp->Show_Lengy(),ui->ly_in,ui->ly_v);
    initialSetParameter(ui->Grp->Show_PHI(),ui->phi_in,ui->phi_v);
    initialSetParameter(ui->Grp->Show_PN(),ui->N_in,ui->N_v);
    initialSetParameter(ui->Grp->Show_ratio(),ui->sr_in,ui->sr_v);
    initialSetParameter(ui->Grp->Show_Pratio1(),ui->mix1_in,ui->mix1_v);
    initialSetParameter(ui->Grp->Show_Pratio2(),ui->mix2_in,ui->mix2_v);
}

void MainWindow::on_MDdefBt_clicked()
{
     //Grp wo init state ni suru

    initialSetParameter(ui->Grp->Show_Tstep(),ui->tstep_in,ui->tstep_v);
        initialSetParameter(ui->Grp->Show_TstepM(),ui->maxT_in,ui->maxT_v);
        initialSetParameter(ui->Grp->Show_DMPt()/ui->Grp->Show_Tstep(),ui->damp_in,ui->damp_v);
        initialSetParameter(ui->Grp->Show_dmptI(),ui->DTinit_in,ui->DTinit_v);
        initialSetParameter(ui->Grp->Show_fraI(),ui->IFT_in,ui->IFT_v);
        initialSetParameter(ui->Grp->Show_fraD(),ui->DFT_in,ui->DFT_v);
        initialSetParameter(ui->Grp->Show_fraA(),ui->DFDT_in,ui->DFDT_v);
        initialSetParameter(ui->Grp->Show_ITFIRE(),ui->delayFIRE_in,ui->delayFIRE_v);
}

void MainWindow::on_startBt_clicked()
{
startMethod();
}

void MainWindow::on_noiseBt_clicked()
{
ui->Grp->Noise();
}

void MainWindow::on_repBt_clicked()
{
ui->Grp->repaint();
}

void MainWindow::on_resetPtBt_clicked()
{
ui->Grp->Set_Pntcnt(0);

}

void MainWindow::on_burnBt_clicked()
{
if(ui->Grp->Show_Pntcnt()<0) {
    ui->burnBt->setText("Burning PNG");
    ui->Grp->Set_Pntcnt(0);
}
else {
    ui->burnBt->setText("Not Burinig");
    ui->Grp->Set_Pntcnt(-1);
}
}

void MainWindow::on_readBt_clicked()
{
ui->Grp->inputZahyodata();
}

void MainWindow::on_calcmodeBt_clicked()
{
    bool plus;
int n=ui->Grp->Modenumber(plus);
ui->mode_lb->setText(QString::number(n));
if(plus) {
ui->neig_lb->setText("Do not Exist^^");
}
else {
QObject::connect(ui->Grp,&FIREVV::minuseig,[this](){ui->neig_lb->setText("Exist><");});
}
}

void MainWindow::on_writeeigBt_clicked()
{
ui->Grp->WriteEIGinfo(ui->seed_v->text().toInt());
}

void MainWindow::on_ccgBt_clicked()
{
if(ui->Grp->Show_paintedCluster()==false) {
    ui->ccgBt->setText("Initialize Color");
    ui->Grp->SoftAnalysis();
    ui->Grp->Set_paintedCluster(true);

}
else {
    ui->ccgBt->setText("CClusterAnalysis");
    ui->Grp->initializeParticleColor();
    ui->Grp->Set_paintedCluster(false);
}
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_exit_bt_clicked()
{
    emit quitApp();
    this->close();
}

void MainWindow::on_startBt_2_clicked()
{
    startMethod();
}

void MainWindow::on_eignum_le_returnPressed()
{
    ui->Grp->Set_Enum(ui->eignum_le->text().toInt());

    //if setting is valid...
    ui->eignum_lb->setText(ui->eignum_le->text());
}
