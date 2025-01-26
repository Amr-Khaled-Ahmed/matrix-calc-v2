/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pbtn_matrices;
    QPushButton *pbtn_cipher;
    QPushButton *Rights;
    QMenuBar *menubar;
    QMenu *menuWelcome_To_our_Math_Calculator;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(860, 552);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pbtn_matrices = new QPushButton(centralwidget);
        pbtn_matrices->setObjectName("pbtn_matrices");

        verticalLayout->addWidget(pbtn_matrices);

        pbtn_cipher = new QPushButton(centralwidget);
        pbtn_cipher->setObjectName("pbtn_cipher");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbtn_cipher->sizePolicy().hasHeightForWidth());
        pbtn_cipher->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pbtn_cipher);

        Rights = new QPushButton(centralwidget);
        Rights->setObjectName("Rights");

        verticalLayout->addWidget(Rights);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 860, 25));
        menuWelcome_To_our_Math_Calculator = new QMenu(menubar);
        menuWelcome_To_our_Math_Calculator->setObjectName("menuWelcome_To_our_Math_Calculator");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuWelcome_To_our_Math_Calculator->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pbtn_matrices->setText(QCoreApplication::translate("MainWindow", "Matrices", nullptr));
        pbtn_cipher->setText(QCoreApplication::translate("MainWindow", "Cipher", nullptr));
        Rights->setText(QCoreApplication::translate("MainWindow", "Rights", nullptr));
        menuWelcome_To_our_Math_Calculator->setTitle(QCoreApplication::translate("MainWindow", "Welcome To our Math Calculator ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
