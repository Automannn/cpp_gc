//
// Created by 14394 on 2020/2/18.
//

#ifndef AUTOMANNN_GC_AUTOMANOBJECT_H
#define AUTOMANNN_GC_AUTOMANOBJECT_H

#include "Reflection.h"
#include <iostream>

using namespace std;

extern vector<AutomanObject*> GcRoot;
extern vector<AutomanObject*> Eden;
extern vector<AutomanObject*> Survivor1;
extern vector<AutomanObject*> Survivor2;
extern vector<AutomanObject*> Tenured;

/**
 * 所有的 gc对象派生自本对象
 * 具有类似 reflection的完整类型信息
 * 不能手工调用 任何 gc object的删除
 * */

enum WAIT_OPERATION_TYPE{
    REQUIRE_EXPANSE,//内存不够申请gc消息
    EXPIRE_TIME_EXPANSE,
    GC_EXIT
};

class AutomanObject {

public:
    bool reachable;

    virtual ClassType* getClassType() =0;

public:
    int genId;
public:
    AutomanObject();

    virtual ~AutomanObject(){}

public:
    virtual void gc(int curGen);
};

class ObjectFactory {
public:
    int count;
public:
    void* getObj(AutomanObject* ptr);

public:
    ObjectFactory():count(0){}

    ~ObjectFactory();
};






#endif //AUTOMANNN_GC_AUTOMANOBJECT_H
