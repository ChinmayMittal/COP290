#include<bits/stdc++.h>
#include<vector>
#include<string>
#include <fstream>

using namespace std ; 

vector<vector<float>> read( string filename ){

    fstream myFile ; 
    int rows , columns ;
    vector<vector<float>> ans ; 
    myFile.open( filename, ios::in) ; 
    if(myFile.is_open()){
        string line ; 
        int linenumber = 0 ; 
        while(getline( myFile , line )){
            // cout << line << "\n" ; 
            stringstream buffer( line) ; 
            string token ; 
            vector<string> tokens ; 
            while(getline( buffer ,token , ' ')){
                tokens.push_back( token ) ;  
            }
            if( linenumber == 0 ){
                columns = stoi( tokens[0]) ; 
            }else if( linenumber == 1){
                rows = stoi( tokens[0]) ;
                ans.resize( rows , vector<float>(columns , 0.0)) ; 
            }else{
                float inputFloat = stof(tokens[0]) ;
                ans[(linenumber-2)%rows][(linenumber-2)/rows] = inputFloat ; 
            }
            linenumber ++ ;  
        }
        myFile.close() ; 
    }
     
    return ans ; 

}