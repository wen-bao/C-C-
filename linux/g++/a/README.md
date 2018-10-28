# .a介绍

.a文件为linux中的静态链接库，具体概念在windows中已经讲明

## 代码示例

### 环境

ubuntu + g++

### 编译

```shell
g++ -std=c++11 -Iinclude -c -o build/MyMath.o src/MyMath.cpp
ar crv -o lib/libMyMath.a build/MyMath.o
g++ -std=c++11 -Iinclude -Llib -o bin/test src/test.cpp -lMyMath
```

ar 生成静态链接库
