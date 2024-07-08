#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <chrono>

#include "option.h"

class RandomTest{
    std::mt19937 gen;

    class MyStack{
        std::vector<int> stack;    // Stack represented by array, num of elements kept track by len
    public:
        size_t len;     // Number of element in stack
        size_t max;
        MyStack(size_t m): len(0), max(m){
            for(size_t i=0; i < m; i++)
                stack.push_back(-1);
        }

        int push(int);
        int pop();

        int top();

        int top2(int *first, int *second);

        bool isEmpty(){return len==0;};
        bool isFull(){return len==max;};

        // If stack is full when add an element
        bool isFullWhenAdd(){return len+2 >= max;};

        // If stack will be empty during popping two elements
        bool isEmptyWhilePopTwice(){return len-2 == 0;};
    };

    class MyArray{
        RandomTest * rt;
    public:
        std::vector<int> arr;
        const size_t arr_max;
        size_t len;

        MyArray(RandomTest * ptr, size_t max): rt(ptr), arr_max(max), len(0)
        {
            for(size_t i=0; i < max; i++){
                arr.push_back(-1);
            }
        }
        int getRandomIntIdx();
        int getRandomFloatIdx();
        int getRandomIdx();
        int addNewVar(int);
    };

    MyStack ms;
    MyArray ma;

    //Get a random instruction code based on current stack and array
    size_t getRandomCodeSelected();

    //Get instruction string
    std::string getIns(size_t ins_code);

    //Update stack and array according to an instruction code
    void updateCode(size_t ins_code);
public:
    RandomTest(size_t smax, size_t vmax): ms(smax), ma(this, vmax){
        long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
        gen = std::mt19937(seed);
    }


    //Generate a selected-randomized test case
    std::string getRandomTC(size_t);

    void printFile(std::string, size_t line);
};

int gimp(int val, const int lower, const int upper);