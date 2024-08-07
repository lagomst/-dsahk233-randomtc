/*
    Determine what local variable space will be used
    0: Not using any store or load ins
    1: Use local array
    2: Use local AVL tree
*/
#define USE_SPACE 1
#define CUSTOM_NUM 0 //allow generating a custom range of number
#if CUSTOM_NUM == 1
    #define INT_LB -10000 //integer lower bound
    #define INT_HB 10000 //integer upper bound
    #define FLOAT_LB -10000 //float lower digits bound
    #define FLOAT_HB 10000 //float upper digits bound
    #define FLOAT_DECIMAL 1000 //number of digits behind dot
#endif

#define WINDOW_OS 0 // use window-related function

//Constant
#define STACK_MAX 6  // maximum num of elements in stack
#define ARR_MAX 3 // maximum num of elements in array
#define LINE 30 // num of lines per file
#define NUM_OF_FILE 5 // num of file generated

#define AVL_MAX 7
#define NAME_LEN_MIN 1
#define NAME_LEN_MAX 3

// Weight of instructions (WoI) (beta)
#define RI_REQTWOINT 3 //  WoI popping two ints and pushing an int
#define RI_REQONEINT 2 // WoI popping one int and pushing an int
#define RI_REQONEFL 2 // WoI popping one float and pushing an int
#define RF_REQTWOFL 1 // WoI popping two floats and pushing a float
#define RF_REQONEFL 1 // WoI popping one float and pushing a float
#define RF_REQONEINT 1 // WoI popping one int and returning one float
#define BOOL_FLOAT 1 // WoI comparision float type
#define BOOL_INT 1 // WoI comparision int type
#define RI_NOREQ 2 // WoI pushing an int
#define RF_NOREQ 1 // WoI pushing a float
#define VIEW_TOP 2 // WoI showing top of the stack
#if USE_SPACE >= 1
    #define STORE_INT 1 // WoI istore
    #define LOAD_INT 1 // WoI iload
    #define STORE_FLOAT 1 // WoI fstore
    #define LOAD_FLOAT 1 // WoI fload
    #define VIEW_VAL 1 // WoI val
    #define PAR_VAL 1 //WoI par
#endif