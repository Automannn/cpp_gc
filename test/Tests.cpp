//
// Created by 14394 on 2020/2/18.
//

#include "Tests.h"
using namespace std;
AType::AType():name("atype"),age(11){}

void AType::info() {cout<<"this is atype function!"<<endl;}

ClassType * AType::getClassType() {
    ClassType* classType = new ClassType;
    return classType;
}

BType::BType():name("btype"),age(12){}

void BType::info() {cout<<"this is btype function."<<endl;}

ClassType * BType::getClassType() {
    ClassType* classType = new ClassType;
    Member* member = new Member;
    member->offset = (uintptr_t)(&(((BType*)0)->aType));
    classType->members.push_back(member);
    return classType;
}

CType::CType(){
    name = "ctype";
    age=15;
}

void CType::info() {
    cout<<"this is ctype function!"<<endl;
}

ClassType * CType::getClassType() {
    ClassType* classType = new ClassType;
    Member* member = new Member;
    member->offset = (uintptr_t)(&(((CType*)0)->aType));
    classType->members.push_back(member);
    return classType;
}

