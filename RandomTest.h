#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include "option.h"

class RandomTest;

// std::string name_pool = {}

struct Node
{
    const std::string name;
    int type;
};

class RandomTest{
    std::mt19937 gen; // Merriam Twister RNG

    class MyStack{
        std::vector<int> stack;    // Stack represented by array, num of elements kept track by len
        size_t len;     // Number of element in stack
        const size_t max;
    public:
        
        MyStack(size_t m): len(0), max(m){
            for(size_t i=0; i < m; i++)
                stack.push_back(-1);
        }
        size_t getLen(){return this->len;}
        size_t getMax(){return this->max;}

        int push(int);
        int pop();

        // Get the top element in stack
        int top();

        //Change first and second value to the top 2 elements of stack
        int top2(int *first, int *second);

        bool isEmpty(){return len==0;};
        bool isFull(){return len==max;};

        // If stack is full when add an element
        bool isFullWhenAdd(){return len+2 >= max;};

        // If stack will be empty during popping two elements
        bool isEmptyWhilePopTwice(){return len-2 == 0;};

        bool isTopTwoInt();
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
        // Get a random index of an integer from array.
        // Return -1 if array has not stored an int.
        int getRandomIntIdx();

        // Get a random index of an float from array.
        // Return -1 if array has not stored a float.
        int getRandomFloatIdx();

        // Get a random index in array.
        // Return -1 if array has not stored any value.
        int getRandomIdx();

        // Store new value to array
        int addNewVar(int);
    };

    class MyAVL
    {
        RandomTest *rt;
        std::unordered_map<std::string, int> mp;
        const size_t smax;
        const size_t len_min;
        const size_t len_max;
    public:
        MyAVL(RandomTest *ptr): rt(ptr), mp({}), smax(AVL_MAX), len_min(NAME_LEN_MIN), len_max(NAME_LEN_MAX){}

        std::string createRandomName();
        char getAlphabetChar(size_t offset);
        void pushVar(std::string name, int type);

        std::string getRandomIntVar();
        std::string getRandomFloatVar();
        std::string getRandomVar();

        int getVarType(std::string name);

        bool isEmpty(){return mp.size() == 0;};
        bool isFull(){return mp.size() >= smax;}
        bool existName(std::string name){return mp.count(name) != 0;}
    };

    MyStack myst;
    MyArray ma;
    MyAVL mavl;
    //Get a random instruction code based on current stack and array
    size_t getRandomCodeSelected();

    std::string updateAndGetIns(size_t opCode);

    std::vector<size_t> getLoadStorePool();
    std::vector<size_t> getOperationPool();
    void addInsToPool (std::vector<size_t> *pool, size_t ins, size_t n);
public:
    RandomTest(size_t smax, size_t vmax): myst(smax), ma(this, vmax), mavl(this){
        //Get time-based seed and seed the generator
        long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
        gen = std::mt19937(seed);
    }

    //Generate a selected-randomized test case
    std::string getRandomTC(size_t);

    void printFile(std::string, size_t line);
};

int gimp(int val, const int lower, const int upper);