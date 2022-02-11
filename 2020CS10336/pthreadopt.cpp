#include<vector>
#include<pthread.h>
#include<iostream>
#include"timing.h"

using namespace std ; 
vector<vector<float>> a ,b , c ; 
int row = 0 ; 
void* rowMul( void* args ) {

    int threadRow = row++ ; 
    int m = a.size() , n = a[0].size() , k = b[0].size() ; 

   
    for( int ansCol = 0 ; ansCol < k ; ansCol ++ ){
        for( int i = 0 ; i < n ;i++ ){
            c[threadRow][ansCol] += (a[threadRow][i]*b[i][ansCol]) ; 
        }
    }

    return NULL ; 
    
}

vector<vector<float>> pthreadOpt(vector<vector<float>>&mat, vector<vector<float>>&weight, vector<vector<float>>&bias ){
    
    a = vector<vector<float>>(mat) ; 
    b =   vector<vector<float>>(weight) ;
    c =  vector<vector<float>>(bias)  ;  

    int thread_count = mat.size() ; // one for each row of the ans 
    pthread_t threads[thread_count] ;
    auto thread_t1 = get_time() ; 
    for( int i = 0 ; i  < thread_count ; i ++ ){
        pthread_create(&threads[i], NULL , rowMul , NULL ) ; 
    } 

    for (int i = 0; i < thread_count ; i++)
        pthread_join(threads[i], NULL); 
    auto thread_t2 = get_time() ; 
    printTimeDuration("PTHREAD: " , thread_t1 , thread_t2 ) ; 
    return c ; 
}


