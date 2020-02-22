//
// Created by 14394 on 2020/2/18.
//

#include <vector>
#include <iostream>
#include <winsock2.h>
#include <process.h>
#include "core/AutomanObject.h"
#include "test/Tests.h"


using namespace std;

/** 代际升级*/
void RiseGen(vector<AutomanObject*> from,vector<AutomanObject*> to);
/** 检查空间是否足够*/
bool SpaceEnough();
//gc线程 --> 有 分代
unsigned GcProcessThread(PVOID pM);

class ObjectFactory;


int main(){
    ObjectFactory f1;  //利用辅助指针 维护 gcRoot
    //模拟程序申请了堆内存
    AType* a1 = static_cast<AType *>(f1.getObj(new AType));
    AType* a2 = static_cast<AType *>(f1.getObj(new AType));
    AType* a3 = static_cast<AType *>(f1.getObj(new AType));

    BType* b1 = static_cast<BType *>(f1.getObj(new BType(a1)));
    BType* b2 = static_cast<BType *>(f1.getObj(new BType(a2)));
    BType* b3 = static_cast<BType *>(f1.getObj(new BType(a3)));
    {
        ObjectFactory f2;
        AType* a21 = static_cast<AType *>(f2.getObj(new AType));
        AType* a22 = static_cast<AType *>(f2.getObj(new AType));
        AType* a23 = static_cast<AType *>(f2.getObj(new AType));
        BType* b21 = static_cast<BType *>(f2.getObj(new BType(a1)));
        BType* b22 = static_cast<BType *>(f2.getObj(new BType(a2)));
        BType* b23 = static_cast<BType *>(f2.getObj(new BType(a21)));
        BType* b24 = static_cast<BType *>(f2.getObj(new BType(a22)));

        //作用域内 进行堆申请
        for (int i = 0; i < 10; ++i) {
            ObjectFactory f3;
            CType* ccc = static_cast<CType *>(f3.getObj(new CType(a1)));
        }


    }

    //实例化完成端口，分配内存IO
    //定义通知事件
    HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,1);
    //开启gc线程
    HANDLE gcThread= (HANDLE)(_beginthreadex(0, 0, GcProcessThread, completionPort, 0, 0));
    CloseHandle(gcThread);

    Sleep(1000*60);//主线程休眠2分钟，模拟程序运行一段事件

    //模拟线程运行内存不够，需要进行内存回收 发送通知
    //触发完成端口通知
    PostQueuedCompletionStatus(completionPort,0,EXPIRE_TIME_EXPANSE,NULL);
    Sleep(1000*60*5);//主线程休眠三分钟，模拟程序又运行一段事件

    CType* c = static_cast<CType *>(f1.getObj(new CType(a1)));

    //程序退出前，关闭gc线程
    PostQueuedCompletionStatus(completionPort,0,GC_EXIT,NULL);
}