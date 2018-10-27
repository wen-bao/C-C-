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
g++ -Iinclude -c -o build/MyMath.o src/MyMath.cpp
g++ -shared -Wall -o bin/MyMath.dll build/MyMath.o
g++ -Iinclude -Lbin -o test src/test.cpp -lMyMath
```

-shared 参数生成动态链接库

make 编译
make clear 清理