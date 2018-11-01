# so介绍

.so在linux中为动态链接库文件后缀名

与windows不同
windows程序执行时会在当前文件夹中尝试寻找动态库而linux只会去特定的文件夹中去找，所以windows加分

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



