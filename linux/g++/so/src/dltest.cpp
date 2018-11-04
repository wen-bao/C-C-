#include <dlfcn.h>
#include "MyMath.h"
#include <iostream>

typedef int (*New)(MyMath *& obj);
typedef int (*Delete)(MyMath *& obj);

int main() {
    void *mymath = dlopen("../lib/libMyMath.so", RTLD_LAZY);

    if(!mymath) {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
        return 0;
    } else {
        std::cout << "load library successful" << std::endl;
    }

    New func;
    func = (New)dlsym(mymath, "createObj");

    MyMath *mm;

    int ret = (*func)(mm); 

    if(ret) {
        std::cout << "create obj failed: " <<dlerror() << std::endl;
        return 0;
    } else {
        std::cout << "create obj successful" << std::endl;
    }

    std::vector<int> v{1, 2, 3};

    int sum = mm->add(v);
    std::cout << sum << std::endl;

    Delete del;
    del = (Delete)dlsym(mymath, "deleteObj");
    int sta = (*del)(mm);

    if(sta) {
        std::cout << "delete obj failed: " << dlerror() << std::endl;
        return 0;
    } else {
        std::cout << "delete obj successful" << std::endl;
    }

    return 0;
}
