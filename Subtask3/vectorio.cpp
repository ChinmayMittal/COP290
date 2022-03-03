#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>
#include "vectorio.h"

#include "validators.h"

using namespace std;

vector<float> readVector(string inputFileName)
{

    fstream myFile;
    int numOfElements;
    vector<float> ans; // stores the input matrix

    myFile.open(inputFileName, ios::in);

    if (myFile.is_open())
    {

        string line;
        int linenumber = 0;
        // each line is assumed to have one token, first one being the size of the vector
        while (getline(myFile, line))
        {
            if (linenumber == 0)
            {
                numOfElements = string_to_int_validator(line, "Error on linenumber " + to_string(linenumber + 1) + " of file " + inputFileName + " number of elements in vector should be positive integer");
                ans.resize(numOfElements, 0.0);
            }
            else
            {
                ans[linenumber - 1] = string_to_float_validator(line, "Error on linenumber " + to_string(linenumber + 1) + " of file " + inputFileName + " elements of vector should be of type float");
            }
            linenumber++;
        }

        myFile.close();
    }
    else
    {
        throw(inputFileName + " does not exist ");
    }

    return ans;
}

vector<float> readVectorInOneLine( string inputFileName ) {

    fstream myFile;
    vector<float> ans; // stores the input vector 

    myFile.open(inputFileName, ios::in);

    if (myFile.is_open())
    {

        string line;
        while (getline(myFile, line))
        {
            
            stringstream buffer(line);
            string token;
            vector<string> tokens; // all tokens of the current line will be stored here
            while (getline(buffer, token, ' '))
            { // string tokenizer which splits the line (stored in a buffer ) about the empty space
                tokens.push_back(token);
            }

            for( auto token : tokens ){
                ans.push_back(string_to_float_validator( token , "float value expected in " + inputFileName)) ; 
            } 


        }

        myFile.close();
    }
    else
    {
        throw(inputFileName + " does not exist ");
    }

    return ans;

}

void writeVector(string outputFileName, vector<float> &arr)
{

    fstream myFile;
    myFile.open(outputFileName, ios::out); // file opened in write mode
    int numberOfElements = arr.size();

    if (myFile.is_open())
    {

        myFile << numberOfElements << "\n";
        // for each loop, outputs all elements of the vector
        for (auto ele : arr)
        {
            myFile << ele << "\n";
        }
        myFile.close();
    }
}