//
// Created by 14394 on 2020/2/18.
//

#ifndef AUTOMANNN_GC_REFLECTION_H
#define AUTOMANNN_GC_REFLECTION_H

#include "AutomanObject.h"
#include <vector>

using namespace std;
class AutomanObject;
/**
 * 用于实现 类的 reflection功能
 * */
struct ClassType;

struct Member{
    int offset; //类的成员变量地址偏移
    void* addr; //存储成员地址
//    struct ClassType* type; //成员变量的类型
};

struct ClassType{
//    int getContainNumber();//获得成员外引用对象数量
//    AutomanObject* getContainObject(int i);//获得成员外引用对象
    vector<Member*> members;// 类的成员变量集合
};

//int ClassType::getContainNumber() {
//    return members.size();
//}

//AutomanObject* ClassType::getContainObject(int i) {
//    if(i>=getContainNumber()) return NULL;
//    return members[i].type;
//}


#endif //AUTOMANNN_GC_REFLECTION_H
