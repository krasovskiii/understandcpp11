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

