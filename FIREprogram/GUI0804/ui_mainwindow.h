/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "FIREVV.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *statustab;
    QLabel *status_lb;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_41;
    QLabel *state_lb;
    QHBoxLayout *horizontalLayout;
    QLabel *label_38;
    QLabel *eng_lb;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_43;
    QLabel *phi_lb;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_45;
    QLabel *mode_lb;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_47;
    QLabel *mcod_lb;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_55;
    QLabel *cvc_lb;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_57;
    QLabel *neig_lb;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_39;
    QLineEdit *eignum_le;
    QLabel *eignum_lb;
    QLabel *statuslabel;
    QPushButton *startBt_2;
    QWidget *paratab1;
    QLabel *syslabel;
    QPushButton *sysdefBt;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_14;
    QLabel *seed_n;
    QLineEdit *seed_in;
    QLabel *seed_v;
    QHBoxLayout *horizontalLayout_12;
    QLabel *phi_n;
    QLineEdit *phi_in;
    QLabel *phi_v;
    QHBoxLayout *horizontalLayout_11;
    QLabel *crrate_v;
    QLineEdit *crrate_in;
    QLabel *crrate_v_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *N_n;
    QLineEdit *N_in;
    QLabel *N_v;
    QHBoxLayout *horizontalLayout_16;
    QLabel *pex_n;
    QLineEdit *pex_in;
    QLabel *pex_v;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lx_n;
    QLineEdit *lx_in;
    QLabel *lx_v;
    QHBoxLayout *horizontalLayout_17;
    QLabel *ly_n;
    QLineEdit *ly_in;
    QLabel *ly_v;
    QHBoxLayout *horizontalLayout_15;
    QLabel *sr_n;
    QLineEdit *sr_in;
    QLabel *sr_v;
    QHBoxLayout *horizontalLayout_3;
    QLabel *mix1_n;
    QLineEdit *mix1_in;
    QLabel *mix1_v;
    QHBoxLayout *horizontalLayout_18;
    QLabel *mix2_n;
    QLineEdit *mix2_in;
    QLabel *mix2_v;
    QWidget *paratab2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_34;
    QLabel *tstep_n;
    QLineEdit *tstep_in;
    QLabel *tstep_v;
    QHBoxLayout *horizontalLayout_35;
    QLabel *damp_n;
    QLineEdit *damp_in;
    QLabel *damp_v;
    QHBoxLayout *horizontalLayout_31;
    QLabel *IFT_n;
    QLineEdit *IFT_in;
    QLabel *IFT_v;
    QHBoxLayout *horizontalLayout_32;
    QLabel *DFT_n;
    QLineEdit *DFT_in;
    QLabel *DFT_v;
    QHBoxLayout *horizontalLayout_33;
    QLabel *DFDT_n;
    QLineEdit *DFDT_in;
    QLabel *DFDT_v;
    QHBoxLayout *horizontalLayout_27;
    QLabel *DTinit_n;
    QLineEdit *DTinit_in;
    QLabel *DTinit_v;
    QHBoxLayout *horizontalLayout_28;
    QLabel *maxT_n;
    QLineEdit *maxT_in;
    QLabel *maxT_v;
    QHBoxLayout *horizontalLayout_29;
    QLabel *delayFIRE_n;
    QLineEdit *delayFIRE_in;
    QLabel *delayFIRE_v;
    QLabel *MDlabel;
    QPushButton *MDdefBt;
    QWidget *tooltab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *startBt;
    QPushButton *noiseBt;
    QPushButton *repBt;
    QPushButton *resetPtBt;
    QPushButton *burnBt;
    QPushButton *readBt;
    QPushButton *calcmodeBt;
    QPushButton *writeeigBt;
    QPushButton *ccgBt;
    QLabel *toollabel;
    QPushButton *exit_bt;
    FIREVV *Grp;
    QMenuBar *menubar;
    QMenu *menuJam;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(440, 15, 350, 450));
        statustab = new QWidget();
        statustab->setObjectName(QStringLiteral("statustab"));
        status_lb = new QLabel(statustab);
        status_lb->setObjectName(QStringLiteral("status_lb"));
        status_lb->setGeometry(QRect(30, 90, 291, 31));
        verticalLayoutWidget_4 = new QWidget(statustab);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(30, 130, 293, 211));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_9->setSpacing(2);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_41 = new QLabel(verticalLayoutWidget_4);
        label_41->setObjectName(QStringLiteral("label_41"));

        horizontalLayout_22->addWidget(label_41);

        state_lb = new QLabel(verticalLayoutWidget_4);
        state_lb->setObjectName(QStringLiteral("state_lb"));

        horizontalLayout_22->addWidget(state_lb);


        verticalLayout_9->addLayout(horizontalLayout_22);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_38 = new QLabel(verticalLayoutWidget_4);
        label_38->setObjectName(QStringLiteral("label_38"));

        horizontalLayout->addWidget(label_38);

        eng_lb = new QLabel(verticalLayoutWidget_4);
        eng_lb->setObjectName(QStringLiteral("eng_lb"));

        horizontalLayout->addWidget(eng_lb);


        verticalLayout_9->addLayout(horizontalLayout);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_43 = new QLabel(verticalLayoutWidget_4);
        label_43->setObjectName(QStringLiteral("label_43"));

        horizontalLayout_23->addWidget(label_43);

        phi_lb = new QLabel(verticalLayoutWidget_4);
        phi_lb->setObjectName(QStringLiteral("phi_lb"));

        horizontalLayout_23->addWidget(phi_lb);


        verticalLayout_9->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_45 = new QLabel(verticalLayoutWidget_4);
        label_45->setObjectName(QStringLiteral("label_45"));

        horizontalLayout_24->addWidget(label_45);

        mode_lb = new QLabel(verticalLayoutWidget_4);
        mode_lb->setObjectName(QStringLiteral("mode_lb"));

        horizontalLayout_24->addWidget(mode_lb);


        verticalLayout_9->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_47 = new QLabel(verticalLayoutWidget_4);
        label_47->setObjectName(QStringLiteral("label_47"));

        horizontalLayout_25->addWidget(label_47);

        mcod_lb = new QLabel(verticalLayoutWidget_4);
        mcod_lb->setObjectName(QStringLiteral("mcod_lb"));

        horizontalLayout_25->addWidget(mcod_lb);


        verticalLayout_9->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_55 = new QLabel(verticalLayoutWidget_4);
        label_55->setObjectName(QStringLiteral("label_55"));

        horizontalLayout_26->addWidget(label_55);

        cvc_lb = new QLabel(verticalLayoutWidget_4);
        cvc_lb->setObjectName(QStringLiteral("cvc_lb"));

        horizontalLayout_26->addWidget(cvc_lb);


        verticalLayout_9->addLayout(horizontalLayout_26);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        label_57 = new QLabel(verticalLayoutWidget_4);
        label_57->setObjectName(QStringLiteral("label_57"));

        horizontalLayout_30->addWidget(label_57);

        neig_lb = new QLabel(verticalLayoutWidget_4);
        neig_lb->setObjectName(QStringLiteral("neig_lb"));

        horizontalLayout_30->addWidget(neig_lb);


        verticalLayout_9->addLayout(horizontalLayout_30);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_39 = new QLabel(verticalLayoutWidget_4);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setMinimumSize(QSize(110, 0));

        horizontalLayout_21->addWidget(label_39);

        eignum_le = new QLineEdit(verticalLayoutWidget_4);
        eignum_le->setObjectName(QStringLiteral("eignum_le"));
        eignum_le->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_21->addWidget(eignum_le);

        eignum_lb = new QLabel(verticalLayoutWidget_4);
        eignum_lb->setObjectName(QStringLiteral("eignum_lb"));
        eignum_lb->setMinimumSize(QSize(50, 0));

        horizontalLayout_21->addWidget(eignum_lb);


        verticalLayout_9->addLayout(horizontalLayout_21);

        statuslabel = new QLabel(statustab);
        statuslabel->setObjectName(QStringLiteral("statuslabel"));
        statuslabel->setGeometry(QRect(80, 40, 181, 31));
        startBt_2 = new QPushButton(statustab);
        startBt_2->setObjectName(QStringLiteral("startBt_2"));
        startBt_2->setGeometry(QRect(160, 360, 158, 27));
        tabWidget->addTab(statustab, QString());
        paratab1 = new QWidget();
        paratab1->setObjectName(QStringLiteral("paratab1"));
        syslabel = new QLabel(paratab1);
        syslabel->setObjectName(QStringLiteral("syslabel"));
        syslabel->setGeometry(QRect(60, 5, 241, 31));
        sysdefBt = new QPushButton(paratab1);
        sysdefBt->setObjectName(QStringLiteral("sysdefBt"));
        sysdefBt->setGeometry(QRect(240, 390, 99, 27));
        verticalLayoutWidget_5 = new QWidget(paratab1);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(40, 40, 270, 346));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        seed_n = new QLabel(verticalLayoutWidget_5);
        seed_n->setObjectName(QStringLiteral("seed_n"));

        horizontalLayout_14->addWidget(seed_n);

        seed_in = new QLineEdit(verticalLayoutWidget_5);
        seed_in->setObjectName(QStringLiteral("seed_in"));

        horizontalLayout_14->addWidget(seed_in);

        seed_v = new QLabel(verticalLayoutWidget_5);
        seed_v->setObjectName(QStringLiteral("seed_v"));

        horizontalLayout_14->addWidget(seed_v);


        verticalLayout_5->addLayout(horizontalLayout_14);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        phi_n = new QLabel(verticalLayoutWidget_5);
        phi_n->setObjectName(QStringLiteral("phi_n"));

        horizontalLayout_12->addWidget(phi_n);

        phi_in = new QLineEdit(verticalLayoutWidget_5);
        phi_in->setObjectName(QStringLiteral("phi_in"));

        horizontalLayout_12->addWidget(phi_in);

        phi_v = new QLabel(verticalLayoutWidget_5);
        phi_v->setObjectName(QStringLiteral("phi_v"));

        horizontalLayout_12->addWidget(phi_v);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        crrate_v = new QLabel(verticalLayoutWidget_5);
        crrate_v->setObjectName(QStringLiteral("crrate_v"));

        horizontalLayout_11->addWidget(crrate_v);

        crrate_in = new QLineEdit(verticalLayoutWidget_5);
        crrate_in->setObjectName(QStringLiteral("crrate_in"));

        horizontalLayout_11->addWidget(crrate_in);

        crrate_v_2 = new QLabel(verticalLayoutWidget_5);
        crrate_v_2->setObjectName(QStringLiteral("crrate_v_2"));

        horizontalLayout_11->addWidget(crrate_v_2);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        N_n = new QLabel(verticalLayoutWidget_5);
        N_n->setObjectName(QStringLiteral("N_n"));

        horizontalLayout_10->addWidget(N_n);

        N_in = new QLineEdit(verticalLayoutWidget_5);
        N_in->setObjectName(QStringLiteral("N_in"));

        horizontalLayout_10->addWidget(N_in);

        N_v = new QLabel(verticalLayoutWidget_5);
        N_v->setObjectName(QStringLiteral("N_v"));

        horizontalLayout_10->addWidget(N_v);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        pex_n = new QLabel(verticalLayoutWidget_5);
        pex_n->setObjectName(QStringLiteral("pex_n"));

        horizontalLayout_16->addWidget(pex_n);

        pex_in = new QLineEdit(verticalLayoutWidget_5);
        pex_in->setObjectName(QStringLiteral("pex_in"));

        horizontalLayout_16->addWidget(pex_in);

        pex_v = new QLabel(verticalLayoutWidget_5);
        pex_v->setObjectName(QStringLiteral("pex_v"));

        horizontalLayout_16->addWidget(pex_v);


        verticalLayout_5->addLayout(horizontalLayout_16);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lx_n = new QLabel(verticalLayoutWidget_5);
        lx_n->setObjectName(QStringLiteral("lx_n"));

        horizontalLayout_2->addWidget(lx_n);

        lx_in = new QLineEdit(verticalLayoutWidget_5);
        lx_in->setObjectName(QStringLiteral("lx_in"));

        horizontalLayout_2->addWidget(lx_in);

        lx_v = new QLabel(verticalLayoutWidget_5);
        lx_v->setObjectName(QStringLiteral("lx_v"));

        horizontalLayout_2->addWidget(lx_v);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        ly_n = new QLabel(verticalLayoutWidget_5);
        ly_n->setObjectName(QStringLiteral("ly_n"));

        horizontalLayout_17->addWidget(ly_n);

        ly_in = new QLineEdit(verticalLayoutWidget_5);
        ly_in->setObjectName(QStringLiteral("ly_in"));

        horizontalLayout_17->addWidget(ly_in);

        ly_v = new QLabel(verticalLayoutWidget_5);
        ly_v->setObjectName(QStringLiteral("ly_v"));

        horizontalLayout_17->addWidget(ly_v);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        sr_n = new QLabel(verticalLayoutWidget_5);
        sr_n->setObjectName(QStringLiteral("sr_n"));

        horizontalLayout_15->addWidget(sr_n);

        sr_in = new QLineEdit(verticalLayoutWidget_5);
        sr_in->setObjectName(QStringLiteral("sr_in"));

        horizontalLayout_15->addWidget(sr_in);

        sr_v = new QLabel(verticalLayoutWidget_5);
        sr_v->setObjectName(QStringLiteral("sr_v"));

        horizontalLayout_15->addWidget(sr_v);


        verticalLayout_5->addLayout(horizontalLayout_15);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        mix1_n = new QLabel(verticalLayoutWidget_5);
        mix1_n->setObjectName(QStringLiteral("mix1_n"));

        horizontalLayout_3->addWidget(mix1_n);

        mix1_in = new QLineEdit(verticalLayoutWidget_5);
        mix1_in->setObjectName(QStringLiteral("mix1_in"));

        horizontalLayout_3->addWidget(mix1_in);

        mix1_v = new QLabel(verticalLayoutWidget_5);
        mix1_v->setObjectName(QStringLiteral("mix1_v"));

        horizontalLayout_3->addWidget(mix1_v);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        mix2_n = new QLabel(verticalLayoutWidget_5);
        mix2_n->setObjectName(QStringLiteral("mix2_n"));

        horizontalLayout_18->addWidget(mix2_n);

        mix2_in = new QLineEdit(verticalLayoutWidget_5);
        mix2_in->setObjectName(QStringLiteral("mix2_in"));

        horizontalLayout_18->addWidget(mix2_in);

        mix2_v = new QLabel(verticalLayoutWidget_5);
        mix2_v->setObjectName(QStringLiteral("mix2_v"));

        horizontalLayout_18->addWidget(mix2_v);


        verticalLayout_5->addLayout(horizontalLayout_18);

        tabWidget->addTab(paratab1, QString());
        paratab2 = new QWidget();
        paratab2->setObjectName(QStringLiteral("paratab2"));
        layoutWidget = new QWidget(paratab2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 110, 329, 234));
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QStringLiteral("horizontalLayout_34"));
        tstep_n = new QLabel(layoutWidget);
        tstep_n->setObjectName(QStringLiteral("tstep_n"));

        horizontalLayout_34->addWidget(tstep_n);

        tstep_in = new QLineEdit(layoutWidget);
        tstep_in->setObjectName(QStringLiteral("tstep_in"));

        horizontalLayout_34->addWidget(tstep_in);

        tstep_v = new QLabel(layoutWidget);
        tstep_v->setObjectName(QStringLiteral("tstep_v"));

        horizontalLayout_34->addWidget(tstep_v);


        verticalLayout_8->addLayout(horizontalLayout_34);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
        damp_n = new QLabel(layoutWidget);
        damp_n->setObjectName(QStringLiteral("damp_n"));

        horizontalLayout_35->addWidget(damp_n);

        damp_in = new QLineEdit(layoutWidget);
        damp_in->setObjectName(QStringLiteral("damp_in"));

        horizontalLayout_35->addWidget(damp_in);

        damp_v = new QLabel(layoutWidget);
        damp_v->setObjectName(QStringLiteral("damp_v"));

        horizontalLayout_35->addWidget(damp_v);


        verticalLayout_8->addLayout(horizontalLayout_35);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        IFT_n = new QLabel(layoutWidget);
        IFT_n->setObjectName(QStringLiteral("IFT_n"));

        horizontalLayout_31->addWidget(IFT_n);

        IFT_in = new QLineEdit(layoutWidget);
        IFT_in->setObjectName(QStringLiteral("IFT_in"));

        horizontalLayout_31->addWidget(IFT_in);

        IFT_v = new QLabel(layoutWidget);
        IFT_v->setObjectName(QStringLiteral("IFT_v"));

        horizontalLayout_31->addWidget(IFT_v);


        verticalLayout_8->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        DFT_n = new QLabel(layoutWidget);
        DFT_n->setObjectName(QStringLiteral("DFT_n"));

        horizontalLayout_32->addWidget(DFT_n);

        DFT_in = new QLineEdit(layoutWidget);
        DFT_in->setObjectName(QStringLiteral("DFT_in"));

        horizontalLayout_32->addWidget(DFT_in);

        DFT_v = new QLabel(layoutWidget);
        DFT_v->setObjectName(QStringLiteral("DFT_v"));

        horizontalLayout_32->addWidget(DFT_v);


        verticalLayout_8->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
        DFDT_n = new QLabel(layoutWidget);
        DFDT_n->setObjectName(QStringLiteral("DFDT_n"));

        horizontalLayout_33->addWidget(DFDT_n);

        DFDT_in = new QLineEdit(layoutWidget);
        DFDT_in->setObjectName(QStringLiteral("DFDT_in"));

        horizontalLayout_33->addWidget(DFDT_in);

        DFDT_v = new QLabel(layoutWidget);
        DFDT_v->setObjectName(QStringLiteral("DFDT_v"));

        horizontalLayout_33->addWidget(DFDT_v);


        verticalLayout_8->addLayout(horizontalLayout_33);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        DTinit_n = new QLabel(layoutWidget);
        DTinit_n->setObjectName(QStringLiteral("DTinit_n"));

        horizontalLayout_27->addWidget(DTinit_n);

        DTinit_in = new QLineEdit(layoutWidget);
        DTinit_in->setObjectName(QStringLiteral("DTinit_in"));

        horizontalLayout_27->addWidget(DTinit_in);

        DTinit_v = new QLabel(layoutWidget);
        DTinit_v->setObjectName(QStringLiteral("DTinit_v"));

        horizontalLayout_27->addWidget(DTinit_v);


        verticalLayout_8->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        maxT_n = new QLabel(layoutWidget);
        maxT_n->setObjectName(QStringLiteral("maxT_n"));

        horizontalLayout_28->addWidget(maxT_n);

        maxT_in = new QLineEdit(layoutWidget);
        maxT_in->setObjectName(QStringLiteral("maxT_in"));

        horizontalLayout_28->addWidget(maxT_in);

        maxT_v = new QLabel(layoutWidget);
        maxT_v->setObjectName(QStringLiteral("maxT_v"));

        horizontalLayout_28->addWidget(maxT_v);


        verticalLayout_8->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        delayFIRE_n = new QLabel(layoutWidget);
        delayFIRE_n->setObjectName(QStringLiteral("delayFIRE_n"));

        horizontalLayout_29->addWidget(delayFIRE_n);

        delayFIRE_in = new QLineEdit(layoutWidget);
        delayFIRE_in->setObjectName(QStringLiteral("delayFIRE_in"));

        horizontalLayout_29->addWidget(delayFIRE_in);

        delayFIRE_v = new QLabel(layoutWidget);
        delayFIRE_v->setObjectName(QStringLiteral("delayFIRE_v"));

        horizontalLayout_29->addWidget(delayFIRE_v);


        verticalLayout_8->addLayout(horizontalLayout_29);

        MDlabel = new QLabel(paratab2);
        MDlabel->setObjectName(QStringLiteral("MDlabel"));
        MDlabel->setGeometry(QRect(70, 50, 191, 31));
        MDdefBt = new QPushButton(paratab2);
        MDdefBt->setObjectName(QStringLiteral("MDdefBt"));
        MDdefBt->setGeometry(QRect(240, 390, 99, 27));
        tabWidget->addTab(paratab2, QString());
        tooltab = new QWidget();
        tooltab->setObjectName(QStringLiteral("tooltab"));
        verticalLayoutWidget = new QWidget(tooltab);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 70, 160, 326));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        startBt = new QPushButton(verticalLayoutWidget);
        startBt->setObjectName(QStringLiteral("startBt"));

        verticalLayout->addWidget(startBt);

        noiseBt = new QPushButton(verticalLayoutWidget);
        noiseBt->setObjectName(QStringLiteral("noiseBt"));

        verticalLayout->addWidget(noiseBt);

        repBt = new QPushButton(verticalLayoutWidget);
        repBt->setObjectName(QStringLiteral("repBt"));

        verticalLayout->addWidget(repBt);

        resetPtBt = new QPushButton(verticalLayoutWidget);
        resetPtBt->setObjectName(QStringLiteral("resetPtBt"));

        verticalLayout->addWidget(resetPtBt);

        burnBt = new QPushButton(verticalLayoutWidget);
        burnBt->setObjectName(QStringLiteral("burnBt"));

        verticalLayout->addWidget(burnBt);

        readBt = new QPushButton(verticalLayoutWidget);
        readBt->setObjectName(QStringLiteral("readBt"));

        verticalLayout->addWidget(readBt);

        calcmodeBt = new QPushButton(verticalLayoutWidget);
        calcmodeBt->setObjectName(QStringLiteral("calcmodeBt"));

        verticalLayout->addWidget(calcmodeBt);

        writeeigBt = new QPushButton(verticalLayoutWidget);
        writeeigBt->setObjectName(QStringLiteral("writeeigBt"));

        verticalLayout->addWidget(writeeigBt);

        ccgBt = new QPushButton(verticalLayoutWidget);
        ccgBt->setObjectName(QStringLiteral("ccgBt"));

        verticalLayout->addWidget(ccgBt);

        toollabel = new QLabel(tooltab);
        toollabel->setObjectName(QStringLiteral("toollabel"));
        toollabel->setGeometry(QRect(100, 20, 151, 31));
        tabWidget->addTab(tooltab, QString());
        exit_bt = new QPushButton(centralwidget);
        exit_bt->setObjectName(QStringLiteral("exit_bt"));
        exit_bt->setGeometry(QRect(620, 510, 158, 27));
        Grp = new FIREVV(centralwidget);
        Grp->setObjectName(QStringLiteral("Grp"));
        Grp->setGeometry(QRect(3, 30, 430, 430));
        MainWindow->setCentralWidget(centralwidget);
        exit_bt->raise();
        Grp->raise();
        tabWidget->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuJam = new QMenu(menubar);
        menuJam->setObjectName(QStringLiteral("menuJam"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuJam->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        status_lb->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\\(^o^)/ &lt; &quot;Hello World!&quot;</p></body></html>", 0));
        label_41->setText(QApplication::translate("MainWindow", "Packing state is... ", 0));
        state_lb->setText(QApplication::translate("MainWindow", "mechanical unstable><", 0));
        label_38->setText(QApplication::translate("MainWindow", "Total energy: ", 0));
        eng_lb->setText(QApplication::translate("MainWindow", "???", 0));
        label_43->setText(QApplication::translate("MainWindow", "Packing fraction: ", 0));
        phi_lb->setText(QApplication::translate("MainWindow", "???", 0));
        label_45->setText(QApplication::translate("MainWindow", "Free modes:", 0));
        mode_lb->setText(QApplication::translate("MainWindow", "???", 0));
        label_47->setText(QApplication::translate("MainWindow", "Mean contact:", 0));
        mcod_lb->setText(QApplication::translate("MainWindow", "???", 0));
        label_55->setText(QApplication::translate("MainWindow", "Co-vibration cluster:", 0));
        cvc_lb->setText(QApplication::translate("MainWindow", "???", 0));
        label_57->setText(QApplication::translate("MainWindow", "Negative eigenvalue...", 0));
        neig_lb->setText(QApplication::translate("MainWindow", "Exist?", 0));
        label_39->setText(QApplication::translate("MainWindow", "Eigenmode:", 0));
        eignum_lb->setText(QApplication::translate("MainWindow", "( ??? )", 0));
        statuslabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">System Status</span></p></body></html>", 0));
        startBt_2->setText(QApplication::translate("MainWindow", "START", 0));
        tabWidget->setTabText(tabWidget->indexOf(statustab), QApplication::translate("MainWindow", "Status", 0));
        syslabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">System parameters</span></p></body></html>", 0));
        sysdefBt->setText(QApplication::translate("MainWindow", "Set Default", 0));
        seed_n->setText(QApplication::translate("MainWindow", "seed:", 0));
        seed_in->setText(QApplication::translate("MainWindow", "0", 0));
        seed_v->setText(QApplication::translate("MainWindow", "(0) ", 0));
        phi_n->setText(QApplication::translate("MainWindow", "Packing Fraction:", 0));
        phi_in->setText(QApplication::translate("MainWindow", "1.0", 0));
        phi_v->setText(QApplication::translate("MainWindow", "(1.0) ", 0));
        crrate_v->setText(QApplication::translate("MainWindow", "Compressing Rate:", 0));
        crrate_in->setText(QApplication::translate("MainWindow", "0.05", 0));
        crrate_v_2->setText(QApplication::translate("MainWindow", "(0.05) ", 0));
        N_n->setText(QApplication::translate("MainWindow", "the number of particles:", 0));
        N_in->setText(QApplication::translate("MainWindow", "64", 0));
        N_v->setText(QApplication::translate("MainWindow", "(64) ", 0));
        pex_n->setText(QApplication::translate("MainWindow", "Potential Exponent:", 0));
        pex_in->setText(QApplication::translate("MainWindow", "2.0", 0));
        pex_v->setText(QApplication::translate("MainWindow", "(2.0) ", 0));
        lx_n->setText(QApplication::translate("MainWindow", "x-length of the box:", 0));
        lx_in->setText(QApplication::translate("MainWindow", "400", 0));
        lx_v->setText(QApplication::translate("MainWindow", "(400) ", 0));
        ly_n->setText(QApplication::translate("MainWindow", "y-length of the box:", 0));
        ly_in->setText(QApplication::translate("MainWindow", "400", 0));
        ly_v->setText(QApplication::translate("MainWindow", "(400) ", 0));
        sr_n->setText(QApplication::translate("MainWindow", "Size Ratio:", 0));
        sr_in->setText(QApplication::translate("MainWindow", "1.4", 0));
        sr_v->setText(QApplication::translate("MainWindow", "(1.4) ", 0));
        mix1_n->setText(QApplication::translate("MainWindow", "Mix Ratio(I):", 0));
        mix1_in->setText(QApplication::translate("MainWindow", "1", 0));
        mix1_v->setText(QApplication::translate("MainWindow", "(1) ", 0));
        mix2_n->setText(QApplication::translate("MainWindow", "Mix Ratio(II):", 0));
        mix2_in->setText(QApplication::translate("MainWindow", "1", 0));
        mix2_v->setText(QApplication::translate("MainWindow", "(1) ", 0));
        tabWidget->setTabText(tabWidget->indexOf(paratab1), QApplication::translate("MainWindow", "Parameters1", 0));
        tstep_n->setText(QApplication::translate("MainWindow", "TimeStep:", 0));
        tstep_in->setText(QApplication::translate("MainWindow", "0.01", 0));
        tstep_v->setText(QApplication::translate("MainWindow", "(0.01)", 0));
        damp_n->setText(QApplication::translate("MainWindow", "Damping Coefficient:", 0));
        damp_in->setText(QApplication::translate("MainWindow", "10", 0));
        damp_v->setText(QApplication::translate("MainWindow", "(10)", 0));
        IFT_n->setText(QApplication::translate("MainWindow", "increasing fraction of Tstep", 0));
        IFT_in->setText(QApplication::translate("MainWindow", "1.1", 0));
        IFT_v->setText(QApplication::translate("MainWindow", "(1.1)", 0));
        DFT_n->setText(QApplication::translate("MainWindow", "decreasing fraction of Tstep", 0));
        DFT_in->setText(QApplication::translate("MainWindow", "0.5", 0));
        DFT_v->setText(QApplication::translate("MainWindow", "(0.5)", 0));
        DFDT_n->setText(QApplication::translate("MainWindow", "decreasing fraction of DampT", 0));
        DFDT_in->setText(QApplication::translate("MainWindow", "0.99", 0));
        DFDT_v->setText(QApplication::translate("MainWindow", "(0.99)", 0));
        DTinit_n->setText(QApplication::translate("MainWindow", "initial DampT value", 0));
        DTinit_in->setText(QApplication::translate("MainWindow", "0.1", 0));
        DTinit_v->setText(QApplication::translate("MainWindow", "(0.1)", 0));
        maxT_n->setText(QApplication::translate("MainWindow", "Tstep Maximum:", 0));
        maxT_in->setText(QApplication::translate("MainWindow", "0.5", 0));
        maxT_v->setText(QApplication::translate("MainWindow", "(0.5)", 0));
        delayFIRE_n->setText(QApplication::translate("MainWindow", "Delay time for FIRE engine", 0));
        delayFIRE_in->setText(QApplication::translate("MainWindow", "5", 0));
        delayFIRE_v->setText(QApplication::translate("MainWindow", "(5)", 0));
        MDlabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">MD parameters</span></p></body></html>", 0));
        MDdefBt->setText(QApplication::translate("MainWindow", "Set Default", 0));
        tabWidget->setTabText(tabWidget->indexOf(paratab2), QApplication::translate("MainWindow", "Parameters2", 0));
        startBt->setText(QApplication::translate("MainWindow", "START", 0));
        noiseBt->setText(QApplication::translate("MainWindow", "Noise", 0));
        repBt->setText(QApplication::translate("MainWindow", "Repaint", 0));
        resetPtBt->setText(QApplication::translate("MainWindow", "Reset-Painter", 0));
        burnBt->setText(QApplication::translate("MainWindow", "NotBurning xx", 0));
        readBt->setText(QApplication::translate("MainWindow", "TEXT-READ", 0));
        calcmodeBt->setText(QApplication::translate("MainWindow", "CalcMode", 0));
        writeeigBt->setText(QApplication::translate("MainWindow", "EIG-WRITE", 0));
        ccgBt->setText(QApplication::translate("MainWindow", "CClusterGroping", 0));
        toollabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">Tool Buttons</span></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tooltab), QApplication::translate("MainWindow", "Tool", 0));
        exit_bt->setText(QApplication::translate("MainWindow", "Exit", 0));
        menuJam->setTitle(QApplication::translate("MainWindow", "2D jamming simulation program", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
