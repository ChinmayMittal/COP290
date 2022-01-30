# COP290
Course repository ( Chinmay Mittal, 2020CS10336) for COP-290  (Design Practices), 4th Semester IIT Delhi

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


