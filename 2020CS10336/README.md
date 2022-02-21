# COP290
Course repository ( Chinmay Mittal, 2020CS10336 and Tanish Tuteja 2020CS10398) for COP-290  (Design Practices), 4th Semester IIT Delhi

---

## Task1: Audio Processing Library

### Subtask-1 

Four functions are supported currently

* Fully Connected Layer, takes an input matrix, multiplies by a weight matrix and add a bias matrix
* Activation, term wise activation of a matrix. Currently supports ReLU and tanh actviation functions
* Pooling Layer, takes an input matrix and stride and performs pooling, currently supports max pooling and average pooling
* Probability takes a vector as an input and converts it to a probability vector, currently supports sigmoid and softmax

---

### Running the code

` make `

This creates the executable in yourcode.out

` make clean `

This deletes all object files and the yourcode.out executable

The arguments or function calls are passed as command line arguments

For fully connected layer, 

` ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt`

---

For activation module,

` ./yourcode.out activation [type] inputmatrix.txt outputmatrix.txt`

type can be one among the following 

* relu
* tanh
---
For pooling module,

` ./yourcode.out pooling [type] inputmatrix.txt [stride] outputmatrix.txt`

type can be one among the following

* average 
* max

stride is a positive integer and the filter size is assumed to be stride*stride

---

For probability module,

` ./yourcode.out probability [type] inputvector.txt outputvector.txt`

type can be one among the following

* sigmoid
* softmax

---

### Error Handling

The following error handling is done

1. Invalid function call arguments
    
    * if wrong function name is passed program terminates
    * if wrong type argument is passed program terminates 
    * output file if not present is creaed, otherwise is overwritten
    * if any input file is not present, program terminates
    * If arguments are less than expected, program terminates

2. Formatting errors

    * Each line of input file is expected to have one token, integer or float number, else program terminates
    * Matrix Dimensions should be correct, positive integers otherwise program terminates

3. Others

    * Invalid dimensions of matrix during multiplication or addition 

---

### Additional Info and Design Choices

The program files are kept seperate from each other, and header files are created wherever required for modularity.

The make command creates the object files seperately and are linked together at the end during creation of the executable. This avoids large coompile times during debugging and development.

Vectors and matrices are passed as reference, wherever possible, to avoid large copy times.

Seperate files are created for pooling / matrix algebra / activation / fileIO etc. The main program is file.cpp, which calls these functions, whenever required.

The program is commented to facilitate readibility.

---
### Subtask-2 ( Code performance and learning through plotting scripts )

---

Improving the effeciency of fully connected layer's matrix operations using : 

1. Opensource implementations such as openblas and Intel MKL
2. Parallelization of our implementation using pthreads

---

### Running the code

` make `

This creates the required object files and three executables ` yourcode.out `,  ` openblas_mm.out`  and `randomMat.out`

` make clean `

This deletes all object files and the executables

***Note***: Both intel MKL and openblas have the same function prototype for matrix multiplication. To avoid conficts of function definition during linking of seperate object files into a single executable, we have decided to create two seperate executables one of which handles the openblas implementation  ( ` openblas_mm.out ` ) and the other handles all other implementations ( ` yourcode.out `). 

The third executable randomMat.out is used to generate random matrices to compare and plot latencies across different implementations.

For other modules ( pooling/activation/probabiltiy), all the commands to execute the code remains same as in subtask-1 ( uses `yourcode.out` ).

For the naive implementation of fullyconnected module the commands remain same ( uses `yourcode.out` )

For other optimization routines additional command line arguments can be provided as follows: 

1. ` ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt [optimization]`

    This supports the following: 

    *  INTEL MKL

    `   ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt mkl`

    *    pthread

    ` . /yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt pthread`



2. ` ./openblas_mm.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt openblas`

    This executable only supports openblas optimization routine.


---

### Design Choices for Subtask-2

* Timing files and headers have been created, to ensure uniformity of timing computations across all implementations.

* Parallelization using pthreads

    * The work of each thread is divided so as to prevent data conficts. 

    * Matrix multiplication A * B can be seperated into multiplication of each row of A with the entire matrix B forming each row of the result from each row of A. This has been used to divide the work among threads with each thread doing the computation assosciated with one or more rows of the output matrix.

    * To prevent a large number of threads from being computed , we restrict the maximum threads to 8 .

    * Thread $ i $ computes the results associated with all rows $ 1 \leq j = i + (8*k ) \leq n $, of the output matrix i.e. all rows differing by multiples of 8 where n is the number of rows in the resultant matrix and k is a whole number.