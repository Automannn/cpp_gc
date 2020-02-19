模拟一般的类进行gc测试
其中：
    A 依赖基本类(int,string)
    B 依赖A   各自又依赖基本类
    C 继承B 依赖A