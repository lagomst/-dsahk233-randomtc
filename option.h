#define USE_LOCALARR 1 //allow using array ins (istore, iload...)

#define CUSTOM_NUM 1 //allow generating a custom range of number
#if CUSTOM_NUM == 1
    #define INT_LB -10000 //integer lower bound
    #define INT_HB 10000 //integer upper bound
    #define FLOAT_LB -10000 //float lower digits bound
    #define FLOAT_HB 10000 //float upper digits bound
    #define FLOAT_DECIMAL 1000 //number of digits behind dot
#endif

#define WINDOW_OS 0 // use window-related function

//Constant
#define STACK_MAX 12 // maximum number in stack
#define ARR_MAX 12 // maximum number in array
#define LINE 30 // number of line per file
#define NUM_OF_FILE 5 // number of file generated