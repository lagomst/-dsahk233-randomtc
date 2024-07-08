#include "RandomTest.cpp"
#include <iostream>

int main()
{
    
    const size_t stack_max = STACK_MAX;
    const size_t arr_max = ARR_MAX;
    const size_t line = LINE;
    const std::string name = "rand_test";
    const std::string format = ".txt";
    for(int i = 0; i < NUM_OF_FILE; i++){
        std::string filename = name + std::to_string(i) + format;
        RandomTest rt(stack_max, arr_max);
        rt.printFile(filename, line);
    }
    return 0;
}