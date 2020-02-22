//
// Created by 14394 on 2020/2/18.
//

#include "AutomanObject.h"
#include <windows.h>
#include <time.h>

unsigned GcProcessTask();

 vector<AutomanObject*> GcRoot;
 vector<AutomanObject*> Eden;
 vector<AutomanObject*> Survivor1;
 vector<AutomanObject*> Survivor2;
 vector<AutomanObject*> Tenured;

AutomanObject::AutomanObject():genId(0){
    //设定一个新对象只能从新生代申请
    Eden.push_back(this);
    cout<<"wtf !! eden.num="<<Eden.size();
    cout<<";  address is="<<this<<endl;
}

/**采用代际回收之后的处理*/
void AutomanObject::gc(int curGen) {
    //当前对象的代际高于回收代际，则终止
    if(genId>curGen){
        return;
    }
    reachable = true;
    ClassType* ptype = this->getClassType();

    vector<Member *>::iterator it;
    for (it=ptype->members.begin(); it != ptype->members.end(); it++){
//        AutomanObject* pObj = (AutomanObject*)(((byte*)this)+(*it)->offset);
        AutomanObject* pObj = static_cast<AutomanObject *>((*it)->addr);
        if(pObj&&pObj->reachable== true) continue;
        pObj->gc(curGen);
    }
}

void * ObjectFactory::getObj(AutomanObject *ptr){
    GcRoot.push_back(ptr);
    this->count++;
    return ptr;
}

ObjectFactory::~ObjectFactory() {
    while (this->count>0){
        GcRoot.pop_back();
        this->count--;
    }
}

/** 代际升级*/
void RiseGen(vector<AutomanObject*>* from,vector<AutomanObject*>* to);
/** 检查空间是否足够*/
bool SpaceEnough();

//gc线程 --> 有 分代
//该线程通过完成端口进行阻塞通信
unsigned GcProcessThread(PVOID pM){
    HANDLE completionPort = pM;
    BOOL bRet = FALSE;
    DWORD dwBytes = 0;
    WAIT_OPERATION_TYPE opType;//等待的信号类型，相当于消息类型
    OVERLAPPED* ol; //消息内容
    while(true){
        bRet = GetQueuedCompletionStatus(completionPort,&dwBytes,(PULONG_PTR)&opType,&ol,INFINITE);
        if(bRet){
            if(REQUIRE_EXPANSE==opType){
                GcProcessTask();
            } else if(EXPIRE_TIME_EXPANSE==opType){
                GcProcessTask();
            } else if(GC_EXIT==opType){
                return 0;
            } else{
                return -1;
            }
        }
    }
}

unsigned GcProcessTask(){
    vector<AutomanObject *>::iterator it;
/************************Eden代 回收***********************************/
    for (it=Eden.begin(); it != Eden.end(); it++){
        (*it)->reachable = false;
    }
    //从所有根对象开始递归标识哪些对象可到达
    for (it=GcRoot.begin();it!=GcRoot.end();it++){
        (*it)->gc(0);
    }
    //清理不可到达对象
    for (it=Eden.begin();it!=Eden.end();it++){
        if((*it)->reachable == false&&(*it)->genId<1){
            //断开对象链表
            delete *it;
            Eden.erase(it);
            it--;
        }
    }
    RiseGen(&Eden,&Survivor1);
    if (SpaceEnough()){
        return 0;
    }
    int siz_num1= Survivor1.size();
/************************survival1代 回收*****************************/
    for (it=Survivor1.begin(); it != Survivor1.end(); it++){
        (*it)->reachable = false;
    }
    //从所有根对象开始递归标识哪些对象可到达
    for (it=GcRoot.begin();it!=GcRoot.end();it++){
        (*it)->gc(1);
    }
    //清理不可到达对象
    for (it=Survivor1.begin();it!=Survivor1.end();it++){
        if((*it)->reachable == false&&(*it)->genId<2){
            //断开对象链表
            delete *it;
            Survivor1.erase(it);
            it--;
        }
    }
    RiseGen(&Survivor1,&Survivor2);
    if (SpaceEnough()){
        return 0;
    }
/************************survival2代 回收*****************************/
    for (it=Survivor2.begin(); it != Survivor2.end(); it++){
        (*it)->reachable = false;
    }
    //从所有根对象开始递归标识哪些对象可到达
    for (it=GcRoot.begin();it!=GcRoot.end();it++){
        (*it)->gc(2);
    }
    //清理不可到达对象
    for (it=Survivor2.begin();it!=Survivor2.end();it++){
        if((*it)->reachable == false&&(*it)->genId<3){
            //断开对象链表
            delete *it;
            Survivor2.erase(it);
            it--;
        }
    }
    RiseGen(&Survivor2,&Tenured);
    if (SpaceEnough()){
        return 0;
    }
/************************Tenured代 回收*****************************/
    for (it=Tenured.begin(); it != Tenured.end(); it++){
        (*it)->reachable = false;
    }
    //从所有根对象开始递归标识哪些对象可到达
    for (it=Tenured.begin();it!=Tenured.end();it++){
        (*it)->gc(3);
    }
    //清理不可到达对象
    for (it=GcRoot.begin();it!=GcRoot.end();it++){
        if((*it)->reachable == false&&(*it)->genId<4){
            //断开对象链表
            delete *it;
            Tenured.erase(it);
            it--;
        }
    }
    if (SpaceEnough()){
        return 0;
    }
    throw "out of memory!";
}

//代际升级
void RiseGen(vector<AutomanObject*>* from,vector<AutomanObject*>* to){
    vector<AutomanObject *>::iterator it;
    for (it=from->begin(); it != from->end(); it++){
        //对象的代际属性进行升级
        (*it)->genId++;
        to->push_back(*it);
        from->erase(it);
        it--;
    }
}

bool SpaceEnough(){
    //种子函数必须间隔一秒
   srand(time(0));
   int MAX = 10;
   int MIN =1;
   Sleep(1000);
   int ranNum= rand();
   ranNum =MIN+ranNum%(MAX-MIN+1);
   cout<<"======================ranNum is "<<ranNum<<endl;
    return ranNum>5;
}
