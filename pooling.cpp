#include<iostream>
#include<vector>

using namespace std ; 

float accumulator( vector<float>&arr , string typeOfpooling ) {

    float ans = 0 ; 

    if( typeOfpooling == "average" ){

        for( auto ele : arr ) {
            ans += ele ; 
        }

        ans = ans / arr.size() ; 

    }else if( typeOfpooling == "max"){

        ans = arr[0] ; 

        for( auto ele : arr  ) {
            ans = max( ans ,ele ) ; 
        } 

    }

    return ans ; 
}


vector<vector<float>> pooling( vector<vector<float>>&mat , int stride ,  string poolingType , int filterSize = 2 ) {

    int rows = mat.size() ; 
    int columns = mat[0].size() ; 
    int ansColumns = ( columns - filterSize ) / stride  + 1 , ansRows = ( rows - filterSize ) / stride + 1 ; 
    vector<vector<float>> ans( ansRows, vector<float>( ansColumns , 0.0f) ) ;

    for( int filterRowEdge = 0 ; filterRowEdge < rows-1 ; filterRowEdge += stride ){
        for( int filterColumnEdge = 0 ; filterColumnEdge < columns -1 ; filterColumnEdge += stride ) {

            vector<float>elementsInFilterShadow  ; 

            for( int rowStart = filterRowEdge ; rowStart < filterRowEdge + filterSize ; rowStart ++  ){
                for( int  colStart = filterColumnEdge ; colStart < filterColumnEdge  + filterSize; colStart ++ ) {
                    elementsInFilterShadow.push_back( mat[rowStart][colStart]) ; 
                }
            }

            float filterAns = accumulator( elementsInFilterShadow , poolingType ) ; 

            ans[filterRowEdge/stride][filterColumnEdge/stride] = filterAns ; 
        }
    }   

    return ans ; 

}