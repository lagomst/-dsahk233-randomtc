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
#define STACK_MAX 12 // maximum num of elements in stack
#define ARR_MAX 12 // maximum num of elements in array
#define LINE 30 // num of lines per file
#define NUM_OF_FILE 5 // num of file generated

// Weight of instructions (WoI) (not implemented yet)
#define INS_WEIGHT 0
#if INS_WEIGHT == 1
    #define RI_REQTWOINT 1 //  WoI popping two ints and pushing an int
    #define RI_REQONEINT 1 // WoI popping one int and pushing an int
    #define RF_REQTWOFL 1 // WoI popping two floats and pushing a float
    #define RF_REQONEFL 1 // WoI popping one float and pushing a float
    #define RT_REQTWOFL 1 // WoI popping two floats and pushing an int
    #define STORE_INT 1 // WoI istore
    #define LOAD_INT 1 // WoI iload
    #define STORE_FLOAT 1 // WoI fstore
    #define LOAD_FLOAT 1 // WoI fload
#endif