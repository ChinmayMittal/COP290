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

    int temp ; 
    try{
        temp = stoi(s) ; 
    }catch(...){
        throw err ; 
    }
    if(temp < 1 ) throw err  ; 
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