#ifndef FORM_MATRICES_H
#define FORM_MATRICES_H

#include "Matrix.h" // Assuming this is your matrix class
#include "ui_form_matrices.h"
#include <QLineEdit>
#include <QWidget>
namespace Ui {
class Form_matrices;
}

class Form_matrices : public QWidget {
    Q_OBJECT

public:
    explicit Form_matrices(QWidget *parent = nullptr);

    ~Form_matrices();

private slots:
    void on_Back_clicked();
    void on_Add_clicked();
    bool validateInput(const QString &input);
    double parseFraction(const QString &input);
    void on_Apply_clicked();
    void onRowHeaderClicked(int index);
    void updateOperationsTable(const QString &operationName);
    void Saved_Matricies_Table(int Rows, int Columns);
    void on_Is_Unit_clicked();
    void on_Is_Skew_clicked();
    void on_Is_Symmetric_clicked();
    void on_Transpose_clicked();

    void on_Swap_Rows_clicked();

    void on_Swap_Columns_clicked();

    void on_Get_Row_clicked();

    void on_Get_Column_clicked();

    void on_Norm_clicked();

    void on_Power_clicked();

    void on_Determinant_clicked();

    void on_inverse_clicked();

    void on_tableWidget_destroyed();

    void on_tableWidget_2_destroyed();

    void on_Doolittle_clicked();

    void on_Croute_clicked();

    void on_Cholesky_clicked();

signals:
    void showMainWindow();

private:
    Ui::Form_matrices *ui;
    QVector<ComplexMatrix> matrix; // Matrix vector to hold the matrices
    QString text;
    int findFirstEmptyMatrixIndex();
    ComplexMatrix getMatrixFromExpression(const QString &expr);
    // Helper function to convert matrix letter (A-Z) to corresponding index
    int letterToIndex(char letter);
    void onMatrixSelected(int index);
    // Function to evaluate matrix operations based on input expression
    ComplexMatrix evaluateExpression(const QString &expression);
    void setupMatrixList();
    // Functions to perform matrix operations
    ComplexMatrix applyAddition(const ComplexMatrix &m1, const ComplexMatrix &m2);
    ComplexMatrix applySubtraction(const ComplexMatrix &m1,
                                   const ComplexMatrix &m2);
    ComplexMatrix applyMultiplication(const ComplexMatrix &m1,
                                      const ComplexMatrix &m2);
    QString matrixToString(const QVector<ComplexMatrix> &matrix, int index);
    int addMatrixToVector(const ComplexMatrix &newMatrix);
    void Saved_Matricies_Table(int Rows, int Columns,QString index);
};

#endif // FORM_MATRICES_H
