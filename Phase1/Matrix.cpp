#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
    // Resize the matrix to the given dimensions
    data.resize(rows);
    for (int i = 0; i < rows; ++i) {
        data[i].resize(cols, 0);  // Initialize with zero
    }
}

void Matrix::setElement(int row, int col, int value) {
    if (row >= 0 && row < rowCount() && col >= 0 && col < columnCount()) {
        data[row][col] = value;
    }
}

int Matrix::getElement(int row, int col) const {
    if (row >= 0 && row < rowCount() && col >= 0 && col < columnCount()) {
        return data[row][col];
    }
    return 0; // Default if out of bounds
}

int Matrix::rowCount() const {
    return data.size();
}

int Matrix::columnCount() const {
    return data.isEmpty() ? 0 : data[0].size();
}

QString Matrix::toString() const {
    QString matrixStr;

    for (int i = 0; i < rowCount(); ++i) {
        QStringList rowStrings;
        for (int j = 0; j < columnCount(); ++j) {
            rowStrings.append(QString::number(data[i][j]));
        }
        matrixStr += rowStrings.join("     ") + "\n\n";  // Join row elements with 4 spaces and add a newline between rows
    }

    return matrixStr;  // Return the matrix as a string without brackets
}

