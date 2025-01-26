/********************************************************************************
** Form generated from reading UI file 'form_cipher.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_CIPHER_H
#define UI_FORM_CIPHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_Cipher
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *messageInput;
    QLabel *msg;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *keyInput;
    QLabel *key;
    QLabel *encryptedMessage;
    QPushButton *CipherButton;
    QPushButton *DecipherButton;
    QPushButton *Back;

    void setupUi(QWidget *Form_Cipher)
    {
        if (Form_Cipher->objectName().isEmpty())
            Form_Cipher->setObjectName("Form_Cipher");
        Form_Cipher->resize(387, 440);
        verticalLayout_2 = new QVBoxLayout(Form_Cipher);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        messageInput = new QLineEdit(Form_Cipher);
        messageInput->setObjectName("messageInput");

        horizontalLayout->addWidget(messageInput);

        msg = new QLabel(Form_Cipher);
        msg->setObjectName("msg");

        horizontalLayout->addWidget(msg);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        keyInput = new QLineEdit(Form_Cipher);
        keyInput->setObjectName("keyInput");

        horizontalLayout_2->addWidget(keyInput);

        key = new QLabel(Form_Cipher);
        key->setObjectName("key");

        horizontalLayout_2->addWidget(key);


        verticalLayout_2->addLayout(horizontalLayout_2);

        encryptedMessage = new QLabel(Form_Cipher);
        encryptedMessage->setObjectName("encryptedMessage");

        verticalLayout_2->addWidget(encryptedMessage);

        CipherButton = new QPushButton(Form_Cipher);
        CipherButton->setObjectName("CipherButton");

        verticalLayout_2->addWidget(CipherButton);

        DecipherButton = new QPushButton(Form_Cipher);
        DecipherButton->setObjectName("DecipherButton");

        verticalLayout_2->addWidget(DecipherButton);

        Back = new QPushButton(Form_Cipher);
        Back->setObjectName("Back");

        verticalLayout_2->addWidget(Back);


        retranslateUi(Form_Cipher);

        QMetaObject::connectSlotsByName(Form_Cipher);
    } // setupUi

    void retranslateUi(QWidget *Form_Cipher)
    {
        Form_Cipher->setWindowTitle(QCoreApplication::translate("Form_Cipher", "Form", nullptr));
        msg->setText(QCoreApplication::translate("Form_Cipher", "Meesage", nullptr));
        key->setText(QCoreApplication::translate("Form_Cipher", "key", nullptr));
        encryptedMessage->setText(QCoreApplication::translate("Form_Cipher", "Encrypted Message", nullptr));
        CipherButton->setText(QCoreApplication::translate("Form_Cipher", "Cipher", nullptr));
        DecipherButton->setText(QCoreApplication::translate("Form_Cipher", "Decipher", nullptr));
        Back->setText(QCoreApplication::translate("Form_Cipher", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_Cipher: public Ui_Form_Cipher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_CIPHER_H
