//
// Created by 14394 on 2020/2/18.
//

#include "AutomanObject.h"
#include <windows.h>
#include <time.h>

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
        AutomanObject* pObj = (AutomanObject*)(((byte*)this)+(*it)->offset);
        if(pObj&&pObj->reachable== true) continue;
        pObj->gc(curGen);
    }
}
/** 代际升级*/
void RiseGen(vector<AutomanObject*> from,vector<AutomanObject*> to);
/** 检查空间是否足够*/
bool SpaceEnough();
//gc线程 --> 有 分代
void GcProcessThread(){
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
            delete *it;
            //断开对象链表
            Eden.erase(it);
        }
    }
    RiseGen(Eden,Survivor1);
    if (SpaceEnough()){
        return;
    }
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
        }
    }
    RiseGen(Survivor1,Survivor2);
    if (SpaceEnough()){
        return;
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
        }
    }
    RiseGen(Survivor2,Tenured);
    if (SpaceEnough()){
        return;
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
        }
    }
    if (SpaceEnough()){
        return;
    }
    throw "out of memory!";

}

//代际升级
void RiseGen(vector<AutomanObject*> from,vector<AutomanObject*> to){
    vector<AutomanObject *>::iterator it;
    for (it=from.begin(); it != from.end(); it++){
        //对象的代际属性进行升级
        (*it)->genId++;
        to.push_back(*it);
        from.erase(it);
    }
}

bool SpaceEnough(){
   srand(time(NULL));
    return rand()>32767/2;
}
