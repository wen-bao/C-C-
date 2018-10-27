# lib介绍

windows中称为静态链接库，将代码模块编译成库方便程序调用。与动态链接库的区别是静态库会将整个库放到程序里面，而动态链接库不会，随着程序的需要动态调用。

直白一点就是说调用完静态库之后静态库失去价值，甚至删除都不会影响程序的运行。相反调用动态库只是将动态库的链接放在程序里面，调用时再去具体地方找。

## 代码示例

### 环境

windows + MinGW

### 编译

```shell
g++ -c MyMath.cpp
ar cqs MyMath.lib MyMath.o
g++ -o test test.cpp -L"." -lMyMath
```

c   参数生成obj文件
ar  命令生成静态链接库
L   参数指定库的路径
l   参数指定调用具体库文件

make 编译
make clear 清理