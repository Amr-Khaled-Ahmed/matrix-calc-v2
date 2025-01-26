#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , formMatrices(new Form_matrices())        // Create the other windows without a parent
    , formCipher(new Form_Cipher())
{
    ui->setupUi(this);

    setDarkModeStyles();
    connect(formMatrices, &Form_matrices::showMainWindow, this, &MainWindow::showMain);
    connect(formCipher, &Form_Cipher::showMainWindow, this, &MainWindow::showMain);
    // Ensure other windows are hidden at the start
    formMatrices->hide();
    formCipher->hide();
    setWindowTitle("Matrix Maestro");

}

MainWindow::~MainWindow()
{
    delete ui;

    // Explicitly delete the sub-windows
    delete formMatrices;
    delete formCipher;
}

void MainWindow::showMain()
{
    this->show();          // Show the main window
}

void MainWindow::on_pbtn_matrices_clicked()
{
    this->hide();          // Hide the main window
    formMatrices->show();  // Show the matrices form
}

void MainWindow::on_pbtn_curveFitting_clicked()
{
    this->hide();                // Hide the main window
}

void MainWindow::on_pbtn_cipher_clicked()
{
    this->hide();          // Hide the main window
    formCipher->show();    // Show the cipher form
}

void MainWindow::setDarkModeStyles()
{
    QString styleSheet = R"(
        * {
            background-color: #1e1e1e;  /* Dark background */
            font-family: "Courier New", Courier, monospace;  /* Monospace font */
            font-size: 12pt;
        }

        QMainWindow {
            /* Removed border */
        }

        QPushButton {
            background-color: #001A6E;   /* Dark blue button background */
            padding: 10px;
            font-size: 12pt;
            border: none;                /* Removed border */
        }

        QPushButton:hover {
            background-color: #000000;   /* Black when hovering */
        }

        QLineEdit {
            background-color: #333333;    /* Dark background for text fields */
        }

        QComboBox, QSpinBox, QDoubleSpinBox {
            background-color: #333333;
        }

        QStatusBar {
            background-color: #212121;    /* Dark status bar */
        }

        QTabWidget {
            background-color: #2a2a2a;
        }

        QTabBar::tab {
            background-color: #333333;
        }

        QTabBar::tab:hover {
            background-color: #444444;
        }

        /* Styling for QTableWidget */
        QTableWidget {
            background-color: #2a2a2a; /* Dark background for table */
        }

        QTableWidget::item {
            padding: 8px;
        }

        QTableWidget::item:selected {
            background-color: #444444;  /* Dark selection color */
        }

        QTableWidget::horizontalHeader {
            background-color: #333333;  /* Dark header background */
        }

        QTableWidget::horizontalHeader::section {
            padding: 8px;
        }

        QTableWidget::verticalHeader {
            background-color: #333333;  /* Dark vertical header background */
        }

        QTableWidget::verticalHeader::section {
            padding: 8px;
        }
    )";

    // Apply the dark mode stylesheet to the entire application
    qApp->setStyleSheet(styleSheet);
}





void MainWindow::on_Rights_clicked()
{
    QString message = R"(
        <html>
            <head>
                <style>
                    body {
                        background-color: #1e1e1e; /* خلفية سوداء */
                        font-family: "Traditional Arabic", serif;
                        text-align: right;
                        line-height: 1.8;
                        color: #00ffff; /* لون النص الأزرق السماوي */
                    }
                    h1 {
                        color: #ffffff; /* لون أبيض للعناوين الرئيسية */
                        font-size: 24px;
                        margin-bottom: 10px;
                    }
                    h2 {
                        font-size: 20px;
                        color: #00ffff; /* لون أزرق سماوي للعناوين الثانوية */
                    }
                    p {
                        margin-bottom: 15px;
                        font-size: 16px;
                    }
                    ul {
                        margin-top: 10px;
                        font-size: 16px;
                        list-style-type: square;
                        padding-right: 20px;
                    }
                </style>
            </head>
            <body>
                <h1>فريق العمل المتميز</h1>
                <p>هذا البرنامج موجه بكل تقدير واحترام إلى  <strong> الدكتور المهندس مصطفى رضا عبدالله طنطاوي</strong>.</p>
                <h2>مغزى البرنامج:</h2>
                <p>
يهدف هذا البرنامج إلى تسهيل بعض العمليات  علي المصفوفات بالإضافة إلى تطبيق عملي علي التشفير بواسطة المصفوفات المربعه يسمي (Hell Cipher )
                </p>
                <h2>فريقنا:</h2>
                <p>يتكون فريق العمل من 12 مهندسًا مبدعًا عملوا بجد على تنفيذ هذا المشروع:</p>
                <ul>
                    <li>أحمد إبراهيم أحمد محمد</li>
                    <li>عمرو خالد أحمد عبد الحميد</li>
                    <li>محمد صلاح الدين محمد سليمان</li>
                    <li>محمود إبراهيم محمد محمد</li>
                    <li>محمد أشرف جلال</li>
                    <li>يوسف أمجد عبد الحليم أحمد</li>
                    <li>محمد أحمد محمد عبد الوهاب</li>
                    <li>مصطفى محمود فتحي</li>
                    <li>عمر فوزي عبد الحميد محمود</li>
                    <li>يوسف سامي جورج</li>
                    <li>جمال مجاهد سيد</li>
                    <li>مصطفى احمد مجد علي</li>

                </ul>
                <p style="font-style: italic;">مع أطيب التحيات والتقدير، فريق العمل.</p>
            </body>
        </html>
    )";

    QDialog dialog(this);
    dialog.setWindowTitle("المساهمون");
    dialog.resize(600, 400);

    QLabel *label = new QLabel(&dialog);
    label->setTextFormat(Qt::RichText);
    label->setText(message);
    label->setAlignment(Qt::AlignTop | Qt::AlignRight);
    label->setWordWrap(true);

    QScrollArea *scrollArea = new QScrollArea(&dialog);
    scrollArea->setWidget(label);
    scrollArea->setWidgetResizable(true);

    // تصميم التخطيط
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(scrollArea);

    // عرض النافذة
    dialog.exec();
}
