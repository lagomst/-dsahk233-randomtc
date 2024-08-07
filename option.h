#define DEFAULT_OPTION 0 // use configuration in default_option.h
#if DEFAULT_OPTION == 1
    #include "default_option.h"
#else

/*
    Determine what local variable space will be used
    0: Not using any store or load ins
    1: Use local array
    2: Use local AVL tree
*/
#define USE_SPACE 2 

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
#define STACK_MAX 5  // maximum num of elements in stack
#define ARR_MAX 10 // maximum num of elements in array
#define LINE 100 // num of lines per file
#define NUM_OF_FILE 3 // num of file generated

#define AVL_MAX 10
#define NAME_LEN_MIN 1
#define NAME_LEN_MAX 3

// Weight of instructions (WoI) (beta)
#define RI_REQTWOINT 4 //  WoI popping two ints and pushing an int
#define RI_REQONEINT 1 // WoI popping one int and pushing an int
#define RI_REQONEFL 1 // WoI popping one float and pushing an int
#define RF_REQTWOFL 2 // WoI popping two floats and pushing a float
#define RF_REQONEFL 1 // WoI popping one float and pushing a float
#define RF_REQONEINT 1 // WoI popping one int and returning one float
#define BOOL_FLOAT 0 // WoI comparision float type
#define BOOL_INT 1 // WoI comparision int type
#define RI_NOREQ 3 // WoI pushing an int
#define RF_NOREQ 2 // WoI pushing a float
#define VIEW_TOP 0 // WoI showing top of the stack
#if USE_SPACE >= 1
    #define STORE_INT 2 // WoI istore
    #define LOAD_INT 1 // WoI iload
    #define STORE_FLOAT 2 // WoI fstore
    #define LOAD_FLOAT 1 // WoI fload
    #define VIEW_VAL 1 // WoI val
    #define PAR_VAL 1 //WoI par
#endif
#endif