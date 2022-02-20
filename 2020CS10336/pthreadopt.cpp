#include<vector>
#include<pthread.h>
#include<iostream>
#include<cmath>
#include<utility>
#include"timing.h"

using namespace std ; 
vector<vector<float>> a ,b , c ; 
// int row = 0 ; 
void* rowMul( void* args ) {
    int thread_id = *(int*)args ; 
    // cout << thread_id << "\n" ; 
    // int threadRow = thread_id ; 
    int m = a.size() , n = a[0].size() , k = b[0].size() ; 

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
    
    a = vector<vector<float>>(mat) ; 
    b =   vector<vector<float>>(weight) ;
    c =  vector<vector<float>>(bias)  ;  

    int thread_count = min(8,(int)mat.size()) ; // one for each row of the ans 
    pthread_t threads[thread_count] ;
    auto thread_t1 = get_time() ; 
    int thread_id = 0 ; 
    for( int i = 0 ; i  < thread_count ; i ++ ){
        int* p = new int ; 
        *p = thread_id ++ ; 
        pthread_create(&threads[i], NULL , rowMul , (void*)p ) ; 
    } 

    for (int i = 0; i < thread_count ; i++)
        pthread_join(threads[i], NULL); 
    auto thread_t2 = get_time() ; 
    printTimeDuration("PTHREAD: " , thread_t1 , thread_t2 ) ; 
    return pair<vector<vector<float>> , double> ( c , getTimeDuration(thread_t1 , thread_t2))  ; 
}


