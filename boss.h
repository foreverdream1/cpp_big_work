//
// Created by Lenovo on 2025/5/24.
//
#pragma
#ifndef WORKERMANAGER_BOSS_H
#define WORKERMANAGER_BOSS_H

#endif //WORKERMANAGER_BOSS_H
#include<iostream>
#include <string>
#include"worker.h"
using namespace std;
class Boss:public Worker{
public:
    Boss(int id,string name,int dId);
    //��ʾ������Ϣ
    virtual void showInfo();
    //��ȡְ����λ����
    virtual string getDeptName();
};

