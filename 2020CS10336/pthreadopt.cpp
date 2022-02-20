#include<vector>
#include<pthread.h>
#include<iostream>
#include<cmath>
#include<utility>
#include"timing.h"

using namespace std ; 
vector<vector<float>> a ,b , c ; 
// main file for pthread implementation 
void* rowMul( void* args ) {

    // multiplies certain number of rows of the first matrix with the second matrix and updates the global matrix

    int thread_id = *(int*)args ; 
 
    int m = a.size() , n = a[0].size() , k = b[0].size() ; 
    
    // each thread handles rows differing by multiples of 8, with the starting row decided by the thread_id
   for( int threadRow = thread_id ; threadRow < m ; threadRow += 8 ){
        for( int ansCol = 0 ; ansCol < k ; ansCol ++ ){
            for( int i = 0 ; i < n ;i++ ){
                c[threadRow][ansCol] += (a[threadRow][i]*b[i][ansCol]) ; 
            }
        }
   }


    return NULL ; 
    
}

pair<vector<vector<float>> , double > pthreadOpt(vector<vector<float>>&mat, vector<vector<float>>&weight, vector<vector<float>>&bias ){
    /*
        Returns the output matrix and the time taken in seconds as a double in a pair 
        computes mat X weights  + bias 
    */
    // initialize global matrices so that all threads can access them
    a = vector<vector<float>>(mat) ; 
    b =   vector<vector<float>>(weight) ;
    c =  vector<vector<float>>(bias)  ;  

    // we don't create more than 8 threads
    int thread_count = min(8,(int)mat.size()) ; // for A*B we split the computation by rows of A , each being multiplied by B
    pthread_t threads[thread_count] ;

    auto thread_t1 = get_time() ; 
    int thread_id = 0 ; // used to assign rows to each thread
    for( int i = 0 ; i  < thread_count ; i ++ ){
        int* p = new int ; 
        *p = thread_id ++ ; 
        pthread_create(&threads[i], NULL , rowMul , (void*)p ) ; 
    } 

    // waiting for all threads to finish computation 
    for (int i = 0; i < thread_count ; i++)
        pthread_join(threads[i], NULL); 
    auto thread_t2 = get_time() ; 

    printTimeDuration("PTHREAD: " , thread_t1 , thread_t2 ) ; 
    return pair<vector<vector<float>> , double> ( c , getTimeDuration(thread_t1 , thread_t2))  ; 
}


