# dll介绍

lib中已经介绍

## 代码示例

### 环境

windows + MinGW

### 编译

文件目录

-src
---MyMath.cpp
---test.cpp

-include
---MyMath.h

-build
---MyMath.o

-bin
---MyMath.dll
---test.exe

```shell
g++ -std=c++11 -Iinclude -c -o build/MyMath.o src/MyMath.cpp
g++ -shared -Wall -o bin/MyMath.dll build/MyMath.o
g++ -std=c++11 -Iinclude -Lbin -o test src/test.cpp -lMyMath
```

-shared 参数生成动态链接库

make 编译
make clear 清理

## 加载方式

### 静态加载

上面示例(-lMyMath)就是采用静态加载动态库的方法，意味着当程序启动时加载动态库，生存周期等于进程生存周期

### 动态加载

顾名思义，动态加载是指在程序执行中调用指定的库函数，没有执行到时不会调用。注意与静态加载的区别（程序启动时加载还是执行时加载）

关于动态载入在windows中如何操作不再说明，毕竟vs解决一切
