#include "RandomTest.h"

size_t RandomTest::getRandomCodeSelected()
{
    std::vector<size_t> numpool = getOperationPool();
    std::vector<size_t> a = getLoadStorePool();
    numpool.insert(numpool.end(), a.begin(), a.end());
    
    // Get a random number from pool and return its value
    std::uniform_int_distribution<int> dist(0, int(numpool.size() - 1));
    return numpool[(size_t)dist(this->gen)];
}

std::vector<size_t> RandomTest::getOperationPool()
{
    std::vector<size_t> numpool;
    if(!myst.isEmpty())
    { // Stack is not empty
        addInsToPool(&numpool, 30, VIEW_TOP);
        if(myst.top() == 0)
        {// Top element is int
            addInsToPool(&numpool, 9, RI_REQONEINT); // ineg
            addInsToPool(&numpool, 28, RF_REQONEINT); // i2f
            addInsToPool(&numpool, 21, BOOL_INT); // ibnot
        }
        if(myst.top() == 1)
        {// Top element is float
            addInsToPool(&numpool, 10, RF_REQONEFL); // fneg
            addInsToPool(&numpool, 29, RI_REQONEFL); // f2i
        }
    }
    if(myst.getLen() > 1)
    {// More than one operand in stack
        // Add ins requiring two floats and returning float
        addInsToPool(&numpool, 1, RF_REQTWOFL); // fadd
        addInsToPool(&numpool, 3, RF_REQTWOFL); // fsub
        addInsToPool(&numpool, 5, RF_REQTWOFL); // fmul
        addInsToPool(&numpool, 7, RF_REQTWOFL); // fdiv
        
        // Add boolean operation requiring two floats
        addInsToPool(&numpool, 14, BOOL_FLOAT); 
        addInsToPool(&numpool, 16, BOOL_FLOAT);
        addInsToPool(&numpool, 18, BOOL_FLOAT);
        addInsToPool(&numpool, 20, BOOL_FLOAT);

        if(myst.isTopTwoInt())
        {
            // Add ins requring two ints and returning int
            addInsToPool(&numpool, 0, RI_REQTWOINT);
            addInsToPool(&numpool, 2, RI_REQTWOINT);
            addInsToPool(&numpool, 4, RI_REQTWOINT);
            addInsToPool(&numpool, 6, RI_REQTWOINT);
            addInsToPool(&numpool, 8, RI_REQTWOINT);

            // Add boolean operation requiring two ints
            addInsToPool(&numpool, 11, BOOL_INT);
            addInsToPool(&numpool, 12, BOOL_INT);
            addInsToPool(&numpool, 13, BOOL_INT);
            addInsToPool(&numpool, 15, BOOL_INT);
            addInsToPool(&numpool, 17, BOOL_INT);
            addInsToPool(&numpool, 19, BOOL_INT);
        }
    }
    if(!myst.isFull())
    {
        addInsToPool(&numpool, 22, RI_NOREQ);
        addInsToPool(&numpool, 23, RF_NOREQ);
    }
    return numpool;
}

std::vector<size_t> RandomTest::getLoadStorePool()
{
#if USE_SPACE == 1
    std::vector<size_t> numpool;
    if (ma.len != 0)
    { // Array is indexable
        for (int i = 0; i < VIEW_VAL; i++)
        { // val
            numpool.push_back(31);
        }
    }
    if (ma.len < ma.arr_max && myst.getLen() > 0)
    { // Array is storable and stack is not empty
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
    }
    if (!myst.isFull())
    { // Stack is not full yet
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
    }
    return numpool;
#endif
#if USE_SPACE == 2
    std::vector<size_t> numpool;
    if(!mavl.isEmpty())
    {
        // Add load, val ins
        addInsToPool(&numpool, 31, VIEW_VAL); // val
        addInsToPool(&numpool, 32, PAR_VAL); // par
    }
    if(!myst.isFull())
    {
        if(mavl.getRandomIntVar() != "") addInsToPool(&numpool, 24, LOAD_INT); // istore
        if(mavl.getRandomFloatVar() != "") addInsToPool(&numpool, 25, LOAD_FLOAT); // fstore
    }
    if(!myst.isEmpty())
    {
        if(myst.top() == 0) addInsToPool(&numpool, 26, STORE_INT);
        if(myst.top() == 1) addInsToPool(&numpool, 27, STORE_FLOAT);
    }
    return numpool;
#endif
    return {};
}

void RandomTest::addInsToPool(std::vector<size_t> *pool, size_t ins, size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        (*pool).push_back(ins);
    }
    return;
}

std::string RandomTest::updateAndGetIns(size_t opCode)
{
    // List of instructions
    std::string instruction[] = {"iadd", "fadd", "isub", "fsub",
                                 "imul", "fmul", "idiv", "fdiv",
                                 "irem", "ineg", "fneg", "iand",
                                 "ior", "ieq", "feq", "ineq",
                                 "fneq", "ilt", "flt", "igt",
                                 "fgt", "ibnot", "iconst", "fconst",
                                 "iload", "fload", "istore", "fstore",
                                 "i2f", "f2i", "top", "val",
                                 "par"};
    std::string ans = instruction[opCode];
    int rand_i;
    float rand_f;
#if CUSTOM_NUM == 1
    // Custom distribution range
    std::uniform_int_distribution<int> dist_i(INT_LB, INT_HB);
    std::uniform_int_distribution<int> dist_f(FLOAT_LB, FLOAT_HB);
    rand_i = dist_i(this->gen);
    rand_f = (float)dist_f(this->gen) / FLOAT_DECIMAL;
#else
    // Default distribution range
    std::uniform_int_distribution<size_t> dist(0, 10000);
    std::uniform_int_distribution<size_t> sign(0, 1);
    rand_i = (int)dist(this->gen);
    rand_i = (sign(this->gen)) ? rand_i : -rand_i;
    rand_f = (float)dist(this->gen) / 1000;
    rand_f = (sign(this->gen)) ? rand_f : -rand_f;
#endif
    switch(opCode)
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

        ans += ' ' + std::to_string(rand_i);
        break;
    }
    case 23: // fconst
    {
        myst.push(1);

        ans += ' ' + std::to_string(rand_f);
        break;
    }
#if USE_SPACE == 1
    case 24: // iload
    {
        // Update stack
        myst.push(0);
        // Update string
        int idx = this->ma.getRandomIntIdx();
        if(idx < 0) throw;
        ans += ' ' + std::to_string(idx * 2);
        break;
    }
    case 25: // fload
    {
        myst.push(1);

        int idx = this->ma.getRandomFloatIdx();
        if (idx < 0) throw;
        ans += ' ' + std::to_string(idx * 2);
        break;
    }
    case 26: // istore
    {
        myst.pop();
        ma.addNewVar(0);

        ans += ' ' + std::to_string((ma.len - 1) * 2);
        break;
    }
    case 27: // fstore
    {
        myst.pop();
        ma.addNewVar(1);

        ans += ' ' + std::to_string((ma.len - 1) * 2);
        break;
    }
    case 31: // val
    {
        int idx = this->ma.getRandomIdx();
        if(idx < 0) throw;
        ans += ' ' + std::to_string(idx * 2);
        break;
    }
#endif
#if USE_SPACE == 2
    case 24: // iload
    {
        // Update stack
        myst.push(0);
        // Update string
        std::string name = this->mavl.getRandomIntVar();
        if(name == "") throw;
        ans += ' ' + name;
        break;
    }
    case 25: // fload
    {
        myst.push(1);

        std::string name = this->mavl.getRandomFloatVar();
        if(name == "") throw;
        ans += ' ' + name;
        break;
    }
    case 26: // istore
    {
        myst.pop();
        std::string name = (mavl.isFull()) ? mavl.getRandomIntVar() : mavl.createRandomName();
        mavl.pushVar(name, 0);

        ans += ' ' + name;
        break;
    }
    case 27: // fstore
    {
        myst.pop();
        std::string rand_name = (mavl.isFull()) ? mavl.getRandomFloatVar() : mavl.createRandomName();
        mavl.pushVar(rand_name, 1);

        ans += ' ' + rand_name;
        break;
    }
    case 31: // val
    case 32: // par
    {
        std::string rand_name = mavl.getRandomVar();
        if(rand_name == "") throw;
        ans += ' ' + rand_name;
        break;
    }
#endif
    default:
    {
        break;
    }
    }
    return ans;
}

std::string RandomTest::getRandomTC(size_t line)
{
    std::string ans;
    for (size_t i = 0; i < line; i++)
    {
        size_t opCode = getRandomCodeSelected();
        ans += updateAndGetIns(opCode) + '\n';
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

bool RandomTest::MyStack::isTopTwoInt()
{
    if (len < 2) return false;
    return (stack[len - 1] == 0 && stack[len - 2] == 0);
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

std::string RandomTest::MyAVL::createRandomName()
{
    //Create a uniform distribution
    std::uniform_int_distribution<size_t> dist_len(this->len_min, this->len_max);
    std::uniform_int_distribution<size_t> dist_char(0, 51);

    // Get a random len
    size_t len = dist_len(this->rt->gen); 
    std::string name;
    for(size_t i = 0; i < len; i++)
    {
        // Get a random char
        name += getAlphabetChar(dist_char(this->rt->gen));
    }
    return name;
}

void RandomTest::MyAVL::pushVar(std::string name, int type)
{
    if(mp.count(name) == 0 && isFull()) return;
    mp[name] = type;
}


int RandomTest::MyAVL::getVarType(std::string name)
{
    if(!existName(name)) return -1;
    return mp[name];
}

std::string RandomTest::MyAVL::getRandomIntVar()
{
    if(isEmpty()) return "";
    std::vector<std::string> namepool;
    for(auto iter = mp.begin(); iter != mp.end(); iter++)
    {
        if (iter->second == 0) namepool.push_back(iter->first);
    }
    if (namepool.empty()) return "";
    std::uniform_int_distribution<size_t> dist(0, namepool.size() - 1);
    return namepool[dist(this->rt->gen)];
}

std::string RandomTest::MyAVL::getRandomFloatVar()
{ 
    if(isEmpty()) 
        return "";
    std::vector<std::string> namepool;
    for(auto iter = mp.begin(); iter != mp.end(); iter++)
    {
        if (iter->second == 1) namepool.push_back(iter->first);
    }
    if (namepool.empty()) return "";
    std::uniform_int_distribution<size_t> dist(0, namepool.size() - 1);
    return namepool[dist(this->rt->gen)];       
}

std::string RandomTest::MyAVL::getRandomVar()
{
    if(isEmpty()) 
        return "";
    auto iter = mp.begin();
    std::uniform_int_distribution<size_t> offset(0, mp.size() - 1);
    std::advance(iter, offset(this->rt->gen));
    return iter->first;
}

char RandomTest::MyAVL::getAlphabetChar(size_t offset)
{
    if(offset >= 52) offset %= 52;
    if(offset >= 26)
    {
        return char( (size_t)'A' + (offset - 26));
    }
    return char( (size_t)'a' + offset);
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