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
    //��ʾ������Ϣ
    virtual void showInfo()=0;
    //��ȡ��λ��Ϣ
    virtual string getDeptName()=0;
    int id;//ְ�����
    string name;//ְ������
    int deptId;//���ű��
};