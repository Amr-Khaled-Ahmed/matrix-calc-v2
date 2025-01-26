//
// Created by Ahmad Ibrahim Ahmad on 08-Nov-24.
// The residue
/// Edited by Mohamed Ashraf 4-12-2024
/// Wanted tasks collections:
/// determinant - inverse_adjoint - testing
/// inverse_SRO - solve_system – testing
/// LSM_method – inner_product_column - testing
/// eign_values – eign_vectors - testing

#ifndef MATH3_1_MATRIX_H
#define MATH3_1_MATRIX_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
//#include "Eigen/dense"
using namespace std;

template <class T>
class Matrix {
private:
    T **elements;
    unsigned int rows;
    unsigned int columns;

    static inline T conjugate(int value) { return value; }
    static inline T conjugate(unsigned int value) { return value; }
    static inline T conjugate(long long value) { return value; }
    static inline T conjugate(unsigned long long value) { return value; }
    static inline T conjugate(long value) { return value; }
    static inline T conjugate(unsigned long value) { return value; }
    static inline T conjugate(float value) { return value; }
    static inline T conjugate(double value) { return value; }
    static inline T conjugate(long double value) { return value; }

public:
    inline Matrix() : rows(0), columns(0), elements(nullptr) {}

    inline Matrix(unsigned int rows, unsigned int columns)
            : rows(rows), columns(columns) {
        elements = new T *[rows];
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i] = new T[columns];
        }
    }

    inline Matrix(unsigned int rows, unsigned int columns, T init)
            : rows(rows), columns(columns) {
        elements = new T *[rows];
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i] = new T[columns];
            for (unsigned int j = 0; j < columns; ++j) {
                elements[i][j] = init;
            }
        }
    }
    T& operator()(size_t row, size_t col) {
        if (row >= rows || col >= columns) {
            throw std::out_of_range("Matrix indices out of range.");
        }
        return elements[row][col]; // Return modifiable reference
    }
    const T& operator()(size_t row, size_t col) const {
        if (row >= rows || col >= columns) {
            throw std::out_of_range("Matrix indices out of range.");
        }
        return elements[row][col];
    }
    Matrix operator*(const T& scalar) const {
        Matrix result(rows, columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                result(i, j) = elements[i][j] * scalar;
            }
        }
        return result;
    }

    // Overload the *= operator for scalar multiplication
    Matrix& operator*=(const T& scalar) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                elements[i][j] *= scalar;
            }
        }
        return *this;
    }
    inline Matrix(const Matrix<T> &mat) : rows(mat.rows), columns(mat.columns) {
        elements = new T *[rows];
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i] = new T[columns];
            for (unsigned int j = 0; j < columns; ++j) {
                elements[i][j] = mat.elements[i][j];
            }
        }
    }

    inline Matrix(Matrix<T> &&mat) noexcept
            : rows(mat.rows), columns(mat.columns), elements(mat.elements) {
        mat.rows = 0;
        mat.columns = 0;
        mat.elements = nullptr;
    }

    inline unsigned int get_num_rows() const { return rows; }

    inline unsigned int get_num_columns() const { return columns; }

    inline T get_element(unsigned int i, unsigned int j) const {
        if (i >= rows || j >= columns) {
            cerr << "Out of boundaries.\n";
            exit(6);
        }
        return elements[i][j];
    }

    inline void set_element(unsigned int i, unsigned int j, T value) {
        elements[i][j] = value;
    }

    inline Matrix<T>& operator=(const Matrix<T>& mat) {
        if (this != &mat) { // Prevent self-assignment
            // Free the existing memory
            for (unsigned int i = 0; i < rows; ++i) {
                delete[] elements[i];
            }
            delete[] elements;

            // Copy the dimensions
            rows = mat.rows;
            columns = mat.columns;

            // Allocate new memory and copy elements
            elements = new T*[rows];
            for (unsigned int i = 0; i < rows; ++i) {
                elements[i] = new T[columns];
                for (unsigned int j = 0; j < columns; ++j) {
                    elements[i][j] = mat.elements[i][j];
                }
            }
        }
        return *this; // Return a reference to the current object
    }


    inline Matrix<T> operator+(const Matrix<T> &mat) const {
        if (rows != mat.rows || columns != mat.columns) {
            cerr << "Matrices must have the same dimensions for addition.\n";
            exit(6);
        }
        Matrix<T> result(rows, columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                result.set_element(i, j, elements[i][j] + mat.get_element(i, j));
            }
        }
        return result;
    }

    inline Matrix<T> operator-(Matrix<T> &mat) const {
        if (rows != mat.rows || columns != mat.columns) {
            cerr << "Matrices must have the same dimensions for subtraction.\n";
            exit(6);
        }
        Matrix<T> result(rows, columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                result.set_element(i, j, elements[i][j] - mat.get_element(i, j));
            }
        }
        return result;
    }

    inline Matrix<T> operator*(const Matrix<T>& mat) const {
        if (columns != mat.rows) {
            cerr << "Number of columns in the first matrix must match the number of "
                    "rows in the second matrix.\n";
            exit(6);
        }
        Matrix<T> result(rows, mat.columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < mat.columns; ++j) {
                T sum = 0;
                for (unsigned int k = 0; k < columns; ++k) {
                    sum += elements[i][k] * mat.get_element(k, j);
                }
                result.set_element(i, j, sum);
            }
        }
        return result;
    }

    inline Matrix<T> operator^(int power) const {
        if (rows != columns) {
            cerr << "Matrix must be square for exponentiation.\n";
            exit(6);
        }
        Matrix<T> result = *this;
        for (int i = 1; i < power; ++i) {
            result = result * *this;
        }
        return result;
    }

    inline Matrix<T> operator+=(Matrix<T> &mat) {
        *this = *this + mat;
        return *this;
    }

    inline Matrix<T> operator-=(Matrix<T> &mat) {
        *this = *this - mat;
        return *this;
    }

    inline Matrix<T> operator*=(Matrix<T> &mat) {
        *this = *this * mat;
        return *this;
    }

    inline Matrix<T> operator^=(int power) {
        *this = *this ^ power;
        return *this;
    }

    inline bool operator==(Matrix<T> &mat) const {
        if (rows != mat.rows || columns != mat.columns) {
            return false;
        }
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                if (elements[i][j] != mat.get_element(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool operator!=(Matrix<T> &mat) const { return !(*this == mat); }

    inline bool operator>=(Matrix<T> &mat) const {
        //  comparison logic here Ahmad Ibrahim
        if(mat.rows!=rows || mat.columns!=columns){
            cerr<<"\nTo make sure that first matrix is small than or equal the second matrix these have to have the same of order.\n";
            exit(7);
        }
        for(unsigned int i=0;i<rows;++i){
            for(unsigned int j=0;j<columns;++j){
                if(elements[i]<mat.elements[i])
                    return false;
            }
        }
        return true;
    }

    inline bool operator<=(Matrix<T> &mat) const {
        //  comparison logic here Ahmad Ibrahim
        if(mat.rows!=rows || mat.columns!=columns){
            cerr<<"\nInvalid comparison, matrices must have the same order.\n";
            exit(7);
        }
        for(unsigned int i=0;i<rows;++i){
            for(unsigned int j=0;j<columns;++j){
                if(elements[i]>mat.elements[i])
                    return false;
            }
        }
        return true;
    }

    inline bool operator<(Matrix<T> &mat) const {
        //  comparison logic here Ahmad Ibrahim

        if(mat.rows!=rows || mat.columns!=columns){
            cerr<<"\nInvalid comparison, matrices must have the same order.\n";
            ~Matrix();
            exit(7);
        }
        for(unsigned int i=0;i<rows;++i){
            for(unsigned int j=0;j<columns;++j){
                if(elements[i]>=mat.elements[i])
                    return false;
            }
        }
        return true;
    }

    inline bool operator>(Matrix<T> &mat) const {
        //  comparison logic here Ahmad Ibrahim
        if(mat.rows!=rows || mat.columns!=columns){
            cerr<<"\nInvalid comparison, matrices must have the same order.\n";
            exit(7);
        }
        for(unsigned int i=0;i<rows;++i){
            for(unsigned int j=0;j<columns;++j){
                if(elements[i]>mat.elements[i])
                    return false;
            }
        }
        return true;
    }


    inline string what_kind() {
        //  kind logic here Amr Khaled
        if (is_zero()){
            return "Zero Matrix";
        } else if (is_symmetric()) {
            return "Symmetric";
        } else if (is_skew_symmetric()) {
            return "Skew-Symmetric";
        } else if (is_unit()) {
            return "Unit Matrix";
        } else {
            return "General Matrix";
        }
    }

    inline Matrix<T> transpose() {
        Matrix<T> result(columns, rows);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                result.set_element(j, i, elements[i][j]);
            }
        }
        return result;
    }

    // Non-const version for modification
    inline T* operator[](int i) {
        if (i < 0 || i >= rows) {
            std::cerr << "Index out of bounds. Must be between 0 and " << rows - 1 << ".\n";
            exit(6);
        }
        return elements[i]; // Return a pointer to the row
    }

    // Const version for read-only access
    inline const T* operator[](int i) const {
        if (i < 0 || i >= rows) {
            std::cerr << "Index out of bounds. Must be between 0 and " << rows - 1 << ".\n";
            exit(6);
        }
        return elements[i]; // Return a const pointer to the row
    }

    T& operator[](unsigned int i=0,unsigned int j=0){
        if(i<0||j<0 || i>=get_num_rows() || j>=get_num_columns()){
            std::cerr << "indices out of bounds. Must be between 0 , " << rows - 1 <<" and 0 , " << columns-1 << ".\n";
            exit(6);
        }
        return elements[i][j];
    }

    inline T determinant() {
        //  determinant logic here "Mahmoud Ibraheem"
        if (this->rows != this->columns || this->rows == 0) {
            // if not a square return 0
            return T(0);
        } else if (this->rows == 1) {
            return this->get_element(0, 0);
        } else if (this->rows == 2) { // Can delete this condition
            return this->get_element(0, 0) *this->get_element(1, 1) - this->get_element(0, 1) * this->get_element(1, 0);
        }

        // Initialize determinant value
        T value = T(1);

        // Use LU decomposition
        Matrix<T> upper(this->rows, this->columns);
        this->Doolittle(upper);

        // Det(A) = Det(L) * Det(U)
        // Determinant of Triangle Matrix = ∏(main diagonal)
        // Det(L) = ∏(main diagonal) = 1
        // Det(U) = ∏(main diagonal)
        for (unsigned int i = 0; i < this->rows; ++i) {
            value *= upper.get_element(i, i);
        }

        return value;
    }

    inline Matrix<T> inverse_adjoint() { // (1/Det(A)) . C^T
        // inverse_adjoint logic here "Mahmoud Ibraheem"

        // if not a square
        if (this->rows != this->columns) {
            throw runtime_error("Not Same Dimensions");
        } else if (this->rows == 0 || this->rows == 1) {
            return *this;
        }

        T main_determinant = this->determinant(); // Det(A)

        Matrix<T> inverse(this->rows, this->columns);
        Matrix<T> cofactor(this->rows - 1, this->columns - 1);

        for (unsigned int m = 0; m < this->rows; ++m) {
            for (unsigned int n = 0; n < this->columns; ++n) {

                // Construction of C(n,m) -> Cofactor
                for (unsigned int i = 0; i < this->rows; ++i) {
                    // exclude same row
                    if (i == m) {
                        continue;
                    }

                    for (unsigned int j = 0; j < this->columns; ++j) {
                        // Exclude same column
                        if (j == n) {
                            continue;
                        } else {
                            cofactor.set_element((i < m) ? i : i - 1, (j < n) ? j : j - 1, this->get_element(i, j));
                        }
                    }
                } // End of construction

                // Set element (m, n) in inverse matrix
                inverse.set_element(m, n, (cofactor.determinant() * T(pow(-1, m + n))) / main_determinant);
            }
        }

        return inverse;
    }

 inline Matrix<T> inverse_SRO() {
    if (rows != columns) {
        cerr << "Matrix must be square to find the inverse.\n";
        exit(6);
    }

    // Create an augmented matrix [A | I]
    Matrix<T> augmented(rows, 2 * columns);
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < columns; ++j) {
            augmented.set_element(i, j, this->get_element(i, j));
            augmented.set_element(i, j + columns, (i == j) ? T(1) : T(0));
        }
    }

    // Perform Gaussian elimination
    for (unsigned int i = 0; i < rows; ++i) {
        // Ensure pivot is non-zero
        if (augmented.get_element(i, i) == T(0)) {
            bool swapped = false;
            for (unsigned int k = i + 1; k < rows; ++k) {
                if (augmented.get_element(k, i) != T(0)) {
                    for (unsigned int j = 0; j < 2 * columns; ++j) {
                        swap(augmented.elements[i][j], augmented.elements[k][j]);
                    }
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                cerr << "Matrix is singular and cannot be inverted.\n";
                exit(6);
            }
        }

        // Normalize the pivot row
        T pivot = augmented.get_element(i, i);
        for (unsigned int j = 0; j < 2 * columns; ++j) {
            augmented.elements[i][j] /= pivot;
        }

        // Eliminate other rows
        for (unsigned int k = 0; k < rows; ++k) {
            if (k == i) continue;
            T factor = augmented.get_element(k, i);
            for (unsigned int j = 0; j < 2 * columns; ++j) {
                augmented.elements[k][j] -= factor * augmented.get_element(i, j);
            }
        }
    }

    // Extract the inverse matrix
    Matrix<T> inverse(rows, columns);
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < columns; ++j) {
            inverse.set_element(i, j, augmented.get_element(i, j + columns));
        }
    }

    return inverse;
}

 inline void solve_system() {
    if (rows != columns) {
      cerr << "Coefficient matrix must be square.\n";
      exit(6);
    }

    // Assuming the last column contains the constants (B)
    Matrix<T> A(rows, columns - 1);
    Matrix<T> B(rows, 1);

    for (unsigned int i = 0; i < rows; ++i) {
      for (unsigned int j = 0; j < columns - 1; ++j) {
        A.set_element(i, j, this->get_element(i, j));
      }
      B.set_element(i, 0, this->get_element(i, columns - 1));
    }

    // Solve X = A^-1 * B
    Matrix<T> A_inv = A.inverse_SRO();
    Matrix<T> X = A_inv * B;

    cout << "Solution:\n" << X;
  }

    inline T inner_product_column(int i, int j) {
        // Defineyourinnerproductcolumnlogic here
        return 0;
    }

//    inline void norm() {
//        // Define your normlogic here
//    }
// to be looking...
    inline T norm(int i) {
        //  norm logic here Ahmad Ibrahim
        T sum;
        for(unsigned int j=0;j<columns;++j){
            for(unsigned int i=0;i<rows;++i){
                if(!i){
                    sum = elements[i][j] * conjugate(elements[i][j]);
                }
                sum += elements[i][j] * conjugate(elements[i][j]);
            }
        }
        return sqrt(sum);
    }

    inline T *get_column(unsigned int j) {
        // get column logic here Ahmad Ibrahim
        if (j >= columns){
            cerr << "Index out of bounds. Must be between 0 and " << columns - 1 << ".\n";
            exit(6);
        }
        T*one_column = new T[rows];
        for(unsigned int i=0;i<rows;++i){
            one_column[i]=elements[i][j];
        }
        return one_column;
    }

    inline T *get_row(unsigned int i) {
        // get row logic here Ahmad Ibrahim
        if (i >= rows){
            cerr << "Index out of bounds. Must be between 0 and " << rows - 1 << ".\n";
            exit(6);
        }
        T*one_row = new T[columns];
        for(unsigned int j=0;j<columns;++j){
            one_row[j] = elements[i][j];
        }
        return one_row;
    }

    inline void swap_two_columns(int i, int j) {
        //  swap two columns logic here
        if (i >= rows || j >= columns || i < 0 || j < 0) {
            cerr << "Out of boundaries.\n";
            exit(6);
        }
        T element;
        for(unsigned int k=0;k<rows;++k){
            element = elements[k][i];
            elements[k][i] = elements[k][j];
            elements[k][j] = element;
        }
    }

    inline void swap_two_rows(int i, int j) {
        //  swap two rows logic here Ahmad Ibrahim
        if (i >= rows || j >= columns || i < 0 || j < 0) {
            cerr << "Out of boundaries.\n";
            exit(6);
        }
        T element;
        for(unsigned int k=0;k<columns;++k){
            element = elements[i][k];
            elements[i][k] = elements[j][k];
            elements[j][k] = element;
        }
    }



    inline Matrix<T> Crout(Matrix<T> &L) {
        // Crout logic here
        Matrix<T> U(L.rows,L.columns);
        Crout(L,U);
        return U;
    }

    // Cholesky Decomposition Implementation
    inline void Cholesky(Matrix<T> &mat, Matrix<T> &mat2) {
        // Cholesky logic here "Mohamed Ashraf"
        // Validate input matrices
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square for Cholesky decomposition");
        }
        if (mat.rows != rows || mat.columns != columns || mat2.rows != rows || mat2.columns != columns) {
            cerr << "\nL and U matrices must have the same order as the original matrix\n";
            exit(8);
        }

        // Verify the matrix is symmetric positive definite
        // (this is a basic check, a more robust method would involve eigenvalue computation)
        if (!is_symmetric()) {
            cerr << "\nMatrix must be symmetric for Cholesky decomposition\n" ;
            exit(9);
        }

        // Initialize L and U matrices to zero
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                mat.set_element(i, j, 0);    // L matrix
                mat2.set_element(i, j, 0);   // U matrix (will be L^T)
            }
        }

        // Perform Cholesky decomposition
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j <= i; ++j) {
                double sum = 0.0;

                // Calculate L[i][j]
                for (unsigned int k = 0; k < j; ++k) {
                    sum += mat.get_element(i, k) * mat.get_element(j, k);
                }

                if (i == j) {
                    // Diagonal elements
                    double diag = get_element(i, i) - sum;
                    if (diag <= 0) {
                        throw std::runtime_error("Matrix is not positive definite");
                    }
                    double value = sqrt(diag);
                    mat.set_element(i, j, value);
                    mat2.set_element(j, i, value);  // Transpose of L
                } else {
                    // Lower triangular elements
                    double value = (get_element(i, j) - sum) / mat.get_element(j, j);
                    mat.set_element(i, j, value);
                    mat2.set_element(j, i, value);  // Transpose of L
                }
            }
        }
    }

    // Doolittle Decomposition Implementation
    inline void Doolittle(Matrix<T> &L, Matrix<T> &U) {
        // Doolittle logic here "Mohamed Ashraf"
        // Validate input matrices
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square for Doolittle decomposition");
        }
        if (L.rows != rows || L.columns != columns || U.rows != rows || U.columns != columns) {
            cerr << "\nL and U matrices must have the same order as the original matrix\n";
            exit(8);
        }

        // Initialize L and U matrices
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                if (j < i) {
                    // Lower triangular part of L
                    L.set_element(i, j, T(0));
                } else if (j == i) {
                    // Diagonal of L is 1
                    L.set_element(i, j, T(1));
                } else {
                    // Upper triangular part of L
                    L.set_element(i, j, T(0));
                }

                if (i <= j) {
                    // Upper triangular part of U (including diagonal)
                    U.set_element(i, j, T(0));
                } else {
                    // Lower triangular part of U
                    U.set_element(i, j, T(0));
                }
            }
        }

        // Perform Doolittle decomposition
        for (unsigned int i = 0; i < rows; ++i) {
            // Calculate U rows
            for (unsigned int j = i; j < columns; ++j) {
                T sum = T(0);
                for (unsigned int k = 0; k < i; ++k) {
                    sum += L.get_element(i, k) * U.get_element(k, j);
                }
                U.set_element(i, j, get_element(i, j) - sum);
            }

            // Calculate L columns
            for (unsigned int j = i + 1; j < rows; ++j) {
                T sum = T(0);
                for (unsigned int k = 0; k < i; ++k) {
                    sum += L.get_element(j, k) * U.get_element(k, i);
                }

                // Protect against division by zero
                if (U.get_element(i, i) == T(0)) {
                    throw std::runtime_error("Division by zero in Doolittle decomposition");
                }

                L.set_element(j, i, (get_element(j, i) - sum) / U.get_element(i, i));
            }
        }
    }

    // Overloaded method for returning decomposed matrices
    inline Matrix<T> Cholesky(Matrix<T> &mat2) {
        Matrix<T> L(rows, columns);
        Cholesky(L, mat2);
        return L;
    }

    inline Matrix<T> Doolittle(Matrix<T> &mat2) {
        Matrix<T> L(rows, columns);
        Doolittle(L, mat2);
        return L;
    }

    inline void Crout(Matrix<T> &L, Matrix<T> &U) {
        // Crout logic here
        // Ensure the matrix is square
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square for LU decomposition");
        }
        if (L.rows != rows || L.columns != columns || U.rows != rows || U.columns != columns){
            cerr << "\nL and U matrices must have the same order like the factorized function\n";
            exit(8);
        }

        // Initialize L and U matrices
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                if (j < i) {
                    U.set_element(i, j, T(0)); // U is upper triangular, so below diagonal is zero
                } else if (j == i) {
                    U.set_element(i, j, T(1)); // Diagonal of U is 1
                }
                L.set_element(i, j, T(0)); // Initialize L to zero
            }
        }

        // Perform Crout decomposition
        for (size_t j = 0; j < columns; ++j) {
            // Calculate the elements of L
            for (size_t i = j; i < rows; ++i) {
                T sum = T(0);
                for (size_t k = 0; k < j; ++k) {
                    sum += L.get_element(i, k) * U.get_element(k, j);
                }
                L.set_element(i, j, get_element(i, j) - sum);
            }

            // Calculate the elements of U
            for (size_t i = j + 1; i < rows; ++i) {
                T sum = T(0);
                for (size_t k = 0; k < j; ++k) {
                    sum += L.get_element(j, k) * U.get_element(k, i);
                }
                size_t x=j;
                T denominator = L.get_element(j, x);
                if (denominator == T(0)) {
                    throw std::runtime_error("Division by zero encountered during Crout decomposition");
                }
                U.set_element(j, i, (get_element(j, i) - sum) / L.get_element(j, j));
            }
        }
        //cout<<L<<endl<<U<<endl;
    }

    inline bool is_zero() {
        // is_symmetric logic here "Mohamed Ashraf"
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (elements[i][j] != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool is_symmetric() {
        // is_symmetric logic here "Amr Khaled"
        if (rows != columns) return false; // A symmetric matrix must be square
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (elements[i][j] != elements[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool is_skew_symmetric() {
        //  is_skew_symmetric logic here Amr Khaled
        if (rows != columns) return false; // A skew-symmetric matrix must be square
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (elements[i][j] != -elements[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool is_unit() {
        // is_unit logic here For Amr Khaled
        if (rows != columns) return false; // A unit matrix must be square
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (i == j && elements[i][j] != 1) return false; // Diagonal elements must be 1
                if (i != j && elements[i][j] != 0) return false; // Non-diagonal elements must be 0
            }
        }
        return true;
    }

    inline static Matrix<T> create_unitmatrix(unsigned int i) {
        // createunitmatrix logic here
        Matrix unit(i,i);
        for(unsigned int k=0;k<i;++k){
            for(unsigned int l=0;l<i;++l){
                if(k==l) {
                    unit[k][l] = 1;
                }
                else{
                    unit[k][l] = 0;
                }
            }
        }
        return unit;
    }

    inline static Matrix<T> create_random_matrix_0_to_1(unsigned int rows,
                                                        unsigned int columns) {
        // create_random_matrix_0_to_1 logic here

        Matrix<T> matrix(rows,columns);
        random_device rd;
        mt19937 gen(rd());  // Mersenne Twister generator initialized with a random seed
        uniform_real_distribution<> dis(0.0, 1.0);
        for(int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){
                // Generate and print a random number between 0 and 1
                double random_value = dis(gen);
                matrix.set_element(i,j,random_value);
            }
        }
        return (matrix);
    }

    inline friend ostream &operator<<(ostream &out, const Matrix<T> &matrix) {
        out << '\n';
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.columns; ++j) {
                out << matrix.get_element(i, j) << '\t';
            }
            out << '\n';
        }
        return out;
    }

    inline friend istream& operator>>(std::istream& in, Matrix<T>& matrix) {
        for (unsigned int i = 0; i < matrix.rows; ++i) {
            for (unsigned int j = 0; j < matrix.columns; ++j) {
                T value;
                in >> value;
                matrix.set_element(i, j, value);
            }
        }
        return in;
    }


    inline friend Matrix<T> operator*(double scalar, Matrix<T> &matrix) {
        Matrix<T> result(matrix.rows, matrix.columns);
        for (unsigned int i = 0; i < matrix.rows; ++i) {
            for (unsigned int j = 0; j < matrix.columns; ++j) {
                result.set_element(i, j, scalar * matrix.get_element(i, j));
            }
        }
        return result;
    }

    inline friend Matrix<T> operator*(Matrix<T> &matrix, double scalar) {
        return scalar * matrix;
    }

    std::vector<T> eign_values() const {
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square to compute eigenvalues.");
        }

        Eigen::MatrixXd eigenMatrix(rows, columns);

        // Copy data from your Matrix class to Eigen's MatrixXd
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                eigenMatrix(i, j) = elements[i][j];
            }
        }

        // Compute eigenvalues
        Eigen::EigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
        Eigen::VectorXd eigenValues = solver.eigenvalues().real(); // Real part of eigenvalues

        // Apply threshold to treat small values as zero
        std::vector<T> result(eigenValues.data(), eigenValues.data() + eigenValues.size());
        for (T &val : result) {
            if (std::abs(val) < 1e-6) {
                val = 0.0;
            }
        }
        return result;
    }


    std::vector<std::vector<T>> eign_vectors() const {
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square to compute eigenvectors.");
        }

        Eigen::MatrixXd eigenMatrix(rows, columns);

        // Copy data from your Matrix class to Eigen's MatrixXd
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                eigenMatrix(i, j) = elements[i][j];
            }
        }

        // Compute eigenvectors
        Eigen::EigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
        Eigen::MatrixXd eigenVectors = solver.eigenvectors().real(); // Real part of eigenvectors

        // Convert to std::vector<std::vector<T>>
        std::vector<std::vector<T>> result(rows, std::vector<T>(columns));
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                result[i][j] = eigenVectors(i, j);
            }
        }
        return result;
    }

    inline ~Matrix() {
        for (unsigned int i = 0; i < rows; ++i) {
            delete[] elements[i];
        }
        delete[] elements;
    }
};

#endif // MATH3_1_MATRIX_H
