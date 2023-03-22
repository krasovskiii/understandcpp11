#include <iostream>
using namespace std;

struct TestStruct {
    TestStruct () : name(__func__) {};
    const char* func() {
        return __func__;
    }

    // void funcFail(string func_name = __func__); // E1036 �����ı�ʶ�� "__func__" ֻ���ں����ڲ�ʹ��
    const char *name;
};

int main() {
    TestStruct ts;
    cout << ts.name << endl;    // TestStruct
    cout << ts.func() << endl; // func
}

/*
�Ӵ����п��Կ������ڽṹ��Ĺ��캯���У���ʼ����Ա�б�ʹ��__func__Ԥ�����ʶ���ǿ��еģ���Ч�����ں�����ʹ��һ����
������__fun__��ʶ����Ϊ����������Ĭ��ֵ�ǲ�����ģ�����������funcFail��ʾ���޷�����ͨ����
���������ڲ�������ʱ��__func__��δ�����塣
*/