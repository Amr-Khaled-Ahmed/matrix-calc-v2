#include "form_cipher.h"
#include "ui_form_cipher.h"
#include <QDebug>

Form_Cipher::Form_Cipher(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form_Cipher)
{
    ui->setupUi(this);

    // Set window flags to prevent maximizing and minimizing
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);

    // Connect signals and slots
    connect(ui->Back, &QPushButton::clicked, this, &Form_Cipher::on_Back_clicked);
    connect(ui->CipherButton, &QPushButton::clicked, this, &Form_Cipher::on_CipherButton_clicked);
    connect(ui->DecipherButton, &QPushButton::clicked, this, &Form_Cipher::on_DecipherButton_clicked);
    setWindowTitle("Hell Cipher");

}

Form_Cipher::~Form_Cipher()
{
    delete ui;
}

void Form_Cipher::on_Back_clicked()
{
    // Reset the inputs
    ui->messageInput->clear();
    ui->keyInput->clear();
    ui->encryptedMessage->clear();

    keyMatrix.clear();
    emit showMainWindow();
    this->hide();
}

void Form_Cipher::on_CipherButton_clicked()
{
    QString message = ui->messageInput->text().trimmed();
    QString key = ui->keyInput->text().trimmed();

    if (message.isEmpty() || key.isEmpty()) {
        ui->encryptedMessage->setText("Message and key cannot be empty.");
        return;
    }

    QString encryptedMessage = hillEncryptMessage(message, key);
    ui->encryptedMessage->setText(encryptedMessage);
}

void Form_Cipher::on_DecipherButton_clicked()
{
    QString encryptedMessage = ui->messageInput->text().trimmed();
    QString key = ui->keyInput->text().trimmed();

    if (encryptedMessage.isEmpty() || key.isEmpty()) {
        ui->encryptedMessage->setText("Encrypted message and key cannot be empty.");
        return;
    }

    if (key.length() != 9) {
        ui->encryptedMessage->setText("Invalid key! Key must be 9 characters long.");
        return;
    }

    // Initialize the key matrix and calculate its inverse
    initializeKeyMatrix(key);
    QVector<QVector<int>> inverseKeyMatrix = calculateInverseMatrix(keyMatrix);

    if (inverseKeyMatrix.isEmpty()) {
        ui->encryptedMessage->setText("The provided key is not invertible.");
        return;
    }

    // Format the encrypted message (pad with spaces if needed)
    QString formattedEncryptedMessage = formatMessageWithSpaces(encryptedMessage);
    QVector<int> decryptedVector;

    // Decrypt the message block by block
    for (int i = 0; i < formattedEncryptedMessage.length(); i += 3) {
        QVector<int> encryptedVector = {
            charToNumber(formattedEncryptedMessage[i]),
            charToNumber(formattedEncryptedMessage[i + 1]),
            charToNumber(formattedEncryptedMessage[i + 2])
        };

        QVector<int> decrypted = multiplyMatrixWithVector(inverseKeyMatrix, encryptedVector);
        decryptedVector.append(decrypted);
    }

    // Convert the decrypted vector back to a string
    QString decryptedMessage = vectorToStringWithSpaces(decryptedVector).trimmed();

    // Display the decrypted message
    ui->encryptedMessage->setText(decryptedMessage);
}

void Form_Cipher::initializeKeyMatrix(const QString &keyInput)
{
    keyMatrix.clear();
    if (keyInput.length() != 9) {
        qWarning() << "Invalid key! Key must be 9 characters long.";
        return;
    }

    for (int i = 0; i < 3; ++i) {
        QVector<int> row;
        for (int j = 0; j < 3; ++j) {
            row.append(keyInput[i * 3 + j].toLatin1() - 'A');
        }
        keyMatrix.append(row);
    }
    qDebug() << "Key Matrix initialized:" << keyMatrix;
}

QString Form_Cipher::hillEncryptMessage(const QString &message, const QString &key)
{
    if (key.length() != 9) {
        return "Invalid key! Key must be 9 characters long.";
    }

    initializeKeyMatrix(key);
    QString formattedMessage = formatMessageWithSpaces(message);
    QVector<int> encryptedVector;

    for (int i = 0; i < formattedMessage.length(); i += 3) {
        QVector<int> messageVector = {
            charToNumber(formattedMessage[i]),
            charToNumber(formattedMessage[i + 1]),
            charToNumber(formattedMessage[i + 2])
        };

        QVector<int> encrypted = multiplyMatrixWithVector(keyMatrix, messageVector);
        encryptedVector.append(encrypted);
    }

    return vectorToStringWithSpaces(encryptedVector);
}

QString Form_Cipher::formatMessageWithSpaces(const QString &message)
{
    QString formattedMessage = message.toUpper();
    while (formattedMessage.length() % 3 != 0) {
        formattedMessage.append(' '); // Padding with spaces
    }
    return formattedMessage;
}

QVector<int> Form_Cipher::multiplyMatrixWithVector(const QVector<QVector<int>> &matrix, const QVector<int> &vec)
{
    QVector<int> result;
    for (int i = 0; i < 3; ++i) {
        int sum = 0;
        for (int j = 0; j < 3; ++j) {
            sum += matrix[i][j] * vec[j];
        }
        result.append(sum % 27); // Modulo 27 to handle the alphabet size
    }
    return result;
}

int Form_Cipher::charToNumber(QChar c)
{
    return (c == ' ') ? 26 : c.toLatin1() - 'A';
}

QChar Form_Cipher::numberToChar(int n)
{
    return (n == 26) ? ' ' : QChar(n + 'A');
}

QString Form_Cipher::vectorToStringWithSpaces(const QVector<int> &vec)
{
    QString result;
    for (int value : vec) {
        result.append(numberToChar(value));
    }
    return result;
}

QVector<QVector<int>> Form_Cipher::calculateInverseMatrix(const QVector<QVector<int>> &matrix)
{
    // Assuming the matrix is 3x3
    if (matrix.size() != 3 || matrix[0].size() != 3) {
        qWarning() << "Invalid matrix size. Matrix must be 3x3.";
        return {};
    }

    QVector<QVector<int>> inverse(3, QVector<int>(3, 0));

    // Calculate the determinant modulo 27
    int det = (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
               matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
               matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0])) % 27;

    if (det < 0) {
        det += 27; // Ensure the determinant is positive
    }

    // Find the modular multiplicative inverse of the determinant modulo 27
    int detInverse = modularInverse(det, 27);
    if (detInverse == -1) {
        qWarning() << "Matrix is not invertible.";
        return {};
    }

    // Calculate the adjugate matrix
    inverse[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % 27;
    inverse[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) % 27;
    inverse[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % 27;

    inverse[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) % 27;
    inverse[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % 27;
    inverse[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) % 27;

    inverse[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % 27;
    inverse[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) % 27;
    inverse[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 27;

    // Multiply each element of the adjugate matrix by the determinant inverse modulo 27
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            inverse[i][j] = (inverse[i][j] * detInverse) % 27;
            if (inverse[i][j] < 0) {
                inverse[i][j] += 27; // Ensure positive values
            }
        }
    }

    return inverse;
}

int Form_Cipher::modularInverse(int a, int m)
{
    for (int x = 1; x < m; ++x) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}
