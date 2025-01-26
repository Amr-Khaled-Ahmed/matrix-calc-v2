//
// Created by Mahmoud on 2024-12-24.
//

#ifndef MATH_3_PROJECT_COMPLEXMATRIX_H
#define MATH_3_PROJECT_COMPLEXMATRIX_H

#include <bits/stdc++.h>
#include <QString>
#include <QMessageBox>


using namespace std;

class ComplexMatrix {
private:
    vector<vector<complex<double>>> elements;
    unsigned int rows;
    unsigned int columns;

public:
    inline static complex<double> ZERO=complex<double>(0, 0);
    inline static complex<double> ONE=complex<double>(1, 0);

    inline ComplexMatrix() : rows(0), columns(0) {}

    inline ComplexMatrix(unsigned int rows, unsigned int columns)
        : rows(rows), columns(columns) {
        elements.resize(rows);
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i].resize(columns);
        }
    }

    inline ComplexMatrix(unsigned int rows, unsigned int columns, complex<double> init)
        : rows(rows), columns(columns) {
        elements.resize(rows);
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i].resize(columns, init);
        }
    }

    inline ComplexMatrix(const ComplexMatrix &mat) : rows(mat.rows), columns(mat.columns) {
        elements.resize(rows);
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i].resize(columns);
        }
        elements = mat.elements;
    }

    inline ComplexMatrix(ComplexMatrix &&mat) noexcept
        : rows(mat.rows), columns(mat.columns) {
        elements = std::move(mat.elements);
        mat.rows = 0;
        mat.columns = 0;
        mat.elements.clear();
    }

    inline void resize(unsigned int row, unsigned int column) {
        rows = row;
        columns = column;

        elements.resize(rows);
        for (unsigned int i = 0; i < rows; ++i) {
            elements[i].resize(columns);
        }
    }

    [[nodiscard]] inline unsigned int get_num_rows() const { return rows; }

    [[nodiscard]] inline unsigned int get_num_columns() const { return columns; }

    [[nodiscard]] inline complex<double> get_element(unsigned int i, unsigned int j) const {
        if (i >= rows || j >= columns) {
            cerr << "Out of boundaries.\n";
            exit(6);
        }
        return elements[i][j];
    }

    inline void set_element(unsigned int i, unsigned int j, complex<double> value) {
        elements[i][j] = value;
    }

    inline ComplexMatrix& operator=(const ComplexMatrix& mat) {
        if (this != &mat) { // Prevent self-assignment

            // Copy the dimensions
            rows = mat.rows;
            columns = mat.columns;
            elements = mat.elements;
        }
        return *this; // Return a reference to the current object
    }

    // Non-const version for modification
    inline vector<complex<double>> &operator[](unsigned int i) {
        if (i >= rows) {
            std::cerr << "Index out of bounds. Must be between 0 and " << rows - 1 << ".\n";
            exit(6);
        }

        return elements[i];
    }

    // Const version for read-only access
    inline const vector<complex<double>> &operator[](unsigned int i) const {
        if (i >= rows) {
            std::cerr << "Index out of bounds. Must be between 0 and " << rows - 1 << ".\n";
            exit(6);
        }
        return elements[i]; // Return a const pointer to the row
    }


    inline ComplexMatrix operator+(const double num)const{
        if(rows!=columns){
            cerr << "I can't add unit matrix to different matrix at dimensions.";
            exit(6);
        }
        ComplexMatrix result(*this);
        for(unsigned int i=0;i<rows;++i){
            result.elements[i][i]+=num;
        }
        return std::move(result);
    }

    inline ComplexMatrix operator-(const double num)const{
        if(rows!=columns){
            cerr << "I can't subtract unit matrix from different matrix at dimensions.";
            exit(6);
        }
        ComplexMatrix result(*this);
        for(unsigned int i=0;i<rows;++i){
            result.elements[i][i]-=num;
        }
        return std::move(result);
    }
    friend ComplexMatrix operator+(const double&num,const ComplexMatrix&mat){
        return mat+num;
    }
    friend ComplexMatrix operator-(const double&num,const ComplexMatrix&mat){
        return mat-num;
    }



    inline bool validate_dimensions(const ComplexMatrix& mat, const string& operation) const {
        if (rows != mat.rows || columns != mat.columns) {
            // Display an error message using Qt's QMessageBox::critical
            display_error_message("Matrices must have the same dimensions for " + operation + ".");
            return false;
        }
        return true;
    }

    inline ComplexMatrix operator+(const ComplexMatrix& mat) const {
        if (!validate_dimensions(mat, "addition")) {
            return ComplexMatrix(0, 0);  // Return an empty matrix if there's an error
        }

        ComplexMatrix result(rows, columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                result.set_element(i, j, elements[i][j] + mat.get_element(i, j));
            }
        }
        return result;
    }

    inline ComplexMatrix operator-(const ComplexMatrix& mat) const {
        if (!validate_dimensions(mat, "subtraction")) {
            return ComplexMatrix(0, 0);  // Return an empty matrix if there's an error
        }

        ComplexMatrix result(rows, columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                result.set_element(i, j, elements[i][j] - mat.get_element(i, j));
            }
        }
        return result;
    }

    inline ComplexMatrix operator*(const ComplexMatrix& mat) const {
        if (columns != mat.rows) {
            // Display error message for invalid multiplication dimensions
            display_error_message("Number of columns in the first matrix must match the number of rows in the second matrix.");
            return ComplexMatrix(0, 0);  // Return an empty matrix if there's an error
        }

        ComplexMatrix result(rows, mat.columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < mat.columns; ++j) {
                complex<double> sum(0);
                for (unsigned int k = 0; k < columns; ++k) {
                    sum += elements[i][k] * mat.get_element(k, j);
                }
                result.set_element(i, j, sum);
            }
        }
        return result;
    }

    // This function will display error messages using Qt's QMessageBox
    void display_error_message(const string& message) const {
        // Convert std::string to QString for use in QMessageBox
        QMessageBox::critical(nullptr, "Matrix Error", QString::fromStdString(message));
    }

    inline ComplexMatrix operator^(int power) const {
        if (rows != columns) {
            cerr << "Matrix must be square for exponentiation.\n";
            exit(6);
        }

        bool negative = false;
        if (power < 0) {
            power *= -1;
            negative = true;
        }

        ComplexMatrix res = create_unitComplexMatrix(this->rows);

        while (power > 0) {
            if (power & 1) {// If n is ODD, A^n = A * A^(n-1)
                power -= 1;
                res *= *this;
            } else { // If n is Even, A^n = A^(n/2) * A^(n/2)
                power >>= 1;
                res *= res;
            }
        }

        if (negative) {
            res = res.inverse_SRO();
        }

        return std::move(res);
    }

    inline ComplexMatrix operator+=(const ComplexMatrix &mat) {
        *this = *this + mat;
        return *this;
    }

    inline ComplexMatrix operator-=(const ComplexMatrix &mat) {
        *this = *this - mat;
        return *this;
    }

    inline ComplexMatrix operator*=(const ComplexMatrix &mat) {
        *this = *this * mat;
        return *this;
    }

    ComplexMatrix& operator^= (int power) {
        if (this->columns != this->rows) {
            cerr << "Matrix must be square for exponentiation.\n";
            exit(6);
        }

        bool negative = false;
        if (power < 0) {
            power *= -1;
            negative = true;
        }

        ComplexMatrix res(this->rows, this->columns);
        for (unsigned int i = 0; i < this->rows; ++i) {
            res.set_element(i, i, ONE);
        }

        while (power > 0) {
            if (power & 1) {// If n is ODD, A^n = A * A^(n-1)
                power -= 1;
                res *= *this;
            } else { // If n is Even, A^n = A^(n/2) * A^(n/2)
                power >>= 1;
                res *= res;
            }
        }

        if (negative) {
            res = res.inverse_SRO();
        }

        *this = res;

        return *this;
    }

    inline bool operator==(const ComplexMatrix &mat) const {
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

    inline bool operator!=(const ComplexMatrix &mat) const { return !(*this == mat); }

    // Zero, Unit, Symmetric, skew, Hermitian, LU triangle, Diagonal, Band, Scalar, Idem, Nil, Invo, Sto
    [[nodiscard]] inline vector<string> kind() const {
        if (!(rows && columns)) {
            return {};
        }

        bool Zero = true, Unit = true, Symmetric = true, skew_symm = true, Hermitian = true, skew_herm = true,
            Lower = true, Upper = true, Diagonal, Band = true, Scalar = true, Idem = true,
            Nil = true, Invo = true, Sto = true;
        if (rows != columns) {
            Unit = false;

            Symmetric = false;
            skew_symm = false;
            Hermitian = false;
            skew_herm = false;

            Upper = false;
            Lower = false;
            Band = false;

            Idem = false;
            Nil = false;
            Invo = false;
        }

        complex<double> index_zero = elements[0][0];
        if (index_zero != ONE) {
            Unit = false;
        }

        unsigned int maxBandwidth = 1;
        for (unsigned int i = 0; i < rows; ++i) {

            double column_sto_sum = 0;

            for (unsigned int j = 0; j < columns; ++j) {
                // if it contains imaginary numbers
                if (elements[i][j].imag() != 0) {
                    Zero = false;
                    Unit = false;
                    Symmetric = false;
                    skew_symm = false;
                    Sto = false;
                }

                // Zero Matrix
                if (Zero && elements[i][j] != ZERO) {
                    Zero = false;
                }

                // Symm
                if (Hermitian || Symmetric) {
                    if (elements[i][j].real() != elements[j][i].real()) {
                        Symmetric = false;
                        Hermitian = false;
                    } else if (elements[i][j].imag() != -elements[j][i].imag()) {
                        Symmetric = false;
                        Hermitian = false;
                    } else if (elements[i][j].imag() != 0) {
                        Symmetric = false;
                    }
                }

                if (Sto) {
                    if (elements[i][j].real() < 0) {
                        Sto = false;
                    } else {
                        column_sto_sum += elements[i][j].real();
                    }
                }

                if (skew_symm || skew_herm) {
                    if (elements[i][j].real() != -elements[j][i].real()) {
                        skew_symm = false;
                        skew_herm = false;
                    } else if (elements[i][j].imag() != elements[j][i].imag()) {
                        skew_symm = false;
                        skew_herm = false;
                    } else if (elements[i][j].imag() != 0) {
                        skew_symm = false;
                    }
                }

                if (elements[i][j] != ZERO) {
                    if (i > j) {
                        maxBandwidth = max(maxBandwidth, i - j);
                    } else {
                        maxBandwidth = max(maxBandwidth, j - i);
                    }
                }

                if (i < j) {
                    // Upper Triangle
                    if (Upper && elements[j][i] != ZERO)
                        Upper = false;

                    if (Scalar && elements[i][j] != ZERO) {
                        Scalar = false;
                        Unit = false;
                    }

                    if (Band && elements[i][j] != ZERO) {
                        maxBandwidth = max(maxBandwidth, j - i);
                    }

                } else if (i > j) {
                    // Upper Triangle
                    if (Lower && elements[j][i] != ZERO)
                        Lower = false;

                    if (Scalar && elements[i][j] != ZERO) {
                        Scalar = false;
                        Unit = false;
                    }

                    if (Band && elements[i][j] != ZERO) {
                        maxBandwidth = max(maxBandwidth, i - j);
                    }

                } else {
                    if (Scalar && elements[i][j] != index_zero) {
                        Scalar = false;
                        Unit = false;
                    }
                }
            }

            if (Band) {
                Band = (maxBandwidth != (rows - 1));
            }

            if (Sto && column_sto_sum != 1) {
                Sto = false;
            }
        }

        Diagonal = Upper && Lower;

        vector<string> traits;
        if (Unit) {
            traits.push_back("Unit Matrix"s);
        } else if (Scalar) {
            traits.push_back("Scalar Matrix"s);
        } else if (Diagonal) {
            traits.push_back("Diagonal Matrix"s);
        } else if (Upper) {
            traits.push_back("Upper Matrix"s);
        } else if (Lower) {
            traits.push_back("Lower Matrix"s);
        } else if (Band) {
            traits.push_back("Band Matrix"s);
        }

        // WILL BE COMBINED ELSE IF
        if (!(Unit || Scalar || Diagonal)) {
            if (Symmetric) {
                traits.push_back("Symmetric Matrix"s);
            } else if (Hermitian) {
                traits.push_back("Hermitian Matrix"s);
            } else if (skew_symm) {
                traits.push_back("Skew-Symmetric Matrix"s);
            } else if (skew_herm) {
                traits.push_back("Skew-Hermitian Matrix"s);
            }

            if (Idem && (*this == (*this ^ 2))) {
                traits.push_back("Idempotent Matrix"s);
            }

            if (Invo) {
                auto is_Involuntary = [this]() -> bool {
                    ComplexMatrix res = create_unitComplexMatrix(this->rows);

                    unsigned int power = this->rows;

                    while (power > 0) {
                        if (power & 1) {// If n is ODD, A^n = A * A^(n-1)
                            power -= 1;
                            res *= *this;
                        } else { // If n is Even, A^n = A^(n/2) * A^(n/2)
                            power >>= 1;
                            res *= res;
                        }

                        if (res.is_zero()) {
                            return true;
                        }
                    }
                    return false;
                };

                if (is_Involuntary()) {
                    traits.push_back("Involuntary Matrix"s);
                }
            }

            if (Nil) {
                if ((*this ^ 2) == create_unitComplexMatrix(rows)) {
                    traits.push_back("Involuntary Matrix"s);
                }
            }
        }

        if (Sto) {
            traits.push_back("Column Stochastic Matrix"s);
        }

        if (traits.empty()) {
            traits.push_back("General Matrix"s);
        }

        return traits;
    }

    [[nodiscard]] inline string what_kind() const {
        //  kind logic here Amr Khaled
        if (is_zero()){
            return "Zero Matrix"s;
        } else if (is_symmetric()) {
            return "Symmetric"s;
        } else if (is_skew_symmetric()) {
            return "Skew-Symmetric"s;
        } else if (is_unit()) {
            return "Unit Matrix"s;
        } else {
            return "General Matrix"s;
        }
    }

    [[nodiscard]] inline ComplexMatrix transpose() const {
        ComplexMatrix result(rows, columns);
        for (unsigned int i = 0; i < columns; ++i) {
            for (unsigned int j = 0; j < rows; ++j) {
                result.set_element(i, j, elements[i][j]);
            }
        }
        return result;
    }

    [[nodiscard]] inline complex<double> determinant() const {
        //  determinant logic here "Mahmoud Ibraheem"
        if (this->rows != this->columns || this->rows == 0 || this->columns == 0) {
            // if not a square return 0
            return {0, 0};
        } else if (this->rows == 1) {
            return this->get_element(0, 0);
        } else if (this->rows == 2) { // Can delete this condition
            return this->get_element(0, 0) *this->get_element(1, 1) - this->get_element(0, 1) * this->get_element(1, 0);
        }

        // Initialize determinant value
        complex<double> value = ONE;

        // Use LU decomposition
        ComplexMatrix upper;
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

    [[nodiscard]] inline ComplexMatrix inverse_adjoint() const { // (1/Det(A)) . C^T
        // inverse_adjoint logic here "Mahmoud Ibraheem"

        // if not a square
        if (this->rows != this->columns) {
            throw runtime_error("Not Same Dimensions");
        } else if (this->rows == 0 || this->rows == 1) {
            return *this;
        }

        complex<double> main_determinant = this->determinant(); // Det(A)
        if (main_determinant == ZERO) {
            cerr << "Matrix is singular and cannot be inverted.\n";
            exit(6);
        }

        ComplexMatrix inverse(this->rows, this->columns);
        ComplexMatrix cofactor(this->rows - 1, this->columns - 1);

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
                        if (j != n) {
                            cofactor.set_element((i < m) ? i : i - 1, (j < n) ? j : j - 1, this->get_element(i, j));
                        }
                    }
                } // End of construction

                // Set element (m, n) in inverse matrix
                inverse.set_element(m, n, (cofactor.determinant() * (pow(-1, m + n))) / main_determinant);
            }
        }

        return inverse;
    }

    [[nodiscard]] inline ComplexMatrix inverse_adjoint(complex<double> main_determinant) const { // (1/Det(A)) . C^T
        // inverse_adjoint logic here "Mahmoud Ibraheem"

        // if not a square
        if (this->rows != this->columns) {
            throw runtime_error("Not Same Dimensions");
        } else if (this->rows == 0 || this->rows == 1) {
            return *this;
        }

        if (main_determinant == ZERO) {
            cerr << "Matrix is singular and cannot be inverted.\n";
            exit(6);
        }

        ComplexMatrix inverse(this->rows, this->columns);
        ComplexMatrix cofactor(this->rows - 1, this->columns - 1);

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
                        if (j != n) {
                            cofactor.set_element((i < m) ? i : i - 1, (j < n) ? j : j - 1, this->get_element(i, j));
                        }
                    }
                } // End of construction

                // Set element (m, n) in inverse matrix
                inverse.set_element(m, n, (cofactor.determinant() * (pow(-1, m + n))) / main_determinant);
            }
        }

        return inverse;
    }

    [[nodiscard]] inline ComplexMatrix inverse_SRO() const {
        if (rows != columns) {
            cerr << "Matrix must be square to find the inverse.\n";
            exit(6);
        }

        // Create an augmented matrix [A | I]
        ComplexMatrix augmented(rows, 2 * columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                augmented.set_element(i, j, this->get_element(i, j));
                augmented.set_element(i, j + columns, (i == j) ? ONE : ZERO);
            }
        }

        // Perform Gaussian elimination
        for (unsigned int i = 0; i < rows; ++i) {
            // Ensure pivot is non-zero
            if (augmented.get_element(i, i) == ZERO) {
                bool swapped = false;
                for (unsigned int k = i + 1; k < rows; ++k) {
                    if (augmented.get_element(k, i) != ZERO) {
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
            complex<double> pivot = augmented.get_element(i, i);
            for (unsigned int j = 0; j < 2 * columns; ++j) {
                augmented.elements[i][j] /= pivot;
            }

            // Eliminate other rows
            for (unsigned int k = 0; k < rows; ++k) {
                if (k == i) continue;
                complex<double> factor = augmented.get_element(k, i);
                for (unsigned int j = 0; j < 2 * columns; ++j) {
                    augmented.elements[k][j] -= factor * augmented.get_element(i, j);
                }
            }
        }

        // Extract the inverse matrix
        ComplexMatrix inverse(rows, columns);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                inverse.set_element(i, j, augmented.get_element(i, j + columns));
            }
        }

        return inverse;
    }

    inline void solve_system() const {
        if (rows != columns) {
            cerr << "Coefficient matrix must be square.\n";
            exit(6);
        }

        // Assuming the last column contains the constants (B)
        ComplexMatrix A(rows, columns - 1);
        ComplexMatrix B(rows, 1);

        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns - 1; ++j) {
                A.set_element(i, j, this->get_element(i, j));
            }
            B.set_element(i, 0, this->get_element(i, columns - 1));
        }

        // Solve X = A^-1 * B
        ComplexMatrix A_inv = A.inverse_SRO();
        ComplexMatrix X = A_inv * B;

        cout << "Solution:\n" << X;
    }

    [[nodiscard]] inline complex<double> inner_product_column(unsigned int first_col_index, unsigned int second_col_index) const {
        // Defineyourinnerproductcolumnlogic here
        vector<complex<double>> column1 = get_column(first_col_index);
        vector<complex<double>>  column2 = get_column(second_col_index);

        complex<double> inner_product(0, 0);
        for (unsigned int i = 0; i < columns; ++i) {
            inner_product = conj(column1[i]) * column2[i];
        }

        return inner_product;
    }

    //    inline void norm() {
    //        // Define your normlogic here
    //    }
    // to be looking...

    [[nodiscard]] inline complex<double> norm() const {
        //  norm logic here Ahmad Ibrahim
        complex<double> sum(0, 0);
        for(unsigned int i = 0 ; i < rows; ++i){
            for(unsigned int j = 0; j < columns; ++j){
                sum += elements[i][j] * elements[i][j];
            }
        }

        return sqrt(sum);
    }

    inline static complex<double> norm(const vector<complex<double>> &vec) {
        //  norm logic here Ahmad Ibrahim
        complex<double> sum(0, 0);
        for (auto &item: vec) {
            sum += item * item;
        }

        return sqrt(sum);
    }

    [[nodiscard]] inline vector<complex<double>> get_column(unsigned int j) const {
        // get column logic here Ahmad Ibrahim
        if (j >= columns){
            cerr << "Index out of bounds. Must be between 0 and " << columns - 1 << ".\n";
            exit(6);
        }
        vector<complex<double>> one_column;
        for(unsigned int i = 0; i < rows; ++i){
            one_column.push_back(elements[i][j]);
        }

        return std::move(one_column);
    }

    [[nodiscard]] inline vector<complex<double>> get_row(unsigned int i) const {
        // get row logic here Ahmad Ibrahim
        if (i >= rows){
            cerr << "Index out of bounds. Must be between 0 and " << rows - 1 << ".\n";
            exit(6);
        }

        return elements[i];
    }

    inline void swap_two_columns(unsigned int i, unsigned int j) {
        //  swap two columns logic here
        if (i >= rows || j >= columns) {
            cerr << "Out of boundaries.\n";
            exit(6);
        }
        complex<double> element;
        for(unsigned int k = 0; k < rows; ++k){
            element = elements[k][i];
            elements[k][i] = elements[k][j];
            elements[k][j] = element;
        }
    }

    inline void swap_two_rows(unsigned int i, unsigned int j) {
        //  swap two rows logic here Ahmad Ibrahim
        if (i >= rows || j >= columns) {
            cerr << "Out of boundaries.\n";
            exit(6);
        }
        complex<double> element;
        for(unsigned int k = 0; k < columns; ++k){
            element = elements[i][k];
            elements[i][k] = elements[j][k];
            elements[j][k] = element;
        }
    }



    inline ComplexMatrix Crout(ComplexMatrix &L) const {
        // Crout logic here
        ComplexMatrix U(L.rows,L.columns);
        Crout(L,U);
        return U;
    }

    inline bool isPosDef() const
    {
        if (!this->is_symmetric()) // A positive definite matrix must be symmetric
            return false;

        ComplexMatrix L(get_num_rows(), get_num_columns());

        for (unsigned int i = 0; i < get_num_rows(); ++i)
        {
            for (unsigned int j = 0; j <= i; ++j) // j <= i since L is lower triangular
            {
                double sum = get_element(i, j).real();

                for (unsigned int k = 0; k < j; ++k)
                {
                    sum -= L.get_element(i, k).real() * L.get_element(j, k).real();
                }

                if (i == j) // Diagonal elements
                {
                    if (sum <= 0.0)
                        return false; // Diagonal elements must be positive
                    L[i][j] = sqrt(sum);
                }
                else // Off-diagonal elements
                {
                    L[i][j] = sum / L.get_element(j, j).real();
                }
            }
        }

        return true; // All checks passed, matrix is positive definite
    }

    // Cholesky Decomposition Implementation
    inline void Cholesky(ComplexMatrix &mat, ComplexMatrix &mat2) const {
        // Cholesky logic here "Mohamed Ashraf"
        // Validate input matrices
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square for Cholesky decomposition");
        }

        // Verify the matrix is symmetric positive definite
        // (this is a basic check, a more robust method would involve eigenvalue computation)
        if (!this->isPosDef())
            throw std::invalid_argument("Matrix must be symmetric and positive definite.");

        mat = ComplexMatrix(rows, columns);
        mat2= ComplexMatrix(rows, columns);

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
                    sum += mat.get_element(i, k).real() * mat.get_element(j, k).real();
                }

                if (i == j) {
                    // Diagonal elements
                    double diag = get_element(i, i).real() - sum;
                    if (diag <= 0) {
                        throw std::runtime_error("Matrix is not positive definite");
                    }
                    double value = sqrt(diag);
                    mat.set_element(i, j, value);
                    mat2.set_element(j, i, value);  // Transpose of L
                } else {
                    // Lower triangular elements
                    double value = (get_element(i, j).real() - sum) / mat.get_element(j, j).real();
                    mat.set_element(i, j, value);
                    mat2.set_element(j, i, value);  // Transpose of L
                }
            }
        }
    }

    // Doolittle Decomposition Implementation
    inline void Doolittle(ComplexMatrix &L, ComplexMatrix &U) const {
        // Doolittle logic here "Mohamed Ashraf"
        // Validate input matrices
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square for Doolittle decomposition");
        }

        L = create_unitComplexMatrix(rows);
        U = ComplexMatrix(rows, columns, ZERO);

        // Perform Doolittle decomposition
        for (unsigned int i = 0; i < rows; ++i) {
            // Calculate U rows
            for (unsigned int j = i; j < columns; ++j) {
                complex<double> sum = ZERO;
                for (unsigned int k = 0; k < i; ++k) {
                    sum += L.get_element(i, k) * U.get_element(k, j);
                }
                U.set_element(i, j, get_element(i, j) - sum);
            }

            // Calculate L columns
            for (unsigned int j = i + 1; j < rows; ++j) {
                complex<double> sum = ZERO;
                for (unsigned int k = 0; k < i; ++k) {
                    sum += L.get_element(j, k) * U.get_element(k, i);
                }

                // Protect against division by zero
                if (U.get_element(i, i) == ZERO) {
                    throw std::runtime_error("Division by zero in Doolittle decomposition");
                }

                L.set_element(j, i, (get_element(j, i) - sum) / U.get_element(i, i));
            }
        }
    }

    // Overloaded method for returning decomposed matrices
    inline ComplexMatrix Cholesky(ComplexMatrix &mat2) const {
        ComplexMatrix L(rows, columns);
        Cholesky(L, mat2);
        return L;
    }

    inline ComplexMatrix Doolittle(ComplexMatrix &mat2) const {
        ComplexMatrix L(rows, columns);
        Doolittle(L, mat2);
        return L;
    }

    inline void Crout(ComplexMatrix &L, ComplexMatrix &U) const {
        // Crout logic here
        // Ensure the matrix is square
        if (rows != columns) {
            throw std::invalid_argument("Matrix must be square for LU decomposition");
        }

        L = ComplexMatrix(rows, columns, ZERO);
        U = create_unitComplexMatrix(rows);

        // Perform Crout decomposition
        for (size_t j = 0; j < columns; ++j) {
            // Calculate the elements of L
            for (size_t i = j; i < rows; ++i) {
                complex<double> sum = ZERO;
                for (size_t k = 0; k < j; ++k) {
                    sum += L.get_element(i, k) * U.get_element(k, j);
                }
                L.set_element(i, j, get_element(i, j) - sum);
            }

            // Calculate the elements of U
            for (size_t i = j + 1; i < rows; ++i) {
                complex<double> sum = ZERO;
                for (size_t k = 0; k < j; ++k) {
                    sum += L.get_element(j, k) * U.get_element(k, i);
                }
                size_t x=j;
                complex<double> denominator = L.get_element(j, x);
                if (denominator == ZERO) {
                    throw std::runtime_error("Division by zero encountered during Crout decomposition");
                }
                U.set_element(j, i, (get_element(j, i) - sum) / L.get_element(j, j));
            }
        }
    }

    [[nodiscard]] inline bool is_zero() const {
        // is_symmetric logic here "Mohamed Ashraf"
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                if (get_element(i, j) != ZERO) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] inline bool is_symmetric() const {
        // is_symmetric logic here "Amr Khaled"
        if (rows != columns) return false; // A symmetric matrix must be square

        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = i + 1; j < columns; ++j) {
                if ((elements[i][j].real() != elements[j][i].real()) || (elements[i][j].imag() != elements[j][i].imag()) || (elements[i][j].imag() != 0)) {
                    return false;
                }
            }
        }

        return true;
    }

    [[nodiscard]] inline bool is_skew_symmetric() const {
        //  is_skew_symmetric logic here Amr Khaled
        if (rows != columns) return false; // A skew-symmetric matrix must be square

        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = i + 1; j < columns; ++j) {
                if ((elements[i][j].real() != -elements[j][i].real()) || (elements[i][j].imag() != elements[j][i].imag()) || (elements[i][j].imag() != 0)) {
                    return false;
                }
            }
        }
        return true;
    }

    [[nodiscard]] inline bool is_unit() const {
        // is_unit logic here For Amr Khaled
        if (rows != columns) return false; // A unit matrix must be square

        for (unsigned int i = 0; i < rows; ++i) {
            if (elements[i][i] != ONE)
                return false; // Diagonal elements must be 1

            for (unsigned int j = i + 1; j < columns; ++j) {
                if ((elements[i][j] != ZERO) || (elements[i][j] != elements[j][i]))
                    return false; // Non-diagonal elements must be 0
            }
        }
        return true;
    }

    inline static ComplexMatrix create_unitComplexMatrix(unsigned int size) {
        // createunitmatrix logic here
        ComplexMatrix unit(size, size, ZERO);

        for(unsigned int i = 0; i < size; ++i){
            unit.elements[i][i] = ONE;
        }

        return unit;
    }

    inline static ComplexMatrix create_random_ComplexMatrix_0_to_1(unsigned int rows,
                                                                   unsigned int columns) {
        // create_random_matrix_0_to_1 logic here

        ComplexMatrix matrix(rows, columns);

        random_device rd;
        mt19937 gen(rd());  // Mersenne Twister generator initialized with a random seed
        uniform_real_distribution<> dis(0.0, 1.0);

        for(unsigned int i = 0; i < rows; i++){
            for(unsigned int j = 0; j < columns; j++){
                // Generate and print a random number between 0 and 1
                complex<double> random_value = dis(gen);
                matrix.set_element(i, j, random_value);
            }
        }

        return matrix;
    }

    inline friend ostream &operator<<(ostream &out, const ComplexMatrix &matrix) {
        out << '\n';
        for (unsigned int i = 0; i < matrix.rows; ++i) {

            out << char(i && matrix.rows - i - 1 ? 179 : !i ? 218 : 192);

            for (unsigned int j = 0; j < matrix.columns; ++j) {
                out << setw(3) << matrix.get_element(i, j) << ' ';
            }

            out << ' ' << char(i && matrix.rows - i - 1 ? 179 : !i ? 191 : 217) << '\n';
        }

        return out;
    }

    inline friend istream& operator>>(std::istream& in, ComplexMatrix& matrix) {
        for (unsigned int i = 0; i < matrix.rows; ++i) {
            for (unsigned int j = 0; j < matrix.columns; ++j) {
                complex<double> value;
                in >> value;
                matrix.set_element(i, j, value);
            }
        }
        return in;
    }


    inline friend ComplexMatrix operator*(double scalar, ComplexMatrix &matrix) {
        ComplexMatrix result(matrix.rows, matrix.columns);
        for (unsigned int i = 0; i < matrix.rows; ++i) {
            for (unsigned int j = 0; j < matrix.columns; ++j) {
                result.set_element(i, j, scalar * matrix.get_element(i, j));
            }
        }
        return result;
    }

    inline friend ComplexMatrix operator*(ComplexMatrix &matrix, double scalar) {
        return scalar * matrix;
    }

    inline static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    inline static string doubleToFraction(double value) {
        const double epsilon = 1e-6;
        const int maxDenominator = 1000;
        int sign = (value < 0) ? -1 : 1;
        value = fabs(value);

        if (fabs(value - M_PI) < epsilon || fabs(value - sqrt(2)) < epsilon) {
            return "";
        }

        int bestNumerator = 1, bestDenominator = 1;
        for (int denominator = 1; denominator <= maxDenominator; ++denominator) {
            int numerator = (int) round(value * denominator);
            if (fabs(value - static_cast<double>(numerator) / denominator) < epsilon) {
                int divisor = ComplexMatrix::gcd(numerator, denominator);
                bestNumerator = numerator / divisor;
                bestDenominator = denominator / divisor;
                if (bestDenominator == 1) {
                    return (sign == -1 ? "-" : "") + to_string(bestNumerator);
                }
                return (sign == -1 ? "-" : "") + to_string(bestNumerator) + "/" + to_string(bestDenominator);
            }
        }

        return "";
    }

    inline static string complexToString(const complex<double>& num) {
        ostringstream oss;
        double real = num.real();
        double imag = num.imag();

        auto formatPart = [](double part) -> string {
            string fraction = doubleToFraction(part);
            if (!fraction.empty()) {
                return fraction;
            }
            ostringstream stream;
            stream << fixed << setprecision(3) << part;
            return stream.str();
        };

        if (real != 0) {
            oss << formatPart(real);
        }

        if (imag != 0) {
            if (real != 0 && imag > 0) {
                oss << " + ";
            } else if (real != 0 && imag < 0) {
                oss << " - ";
            } else if (imag < 0) {
                oss << "-";
            }
            oss << formatPart(fabs(imag)) << "i";
        }

        if (real == 0 && imag == 0) {
            return "0";
        }

        return oss.str();
    }

    inline static complex<double> stringToComplex(const string& input) {
        regex pureImaginaryPattern(R"(^\s*([+-]?[\d.]+(?:/[\d.]+)?)i\s*$)");
        regex pureRealPattern(R"(^\s*([+-]?[\d.]+(?:/[\d.]+)?)\s*$)");
        regex complexPattern(R"(^\s*([+-]?[\d.]+(?:/[\d.]+)?)?\s*(?:([+-]?)\s*([\d.]+(?:/[\d.]+)?)?i)?\s*$)");
        smatch matches;

        auto fractionToDouble = [](const string& fraction) -> double {
            if (fraction.find('/') != string::npos) {
                size_t pos = fraction.find('/');
                double numerator = stod(fraction.substr(0, pos));
                double denominator = stod(fraction.substr(pos + 1));
                return numerator / denominator;
            } else {
                return stod(fraction);
            }
        };

        if (regex_match(input, matches, pureImaginaryPattern)) {
            double imag = fractionToDouble(matches[1].str());
            return {0.0, imag};
        }

        if (regex_match(input, matches, pureRealPattern)) {
            double real = fractionToDouble(matches[1].str());
            return {real, 0.0};
        }

        if (regex_match(input, matches, complexPattern)) {
            double real = 0.0, imag = 0.0;

            if (matches[1].matched && !matches[1].str().empty()) {
                real = fractionToDouble(matches[1].str());
            }

            if (matches[3].matched && !matches[3].str().empty()) {
                imag = fractionToDouble(matches[3].str());
                if (matches[2].matched && matches[2].str() == "-") {
                    imag = -imag;
                }
            }

            return {real, imag};
        }

        throw invalid_argument("Invalid complex number format");
    }

    //    std::vector eign_values() const {
    //        if (rows != columns) {
    //            throw std::invalid_argument("Matrix must be square to compute eigenvalues.");
    //        }
    //
    //        Eigen::MatrixXd eigenMatrix(rows, columns);
    //
    //        // Copy data from your Matrix class to Eigen's MatrixXd
    //        for (unsigned int i = 0; i < rows; ++i) {
    //            for (unsigned int j = 0; j < columns; ++j) {
    //                eigenMatrix(i, j) = elements[i][j];
    //            }
    //        }
    //
    //        // Compute eigenvalues
    //        Eigen::EigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
    //        Eigen::VectorXd eigenValues = solver.eigenvalues().real(); // Real part of eigenvalues
    //
    //        // Apply threshold to treat small values as zero
    //        std::vector result(eigenValues.data(), eigenValues.data() + eigenValues.size());
    //        for (complex<double> &val : result) {
    //            if (std::abs(val) < 1e-6) {
    //                val = 0.0;
    //            }
    //        }
    //        return result;
    //    }
    //
    //
    //    std::vector<std::vector> eign_vectors() const {
    //        if (rows != columns) {
    //            throw std::invalid_argument("Matrix must be square to compute eigenvectors.");
    //        }
    //
    //        Eigen::MatrixXd eigenMatrix(rows, columns);
    //
    //        // Copy data from your Matrix class to Eigen's MatrixXd
    //        for (unsigned int i = 0; i < rows; ++i) {
    //            for (unsigned int j = 0; j < columns; ++j) {
    //                eigenMatrix(i, j) = elements[i][j];
    //            }
    //        }
    //
    //        // Compute eigenvectors
    //        Eigen::EigenSolver<Eigen::MatrixXd> solver(eigenMatrix);
    //        Eigen::MatrixXd eigenVectors = solver.eigenvectors().real(); // Real part of eigenvectors
    //
    //        // Convert to std::vector<std::vector>
    //        std::vector<std::vector> result(rows, std::vector(columns));
    //        for (unsigned int i = 0; i < rows; ++i) {
    //            for (unsigned int j = 0; j < columns; ++j) {
    //                result[i][j] = eigenVectors(i, j);
    //            }
    //        }
    //        return result;
    //    }

    inline ~ComplexMatrix() = default;
};


#endif //MATH_3_PROJECT_COMPLEXMATRIX_H
