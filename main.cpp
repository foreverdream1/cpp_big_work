#include<iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<cstdlib>

using namespace std;
void test();
int main(){
    WorkerManager wm;
    int choice=0;
    while(1){
        wm.Show_Menu();
        cout<<"����������ѡ��"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"���ְ��"<<endl;
                wm.Add_Emp();
                wm.init_Emp();
                break;
            case 2:
                cout<<"��ʾְ��"<<endl;
                wm.Show_Emp();
                break;
            case 3:
                cout<<"ɾ��ְ��"<<endl;
                wm.Del_Emp();
                break;
            case 4:
                cout<<"�޸�ְ��"<<endl;
                wm.Mod_Emp();
                break;
            case 5:
                cout<<"����ְ��"<<endl;
                wm.Find_Emp();
                break;
            case 6:
                cout<<"�˳�ϵͳ"<<endl;
                wm.exitSystem();
                break;
            case 7:
                cout<<"����ļ�"<<endl;
                wm.Clean_File();
                break;
            case 8:
                cout<<"ͳ������"<<endl;
                wm.Sort_Emp();
                wm.get_EmpNum();
                break;
            default:
                cout<<"�����������������"<<endl;
                break;
        }
        system("pause");
        // test();
    }
    return 0;
}
/*void test(){
    Worker *worker=nullptr;
    worker=new Employee(1,"����",1);
    worker->showInfo();
    delete worker;
    worker=new Manager(2,"����",2);
    worker->showInfo();
    delete worker;
    worker=new Boss(3,"����",3);
    worker->showInfo();
    delete worker;
}*/