#ifndef FORM_CIPHER_H
#define FORM_CIPHER_H

#include <QWidget>
#include <QVector>
#include <QString>

namespace Ui {
class Form_Cipher;
}

class Form_Cipher : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Cipher(QWidget *parent = nullptr);
    ~Form_Cipher();

private slots:
    void on_Back_clicked();
    void on_CipherButton_clicked();

    void on_DecipherButton_clicked();

signals:
    void showMainWindow();

private:

    Ui::Form_Cipher *ui;
    QVector<QVector<int>> keyMatrix;
    // Methods for key matrix and encryption
    void initializeKeyMatrix(const QString &keyInput);
    QString hillEncryptMessage(const QString &message, const QString &key);

    // Methods for handling message formatting and conversion
    QString formatMessageWithSpaces(const QString &message);
    QVector<int> multiplyMatrixWithVector(const QVector<QVector<int>> &matrix, const QVector<int> &vec);
    QString vectorToStringWithSpaces(const QVector<int> &vec);

    // Character conversion methods
    int charToNumber(QChar c);
    QChar numberToChar(int n);

    // inverse
    QVector<QVector<int>> calculateInverseMatrix(const QVector<QVector<int>> &matrix);
    int modularInverse(int a, int m);

};

#endif // FORM_CIPHER_H
