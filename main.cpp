#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Alias for 2D matrix
using Matrix = vector<vector<int>>;

// Helper function to print a matrix with aligned columns
void printMatrix(const Matrix& mat) {
    for (size_t i = 0; i < mat.size(); ++i) {
        for (size_t j = 0; j < mat[i].size(); ++j) {
            cout << setw(4) << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

// 1. Read values from file into two N x N matrices
bool loadMatricesFromFile(const string& filename, int& N, Matrix& A, Matrix& B) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    if (!(inFile >> N) || N <= 0) {
        cerr << "Error: Invalid matrix dimension N.\n";
        return false;
    }

    // Allocate memory for two N x N matrices
    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));

    // Read Matrix A
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(inFile >> A[i][j])) {
                cerr << "Error: Insufficient data for Matrix A.\n";
                return false;
            }
        }
    }

    // Read Matrix B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(inFile >> B[i][j])) {
                cerr << "Error: Insufficient data for Matrix B.\n";
                return false;
            }
        }
    }

    inFile.close();
    return true;
}

// 2. Add two matrices and display the result
Matrix addMatrices(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix result(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    cout << "\n--- Result of Matrix Addition (A + B) ---\n";
    printMatrix(result);
    return result;
}

// 3. Multiply two matrices and display the result
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "\n--- Result of Matrix Multiplication (A * B) ---\n";
    printMatrix(result);
    return result;
}

// 4. Get the sums of matrix diagonal elements
void displayDiagonalSums(const Matrix& mat) {
    int N = mat.size();
    int mainDiagSum = 0;
    int secDiagSum = 0;

    for (int i = 0; i < N; ++i) {
        mainDiagSum += mat[i][i];
        secDiagSum += mat[i][N - 1 - i];
    }

    cout << "\n--- Diagonal Sums ---\n";
    cout << "Main Diagonal Sum:      " << mainDiagSum << "\n";
    cout << "Secondary Diagonal Sum: " << secDiagSum << "\n";
}

// 5. Swap matrix rows and display the result
Matrix swapRows(Matrix mat, int row1, int row2) {
    int N = mat.size();
    cout << "\n--- Swapping Rows " << row1 << " and " << row2 << " ---\n";

    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) {
        cerr << "Error: Row indices out of bounds (0 to " << N - 1 << ").\n";
        return mat;
    }

    swap(mat[row1], mat[row2]);
    printMatrix(mat);
    return mat;
}

// 6. Swap matrix columns and display the result
Matrix swapColumns(Matrix mat, int col1, int col2) {
    int N = mat.size();
    cout << "\n--- Swapping Columns " << col1 << " and " << col2 << " ---\n";

    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) {
        cerr << "Error: Column indices out of bounds (0 to " << N - 1 << ").\n";
        return mat;
    }

    for (int i = 0; i < N; ++i) {
        swap(mat[i][col1], mat[i][col2]);
    }

    printMatrix(mat);
    return mat;
}

// 7. Update a matrix element and display the result
Matrix updateElement(Matrix mat, int row, int col, int newValue) {
    int N = mat.size();
    cout << "\n--- Updating Element at [" << row << "][" << col << "] to " << newValue << " ---\n";

    if (row < 0 || row >= N || col < 0 || col >= N) {
        cerr << "Error: Row or Column index out of bounds (0 to " << N - 1 << ").\n";
        return mat;
    }

    mat[row][col] = newValue;
    printMatrix(mat);
    return mat;
}

int main() {
    string filename;
    cout << "Enter the matrix input filename: ";
    cin >> filename;

    int N = 0;
    Matrix A, B;

    // 1. Read & Print initial matrices
    if (!loadMatricesFromFile(filename, N, A, B)) {
        return 1;
    }

    cout << "\nMatrix A (" << N << "x" << N << "):\n";
    printMatrix(A);

    cout << "\nMatrix B (" << N << "x" << N << "):\n";
    printMatrix(B);

    // 2. Add
    addMatrices(A, B);

    // 3. Multiply
    multiplyMatrices(A, B);

    // 4. Diagonal sums (demonstrated on Matrix A)
    cout << "\nCalculating Diagonals for Matrix A:";
    displayDiagonalSums(A);

    // 5. Swap rows (swapping row 0 and row 1 on Matrix A)
    swapRows(A, 0, 1);

    // 6. Swap columns (swapping column 0 and column 2 on Matrix A)
    swapColumns(A, 0, 2);

    // 7. Update element (updating cell [1][1] to 99 on Matrix A)
    updateElement(A, 1, 1, 99);

    return 0;
}