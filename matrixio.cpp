#include<bits/stdc++.h>
#include<vector>
#include<string>
#include <fstream>

using namespace std ; 

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int string_to_int_validator( string s , string err ){
    // cout << s.size() <<  " " << s[1] + '\0'<< endl;
    if(!is_number(s)){
        throw err ;
    }

    int temp = stoi(s) ; 

    if( temp < 1 ) throw err ;

    return temp ; 

}

float string_to_float_validator( string s , string err ) {

    float temp ; 
    try{
        temp = stof(s) ; 
    }catch(...){
        throw err ; 
    }
    return temp ; 
}

vector<vector<float>> read( string filename ){

    fstream myFile ; 
    int rows , columns ;
    vector<vector<float>> ans ; // will store the matrix to be returned 

    myFile.open( filename, ios::in) ; // opens the input file in read mode 

    if(myFile.is_open()){

        string line ; 
        int linenumber = 0 ; 

        while(getline( myFile , line )){
            // cout << line << "\n" ; 
            stringstream buffer( line) ; 
            string token ; 
            vector<string> tokens ; // all tokens of the current line will be stored here 
            while(getline( buffer ,token , ' ')){ // string tokenizer which splits the line (stored in a buffer ) about the empty space
                tokens.push_back( token ) ;  
            }
            // cout << tokens.size() << "\n" ; 
            // each line should have a unique token
            if(tokens.size()!=1){
                throw ("ERROR on linenumber " + to_string(linenumber+1) + " of file " + filename + " one token expected, " + to_string(tokens.size()) +" found") ; 
            }
            if( linenumber == 0 ){
                // number of columns on the first line
                tokens[0].pop_back() ; // removes carriage return 
                columns = string_to_int_validator(tokens[0] , ("Error on linenumber " +  to_string(linenumber+1) + " of " +  filename + ", Number of columns should be a positive integer") ) ;
                // columns = stoi(tokens[0]) ;  
                
            }else if( linenumber == 1){
                // number of rows on the second line
                tokens[0].pop_back() ; // removes carriage return 
                rows = string_to_int_validator(tokens[0] , ("Error on linenumber " +  to_string(linenumber+1) + " of " +  filename + ", Number of rows should be a positive integer")) ;
                ans.resize( rows , vector<float>(columns , 0.0)) ; 
            }else{
                // float inputFloat = stof(tokens[0]) ;
                float inputFloat = string_to_float_validator(tokens[0] ,"Error on linenumber " +  to_string(linenumber+1) + " of " +  filename + ", matrix elements should be  32 bit floats") ; 
                // finds the correct index of the element in the current line according to rows major order
                ans[(linenumber-2)%rows][(linenumber-2)/rows] = inputFloat ; 
            }
            linenumber ++ ;  
        }
        myFile.close() ; 
    }else{
        throw ( filename + "  does not exists ") ; // throws error if file is not found 
    }
     
    return ans ; 

}


void write( vector<vector<float>>& mat , string filename ) {

    fstream myFile ; 
    int rows = mat.size()  , columns = mat[0].size() ; 
    myFile.open( filename , ios::out) ; 
    if(myFile.is_open()){
        myFile << columns << "\n" ;  // number of columns 
        myFile << rows << "\n" ;  // number of rows
        for( int col = 0 ; col  < columns ; col ++  ){
            for( int row = 0 ; row < rows ; row ++ ){
                myFile << mat[row][col] << "\n" ; 
            }
        }
        myFile.close() ; 
    }

}