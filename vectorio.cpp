#include<bits/stdc++.h>
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
                numOfElements = stoi(line) ; 
                ans.resize( numOfElements , 0.0 ) ; 
            }else{
                ans[linenumber-1] = stof(line) ; 
            }
            linenumber ++ ; 
        }
        myFile.close() ; 
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