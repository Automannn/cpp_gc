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

class SmartPtr;

class ObjectFactory;

void popStack(){
    GcRoot.pop_back();
}


int main(){
    ObjectFactory f1;  //利用辅助指针 维护 gcRoot
    //模拟程序申请了堆内存
    AType* a = static_cast<AType *>(f1.getObj(new AType));//对分配
    {
        ObjectFactory f2;
        BType* b = static_cast<BType *>(f2.getObj(new BType(a)));
        BType* b1 = static_cast<BType *>(f2.getObj(new BType(a)));
        BType* b2 = static_cast<BType *>(f2.getObj(new BType(a)));
        BType* b3 = static_cast<BType *>(f2.getObj(new BType(a)));

        //作用域内 进行堆申请
        for (int i = 0; i < 10; ++i) {
            ObjectFactory f3;
            CType* ccc = static_cast<CType *>(f3.getObj(new CType(a)));
        }
    }

    CType* c = static_cast<CType *>(f1.getObj(new CType(a)));
    //模拟程序运行了很久
    //todo:

    //模拟程序申请内存不够，触发gc线程
    //todo:



}