#include <vector>
#include <iostream>
#include <chrono>

int main(){
    std::vector<std::vector<int>> matrix = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
    std::vector<std::vector<int>> kernel = { {-1,0,-1}, {-1,0,-1}, {-1,0,-1} };

    int stride = 1;

    int matrixRows = matrix.size() - kernel.size() + 1;
    int matrixCols = matrix[0].size() - kernel[0].size() + 1;

    std::vector<std::vector<int>> result(matrixRows, std::vector<int>(matrixCols, 0));

    auto start2D = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < matrixRows; i += stride) {
        for (int j = 0; j < matrixCols; j += stride) {
            int sum = 0;
            for (int kernelI = 0; kernelI < kernel.size(); kernelI++){
                const auto& row = matrix[i + kernelI];
                for (int kernelJ = 0; kernelJ < kernel[0].size(); kernelJ++){
                    sum += row[j + kernelJ] * kernel[kernelI][kernelJ];
                }
            }
            result[i][j] = sum;
        }
    }

    auto end2D = std::chrono::high_resolution_clock::now();
    auto duration2D = std::chrono::duration_cast<std::chrono::nanoseconds>(end2D - start2D).count();
    std::cout << "2D vector convolution time: " << duration2D << " ns" << std::endl;

    // Print the result matrix
    std::cout << "Result Matrix:" << std::endl;
    for (const auto& row : result) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    int newMatrixRows = 4;
    int newMatrixCols = 4;
    int newKernelSize = 3;

    int flattenedMatrix[16] = { 
        1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
       13,14,15,16
    };
    int flattenedKernel[9] = {
        -1,0,-1,
        -1,0,-1,
        -1,0,-1
    };

    int flattenedResult[4] = {0};

    int newResultRows = newMatrixRows - newKernelSize + 1;
    int newResultCols = newMatrixCols - newKernelSize + 1;

    auto start1D = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < newResultRows; i += stride) {
        for (int j = 0; j < newResultCols; j += stride) {
            int sum = 0;
            for (int kernelI = 0; kernelI < newKernelSize; kernelI++){
                for (int kernelJ = 0; kernelJ < newKernelSize; kernelJ++){
                    sum += flattenedMatrix[(i + kernelI) * newMatrixCols + (j + kernelJ)] * flattenedKernel[kernelI * newKernelSize + kernelJ];
                }
            }
            flattenedResult[i * newResultCols + j] = sum;
        }
    }

    auto end1D = std::chrono::high_resolution_clock::now();
    auto duration1D = std::chrono::duration_cast<std::chrono::nanoseconds>(end1D - start1D).count();
    std::cout << "1D flattened convolution time: " << duration1D << " ns" << std::endl;

    // Print the result matrix
    std::cout << "Result Matrix with Optimizations:" << std::endl;
    for (int i = 0; i < newResultRows; i++) {
        for (int j = 0; j < newResultCols; j++) {
            std::cout << flattenedResult[i * newResultCols + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}