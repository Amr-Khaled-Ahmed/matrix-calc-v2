#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form_matrices.h"
#include "form_cipher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbtn_matrices_clicked();
    void on_pbtn_curveFitting_clicked();
    void on_pbtn_cipher_clicked();
    void showMain(); // Slot to handle showing the main window

    void on_Rights_clicked();

private:
    Ui::MainWindow *ui;

    // Instances of the other windows
    Form_matrices *formMatrices;
    Form_Cipher *formCipher;

    // style
    void setDarkModeStyles();

};

#endif // MAINWINDOW_H
