#include "form_matrices.h"
#include "Matrix.h"
#include "ui_form_matrices.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTemporaryFile>
#include <QTextStream>
#include <QVBoxLayout>
#include  <QVector>


Form_matrices::Form_matrices(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form_matrices) {
    ui->setupUi(this);
    setupMatrixList();
    matrix.clear();
    matrix.resize(26);

    connect(ui->tableWidget->verticalHeader(), &QHeaderView::sectionClicked, this,
            &Form_matrices::onRowHeaderClicked);
}

Form_matrices::~Form_matrices() { delete ui; }

void Form_matrices::on_Back_clicked() {
    emit showMainWindow(); // Emit signal to show the main window
    this->hide();
    // Remove the matrix text from label_3
    ui->label_3->clear();
    matrix.clear();
    matrix.resize(26);
    ui->comboBox->setCurrentIndex(0);
    on_tableWidget_destroyed();
    on_tableWidget_2_destroyed();
}

// Helper function to parse fractions and decimals
double Form_matrices::parseFraction(const QString &input) {
    // First, check if the input contains a fraction (i.e., '/')
    if (input.contains('/')) {
        QStringList parts = input.split('/');
        if (parts.size() == 2) {
            bool ok1, ok2;
            double numerator = parts[0].toDouble(&ok1);
            double denominator = parts[1].toDouble(&ok2);
            if (ok1 && ok2 && denominator != 0) {
                return numerator / denominator;
            }
        }
    }

    // If the input is not a fraction, try to interpret it as a decimal or integer
    bool ok;
    double value = input.toDouble(&ok);
    if (ok) {
        return value; // Successfully parsed a decimal or integer
    }

    // If the input is not a valid number or fraction, return 0 (or handle the
    // error as needed)
    return 0.0;
}
void Form_matrices::Saved_Matricies_Table(int Rows, int Columns) {
    QString selectedmatrix = ui->comboBox->currentText();
    bool found = false;
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem *headerItem = ui->tableWidget->verticalHeaderItem(i);
        if (headerItem && headerItem->text() == selectedmatrix) {
            // Matrix already exists in the table, update its information
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString("%1 x %2").arg(Rows).arg(Columns)));
            found = true;
            break;
        }
    }

    if (!found) {
        // Matrix not found, add a new row
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setVerticalHeaderItem(
            rowCount, new QTableWidgetItem(selectedmatrix));
        ui->tableWidget->setItem(
            rowCount, 0,
            new QTableWidgetItem(QString("%1 x %2").arg(Rows).arg(Columns)));
    }
}

void Form_matrices::Saved_Matricies_Table(int Rows, int Columns,QString index) {
    QString selectedmatrix = index;
    bool found = false;
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem *headerItem = ui->tableWidget->verticalHeaderItem(i);
        if (headerItem && headerItem->text() == selectedmatrix) {
            // Matrix already exists in the table, update its information
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString("%1 x %2").arg(Rows).arg(Columns)));
            found = true;
            break;
        }
    }

    if (!found) {
        // Matrix not found, add a new row
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setVerticalHeaderItem(
            rowCount, new QTableWidgetItem(selectedmatrix));
        ui->tableWidget->setItem(
            rowCount, 0,
            new QTableWidgetItem(QString("%1 x %2").arg(Rows).arg(Columns)));
    }
}
void Form_matrices::on_Add_clicked() {
    // Ask the user how they want to input the matrix
    QStringList options = {tr("Enter manually"), tr("Unit matrix"), tr("Random matrix")};
    bool ok;
    QString choice = QInputDialog::getItem(this, tr("Input Method"),
                                           tr("Choose how to input the matrix:"),
                                           options, 0, false, &ok);

    if (!ok)
        return; // User canceled

    ComplexMatrix matrixObj; // Create a Matrix object (initialized with 0)

    if (choice == tr("Unit matrix")) {
        // Generate a unit matrix
        int size = QInputDialog::getInt(this, tr("Matrix Size"),
                                        tr("Enter size of the unit matrix:"), 1, 1, 100, 1, &ok);
        if (!ok)
            return; // User canceled

        matrixObj = ComplexMatrix(size, size);
        for (int i = 0; i < size; ++i) {
            matrixObj.set_element(i, i, ComplexMatrix::ONE); // Set diagonal elements to 1
        }
    } else if (choice == tr("Random matrix")) {
        // Generate a random matrix
        int rows = QInputDialog::getInt(this, tr("Matrix Rows"),
                                        tr("Enter number of rows:"), 1, 1, 100, 1, &ok);
        if (!ok)
            return; // User canceled

        int columns = QInputDialog::getInt(this, tr("Matrix Columns"),
                                           tr("Enter number of columns:"), 1, 1, 100, 1, &ok);
        if (!ok)
            return; // User canceled

        matrixObj = ComplexMatrix(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                // Generate random real and imaginary parts, each mod 100
                double realPart = static_cast<double>(rand() % 100);
                double imagPart = static_cast<double>(rand() % 100);
                matrixObj.set_element(i, j, std::complex<double>(realPart, imagPart));
            }
        }
    } else if (choice == tr("Enter manually")) {
        // Enter manually
        int rows = QInputDialog::getInt(this, tr("Matrix Rows"),
                                        tr("Enter number of rows:"), 1, 1, 100, 1, &ok);
        if (!ok)
            return; // User canceled

        int columns = QInputDialog::getInt(this, tr("Matrix Columns"),
                                           tr("Enter number of columns:"), 1, 1, 100, 1, &ok);
        if (!ok)
            return; // User canceled

        matrixObj = ComplexMatrix(rows, columns); // Resize Matrix object

        QVector<QVector<complex<double>>> tempMatrix(rows, QVector<complex<double>>(columns, 0)); // Internal storage for matrix values

        // Collect user input for each matrix element (same logic as before)
        while (true) {
            QDialog dialog(this);
            dialog.setWindowTitle(tr("Enter Matrix Elements"));

            QVBoxLayout *layout = new QVBoxLayout(&dialog);

            QTableWidget *tableWidget = new QTableWidget(rows, columns, &dialog);
            tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            tableWidget->setMinimumSize(400, 300);

            // Populate the table with previously entered values or leave cells empty
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    QTableWidgetItem *item = tableWidget->item(i, j);
                    if (!item) {
                        item = new QTableWidgetItem;
                        tableWidget->setItem(i, j, item);
                    }
                    if (tempMatrix[i][j] != ComplexMatrix::ZERO) {
                        item->setText(QString::fromStdString(ComplexMatrix::complexToString(tempMatrix[i][j])));
                    }
                    item->setTextAlignment(Qt::AlignCenter);
                }
            }

            layout->addWidget(tableWidget);

            QPushButton *okButton = new QPushButton(tr("OK"), &dialog);
            QPushButton *cancelButton = new QPushButton(tr("Cancel"), &dialog);

            QHBoxLayout *buttonLayout = new QHBoxLayout;
            buttonLayout->addWidget(okButton);
            buttonLayout->addWidget(cancelButton);
            layout->addLayout(buttonLayout);

            connect(okButton, &QPushButton::clicked, [&dialog]() { dialog.accept(); });
            connect(cancelButton, &QPushButton::clicked, [&dialog]() { dialog.reject(); });

            if (dialog.exec() == QDialog::Accepted) {
                bool allFilled = true;

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < columns; ++j) {
                        QTableWidgetItem *item = tableWidget->item(i, j);
                        if (!item || item->text().isEmpty()) {
                            allFilled = false;
                        } else {
                            tempMatrix[i][j] = ComplexMatrix::stringToComplex(item->text().toStdString());
                        }
                    }
                }

                if (!allFilled) {
                    QMessageBox::warning(this, tr("Incomplete Matrix"),
                                         tr("Please fill all cells before proceeding."));
                    continue;
                }

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < columns; ++j) {
                        matrixObj.set_element(i, j, tempMatrix[i][j]);
                    }
                }

                break;
            } else {
                return; // User canceled
            }
        }
    }

    QString selectedmatrix = ui->comboBox->currentText();
    int index = selectedmatrix[0].toLatin1() - 'A';
    matrix[index] = matrixObj;
    QString matrixStr = matrixToString(matrix, index);

    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(11);
    ui->label_3->setFont(font);

    Saved_Matricies_Table(matrixObj.get_num_rows(), matrixObj.get_num_columns());
}

void Form_matrices::onRowHeaderClicked(int index) {
    QTableWidgetItem *headerItem = ui->tableWidget->verticalHeaderItem(index);
    if (!headerItem) {
        QMessageBox::warning(this, "Error", "Invalid row header clicked.");
        return;
    }

    QString selectedMatrix = headerItem->text(); // Get the row header text
    int matrixIndex =
        selectedMatrix[0].toLatin1() - 'A'; // Convert to matrix index

    if (matrixIndex < 0 || matrixIndex >= matrix.size() ||
        matrix[matrixIndex].get_num_rows() == 0) {
        QMessageBox::warning(this, "Matrix Not Found",
                             "No matrix exists for the selected header.");
        return;
    }

    // Convert the matrix to a string and display it
    QString matrixStr = matrixToString(matrix, matrixIndex);

    ui->label_3->clear();
    ui->label_3->setText(matrixStr);

    // Optionally adjust the font size
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14); // Adjust the font size as needed
    ui->label_3->setFont(font);
}
void Form_matrices::on_Is_Unit_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Get the dimensions of the selected matrix
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Check if the matrix is square
    if (rows != columns) {
        QMessageBox::information(
            this, tr("Result"),
            tr("The selected matrix is not square and cannot be a unit matrix."));
        return;
    }

    // Check if the matrix is an identity (unit) matrix
    bool isUnitMatrix = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            auto value = selectedMatrix.get_element(i, j);
            if (i == j) {
                // Diagonal elements must be 1
                if (value != 1.0) {
                    isUnitMatrix = false;
                    break;
                }
            } else {
                // Off-diagonal elements must be 0
                if (value != 0.0) {
                    isUnitMatrix = false;
                    break;
                }
            }
        }
        if (!isUnitMatrix)
            break;
    }

    // Show result to the user
    QString resultMessage = isUnitMatrix
                                ? tr("The selected matrix is a unit matrix.")
                                : tr("The selected matrix is not a unit matrix.");
    QMessageBox::information(this, tr("Result"), resultMessage);

    // Log the operation (similar to how other matrix operations are logged)
    QString operation =
        QString(" Unit Matrix %1").arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);
}

void Form_matrices::on_Is_Skew_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Get the dimensions of the selected matrix
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Check if the matrix is square
    if (rows != columns) {
        QMessageBox::information(
            this, tr("Result"),
            tr("The selected matrix is not square and cannot be skew-symmetric."));
        return;
    }

    // Check if the matrix is skew-symmetric
    bool isSkewSymmetric = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            auto a_ij = selectedMatrix.get_element(i, j);
            auto a_ji = selectedMatrix.get_element(j, i);

            if (i == j) {
                // Diagonal elements must be 0
                if (a_ij != 0.0) {
                    isSkewSymmetric = false;
                    break;
                }
            } else {
                // Off-diagonal elements must satisfy a_ij = -a_ji
                if (a_ij != -a_ji) {
                    isSkewSymmetric = false;
                    break;
                }
            }
        }
        if (!isSkewSymmetric)
            break;
    }

    // Show result to the user
    QString resultMessage =
        isSkewSymmetric ? tr("The selected matrix is skew-symmetric.")
                        : tr("The selected matrix is not skew-symmetric.");
    QMessageBox::information(this, tr("Result"), resultMessage);

    // Log the operation (similar to how transpose and symmetry checks are logged)
    QString operation = QString(" Skew-Symmetry Matrix %1")
                            .arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);
}

void Form_matrices::on_Is_Symmetric_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Get the dimensions of the selected matrix
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Check if the matrix is square
    if (rows != columns) {
        QMessageBox::information(
            this, tr("Result"),
            tr("The selected matrix is not square and cannot be symmetric."));
        return;
    }

    // Check if the matrix is symmetric
    bool isSymmetric = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            auto a_ij = selectedMatrix.get_element(i, j);
            auto a_ji = selectedMatrix.get_element(j, i);

            if (a_ij != a_ji) {
                isSymmetric = false;
                break;
            }
        }
        if (!isSymmetric)
            break;
    }

    // Show result to the user
    QString resultMessage = isSymmetric
                                ? tr("The selected matrix is symmetric.")
                                : tr("The selected matrix is not symmetric.");
    QMessageBox::information(this, tr("Result"), resultMessage);

    // Log the operation (similar to how the transpose operation is logged)
    QString operation =
        QString("Symmetry Matrix %1").arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);
}

void Form_matrices::on_Transpose_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();
    int new_index = selectedmatrix[0].toLatin1() - 'A';

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Get the dimensions of the selected matrix
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Create a new matrix for the transpose
    ComplexMatrix transposedMatrix(columns, rows);

    // Fill the transposed matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            transposedMatrix.set_element(j, i, selectedMatrix.get_element(i, j));
        }
    }

    // Replace the current matrix with its transpose
    matrix[new_index] = transposedMatrix;
    Saved_Matricies_Table(columns, rows);

    QString operation =
        QString("Transposed Matrix %1").arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);

    // Update the label to display the transposed matrix
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);

    QMessageBox::information(
        this, tr("Result"),
        tr("The transpose of the matrix has been computed and saved."));
}
void Form_matrices::updateOperationsTable(const QString &operationName) {
    int rowCount = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(
        rowCount); // Insert a new row at the end of tableWidget2

    // Add operation name to the first column
    ui->tableWidget_2->setItem(rowCount, 0, new QTableWidgetItem(operationName));
}
#include<algorithm>
QString Form_matrices::matrixToString(const QVector<ComplexMatrix>& matrix, int index) {
    const ComplexMatrix& mat = matrix[index];
    int rows = mat.get_num_rows();
    int columns = mat.get_num_columns();

    if (rows == 0 || columns == 0) {
        return "Empty Matrix";
    }

    std::vector<std::vector<QString>> formattedElements(rows, std::vector<QString>(columns));
    int maxWidth = 0;

    // Format each element and calculate maximum width
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::complex<double> value = mat.get_element(i, j);
            QString realPart = QString::number(value.real(), 'f', 2);
            QString imagPart = QString::number(value.imag(), 'f', 2);

            // Remove the decimal point if the real or imaginary part is a whole number
            if (realPart.endsWith(".00")) {
                realPart = realPart.left(realPart.length() - 3);
            }
            if (imagPart.endsWith(".00")) {
                imagPart = imagPart.left(imagPart.length() - 3);
            }

            // Construct the complex number string
            QString element = realPart;
            if (value.imag() != 0) {
                element += (value.imag() > 0 ? "+" : "") + imagPart + "i";
            }

            formattedElements[i][j] = element;
            maxWidth = std::max(maxWidth, static_cast<int>(element.length()));  // Ensure type match
        }
    }

    QString result;

    // Print the matrix with dynamic spacing
    for (int i = 0; i < rows; ++i) {
        result += "|"; // Start of row
        for (int j = 0; j < columns; ++j) {
            result += " " + formattedElements[i][j].rightJustified(maxWidth, ' ') + " ";
        }
        result += "|\n"; // End of row
    }

    return result;
}


// Function to validate the input string
bool Form_matrices::validateInput(const QString &input) {
    // Strict regular expression for validation
    QRegularExpression regex(
        R"(^(\(*\s*[0-9]*\s*[A-Z]\s*(\s*[\+\-\*]\s*\(*\s*[0-9]*\s*[A-Z]\s*\)*)*\s*\)*|\(\s*[0-9]*\s*[A-Z]\s*(\s*[\+\-\*]\s*\(*\s*[0-9]*\s*[A-Z]\s*\)*)*\s*\))(\s*[\+\-\*]\s*(\(*\s*[0-9]*\s*[A-Z]\s*(\s*[\+\-\*]\s*\(*\s*[0-9]*\s*[A-Z]\s*\)*)*\)*|\(\s*[0-9]*\s*[A-Z]\s*(\s*[\+\-\*]\s*\(*\s*[0-9]*\s*[A-Z]\s*\)*)*\s*\)))*$)");

    // Match the input string against the regex
    QRegularExpressionMatch match = regex.match(input);

    // Return true if it matches, false otherwise
    return match.hasMatch();
}

void Form_matrices::on_Apply_clicked() {
    text = ui->Text_Editor->toPlainText(); // Get the input from the editor
    updateOperationsTable(text);

    // Get the selected matrix letter from the combo box
    QString selectedMatrix = ui->comboBox->currentText();

    if (selectedMatrix.isEmpty()) {
        QMessageBox::warning(this, "No Matrix Selected",
                             "Please select a matrix from the list.");
        return;
    }

    // Validate the input expression
    if (validateInput(text)) {
        ui->Text_Editor->clear();

        // Check if all matrices referenced in the input exist in the matrix list
        for (const QChar &ch : text) {
            if (ch.isUpper()) { // Only process uppercase letters (matrix identifiers)
                int index = ch.toLatin1() -
                            'A'; // Convert 'A', 'B', 'C', etc. to indices 0, 1, 2, etc.
                if (index >= matrix.size()) {
                    QMessageBox::warning(
                        this, "Matrix Out of Range",
                        QString("Matrix '%1' does not exist. Please add it first.")
                            .arg(ch));
                    return;
                }
            }
        }

        // Perform the operations based on the input expression
        ComplexMatrix result = evaluateExpression(text);
        if (result.get_num_rows() > 0 && result.get_num_columns() > 0) {
            // Find the index of the selected matrix
            int matrixIndex = selectedMatrix[0].toLatin1() - 'A';

            // Store the result in the selected matrix
            matrix[matrixIndex] =
                result; // Store the evaluated result in the matrix list

            // Convert matrix to string for display
            QString resultStr = matrixToString(matrix, matrixIndex);

            ui->label_3->clear();
            ui->label_3->setText(resultStr);

            // Optionally adjust the font size
            ui->label_3->setAlignment(Qt::AlignCenter);
            ui->label_3->setWordWrap(true);
            QFont font = ui->label_3->font();
            font.setPointSize(14); // Adjust the font size as per your requirement
            ui->label_3->setFont(font); // Apply the font to the label
        }
    } else {
        QMessageBox::warning(this, "Invalid Input",
                             "The input must follow the format: A*(B+C) with only "
                             "single capital letters and +, -, *, operators!");
        ui->Text_Editor->clear();
    }
}

ComplexMatrix Form_matrices::evaluateExpression(const QString &expression) {

    QString expr = expression.trimmed();

    if (expr.isEmpty()) {
        throw std::invalid_argument("Expression is empty.");
    }

    QVector<QString> outputQueue; // For postfix notation
    QVector<QChar> operatorStack; // Operator stack

    // Helper to determine operator precedence
    auto precedence = [](QChar op) {
        if (op == '*')
            return 2;
        if (op == '+' || op == '-')
            return 1;
        return 0;
    };

    // Helper to apply operators
    auto applyOperator = [this](const ComplexMatrix &left,
                                const ComplexMatrix &right,
                                QChar op) -> ComplexMatrix {
        if (op == '*')
            return applyMultiplication(left, right);

        if (op == '+')
            return applyAddition(left, right);

        if (op == '-')
            return applySubtraction(left, right);

        throw std::invalid_argument("Unknown operator.");
    };

    // 1. Tokenize the input expression
    QString token;
    QString scalarBuffer; // Buffer to store scalars
    for (int i = 0; i < expr.size(); ++i) {
        QChar c = expr[i];

        if (c.isSpace())
            continue;

        if (c.isDigit()) {
            scalarBuffer.append(c); // Build scalar number
        } else if (c.isUpper()) { // Matrix identifier
            if (!scalarBuffer.isEmpty()) {
                outputQueue.append(scalarBuffer + c); // Add scalar + matrix as a token
                scalarBuffer.clear();                 // Clear scalar buffer
            } else {
                outputQueue.append(QString(c)); // Add matrix identifier directly
            }
        } else if (c == '(') {
            operatorStack.append(c);
        } else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.last() != '(') {
                outputQueue.append(QString(operatorStack.takeLast()));
            }
            if (operatorStack.isEmpty() || operatorStack.last() != '(') {
                throw std::invalid_argument("Mismatched parentheses.");
            }
            operatorStack.pop_back();                    // Remove '('
        } else if (c == '*' || c == '+' || c == '-') { // Operator
            while (!operatorStack.isEmpty() &&
                   precedence(operatorStack.last()) >= precedence(c)) {
                outputQueue.append(QString(operatorStack.takeLast()));
            }
            operatorStack.append(c);
        } else {
            throw std::invalid_argument("Invalid character in expression.");
        }
    }

    // Pop any remaining operators
    while (!operatorStack.isEmpty()) {
        if (operatorStack.last() == '(') {
            throw std::invalid_argument("Mismatched parentheses.");
        }
        outputQueue.append(QString(operatorStack.takeLast()));
    }

    // 2. Evaluate the postfix expression
    QVector<ComplexMatrix> evaluationStack;

    for (const QString &token : outputQueue) {
        if (token.size() > 1 && token[0].isDigit() && token.back().isUpper()) {
            // Scalar multiplication case (e.g., "3A")
            double scalar = token.left(token.size() - 1).toDouble();
            QString matrixId = token.right(1);
            ComplexMatrix matrix = getMatrixFromExpression(matrixId);
            evaluationStack.append(matrix * scalar); // Perform scalar multiplication
        } else if (token.size() == 1 && token[0].isUpper()) {
            // Regular matrix identifier
            evaluationStack.append(getMatrixFromExpression(token));
        } else if (token.size() == 1 &&
                   (token[0] == '*' || token[0] == '+' || token[0] == '-')) {
            // Operator
            if (evaluationStack.size() < 2) {
                throw std::invalid_argument("Invalid expression format.");
            }

            ComplexMatrix right = evaluationStack.takeLast();
            ComplexMatrix left = evaluationStack.takeLast();
            evaluationStack.append(applyOperator(left, right, token[0].toLatin1()));
        } else {
            throw std::invalid_argument("Invalid token in postfix expression.");
        }
    }

    // At the end, the stack should have exactly one matrix
    if (evaluationStack.size() != 1) {
        throw std::invalid_argument("Invalid expression format.");
    }

    return evaluationStack.last();
}

ComplexMatrix Form_matrices::getMatrixFromExpression(const QString &expr) {
    if (expr == "ans") {
        if (matrix.isEmpty()) {
            throw std::invalid_argument("'ans' is not defined yet.");
        }
        return matrix.last();
    }

    if (expr.size() == 1 && expr[0].isUpper()) {
        int index = letterToIndex(expr[0].toLatin1());
        if (index < 0 || index >= matrix.size()) {
            throw std::out_of_range("Matrix index is out of range.");
        }
        return matrix[index];
    }

    throw std::invalid_argument("Invalid matrix identifier: " +
                                expr.toStdString());
}

// Matrix addition
ComplexMatrix Form_matrices::applyAddition(const ComplexMatrix &m1,
                                           const ComplexMatrix &m2) {

    // Implement matrix addition logic (ensure the matrices are compatible)
    if(m1.get_num_columns()==m2.get_num_columns() && m2.get_num_rows()==m1.get_num_rows()) Saved_Matricies_Table(m1.get_num_rows(), m1.get_num_columns());
    return m1 + m2;
}

// Matrix subtraction
ComplexMatrix Form_matrices::applySubtraction(const ComplexMatrix &m1,
                                              const ComplexMatrix &m2) {
    // Implement matrix subtraction logic (ensure the matrices are compatible)
    if(m1.get_num_columns()==m2.get_num_columns() && m2.get_num_rows()==m1.get_num_rows())Saved_Matricies_Table(m1.get_num_rows(), m1.get_num_columns());
    return m1 - m2;
}

// Matrix multiplication
ComplexMatrix Form_matrices::applyMultiplication(const ComplexMatrix &m1,
                                                 const ComplexMatrix &m2) {
    // Implement matrix multiplication logic (ensure the matrices are compatible)
    if(m2.get_num_columns()==m1.get_num_rows())Saved_Matricies_Table(m1.get_num_rows(), m2.get_num_columns());
    return m1 * m2;
}

int Form_matrices::letterToIndex(char letter) { return letter - 'A'; }
void Form_matrices::setupMatrixList() {
    // Adding letters A to Z to the combo box
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        ui->comboBox->addItem(QString(QChar(letter)));
    }
}

int Form_matrices::addMatrixToVector(const ComplexMatrix &newMatrix) {
    // Find the first empty slot (uninitialized or empty matrix)
    int emptyIndex = -1;
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i].get_num_rows() == 0 && matrix[i].get_num_columns() == 0) {
            emptyIndex = i;
            break;
        }
    }

    // If no empty slot is found, resize the vector and add the matrix
    return emptyIndex;
}

int Form_matrices::findFirstEmptyMatrixIndex() {
    // Iterate over the matrix vector to find the first empty index
    for (int i = 0; i < matrix.size(); ++i) {
        // Check if the matrix at index i is empty (no rows and columns)
        if (matrix[i].get_num_rows() == 0 && matrix[i].get_num_columns() == 0) {
            return i; // Return the first empty index found
        }
    }

    // If no empty index is found, return -1
    return -1;
}

void Form_matrices::on_Swap_Rows_clicked() {
    // Get the selected matrix letter
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();
    int new_index = selectedmatrix[0].toLatin1() - 'A';

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    ComplexMatrix &selectedMatrixObj = matrix[displayedMatrixIndex];
    // Get the dimensions of the selected matrix
    int rows = selectedMatrixObj.get_num_rows();
    int columns = selectedMatrixObj.get_num_columns();

    // Create a new matrix for the swaped
    ComplexMatrix swaped_matrix(rows, columns);

    if (rows == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Prompt user for row indices
    bool ok1, ok2;
    QString text = QInputDialog::getText(
        this, "Swap Rows",
        QString("Enter the row numbers to swap (1-%1), separated by a comma:")
            .arg(rows),
        QLineEdit::Normal, "", &ok1);

    if (!ok1)
        return; // User canceled

    // Parse the input
    QStringList parts = text.split(',');
    if (parts.size() != 2) {
        QMessageBox::warning(
            this, "Invalid Input",
            "Please enter exactly two row numbers separated by a comma.");
        return;
    }

    int row1 = parts[0].trimmed().toInt(&ok1);
    int row2 = parts[1].trimmed().toInt(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Invalid Input",
                             "Invalid row numbers. Please enter integers.");
        return;
    }

    // Adjust for zero-based indexing
    row1--;
    row2--;

    // Validate row indices
    if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
        QMessageBox::warning(
            this, "Invalid Row Indices",
            QString("Row indices must be between 1 and %1.").arg(rows));
        return;
    }

    // Check if both rows are the same
    if (row1 == row2) {
        QMessageBox::information(this, "Same Rows",
                                 "Both rows are the same. No swap is performed.");
        return;
    }

    // Swap the rows in the matrix
    swaped_matrix = selectedMatrixObj;
    swaped_matrix.swap_two_rows(row1, row2);

    matrix[new_index] = swaped_matrix;
    Saved_Matricies_Table(rows, columns);

    QString operation =
        QString("swapped Matrix %1").arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);

    // Update the display
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);
}

void Form_matrices::on_Swap_Columns_clicked() {
    // Get the selected matrix letter
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();
    int new_index = selectedmatrix[0].toLatin1() - 'A';

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    ComplexMatrix &selectedMatrixObj = matrix[displayedMatrixIndex];
    // Get the dimensions of the selected matrix
    int rows = selectedMatrixObj.get_num_rows();
    int columns = selectedMatrixObj.get_num_columns();

    // Create a new matrix for the swaped
    ComplexMatrix swaped_matrix(rows, columns);

    if (columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Prompt user for column indices
    bool ok1, ok2;
    QString text = QInputDialog::getText(
        this, "Swap Columns",
        QString("Enter the column numbers to swap (1-%1), separated by a comma:")
            .arg(columns),
        QLineEdit::Normal, "", &ok1);

    if (!ok1)
        return; // User canceled

    // Parse the input
    QStringList parts = text.split(',');
    if (parts.size() != 2) {
        QMessageBox::warning(
            this, "Invalid Input",
            "Please enter exactly two column numbers separated by a comma.");
        return;
    }

    int col1 = parts[0].trimmed().toInt(&ok1);
    int col2 = parts[1].trimmed().toInt(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Invalid Input",
                             "Invalid column numbers. Please enter integers.");
        return;
    }

    // Adjust for zero-based indexing
    col1--;
    col2--;

    // Validate column indices
    if (col1 < 0 || col1 >= columns || col2 < 0 || col2 >= columns) {
        QMessageBox::warning(
            this, "Invalid Column Indices",
            QString("Column indices must be between 1 and %1.").arg(columns));
        return;
    }

    // Check if both columns are the same
    if (col1 == col2) {
        QMessageBox::information(
            this, "Same Columns",
            "Both columns are the same. No swap is performed.");
        return;
    }

    // Swap the columns in the matrix
    swaped_matrix = selectedMatrixObj;
    swaped_matrix.swap_two_columns(col1, col2);

    matrix[new_index] = swaped_matrix;
    Saved_Matricies_Table(rows, columns);

    QString operation =
        QString("swapped Matrix %1").arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);

    // Update the display
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);
}

void Form_matrices::on_Get_Row_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    ComplexMatrix &selectedMatrixObj = matrix[displayedMatrixIndex];
    unsigned int rows = selectedMatrixObj.get_num_rows();

    if (rows == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Prompt user for row index
    bool ok;
    int rowIndex = QInputDialog::getInt(
        this, "Get Row",
        QString("Enter the row number to retrieve (1-%1):").arg(rows), 1, 1, rows,
        1, &ok);

    if (!ok)
        return; // User canceled

    // Adjust for zero-based indexing
    rowIndex--;

    // Retrieve the row data
    auto RowData =selectedMatrixObj.get_row(rowIndex);
    QVector<complex<double>> row = QVector(RowData.begin(),RowData.end());

    // Convert row data to a string for display in transposed format
    QString rowStr = "Row " + QString::number(rowIndex + 1) + ":\n[";
    for (int i = 0; i < row.size(); ++i) {
        rowStr += QString::fromStdString(ComplexMatrix::complexToString(row[i]) + (i < row.size() - 1 ? "  " : ""));
    }
    rowStr += "]";

    // Display the row data in a message box or another widget
    QMessageBox::information(this, "Row Data", rowStr);
}

void Form_matrices::on_Get_Column_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    ComplexMatrix selectedMatrixObj = matrix[displayedMatrixIndex];
    int columns = selectedMatrixObj.get_num_columns();

    if (columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Prompt user for column index
    bool ok;
    int columnIndex = QInputDialog::getInt(
        this, "Get Column",
        QString("Enter the column number to retrieve (1-%1):").arg(columns), 1, 1,
        columns, 1, &ok);

    if (!ok)
        return; // User canceled

    // Adjust for zero-based indexing
    columnIndex--;

    // Retrieve the column data
    auto ColumnData =selectedMatrixObj.get_column(columnIndex);
    QVector<complex<double>> column = QVector(ColumnData.begin(),ColumnData.end());

    // Convert column data to a string for display
    QString columnStr =
        "Column " + QString::number(columnIndex + 1) + " (transposed):\n[";
    for (int i = 0; i < column.size(); ++i) {
        columnStr +=
            QString::fromStdString(ComplexMatrix::complexToString(column[i])) + (i < column.size() - 1 ? "  " : "");
    }
    columnStr += "]";

    // Display the column data in a message box or another widget
    QMessageBox::information(this, "Column Data", columnStr);
}

void Form_matrices::on_Norm_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    ComplexMatrix &selectedMatrixObj = matrix[displayedMatrixIndex];
    int rows = selectedMatrixObj.get_num_rows();
    int columns = selectedMatrixObj.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    // Ask the user whether to compute row or column norm
    QStringList options;
    options << "Row" << "Column";
    QString selection = QInputDialog::getItem(this, "Select Norm Type",
                                              "Choose type:", options, 0, false);

    if (selection.isEmpty()) {
        return; // User canceled
    }

    bool ok;
    int index;

    if (selection == "Row") { // Row
        index = QInputDialog::getInt(this, "Enter Row Number",
                                     QString("Enter row number (1-%1):").arg(rows),
                                     1, 1, rows, 1, &ok);
        if (!ok)
            return; // User canceled
        index--;  // Adjust for zero-based indexing

        // Retrieve the row data
        auto RowData =selectedMatrixObj.get_row(index);
        vector<complex<double>> row = vector(RowData.begin(),RowData.end());

        // Calculate the norm
        auto norm = QString::fromStdString(ComplexMatrix::complexToString(
            ComplexMatrix(selectedMatrixObj).norm(row)));

        // Display the norm
        QMessageBox::information(this, "Row Norm",
                                 "The norm of row " + QString::number(index + 1) +
                                     " is: " + norm);
    } else { // Column
        index = QInputDialog::getInt(
            this, "Enter Column Number",
            QString("Enter column number (1-%1):").arg(columns), 1, 1, columns, 1,
            &ok);
        if (!ok)
            return; // User canceled
        index--;  // Adjust for zero-based indexing

        // Retrieve the column data
        auto ColumnData =selectedMatrixObj.get_column(index);
        vector<complex<double>> column = vector(ColumnData.begin(),ColumnData.end());

        // Calculate the norm
        auto norm = QString::fromStdString(ComplexMatrix::complexToString(
            ComplexMatrix(selectedMatrixObj).norm(column)));

        // Display the norm
        QMessageBox::information(this, "Column Norm",
                                 "The norm of column " +
                                     QString::number(index + 1) +
                                     " is: " + norm);
    }
}

void Form_matrices::on_Power_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;
    QString selectedmatrix = ui->comboBox->currentText();
    int newIndex = selectedmatrix[0].toLatin1() - 'A';

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrixObj = matrix[displayedMatrixIndex];

    int rows = selectedMatrixObj.get_num_rows();
    int columns = selectedMatrixObj.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    if (rows != columns) {
        QMessageBox::warning(this, "Non-Square Matrix",
                             "Only square matrices can be raised to a power.");
        return;
    }

    bool ok;
    int exponent = QInputDialog::getInt(
        this, "Exponent", "Enter the exponent (positive integer):", 1, 1, INT_MAX, 1,
        &ok);
    if (!ok) {
        return;
    }

    ComplexMatrix result = selectedMatrixObj^exponent;

    if (newIndex == -1) {
        matrix.resize(matrix.size() + 1);
        newIndex = matrix.size() - 1;
    }
    matrix[newIndex] = result;
    Saved_Matricies_Table(result.get_num_rows(), result.get_num_columns());

    QString operation = QString("Matrix %1 raised to the power of %2 ")
                            .arg(QChar('A' + displayedMatrixIndex))
                            .arg(exponent);
    updateOperationsTable(operation);

    QString matrixStr = matrixToString(matrix, newIndex);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);
}

void Form_matrices::on_Determinant_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Ensure the matrix is square
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 || columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    if (rows != columns) {
        QMessageBox::warning(
            this, tr("Error"),
            tr("The determinant can only be computed for square matrices."));
        return;
    }

    // Compute the determinant
    auto det = QString::fromStdString(ComplexMatrix::complexToString(
        ComplexMatrix(selectedMatrix).determinant()));
    // Update the label to display the determinant
    QString determinantStr = QString("Determinant: %1").arg(det);

    QString operation = QString("Computed Determinant of Matrix %1")
                            .arg(QChar('A' + displayedMatrixIndex));
    updateOperationsTable(operation);

    QMessageBox::information(
        this, tr("Result"),
        tr("The determinant of the displayed matrix has been computed: %1")
            .arg(det));
}

void Form_matrices::on_inverse_clicked() {
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    const ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Ensure the matrix is square
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    if (rows != columns) {
        QMessageBox::warning(
            this, tr("Error"),
            tr("The inverse can only be computed for square matrices."));
        return;
    }

    // Compute the determinant
    auto det = ComplexMatrix(selectedMatrix).determinant();
    if (det == ComplexMatrix::ZERO) {
        QMessageBox::warning(
            this, tr("Error"),
            tr("The matrix is singular and does not have an inverse."));
        return;
    }

    // Compute the inverse
    ComplexMatrix inverseMatrix =
        ComplexMatrix(selectedMatrix).inverse_adjoint(det);

    // Replace the current matrix with its inverse
    int new_index = ui->comboBox->currentText()[0].toLatin1() - 'A';
    matrix[new_index] = inverseMatrix;
    Saved_Matricies_Table(rows, columns);

    QString operation =
        QString("Inverse of Matrix %1").arg(QChar('A' + displayedMatrixIndex));

    // Debugging: Check if the operation string is correct
    qDebug() << "Updating operation table with:" << operation;

    updateOperationsTable(operation);

    // Verify if the operation table is updated
    qDebug() << "Operation table updated successfully.";

    // Update the label to display the inverse matrix
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);

    QMessageBox::information(
        this, tr("Result"),
        tr("The inverse of the matrix has been computed and saved."));
}

void Form_matrices::on_tableWidget_destroyed() {
    for (int i = ui->tableWidget->rowCount(); i >= 0; i--)
        ui->tableWidget->removeRow(i);
}

void Form_matrices::on_tableWidget_2_destroyed() {
    for (int i = ui->tableWidget_2->rowCount(); i >= 0; i--)
        ui->tableWidget_2->removeRow(i);
}

void Form_matrices::on_Doolittle_clicked()
{
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Ensure the matrix is square
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    if (rows != columns) {
        QMessageBox::warning(
            this, tr("Error"),
            tr("The Dolittle decompostion can only be computed for square matrices."));
        return;
    }
    ComplexMatrix m1,m2;
    ComplexMatrix(selectedMatrix).Doolittle(m1,m2);
    // Replace the current matrix with its inverse
    int new_index = ui->comboBox->currentText()[0].toLatin1() - 'A';
    matrix[new_index] = m1;
    Saved_Matricies_Table(rows, columns,QString(1, QChar('A' + new_index)));
    if(new_index==25){
        new_index=-1;
    }
    matrix[++new_index]=m2;
    Saved_Matricies_Table(rows,columns,QString(1, QChar('A' + new_index)));
    QString operation =
        QString("Doolittle of Matrix %1").arg(QChar('A' + displayedMatrixIndex));

    // Debugging: Check if the operation string is correct
    qDebug() << "Updating operation table with:" << operation;

    updateOperationsTable(operation);

    // Verify if the operation table is updated
    qDebug() << "Operation table updated successfully.";

    // Update the label to display the inverse matrix
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);

    QMessageBox::information(
        this, tr("Result"),
        tr("The Dolittle decompostion of the matrix has been computed and saved."));
}


void Form_matrices::on_Croute_clicked()
{
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Ensure the matrix is square
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    if (rows != columns) {
        QMessageBox::warning(
            this, tr("Error"),
            tr("The Croute decompostion can only be computed for square matrices."));
        return;
    }
    ComplexMatrix m1,m2;
    ComplexMatrix(selectedMatrix).Crout(m1,m2);
    // Replace the current matrix with its inverse
    int new_index = ui->comboBox->currentText()[0].toLatin1() - 'A';
    matrix[new_index] = m1;
    Saved_Matricies_Table(rows, columns,QString(1, QChar('A' + new_index)));
    if(new_index==25){
        new_index=-1;
    }
    matrix[++new_index]=m2;
    Saved_Matricies_Table(rows,columns,QString(1, QChar('A' + new_index)));
    QString operation =
        QString("Croute of Matrix %1").arg(QChar('A' + displayedMatrixIndex));

    // Debugging: Check if the operation string is correct
    qDebug() << "Updating operation table with:" << operation;

    updateOperationsTable(operation);

    // Verify if the operation table is updated
    qDebug() << "Operation table updated successfully.";

    // Update the label to display the inverse matrix
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);

    QMessageBox::information(
        this, tr("Result"),
        tr("The Croute decompostion of the matrix has been computed and saved."));
}


void Form_matrices::on_Cholesky_clicked()
{
    // Identify the matrix currently displayed on the label
    QString displayedMatrixStr = ui->label_3->text();
    int displayedMatrixIndex = -1;

    // Find the index of the matrix currently displayed
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrixToString(matrix, i) == displayedMatrixStr) {
            displayedMatrixIndex = i;
            break;
        }
    }

    if (displayedMatrixIndex == -1) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No matrix is currently displayed on the label."));
        return;
    }

    // Get the matrix currently displayed
    ComplexMatrix &selectedMatrix = matrix[displayedMatrixIndex];

    // Ensure the matrix is square
    int rows = selectedMatrix.get_num_rows();
    int columns = selectedMatrix.get_num_columns();

    if (rows == 0 && columns == 0) {
        QMessageBox::warning(this, "Empty Matrix", "The selected matrix is empty.");
        return;
    }

    if (rows != columns) {
        QMessageBox::warning(
            this, tr("Error"),
            tr("The Cholesky decompostion can only be computed for square matrices."));
        return;
    }
    if(!selectedMatrix.isPosDef()){
        QMessageBox::warning(
            this, tr("Error"),
            tr("The Cholesky decompostion can only be computed for Symmteric and positive definite matrices."));
        return;
    }
    ComplexMatrix m1,m2;
    ComplexMatrix(selectedMatrix).Cholesky(m1,m2);
    // Replace the current matrix with its inverse
    int new_index = ui->comboBox->currentText()[0].toLatin1() - 'A';
    matrix[new_index] = m1;
    Saved_Matricies_Table(rows, columns,QString(1, QChar('A' + new_index)));
    if(new_index==25){
        new_index=-1;
    }
    matrix[++new_index]=m2;
    Saved_Matricies_Table(rows,columns,QString(1, QChar('A' + new_index)));
    QString operation =
        QString("Cholesky of Matrix %1").arg(QChar('A' + displayedMatrixIndex));

    // Debugging: Check if the operation string is correct
    qDebug() << "Updating operation table with:" << operation;

    updateOperationsTable(operation);

    // Verify if the operation table is updated
    qDebug() << "Operation table updated successfully.";

    // Update the label to display the inverse matrix
    QString matrixStr = matrixToString(matrix, new_index);
    ui->label_3->setText(matrixStr);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setWordWrap(true);
    QFont font = ui->label_3->font();
    font.setPointSize(14);
    ui->label_3->setFont(font);

    QMessageBox::information(
        this, tr("Result"),
        tr("The Cholesky decompostion of the matrix has been computed and saved."));
}

