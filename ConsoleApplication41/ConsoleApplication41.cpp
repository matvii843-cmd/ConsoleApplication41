#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Helper function to create a dynamic 2D array
int** createMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

// Helper function to fill a matrix with random numbers
void fillMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 90 + 10; // Random numbers from 10 to 99
        }
    }
}

// Helper function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    if (rows == 0 || cols == 0) {
        cout << "Matrix is empty." << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// Helper function to free memory of a matrix
void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Task 1. Add a row to the beginning of the matrix
void addRowToStart(int**& matrix, int& rows, int cols) {
    int** newMatrix = createMatrix(rows + 1, cols);
    // New row at index 0
    for (int j = 0; j < cols; j++) {
        newMatrix[0][j] = rand() % 90 + 10;
    }
    // Copy old rows shifted down
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i + 1][j] = matrix[i][j];
        }
    }
    deleteMatrix(matrix, rows);
    matrix = newMatrix;
    rows++;
    cout << "Row added to the beginning." << endl;
}

// Task 2. Delete a row from the beginning of the matrix
void deleteRowFromStart(int**& matrix, int& rows, int cols) {
    if (rows == 0) {
        cout << "Matrix is empty." << endl;
        return;
    }
    if (rows == 1) {
        deleteMatrix(matrix, rows);
        matrix = nullptr;
        rows = 0;
        cout << "Row deleted. Matrix is now empty." << endl;
        return;
    }
    int** newMatrix = createMatrix(rows - 1, cols);
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i - 1][j] = matrix[i][j];
        }
    }
    deleteMatrix(matrix, rows);
    matrix = newMatrix;
    rows--;
    cout << "First row deleted." << endl;
}

// Task 3. Delete a row from a specified position
void deleteRowAtPosition(int**& matrix, int& rows, int cols, int pos) {
    if (rows == 0) {
        cout << "Matrix is empty." << endl;
        return;
    }
    if (pos < 0 || pos >= rows) {
        cout << "Invalid row position." << endl;
        return;
    }
    if (rows == 1) {
        deleteMatrix(matrix, rows);
        matrix = nullptr;
        rows = 0;
        cout << "Row deleted. Matrix is now empty." << endl;
        return;
    }
    int** newMatrix = createMatrix(rows - 1, cols);
    int newRow = 0;
    for (int i = 0; i < rows; i++) {
        if (i == pos) continue;
        for (int j = 0; j < cols; j++) {
            newMatrix[newRow][j] = matrix[i][j];
        }
        newRow++;
    }
    deleteMatrix(matrix, rows);
    matrix = newMatrix;
    rows--;
    cout << "Row at position " << pos << " deleted." << endl;
}

// Task 4. Add a column to the beginning of the matrix
void addColumnToStart(int**& matrix, int rows, int& cols) {
    int** newMatrix = createMatrix(rows, cols + 1);
    for (int i = 0; i < rows; i++) {
        newMatrix[i][0] = rand() % 90 + 10; // New column at index 0
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j + 1] = matrix[i][j];
        }
    }
    deleteMatrix(matrix, rows);
    matrix = newMatrix;
    cols++;
    cout << "Column added to the beginning." << endl;
}

// Task 5. Add a column at a specified position
void addColumnAtPosition(int**& matrix, int rows, int& cols, int pos) {
    if (pos < 0 || pos > cols) {
        cout << "Invalid column position." << endl;
        return;
    }
    int** newMatrix = createMatrix(rows, cols + 1);
    for (int i = 0; i < rows; i++) {
        int newCol = 0;
        for (int j = 0; j <= cols; j++) {
            if (j == pos) {
                newMatrix[i][j] = rand() % 90 + 10;
            }
            else {
                newMatrix[i][j] = matrix[i][newCol++];
            }
        }
    }
    deleteMatrix(matrix, rows);
    matrix = newMatrix;
    cols++;
    cout << "Column inserted at position " << pos << "." << endl;
}

// Task 6. Delete a column at a specified position
void deleteColumnAtPosition(int**& matrix, int rows, int& cols, int pos) {
    if (cols == 0) {
        cout << "Matrix has no columns." << endl;
        return;
    }
    if (pos < 0 || pos >= cols) {
        cout << "Invalid column position." << endl;
        return;
    }
    if (cols == 1) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
        cols = 0;
        cout << "Column deleted. Matrix has no columns now." << endl;
        return;
    }
    int** newMatrix = createMatrix(rows, cols - 1);
    for (int i = 0; i < rows; i++) {
        int newCol = 0;
        for (int j = 0; j < cols; j++) {
            if (j == pos) continue;
            newMatrix[i][newCol++] = matrix[i][j];
        }
    }
    deleteMatrix(matrix, rows);
    matrix = newMatrix;
    cols--;
    cout << "Column at position " << pos << " deleted." << endl;
}

int main() {
    srand(time(0)); // Seed for random numbers

    int** matrix = nullptr;
    int rows = 0;
    int cols = 0;
    int choice;

    do {
        cout << "\nMENU:\n";
        cout << "1. Create and fill matrix\n";
        cout << "2. Print matrix\n";
        cout << "3. Add row to beginning\n";
        cout << "4. Delete row from beginning\n";
        cout << "5. Delete row at position\n";
        cout << "6. Add column to beginning\n";
        cout << "7. Add column at position\n";
        cout << "8. Delete column at position\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (matrix != nullptr) deleteMatrix(matrix, rows);
            cout << "Enter number of rows: ";
            cin >> rows;
            cout << "Enter number of columns: ";
            cin >> cols;
            if (rows <= 0 || cols <= 0) {
                cout << "Rows and columns must be positive." << endl;
                rows = 0; cols = 0; matrix = nullptr;
            }
            else {
                matrix = createMatrix(rows, cols);
                fillMatrix(matrix, rows, cols);
                cout << "Matrix created and filled." << endl;
            }
            break;
        }
        case 2: {
            if (matrix == nullptr || rows == 0 || cols == 0) {
                cout << "Matrix is empty." << endl;
            }
            else {
                cout << "Matrix:" << endl;
                printMatrix(matrix, rows, cols);
            }
            break;
        }
        case 3: {
            if (matrix == nullptr || rows == 0 || cols == 0) {
                cout << "Matrix is empty." << endl;
            }
            else {
                addRowToStart(matrix, rows, cols);
            }
            break;
        }
        case 4: {
            if (matrix == nullptr) {
                cout << "Matrix is empty." << endl;
            }
            else {
                deleteRowFromStart(matrix, rows, cols);
            }
            break;
        }
        case 5: {
            if (matrix == nullptr || rows == 0) {
                cout << "Matrix is empty." << endl;
            }
            else {
                int pos;
                cout << "Enter row position to delete (0 to " << rows - 1 << "): ";
                cin >> pos;
                deleteRowAtPosition(matrix, rows, cols, pos);
            }
            break;
        }
        case 6: {
            if (matrix == nullptr || rows == 0) {
                cout << "Matrix is empty." << endl;
            }
            else {
                addColumnToStart(matrix, rows, cols);
            }
            break;
        }
        case 7: {
            if (matrix == nullptr || rows == 0) {
                cout << "Matrix is empty." << endl;
            }
            else {
                int pos;
                cout << "Enter column position to insert (0 to " << cols << "): ";
                cin >> pos;
                addColumnAtPosition(matrix, rows, cols, pos);
            }
            break;
        }
        case 8: {
            if (matrix == nullptr || rows == 0 || cols == 0) {
                cout << "Matrix is empty." << endl;
            }
            else {
                int pos;
                cout << "Enter column position to delete (0 to " << cols - 1 << "): ";
                cin >> pos;
                deleteColumnAtPosition(matrix, rows, cols, pos);
            }
            break;
        }
        case 0: {
            if (matrix != nullptr) deleteMatrix(matrix, rows);
            cout << "Exiting program." << endl;
            break;
        }
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}