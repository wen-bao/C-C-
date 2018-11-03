#include <stdio.h>
#include <dlfcn.h>
#include "MyMath.h"
#include <iostream>

typedef int (*FunPtr)(MyMath *& client);

int main() {

    void *mymath = dlopen("../lib/MyMath.so", RTLD_LAZY);

    if(!mymath) {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
    }

    FunPtr func;
    func = (FunPtr)dlsym(mymath, "createObj");

    MyMath *mm;

    int ret = (*func)(mm); 

    std::vector<int> v{1, 2, 3};

    int sum = mm->add(v);
    printf("%d\n", sum);

    return 0;
}
