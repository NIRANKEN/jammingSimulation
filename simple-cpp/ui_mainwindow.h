/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkSingle;
    QHBoxLayout *horizontalLayout;
    QLabel *label_num;
    QLineEdit *lineEdit_num;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *inputButton;
    QPushButton *eigvecButton;
    QPushButton *zahyoButton;
    QPushButton *exitButton;
    QLabel *label_title;
    QMenuBar *menubar;
    QMenu *menuHello_World;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 140, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkSingle = new QCheckBox(verticalLayoutWidget);
        checkSingle->setObjectName(QStringLiteral("checkSingle"));

        verticalLayout->addWidget(checkSingle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_num = new QLabel(verticalLayoutWidget);
        label_num->setObjectName(QStringLiteral("label_num"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_num->sizePolicy().hasHeightForWidth());
        label_num->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_num);

        lineEdit_num = new QLineEdit(verticalLayoutWidget);
        lineEdit_num->setObjectName(QStringLiteral("lineEdit_num"));

        horizontalLayout->addWidget(lineEdit_num);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(240, 140, 160, 113));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        inputButton = new QPushButton(verticalLayoutWidget_2);
        inputButton->setObjectName(QStringLiteral("inputButton"));

        verticalLayout_2->addWidget(inputButton);

        eigvecButton = new QPushButton(verticalLayoutWidget_2);
        eigvecButton->setObjectName(QStringLiteral("eigvecButton"));

        verticalLayout_2->addWidget(eigvecButton);

        zahyoButton = new QPushButton(verticalLayoutWidget_2);
        zahyoButton->setObjectName(QStringLiteral("zahyoButton"));

        verticalLayout_2->addWidget(zahyoButton);

        exitButton = new QPushButton(verticalLayoutWidget_2);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        verticalLayout_2->addWidget(exitButton);

        label_title = new QLabel(centralwidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(110, 20, 191, 51));
        QFont font;
        font.setPointSize(20);
        label_title->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 22));
        menuHello_World = new QMenu(menubar);
        menuHello_World->setObjectName(QStringLiteral("menuHello_World"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHello_World->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ControlWindow", Q_NULLPTR));
        checkSingle->setText(QApplication::translate("MainWindow", "single mode", Q_NULLPTR));
        label_num->setText(QApplication::translate("MainWindow", "Number:", Q_NULLPTR));
        inputButton->setText(QApplication::translate("MainWindow", "Input", Q_NULLPTR));
        eigvecButton->setText(QApplication::translate("MainWindow", "EigenVec", Q_NULLPTR));
        zahyoButton->setText(QApplication::translate("MainWindow", "Coordinate Only", Q_NULLPTR));
        exitButton->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        label_title->setText(QApplication::translate("MainWindow", "TEST 3D Zahyo", Q_NULLPTR));
        menuHello_World->setTitle(QApplication::translate("MainWindow", "Hello World!", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
