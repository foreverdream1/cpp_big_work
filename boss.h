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
    //显示个人信息
    virtual void showInfo();
    //获取职工岗位名称
    virtual string getDeptName();
};

