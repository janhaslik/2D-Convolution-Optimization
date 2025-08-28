# Small 2D Convolution Optimization Project

## Overview

This small project demonstrates the **performance improvement** of 2D convolution when using **flattened 1D arrays** instead of `std::vector<std::vector<int>>`.  

Convolution is applied to a small `4x4` matrix with a `3x3` kernel. The project compares the execution time between the traditional 2D vector approach and the optimized 1D flattened array approach.

---

## Matrix and Kernel Example

**Input Matrix (4x4):**  

```

1   2   3   4
5   6   7   8
9  10  11  12
13 14  15  16
```

**Kernel (3x3):**  

```

-1  0 -1
-1  0 -1
-1  0 -1
```

---

## Flattening Concept

### 2D → 1D Flattening

A 2D matrix:

```

[ [1, 2, 3, 4],
[5, 6, 7, 8],
[9,10,11,12],
[13,14,15,16] ]
```

is flattened into a 1D array:

```

[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
```

**Index formula:**

```

matrix[i][j]  →  matrix1D[i * num_cols + j]
```

Example:

```

matrix[2][1] = 10
index = 2*4 + 1 = 9
matrix1D[9] = 10
```

---

## Features

- 2D vector convolution implementation.
- Optimized 1D flattened array convolution.
- Benchmarking using `std::chrono` for high-resolution timing.

---

## Results

**Execution times:**

| Method                     | Time (ns) |
|-----------------------------|-----------|
| 2D vector convolution       | 1333      |
| 1D flattened convolution    | 625       |

**Output Result Matrix (both methods):**

```

-36 -42
-60 -66
```

**Observations:**  
- Flattening the matrix to 1D reduces memory indirection and improves cache locality, resulting in a ~2.13× speed-up for this small example.
- Both methods produce identical results, confirming correctness.

---

## How It Works

1. **2D Vector Method**  
   - Uses nested `std::vector<std::vector<int>>` for the matrix and result.
   - Loops over the matrix and kernel to compute convolution.

2. **1D Flattened Method**  
   - Flattens the 2D matrix and kernel into 1D arrays.
   - Computes the convolution using index arithmetic:  

```

index = row * num_cols + col
````