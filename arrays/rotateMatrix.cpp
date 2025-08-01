

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Step 1: Flip the matrix vertically
    int top = 0, bottom = n - 1;
    while (top < bottom) {
        for (int col = 0; col < n; col++) {
            swap(matrix[top][col], matrix[bottom][col]);
        }
        top++;
        bottom--;
    }

    // Step 2: Transpose the matrix
    for (int row = 0; row < n; row++) {
        for (int col = row + 1; col < n; col++) {
            swap(matrix[row][col], matrix[col][row]);
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Original Matrix:\n";
    printMatrix(matrix);

    rotate(matrix);

    cout << "\nRotated Matrix (90 degrees clockwise):\n";
    printMatrix(matrix);

    return 0;
}
