//
// Created by 14394 on 2020/2/18.
//

#ifndef AUTOMANNN_GC_AUTOMANOBJECT_H
#define AUTOMANNN_GC_AUTOMANOBJECT_H

#include "Reflection.h"
using namespace std;
//object的大链表
//static vector<AutomanObject*> AutomanObjects;
static vector<AutomanObject*> Eden;
static vector<AutomanObject*> Survivor1;
static vector<AutomanObject*> Survivor2;
static vector<AutomanObject*> Tenured;
/**
 * 所有的 gc对象派生自本对象
 * 具有类似 reflection的完整类型信息
 * 不能手工调用 任何 gc object的删除
 * */

class AutomanObject {
public:
    static vector<AutomanObject*> Roots;
    AutomanObject* next;
    AutomanObject* prev;

    //定义回收的代
    static AutomanObject gen0;//新生代
    static AutomanObject gen1;//老年代
    static AutomanObject gen2;//持久代

    int genId;

    bool reachable;

    virtual ClassType* getClassType() =0;

public:
    AutomanObject(){
        //连接本对象到Object的大链表
        AutomanObjects.push_back(this);
    }

public:
    virtual void gc();
    virtual void gc(int curGen);
};






#endif //AUTOMANNN_GC_AUTOMANOBJECT_H
