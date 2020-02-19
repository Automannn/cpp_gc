//
// Created by 14394 on 2020/2/18.
//

#include <vector>
#include <iostream>
#include "core/AutomanObject.h"
#include "test/Tests.h"
using namespace std;

/** 代际升级*/
void RiseGen(vector<AutomanObject*> from,vector<AutomanObject*> to);
/** 检查空间是否足够*/
bool SpaceEnough();
//gc线程 --> 有 分代
void GcProcessThread();
class Bclass{
    int a,b,c,bs;
    string hh,bb,cc,dd;
    char* wdg,sdk,dfd;
public:
    ~Bclass(){
        cout<<"destroy b class"<<endl;
    }
};
class TestClass{
public:
    TestClass():num(11){
        cout<<"test class constructor"<<endl;
    }

    ~TestClass(){
        cout<<"test class destroy constructor"<<endl;
    }

private:
    string info;
    int num;
    Bclass b,c,d,e,f,g;
};

int main(){
    //模拟程序运行很久
    //模拟新开程序不足 ->触发gc

    {
        TestClass testClass;
        cout<<"pause!"<<endl;
    }
}