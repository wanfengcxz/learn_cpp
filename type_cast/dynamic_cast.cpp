//
// Created by wanfengcxz on 2024/6/15.
//

#include <iostream>

using namespace std;

class NoVirtualBase {

};

class NoVirtualDerived : public NoVirtualBase {

};

void test_no_virtual_cast() {
    /// 父类指针指向子类对象
    NoVirtualBase *basePtr = new NoVirtualDerived;

    /// 向下转型
    NoVirtualDerived *derivedPtr1 = static_cast<NoVirtualDerived *>(basePtr);
    /// NoVirtualBase is not polymorphic
//    NoVirtualDerived *derivedPtr2 = dynamic_cast<NoVirtualDerived *>(basePtr);

}


class Base {
public:
    Base() : b(1) {}

    virtual void virtual_fun() {
        cout << "base" << endl;
    }

    void fun1() {
        cout << "b:" << b << endl;
    }

    int b;
};

class Derived : public Base {
public:
    Derived() : d(2) {}

    void virtual_fun() override {
        cout << "derived" << endl;
    }

    void fun2() {
        cout << "d:" << d << endl;
    }

    int d;
};


void test_virtual_cast1() {
    /// 父类指针指向子类对象
    Base *basePtr1 = new Derived;

    /// 向下转型
    Derived *derivedPtr1 = dynamic_cast<Derived *>(basePtr1);
    Derived *derivedPtr2 = static_cast<Derived *>(basePtr1);

    derivedPtr1->fun2();
    derivedPtr2->fun2();
    derivedPtr1->virtual_fun();
    derivedPtr2->virtual_fun();
    cout << endl;


    /// 父类指针指向父类对象
    Base *basePtr2 = new Base;

    /// 向下转型 实际上不允许 非法的
    Derived *derivedPtr3 = dynamic_cast<Derived *>(basePtr2);   /// 返回空指针
    Derived *derivedPtr4 = static_cast<Derived *>(basePtr2);

    if (derivedPtr3 == nullptr) {
        cout << "derivedPtr3 nullptr" << endl;
    }

    /// 不报错是因为函数寻址是通过指针的类型
    derivedPtr4->fun2();            /// 输出的d是错误值
    derivedPtr4->virtual_fun();     /// 调用base版本的函数 因为虚指针没有改变
}

void test_virtual_cast2() {
    /// 子类指针指向子类对象
    Derived *derivedPtr1 = new Derived;

    /// 向上转型
    Base *basePtr1 = dynamic_cast<Base *>(derivedPtr1);
    Base *basePtr2 = static_cast<Base *>(derivedPtr1);

    /// 当类对象在向上转型（upcasting）时，对象中的虚表指针（vptr）不会被改变。
    /// 这个行为相当于基类指针指向子类对象。
    basePtr1->fun1();
    basePtr2->fun1();
    basePtr1->virtual_fun();
    basePtr2->virtual_fun();
    cout << endl;
}

int main() {

//    test_virtual_cast1();
    test_virtual_cast2();

    return 0;
}