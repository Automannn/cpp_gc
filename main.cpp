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
static BType* bb=new BType;

class SmartPtr;

void popStack(){
    GcRoot.pop_back();
}


int main(){
    SmartPtr p1;  //利用辅助指针 维护 gcRoot
    //模拟程序申请了堆内存
    AType* a = new AType;//对分配
    p1 = a;
    {
        SmartPtr p2;
        BType* b = new BType; p2=b;
        BType* b1 = new BType; p2=b1;
        BType* b2 = new BType; p2=b2;
        BType* b3 = new BType; p2=b3;

        //作用域内 进行堆申请
        for (int i = 0; i < 10; ++i) {
            SmartPtr p3;
            CType* ccc = new CType;
            p3=ccc;
        }
    }

    CType* c = new CType;
    //模拟维护GcRoot

    //模拟程序运行了很久

    //模拟新开程序不足 ->触发gc


}