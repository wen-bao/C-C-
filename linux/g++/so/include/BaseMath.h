#ifndef _BASEMATH_H_
#define _BASEMATH_H_

#include <vector>

class BaseMath {
public:
    BaseMath(){}
    ~BaseMath(){}
    virtual int add(std::vector<int> v) = 0;
};

extern "C" int createObj(BaseMath *& client);

#endif // !_BASEMATH_H_