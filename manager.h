//
// Created by Lenovo on 2025/5/24.
//
#pragma
#ifndef WORKERMANAGER_MANAGER_H
#define WORKERMANAGER_MANAGER_H

#endif //WORKERMANAGER_MANAGER_H
#include<iostream>
#include<string>
#include"worker.h"
using namespace std;
class Manager:public Worker{
public:
    Manager(int id,string name,int dId);
    //显示个人信息
    virtual void showInfo();
    //获取岗位信息
    virtual string getDeptName();
};