//
// Created by 14394 on 2020/2/18.
//

#ifndef AUTOMANNN_GC_TESTS_H
#define AUTOMANNN_GC_TESTS_H

#include <iostream>

#include "../core/AutomanObject.h"
using namespace std;
class  AType:public AutomanObject{
public:
    ClassType * getClassType() override;

public:
    string name;
    int age;
    AType();
    ~AType();

public:
    void info();
};

class  BType:public AutomanObject{
public:
    ClassType * getClassType() override;

public:
    string name;
    int age;
    AType* aType;
    BType(AType* atype);
    ~BType();
public:
    virtual void info();
};

class  CType:public BType{
public:
    ClassType * getClassType() override;

public:
    void info();
    CType(AType* atype);
    ~CType();
};


#endif //AUTOMANNN_GC_TESTS_H
