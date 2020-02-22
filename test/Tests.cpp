//
// Created by 14394 on 2020/2/18.
//

#include "Tests.h"
using namespace std;
AType::AType():name("atype"),age(11){
}

AType::~AType(){
    cout<<"this is atype destroy function! addr is "<<endl;
}

void AType::info() {cout<<"this is atype function!"<<endl;}

ClassType * AType::getClassType() {
    ClassType* classType = new ClassType;
    return classType;
}

BType::BType(AType* atype):name("btype"),age(12){
    this->aType = atype;
}
BType::~BType() {
    cout<<"this is B type destroy function.addr is "<<this<<endl;
}

void BType::info() {cout<<"this is btype function."<<endl;}

ClassType * BType::getClassType() {
    ClassType* classType = new ClassType;
    Member* member = new Member;
    member->offset = (uintptr_t)(&(((BType*)0)->aType));
    //将变量的地址保存(之后在转化的时候，就需要类的类型)
    member->addr = this->aType;
    classType->members.push_back(member);
    return classType;
}

CType::CType(AType* aType1):BType(aType1){
    name = "ctype";
    age=15;
}
CType::~CType() {
    cout<<"this is ctype destroy function! addr is "<<endl;
}

void CType::info() {
    cout<<"this is ctype function!"<<endl;
}

ClassType * CType::getClassType() {
    ClassType* classType = new ClassType;
    Member* member = new Member;
    member->offset = (uintptr_t)(&(((CType*)0)->aType));
    member->addr = this->aType;
    classType->members.push_back(member);
    return classType;
}

