#define USE_LOCALARR 1 //allow using array ins (istore, iload...)

#define CUSTOM_NUM 1 //generate a custom range of number
#if CUSTOM_NUM == 1
    #define INT_LB -10000 //integer lower bound
    #define INT_HB 10000 //integer upper bound
    #define FLOAT_LB -10000 //float lower digits bound
    #define FLOAT_HB 10000 //float upper digits bound
    #define FLOAT_DECIMAL 1000 //number of digits behind dot
#endif

//Constant
#define STACK_MAX 12
#define ARR_MAX 12
#define LINE 30
#define NUM_OF_FILE 5