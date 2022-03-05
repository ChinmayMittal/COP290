typedef struct
{
    int label;
    float prob;
} pred_t;

void libaudioAPI(const char *audiofeatures, pred_t *pred);