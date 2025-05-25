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
        cout<<"请输入您的选择："<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"添加职工"<<endl;
                wm.Add_Emp();
                wm.init_Emp();
                break;
            case 2:
                cout<<"显示职工"<<endl;
                wm.Show_Emp();
                break;
            case 3:
                cout<<"删除职工"<<endl;
                wm.Del_Emp();
                break;
            case 4:
                cout<<"修改职工"<<endl;
                wm.Mod_Emp();
                break;
            case 5:
                cout<<"查找职工"<<endl;
                wm.Find_Emp();
                break;
            case 6:
                cout<<"退出系统"<<endl;
                wm.exitSystem();
                break;
            case 7:
                cout<<"清空文件"<<endl;
                wm.Clean_File();
                break;
            case 8:
                cout<<"统计人数"<<endl;
                wm.Sort_Emp();
                wm.get_EmpNum();
                break;
            default:
                cout<<"输入错误，请重新输入"<<endl;
                break;
        }
        system("pause");
        // test();
    }
    return 0;
}
/*void test(){
    Worker *worker=nullptr;
    worker=new Employee(1,"张三",1);
    worker->showInfo();
    delete worker;
    worker=new Manager(2,"李四",2);
    worker->showInfo();
    delete worker;
    worker=new Boss(3,"王五",3);
    worker->showInfo();
    delete worker;
}*/