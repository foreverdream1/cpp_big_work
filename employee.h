//
// Created by Lenovo on 2025/5/24.
//
#pragma once
#ifndef WORKERMANAGER_EMPLOYEE_H
#define WORKERMANAGER_EMPLOYEE_H

#endif //WORKERMANAGER_EMPLOYEE_H
#include<iostream>
#include<string>
using namespace std;
#include"worker.h"
class Employee :public Worker{
public:
    //构造函数
    Employee(int id,string name,int dId);
    //显示个人信息
    virtual void showInfo();
    //获取职工岗位信息
    virtual string getDeptName();
};
