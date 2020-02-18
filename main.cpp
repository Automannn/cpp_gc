//
// Created by 14394 on 2020/2/18.
//

#include "main.h"
#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<int> vec{1, 4, 3, 2, 5, 2};

    for(auto it = vec.begin(); it != vec.end(); it++){
        if(*it < 3){
            cout << "num is " << *it << endl;
//            it = vec.erase(it);
//            if(it == vec.end()) break;
        }
    }
}