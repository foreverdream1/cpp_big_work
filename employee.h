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
    //���캯��
    Employee(int id,string name,int dId);
    //��ʾ������Ϣ
    virtual void showInfo();
    //��ȡְ����λ��Ϣ
    virtual string getDeptName();
};
