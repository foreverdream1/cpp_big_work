//
// Created by Lenovo on 2025/5/24.
//
#pragma once
#ifndef WORKERMANAGER_WORKER_H
#define WORKERMANAGER_WORKER_H

#endif //WORKERMANAGER_WORKER_H
#include<iostream>
#include<string>
using namespace std;
class Worker{
public:
    //显示个人信息
    virtual void showInfo()=0;
    //获取岗位信息
    virtual string getDeptName()=0;
    int id;//职工编号
    string name;//职工姓名
    int deptId;//部门编号
};