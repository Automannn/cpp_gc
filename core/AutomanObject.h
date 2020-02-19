//
// Created by 14394 on 2020/2/18.
//

#ifndef AUTOMANNN_GC_AUTOMANOBJECT_H
#define AUTOMANNN_GC_AUTOMANOBJECT_H

#include "Reflection.h"
using namespace std;
//object的大链表
static vector<AutomanObject*> GcRoot;
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
    bool reachable;

    virtual ClassType* getClassType() =0;

public:
    int genId;
public:
    AutomanObject():genId(0){
        //设定一个新对象只能从新生代申请
        Eden.push_back(this);
    }

    virtual ~AutomanObject(){}

public:
    virtual void gc(int curGen);
};






#endif //AUTOMANNN_GC_AUTOMANOBJECT_H
