#include"boss.h"
#include<iostream>
#include<string>
using namespace std;
Boss::Boss(int id,string name,int dId){
    this->id=id;
    this->name=name;
    this->deptId=dId;
}

void Boss::showInfo() {
    cout<<"ְ�����:"<<this->id
    <<"\tְ������:"<<this->name
    <<"\t��λ:"<<this->getDeptName()
    <<"\t��λְ��:����˾��������"<<endl;
}

string Boss::getDeptName() {
    return string("�ܲ�");
}