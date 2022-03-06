// data and function definitions for the library 
typedef struct
{
    int label;
    float prob;
} pred_t;

pred_t* libaudioAPI(const char *audiofeatures, pred_t *pred);
