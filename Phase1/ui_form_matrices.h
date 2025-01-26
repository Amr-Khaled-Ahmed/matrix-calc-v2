/********************************************************************************
** Form generated from reading UI file 'form_matrices.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_MATRICES_H
#define UI_FORM_MATRICES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_matrices
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableWidget *tableWidget_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *Add;
    QPushButton *Back;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Get_Row;
    QPushButton *Get_Column;
    QPushButton *Swap_Rows;
    QPushButton *Swap_Columns;
    QPushButton *Doolittle;
    QPushButton *Croute;
    QPushButton *Cholesky;
    QPushButton *Norm;
    QHBoxLayout *horizontalLayout;
    QPushButton *Is_Unit;
    QPushButton *Is_Skew;
    QPushButton *Is_Symmetric;
    QPushButton *inverse;
    QPushButton *Determinant;
    QPushButton *Transpose;
    QPushButton *Power;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QTextEdit *Text_Editor;
    QComboBox *comboBox;
    QPushButton *Apply;

    void setupUi(QWidget *Form_matrices)
    {
        if (Form_matrices->objectName().isEmpty())
            Form_matrices->setObjectName("Form_matrices");
        Form_matrices->resize(1048, 550);
        gridLayout = new QGridLayout(Form_matrices);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(Form_matrices);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        tableWidget = new QTableWidget(Form_matrices);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_2->addWidget(tableWidget);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(Form_matrices);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        tableWidget_2 = new QTableWidget(Form_matrices);
        if (tableWidget_2->columnCount() < 1)
            tableWidget_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setLineWidth(4);
        tableWidget_2->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout->addWidget(tableWidget_2);


        verticalLayout_3->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        label_3 = new QLabel(Form_matrices);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(500, 400));
        label_3->setMaximumSize(QSize(500, 448));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        Add = new QPushButton(Form_matrices);
        Add->setObjectName("Add");

        verticalLayout_4->addWidget(Add);

        Back = new QPushButton(Form_matrices);
        Back->setObjectName("Back");

        verticalLayout_4->addWidget(Back);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Get_Row = new QPushButton(Form_matrices);
        Get_Row->setObjectName("Get_Row");

        horizontalLayout_2->addWidget(Get_Row);

        Get_Column = new QPushButton(Form_matrices);
        Get_Column->setObjectName("Get_Column");

        horizontalLayout_2->addWidget(Get_Column);

        Swap_Rows = new QPushButton(Form_matrices);
        Swap_Rows->setObjectName("Swap_Rows");

        horizontalLayout_2->addWidget(Swap_Rows);

        Swap_Columns = new QPushButton(Form_matrices);
        Swap_Columns->setObjectName("Swap_Columns");

        horizontalLayout_2->addWidget(Swap_Columns);

        Doolittle = new QPushButton(Form_matrices);
        Doolittle->setObjectName("Doolittle");

        horizontalLayout_2->addWidget(Doolittle);

        Croute = new QPushButton(Form_matrices);
        Croute->setObjectName("Croute");

        horizontalLayout_2->addWidget(Croute);

        Cholesky = new QPushButton(Form_matrices);
        Cholesky->setObjectName("Cholesky");

        horizontalLayout_2->addWidget(Cholesky);

        Norm = new QPushButton(Form_matrices);
        Norm->setObjectName("Norm");

        horizontalLayout_2->addWidget(Norm);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Is_Unit = new QPushButton(Form_matrices);
        Is_Unit->setObjectName("Is_Unit");

        horizontalLayout->addWidget(Is_Unit);

        Is_Skew = new QPushButton(Form_matrices);
        Is_Skew->setObjectName("Is_Skew");

        horizontalLayout->addWidget(Is_Skew);

        Is_Symmetric = new QPushButton(Form_matrices);
        Is_Symmetric->setObjectName("Is_Symmetric");

        horizontalLayout->addWidget(Is_Symmetric);

        inverse = new QPushButton(Form_matrices);
        inverse->setObjectName("inverse");

        horizontalLayout->addWidget(inverse);

        Determinant = new QPushButton(Form_matrices);
        Determinant->setObjectName("Determinant");

        horizontalLayout->addWidget(Determinant);

        Transpose = new QPushButton(Form_matrices);
        Transpose->setObjectName("Transpose");

        horizontalLayout->addWidget(Transpose);

        Power = new QPushButton(Form_matrices);
        Power->setObjectName("Power");

        horizontalLayout->addWidget(Power);


        verticalLayout_5->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_5);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_4 = new QLabel(Form_matrices);
        label_4->setObjectName("label_4");

        verticalLayout_6->addWidget(label_4);

        Text_Editor = new QTextEdit(Form_matrices);
        Text_Editor->setObjectName("Text_Editor");

        verticalLayout_6->addWidget(Text_Editor);

        comboBox = new QComboBox(Form_matrices);
        comboBox->setObjectName("comboBox");

        verticalLayout_6->addWidget(comboBox);

        Apply = new QPushButton(Form_matrices);
        Apply->setObjectName("Apply");

        verticalLayout_6->addWidget(Apply);


        gridLayout->addLayout(verticalLayout_6, 0, 2, 1, 1);


        retranslateUi(Form_matrices);

        QMetaObject::connectSlotsByName(Form_matrices);
    } // setupUi

    void retranslateUi(QWidget *Form_matrices)
    {
        Form_matrices->setWindowTitle(QCoreApplication::translate("Form_matrices", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form_matrices", "Saved Matrices", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Form_matrices", "Size", nullptr));
        label_2->setText(QCoreApplication::translate("Form_matrices", "Last Operations", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Form_matrices", "Operation", nullptr));
        label_3->setText(QString());
        Add->setText(QCoreApplication::translate("Form_matrices", "Add Matrix", nullptr));
        Back->setText(QCoreApplication::translate("Form_matrices", "Back", nullptr));
        Get_Row->setText(QCoreApplication::translate("Form_matrices", "Get Row", nullptr));
        Get_Column->setText(QCoreApplication::translate("Form_matrices", "Get Column", nullptr));
        Swap_Rows->setText(QCoreApplication::translate("Form_matrices", "Swap Two rows", nullptr));
        Swap_Columns->setText(QCoreApplication::translate("Form_matrices", "Swap two Columns", nullptr));
        Doolittle->setText(QCoreApplication::translate("Form_matrices", "Doolittle", nullptr));
        Croute->setText(QCoreApplication::translate("Form_matrices", "Croute", nullptr));
        Cholesky->setText(QCoreApplication::translate("Form_matrices", "Cholesky", nullptr));
        Norm->setText(QCoreApplication::translate("Form_matrices", "Norm", nullptr));
        Is_Unit->setText(QCoreApplication::translate("Form_matrices", "Is_Unit", nullptr));
        Is_Skew->setText(QCoreApplication::translate("Form_matrices", "Is_Skew_Symmetric", nullptr));
        Is_Symmetric->setText(QCoreApplication::translate("Form_matrices", "Is_Symmetric", nullptr));
        inverse->setText(QCoreApplication::translate("Form_matrices", "Inverse", nullptr));
        Determinant->setText(QCoreApplication::translate("Form_matrices", "Determinant", nullptr));
        Transpose->setText(QCoreApplication::translate("Form_matrices", "Transpose", nullptr));
        Power->setText(QCoreApplication::translate("Form_matrices", "Power", nullptr));
        label_4->setText(QCoreApplication::translate("Form_matrices", "Enter Text", nullptr));
        Apply->setText(QCoreApplication::translate("Form_matrices", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_matrices: public Ui_Form_matrices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_MATRICES_H
