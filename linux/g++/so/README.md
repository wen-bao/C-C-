# so介绍

.so在linux中为动态链接库文件后缀名


## 代码示例

### 环境

ubuntu + g++

### 编译

```shell
g++ -fPIC -std=c++11 -Iinclude -c -o build/MyMath.o src/MyMath.cpp
g++ -fPIC -shared -o /usr/lib/libMyMath.so build/MyMath.o
g++ -fPIC -std=c++11 -Iinclude -o bin/test src/test.cpp -lMyMath
```

-shared 编译为动态链接库

## 载入方式

### 静态载入

上面演示的就是静态载入的动态库的方式(-lMyMath)，最明显的是程序运行时立即加载动态库

需要注意的是静态载入动态库时默认只会到指定的文件夹下面找，最好的解决方法是指定寻找路径（-Wl,-rpath=dir:dir2:dir3）

### 动态载入

动态载入就是说在程序运行到需要时载入,主要通过dl相关库函数实现

```c++
#include <dlfcn.h>
void *dlopen(const char *pathname, int mode);

//mode
//RTLD_LAZY
//RTLD_NOW
//RTLD_GLOBAL
//RTLD_LOCAL

void *dlsym(void *, const char *);
int dlclose(void *);
char *dlerror(void);
```
