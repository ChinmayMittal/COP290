#include<bits/stdc++.h>
#include"validator.h"
#include<vector>
#include<string>
#include <fstream>

using namespace std ;

vector<float> readVector( string inputFileName ) {

    fstream myFile ; 
    int numOfElements ;
    vector<float> ans ; 

    myFile.open( inputFileName, ios::in) ;

    if( myFile.is_open() ) {

        string line ; 
        int linenumber = 0 ;
        while( getline( myFile , line )){
            if( linenumber == 0 ){
                numOfElements = string_to_int_validator(line, "Error on linenumber " + to_string(linenumber+1) + " of file " + inputFileName + " number of elements in vector should be positive integer"); 
                ans.resize( numOfElements , 0.0 ) ; 
            }else{
                ans[linenumber-1] = string_to_float_validator( line, "Error on linenumber " + to_string(linenumber+1) + " of file " + inputFileName + " elements of vector should be of type float") ; 
            }
            linenumber ++ ; 
        }

        myFile.close() ; 

    }else{
        throw (  inputFileName + " does not exist " ) ; 
    }

    return ans ; 
}

void writeVector( string outputFileName, vector<float>&arr ) {

    fstream myFile ; 
    myFile.open( outputFileName , ios::out ) ; 
    int numberOfElements = arr.size() ; 

    if( myFile.is_open()){
        
        myFile << numberOfElements << "\n" ; 
        for( auto ele : arr ) {
            myFile << ele << "\n" ; 
        }
        myFile.close() ; 
    }
}