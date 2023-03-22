# understanding-cpp11
Notes on the book "深入理解C++11：C++11新特性解析与应用"

code resoure: https://www.hzcourse.com/web/refbook/detail/5075/208
GNU: gcc >= 4.3

## chap 1 新标准的诞生

### 新语言的设计目标：
- 比C语言更适合系统编程（兼容C）
- 支持**数据抽象**
- 支持**面向对象编程**
- 支持**泛型编程**

### C++11的整体设计目标：
- 使得C++成为更好的适用于**系统开发**及**库开发**的语言
- 使得C++成为更易于教学的语言（语法更加一致化和简单化）
- 保证语言的**稳定性**，以及和C++03及C语言的**兼容性**

### 相比C++98/03 增强：
- 通过内存模型、线程、原子操作支持**并行编程**
- 通过统一初始化表达式、auto、declytype、移动语义等来统一对**泛型编程**的支持
- 通过constexpr、POD（概念）等更好地支持**系统编程**
- 通过内联命名空间、继承构造函数和右值引用等，以更好地支持**库的构建**
  
### WG21设计理念
- 保持语言的**稳定性**和**兼容性**（Maintain stability and compatibility）
- 更倾向于**使用库**而不是扩展语言来实现特性（Prefer libraries to language extensions）
- 更倾向于**通用**的而不是特殊的手段来实现特性（Prefer generality to specailization）
- 专家新手一概支持（Support both experts and novices）
- 增强**类型的安全性**（Increase type safety）
- 增强代码执行性能和操作硬件的能力（Improve performance and ability to work directly with hardware）
- 开发能够改变人们思维方式的特性（Make only changes that change the way people think）
- 融入编程现实（Fit into the real world）

### C++11特性人群划分
- class writer
- library writer
- everyone
- everyone else

### C++11新特性划分表格
> 待补充

## chap 2 保证稳定性和兼容性

### 2.1 保持与C99的兼容性
c++03标准基于C++98，微小的修正。C++11将C99特性支持也纳入新标准：
#### 2.1.1 C99中的预定义宏
- 可以通过#ifdef/#endif对平台相关代码在适合于当前平台的代码上编译，完成对多平台的支持
```
#include <iostream>
using namespace std;

int main() {
    cout << "Standard Clib: " << __STDC_HOSTED__ << endl;   // Standard Clib: 1
    cout << "Standard C: " << __STDC__ << endl;             // Standard C: 1
    // cout << "C Stardard version: " << __STDC_VERSION__ << endl; //compile error: not declared in this scope
    cout << "ISO/IEC " << __STDC_ISO_10646__ << endl;       // ISO/IEC 200009 -> local ubuntu: 201706
}
```
#### 2.1.2 __fun__预定义标识符
- 返回函数的名字，方便轻量级代码调试
```
#include <string>
#include <iostream>
using namespace std;

const char* hello() { return __func__; }
const char* world() { return __func__; }

int main(){ 
    cout << hello() << ", " << world() << endl; // hello, world
}
```
- 类或结构体中使用__fun__
```
#include <iostream>
using namespace std;

struct TestStruct {
    TestStruct () : name(__func__) {};
    const char* func() {
        return __func__;
    }

    // void funcFail(string func_name = __func__); // E1036 保留的标识符 "__func__" 只能在函数内部使用
    const char *name;
};

int main() {
    TestStruct ts;
    cout << ts.name << endl;    // TestStruct
    cout << ts.func() << endl; // func
}
```
/*
从代码中可以看到，在结构体的构造函数中，初始化成员列表使用__func__预定义标识符是可行的，其效果跟在函数中使用一样。
不过将__fun__标识符作为函数参数的默认值是不允许的，如上例函数funcFail所示（无法编译通过）
这是由于在参数声明时，__func__还未被定义。
*/

#### 2.1.3 _Pragma操作符 [待补充]
- _Pragma #pragma once与 #ifndef的区别
  - 目标：避免同一个头文件被包含(include)引用，造成重复定义，报错
  - 区别：
    - #ifndef保证同一个文件不会被包含多次，也保证内容完全相同的两个文件不会被不小心同时包含，不同头文件中宏名撞车的时候，会导致明明头文件存在，但编译器却找不到声明的情况，编译时间较长。
    - __pragma操作符在宏定义中是以内联方式使用的

#### 2.1.4 不定参数宏定义及__VA_ARGS__
- 变长参数宏的应用
```
#include <stdio.h>

#define LOG(...)  {\
    fprintf(stderr,"%s: Line %d:\t", __FILE__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr,"\n");\
} 

int main() {
    int x = 3;
    // 一些代码...
    LOG("x = %d", x); // 2-1-5.cpp: Line 12:     x = 3
}

```
可以追溯代码中产生这些记录的位置

#### 2.1.5 宽窄字符串连接
窄字符串（char）
为了更好支持Unicode，定义了更多种类的字符串类型

### 2.2 long long 整型
long long 整型有两种：
- long long
- unsigned long long

long long整型可以在不同平台有不同的长度，但至少64位。书写时在常数字面量时，可以使用LL后缀（或ll）,unsigned long long （ULL, Ull, uLL, ull）
> long long int lli = -90000000000000LL;
> unsigned long long int ulli = -90000000000000ULL;

了解平台上long long大小的方法就是查看<climit>（或<limits.h>中的宏）
```
#include <climits>
#include <cstdio>
using namespace std;

int main() {
    long long ll_min = LLONG_MIN;
    long long ll_max = LLONG_MAX;
    unsigned long long ull_max = ULLONG_MAX;

    printf("min of long long: %lld\n", ll_min); // min of long long: -9223372036854775808
    printf("max of long long: %lld\n", ll_max); // max of long long: 9223372036854775807
    printf("max of unsigned long long: %llu\n", ull_max);   // max of unsigned long long: 18446744073709551615
}
```
### 2.3 扩展的整型
C++11 定义以下五种标准的有符号整型：
- signed char
- short int
- int
- long int
- long long int

编译器出于需要，也会自行扩展一些整型，在进行隐式转换的时候，一般按照低等级整型转换为高等级整型，有符号转换为无符号。

### 2.4 宏 __cplusplus
```
#ifdef __cplusplus
extern "C" {
#endif
//一些代码
#ifdef __cplusplus
}
#endif

```
extern "C"抑制C++对函数名、变量名等符号进行名称重整（name mangling），因此编译出的C目标文件和C++目标文件中的变量、函数名称等符号都是相同的，链接器可以可靠地对两种类型的目标文件进行链接。这样成为了C与C++混用头文件的典型做法。

### 2.5 静态断言
