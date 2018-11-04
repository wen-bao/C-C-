#ifndef _BASEMATH_H_
#define _BASEMATH_H_

#include <vector>

class BaseMath {
public:
    BaseMath(){}
    ~BaseMath(){}
    virtual int add(std::vector<int> v) = 0;
};

extern "C" int createObj(BaseMath *& obj);
extern "C" int deleteObj(BaseMath *& obj);

#endif // !_BASEMATH_H_