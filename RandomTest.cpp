#include "RandomTest.h"

size_t RandomTest::getRandomCodeSelected()
{
    std::vector<size_t> numpool;
#if INS_WEIGHT == 1

    if (myst.getLen() >= 1)
    { // Stack has at least one element
        if (myst.top() == 0)
        { // top element is an int
            for (int i = 0; i < RI_REQONEINT; i++)
            { 
                numpool.push_back(9);  // ineg
            }
            for (int i = 0; i < RF_REQONEINT; i++)
            { 
                numpool.push_back(28); // i2f
            }
            for (int i = 0; i < BOOL_INT; i++)
            {
                numpool.push_back(21); // ibnot
            }
        }
        if (myst.top() == 1)
        { // top element is a float
            for (int i = 0; i < RF_REQONEFL; i++)
            { // add ins requiring one float and returning float
                numpool.push_back(10);
            }
            for (int i = 0; i < RI_REQONEFL; i++)
            { // add ins requiring one float and returning int
                numpool.push_back(29); // f2i
            }
        }
        for (int i = 0; i < VIEW_TOP; i++)
        { // top
            numpool.push_back(30);
        }
    }
    if (myst.getLen() >= 2)
    { // Stack has at least 2 elements
        for (int i = 0; i < RF_REQTWOFL; i++)
        { // add ins requiring two floats and returning float
            std::vector<size_t> pool = {1, 3, 5, 7};
            numpool.insert(numpool.end(), pool.begin(), pool.end());
        }
        for (int i = 0; i < BOOL_FLOAT; i++)
        { // add ins requiring two floats and returning int
            std::vector<size_t> pool = {14, 16, 18, 20};
            numpool.insert(numpool.end(), pool.begin(), pool.end());
        }
        int a = -1, b = -1;
        myst.top2(&a, &b);
        if (a == 0 && b == 0)
        { // add ins requiring two ints and returning int
            for (int i = 0; i < RI_REQTWOINT; i++)
            {
                std::vector<size_t> pool = {0, 2, 4, 6, 8};
                numpool.insert(numpool.end(), pool.begin(), pool.end());
            }
            for (size_t i = 0; i < BOOL_INT; i++)
            {
                /* code */
                std::vector<size_t> pool = {11, 12, 13, 15, 17, 19};
                numpool.insert(numpool.end(), pool.begin(), pool.end());
            }
            
        }
    }
    if (myst.getLen() + 1 < myst.getMax())
    { // Stack is not full yet
        for (int i = 0; i < RI_NOREQ; i++)
        { // iconst
            numpool.push_back(22);
        }
        for (int i = 0; i < RF_NOREQ; i++)
        { // iconst
            numpool.push_back(23);
        }
    }
#if USE_LOCALARR == 1

    if (myst.getLen() >= 1)
    {
        if (ma.getRandomIntIdx() >= 0)
        { // there exists an index storing an integer
            for (int i = 0; i < LOAD_INT; i++)
            { // iload
                numpool.push_back(24);
            }
        }
        if (ma.getRandomFloatIdx() >= 0)
        { // there exists an index storing a float
            for (int i = 0; i < LOAD_FLOAT; i++)
            { // fload
                numpool.push_back(25);
            }
        }
        if (myst.top() == 0)
        { // top element is int
            for (int i = 0; i < STORE_INT; i++)
            { // istore
                numpool.push_back(26);
            }
        }
        if (myst.top() == 1)
        { // top element is float
            for (int i = 0; i < STORE_FLOAT; i++)
            { // fstore
                numpool.push_back(27);
            }
        }
        for (int i = 0; i < VIEW_VAL; i++)
        { // val
            numpool.push_back(31);
        }
    }
#endif
#else
    std::vector<std::vector<size_t>> insReqTwo = {{0, 2, 4, 6, 8, 11, 12, 13, 15, 17, 19}, {1, 3, 5, 7, 14, 16, 18, 20}};
    if (myst.getLen() >= 1)
    { // Stack has at least one elements
        if (myst.top() == 1)
        { // add instruction requiring one float
            numpool.push_back(10);
            numpool.push_back(29);
        }
        if (myst.top() == 0)
        { // add instruction requiring one int
            numpool.push_back(9);
            numpool.push_back(21);
            numpool.push_back(28);
        }
        // top ins
        numpool.push_back(30);
#if USE_LOCALARR == 1
        if (ma.len < ma.arr_max)
        { // If array index are not out of bound yet
            if (myst.top() == 0)
            {
                // istore ins
                numpool.push_back(26);
            }
            if (myst.top() == 1)
            {
                // fstore ins
                numpool.push_back(27);
            }
        }
        if (ma.len > 0)
        {
            // val ins
            numpool.push_back(31);
        }
#endif
    }

    if (myst.getLen() >= 2)
    { // Stack has at least two elements
        // Add instruction requiring 2 floats
        numpool.insert(numpool.end(), insReqTwo[1].begin(), insReqTwo[1].end());
        int i = -1, j = -1;
        myst.top2(&i, &j);
        if (i == 0 && j == 0)
        { // 2 top elements are of int type
            // Add instruction requiring 2 ints
            numpool.insert(numpool.end(), insReqTwo[0].begin(), insReqTwo[0].end());
        }
    }
    if (myst.getLen() + 1 < myst.getMax())
    { // Stack isnt full yet
#if USE_LOCALARR == 1
        if (ma.getRandomIntIdx() >= 0)
        {                          // Exist an integer element
            numpool.push_back(24); // iload
        }
        if (ma.getRandomFloatIdx() >= 0)
        {                          // Exist a float element
            numpool.push_back(25); // fload
        }
#endif
        // iconst, fconst
        numpool.push_back(22);
        numpool.push_back(23);
    }
#endif
    // Get a random number from pool and return its value
    std::uniform_int_distribution<int> dist(0, int(numpool.size() - 1));
    return numpool[(size_t)dist(this->gen)];
}

std::string RandomTest::getIns(size_t opCode)
{
    // List of instructions
    std::string instruction[32] = {"iadd", "fadd", "isub", "fsub",
                                   "imul", "fmul", "idiv", "fdiv",
                                   "irem", "ineg", "fneg", "iand",
                                   "ior", "ieq", "feq", "ineq",
                                   "fneq", "ilt", "flt", "igt",
                                   "fgt", "ibnot", "iconst", "fconst",
                                   "iload", "fload", "istore", "fstore",
                                   "i2f", "f2i", "top", "val"};
    std::string ans = instruction[opCode];
#if CUSTOM_NUM == 1
    // Custom distribution range
    std::uniform_int_distribution<int> dist_i(INT_LB, INT_HB);
    std::uniform_int_distribution<int> dist_f(FLOAT_LB, FLOAT_HB);
#else
    // Default distribution range
    std::uniform_int_distribution<size_t> dist(0, 10000);
    std::uniform_int_distribution<size_t> sign(0, 1);
#endif
    switch (opCode)
    {
    case 22:
    { // iconst
#if CUSTOM_NUM == 1
        int rand_i = dist_i(this->gen);
#else
        int rand_i = (int)dist(this->gen);
        rand_i = (sign(this->gen)) ? rand_i : -rand_i;
#endif
        ans += ' ' + std::to_string(rand_i);
        break;
    }
    case 23:
    { // fconst
#if CUSTOM_NUM == 1
        int rand_i = dist_f(this->gen);
        float rand_f = (float)rand_i / FLOAT_DECIMAL;
#else
        float rand_f = float(dist(this->gen)) / 1000;
        rand_f = (sign(this->gen)) ? rand_f : -rand_f;
#endif
        ans += ' ' + std::to_string(rand_f);
        break;
    }
#if USE_LOCALARR == 1
    case 24:
    { // iload
        int idx = ma.getRandomIntIdx();
        if (idx >= 0)
        {
            ans += ' ' + std::to_string(idx * 2);
        }
        else
        {
            // If no integer in array, use val instead
            return getIns(31);
        }
        break;
    }
    case 25:
    { // fload
        int idx = ma.getRandomFloatIdx();
        if (idx >= 0)
        {
            ans += ' ' + std::to_string(idx * 2);
        }
        else
        {
            // If no float in array, use val instead
            return getIns(31);
        }
        break;
    }
    case 26:
    case 27:
    { // istore, fstore
        ans += ' ' + std::to_string((ma.len - 1) * 2);
        break;
    }
    case 31:
    {
        int idx = ma.getRandomIdx();
        if (idx >= 0)
        {
            ans += ' ' + std::to_string(idx * 2);
        }
        else
        {
            // If no element in array, use top instead
            return getIns(30);
        }
    }
#endif
    default:
        break;
    }
    return ans;
}

void RandomTest::updateCode(size_t opCode)
{
    switch (opCode)
    {
    case 0:  // iadd
    case 2:  // isub
    case 4:  // imul
    case 6:  // idiv
    case 8:  // irem
    case 11: // iand
    case 12: // ior
    case 13: // ieq
    case 14: // feq
    case 15: // ineq
    case 16: // fneq
    case 17: // ilt
    case 18: // flt
    case 19: // igt
    case 20: // fgt
    {        // pop 2 num and add an int to stack
        myst.pop();
        myst.pop();
        myst.push(0);
        break;
    }
    case 1: // fadd
    case 3: // fsub
    case 5: // fmul
    case 7: // fdiv
    {       // pop 2 num and add a float to stack
        myst.pop();
        myst.pop();
        myst.push(1);
        break;
    }
    case 9:  // ineg
    case 21: // ibnot
    case 29: // f2i
    {        // pop 1 num and add an int to stack
        myst.pop();
        myst.push(0);
        break;
    }
    case 10: // fneg
    case 28: // i2f
    {        // pop 1 num and add a float to stack
        myst.pop();
        myst.push(1);
        break;
    }
    case 22: // iconst
    {
        myst.push(0);
        break;
    }
    case 23: // fconst
    {
        myst.push(1);
        break;
    }
#if USE_LOCALARR == 1
    case 24: // iload
    {
        myst.push(0);
        break;
    }
    case 25: // fload
    {
        myst.push(1);
        break;
    }
    case 26: // istore
    {
        myst.pop();
        ma.addNewVar(0);
        break;
    }
    case 27: // fstore
    {
        myst.pop();
        ma.addNewVar(1);
        break;
    }
#endif
    default:
    {
        break;
    }
    }
    return;
}

std::string RandomTest::getRandomTC(size_t line)
{
    std::string ans;
    for (size_t i = 0; i < line; i++)
    {
        size_t opCode = getRandomCodeSelected();
        updateCode(opCode);
        ans += getIns(opCode) + '\n';
    }
    return ans;
}

void RandomTest::printFile(std::string filename, size_t line)
{
    std::ofstream file(filename);
    std::string ans = getRandomTC(line);
    file << ans;
    file << "top";
    file.close();
}

int RandomTest::MyStack::push(int a)
{
    if (isFull())
    {
        return -1;
    }
    stack[len] = a;
    len++;
    return 0;
}

int RandomTest::MyStack::pop()
{
    if (isEmpty())
        return -1;
    int temp = stack[len - 1];
    len--;
    return temp;
}

int RandomTest::MyStack::top()
{
    if (isEmpty())
        return -1;
    return stack[len - 1];
}

int RandomTest::MyStack::top2(int *first, int *second)
{
    if (len < 2)
    {
        *first = *second = -1;
        return -1;
    }

    *first = stack[len - 1];
    *second = stack[len - 2];
    return 0;
}

int RandomTest::MyArray::getRandomIntIdx()
{
    // Create a pool of integer's index
    std::vector<size_t> pool;
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] == 0)
        {
            pool.push_back(i);
        }
    }
    if (pool.size() == 0)
    {
        return -1;
    }
    // Choose a random number in the pool,
    // by returning values from a random index of pool
    std::uniform_int_distribution<int> dist(0, int(pool.size() - 1));
    return (int)pool[(size_t)dist(rt->gen)];
}

int RandomTest::MyArray::getRandomFloatIdx()
{
    // Create a pool of integer's index
    std::vector<size_t> pool;
    for (size_t i = 0; i < len; i++)
    {
        if (arr[i] == 1)
        {
            pool.push_back(i);
        }
    }
    if (pool.size() == 0)
    {
        return -1;
    }
    // Choose a random number in the pool,
    // by returning values from a random index of pool
    std::uniform_int_distribution<int> dist(0, int(pool.size() - 1));
    return (int)pool[(size_t)dist(rt->gen)];
}

int RandomTest::MyArray::getRandomIdx()
{
    if (len == 0)
    {
        return -1;
    }
    int max = int(len - 1);
    std::uniform_int_distribution<int> dist(0, max);
    return dist(rt->gen);
}

int RandomTest::MyArray::addNewVar(int a)
{
    if (len >= arr_max)
    {
        return -1;
    }
    arr[len++] = a;
    return 0;
}

int gimp(int val, const int lower, const int upper)
{
    if (val < lower)
    {
        return lower;
    }
    if (val > upper)
    {
        return upper;
    }
    return val;
}