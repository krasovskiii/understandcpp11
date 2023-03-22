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

/*
从代码中可以看到，在结构体的构造函数中，初始化成员列表使用__func__预定义标识符是可行的，其效果跟在函数中使用一样。
不过将__fun__标识符作为函数参数的默认值是不允许的，如上例函数funcFail所示（无法编译通过）
这是由于在参数声明时，__func__还未被定义。
*/