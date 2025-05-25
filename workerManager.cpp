#include "workerManager.h"
#include <cstdlib>  
#include<iostream>
#include <string>

#include "boss.h"
#include "employee.h"
#include "manager.h"
#include<set>

WorkerManager::WorkerManager(){
    //初始化人数
    this->empnum=0;
    //初始化数组指针
    this->Emparray=nullptr;
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    //文件不存在情况
    if (!ifs.is_open()) {
        cout<<"文件不存在"<<endl;//测试输出
        this->empnum=0;//初始化人数
        this->FileIsEmpty=true;//初始化文件为空标志
        this->Emparray=NULL;//初始化数组
        char ch;
        ifs>>ch;
        if (ifs.eof())
        ifs.close();//关闭文件
        return ;
    }
    //文件存在，数据为空
    char ch;
    ifs>>ch;
    if (ifs.eof()) {
        cout<<"文件为空!"<<endl;
        this->empnum=0;
        this->FileIsEmpty=true;
        this->Emparray=NULL;
        ifs.close();
        return ;
    }

    int num=this->get_EmpNum();
    cout<<"职工个数为:"<<num<<endl;//测试代码
    this->empnum=num;//更新成员属性

    //根据职工数创建数组
    this->Emparray=new Worker *[this->empnum];
    //初始化职工
    init_Emp();
    //测试代码
    for (int i=0;i<this->empnum;i++) {
        cout<<"职工编号："<<this->Emparray[i]->id
        <<"\t姓名："<<this->Emparray[i]->name
        <<"\t   `岗位："<<this->Emparray[i]->getDeptName()<<endl;
    }
}

void WorkerManager::Show_Menu(){
    cout<<"**********************************"<<endl;
    cout<<"********* 1.添加职工 *************"<<endl;
    cout<<"********* 2.显示职工 *************"<<endl;
    cout<<"********* 3.删除职工 *************"<<endl;
    cout<<"********* 4.修改职工 *************"<<endl;
    cout<<"********* 5.查找职工 *************"<<endl;
    cout<<"********* 6.退出系统 *************"<<endl;
    cout<<"********* 7.清空文件 *************"<<endl;
    cout<<"********* 8.统计人数 *************"<<endl;
    cout<<"**********************************"<<endl;
    cout<<endl;
}
void WorkerManager::Add_Emp() {
    cout << "请输入增加职工数量：" << endl;
    int addNum = 0;
    cin >> addNum;

    // 验证输入数量
    if (addNum <= 0) {
        cout << "输入错误" << endl;
        system("pause");
        system("cls");
        return;
    }

    // 计算新空间大小
    int newSize = this->empnum + addNum;

    // 开辟新空间
    Worker** newSpace = new Worker*[newSize](); // 初始化为nullptr

    // 复制原有数据
    if (this->Emparray != NULL) {
        for (int i = 0; i < this->empnum; i++) {
            newSpace[i] = this->Emparray[i];
        }
    }

    // 预先加载现有ID用于检查重复
    set<int> existingIds;
    ifstream ifs(FILENAME, ios::in);
    if (ifs.is_open()) {
        int existingId;
        string tempName;
        int tempDId;
        while (ifs >> existingId >> tempName >> tempDId) {
            existingIds.insert(existingId);
        }
        ifs.close();
    }

    // 添加新员工
    for (int i = 0; i < addNum; i++) {
        cout << "请输入第" << i + 1 << "个职工的id：" << endl;
        int id;
        cin >> id;

        // 检查ID是否已存在
        while (existingIds.find(id) != existingIds.end()) {
            cout << "id已存在，请重新输入：" << endl;
            cin >> id;
        }
        existingIds.insert(id); // 添加到已存在ID集合

        cout << "请输入第" << i + 1 << "个职工的姓名：" << endl;
        string name;
        cin >> name;

        cout << "请选择该职工的岗位:" << endl;
        cout << "1、普通职工" << endl;
        cout << "2、经理" << endl;
        cout << "3、老板" << endl;
        int dSelect;
        cin >> dSelect;

        // 验证岗位选择
        while (dSelect < 1 || dSelect > 3) {
            cout << "输入错误，请重新选择(1-3):" << endl;
            cin >> dSelect;
        }

        Worker* worker = nullptr;
        switch (dSelect) {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
        }

        newSpace[this->empnum + i] = worker;
    }

    // 释放原有空间
    delete[] this->Emparray;

    // 更新成员变量
    this->Emparray = newSpace;
    this->empnum = newSize;
    this->FileIsEmpty = false;

    cout << "成功添加" << addNum << "名职工" << endl;
    this->save();

    system("pause");
    system("cls");
}

void WorkerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME,ios::out);
    for (int i=0;i<this->empnum;i++) {
        ofs<<this->Emparray[i]->id<<" "
        <<this->Emparray[i]->name<<" "
        <<this->Emparray[i]->deptId<<endl;
    }
    ofs.close();
}
int WorkerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;

    int num=0;
    while (ifs>>id&&ifs>>name&&ifs>>dId) {
        //记录人数
        num++;
    }
    ifs.close();
    return num;
}
void WorkerManager::init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;
    int index=0;
    while (ifs>>id&&ifs>>name&&ifs>>dId) {
        Worker * worker=NULL;
        //根据不同的部门ID创建不同的对象
        switch (dId) {
            case 1:
                worker=new Employee(id,name,1);
                break;
            case 2:
                worker=new Manager(id,name,2);
                break;
            case 3:
                worker=new Boss(id,name,3);
                break;
            default:
                cout<<"输入错误"<<endl;
                break;
        }
        //存放在数组中
        this->Emparray[index]=worker;
        index++;
    }
}

void WorkerManager::Show_Emp() {
    if (this->FileIsEmpty) {
        cout<<"文件不存在或空"<<endl;
    }
    else {
        //利用多态调用接口
        for (int i=0;i<this->empnum;i++) {
            this->Emparray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}
int WorkerManager::IsExist(int id) {
    int index=-1;

    for (int i=0;i<this->empnum;i++) {
        if (this->Emparray[i]->id==id) {
            index=i;
            break;
        }
    }
    return index;
}

//删除职工
void WorkerManager::Del_Emp() {
    if (this->FileIsEmpty) {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else {
        cout<<"请输入删除职工的id："<<endl;
        int id=0;
        cin>>id;
        int index=this->IsExist(id);
        if (index!=-1) {//index位置上数据需要删除
            for (int i=index;i<this->empnum-1;i++) {
                //数据前移
                this->Emparray[i]=this->Emparray[i+1];
            }
            this->empnum--;
            this->save();//保存到文件中
            cout<<"删除成功"<<endl;
            system("pause");
            system("cls");
        }
        else {
            cout<<"删除失败,未找到该职工"<<endl;
        }
    }
}

//修改职工
void WorkerManager::Mod_Emp() {
    if (this->FileIsEmpty) {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else {
        cout<<"请输入修改职工的编号:"<<endl;
        int id=0;
        cin>>id;

        int ret=this->IsExist(id);
        if (ret!=-1) {
            //查找到编号的职工

            delete this->Emparray[ret];
            int newId=0;
            string Newname="";
            int dSelect=0;

            cout<<"查到："<<id<<"号职工，请输入新职工id"<<endl;
            cin>>newId;
            cout<<"请输入新职工姓名："<<endl;
            cin>>Newname;

            cout<<"请输入岗位:"<<endl;
            cout<<"1、普通职工"<<endl;
            cout<<"2、经理"<<endl;
            cout<<"3、老板"<<endl;
            cin>>dSelect;
            Worker * worker=NULL;
            switch (dSelect) {
                case 1:
                    worker=new Employee(newId,Newname,dSelect);
                    break;
                case 2:
                    worker=new Manager(newId,Newname,dSelect);
                    break;
                case 3:
                    worker=new Boss(newId,Newname,dSelect);
                    break;
                default:
                    cout<<"输入错误，请重新输入岗位"<<endl;
                    break;
            }
            //更新数据到数组中
            this->Emparray[ret]=worker;

            cout<<"修改成功"<<endl;

            //保存到文件中
            this->save();
        }
        else {
            cout<<"修改失败，查无此人"<<endl;
        }
        system("pause");
        system("cls");
    }
}

//查找职工
void WorkerManager::Find_Emp() {
    if (this->FileIsEmpty) {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else {
        cout<<"请输入查找的方式:"<<endl;
        cout<<"1、按职工id查找"<<endl;
        cout<<"2、按姓名查找"<<endl;

        int select=0;
        cin>>select;


        if (select==1) {
            int id;
            cout<<"请输入查找的职工id:"<<endl;
            cin>>id;

            int res=IsExist(id);
            if (res!=-1) {
                cout<<"查找成功，该职工信息如下："<<endl;
                this->Emparray[res]->showInfo();
            }
            else {
                cout<<"查找失败，查无此人"<<endl;
            }
        }
        else if (select==2) {
            string name;
            cout<<"请输入查找的姓名"<<endl;
            cin>>name;

            bool flag=false;//查找到的标志
            for (int i=0;i<empnum;i++) {
                if (Emparray[i]->name==name) {
                    cout<<"查找成功，职工id为："
                    <<Emparray[i]->id<<"职工姓名为："<<Emparray[i]->name<<endl;

                    flag=true;

                    this->Emparray[i]->showInfo();
                }
            }
            if (flag==false) {
                //查无此人
                cout<<"查找失败，查无此人"<<endl;
            }

        }
        else {
            cout<<"输入选项有误"<<endl;
        }
    }
    system("pause");
    system("cls");
}

//排序职工
void WorkerManager::Sort_Emp() {
    if (this->FileIsEmpty) {
        cout<<"文件不存在或记录为空"<<endl;
    }
    else {
        cout<<"请选择排序方式："<<endl;
        cout<<"1、按职工id进行升序"<<endl;
        cout<<"2、按职工id进行降序"<<endl;

        int select=0;
        cin>>select;
        for (int i=0;i<empnum;i++) {
            int minOrmax=i;
            for (int j=i+1;j<empnum;j++) {
                if (select==1) {//升序
                    if (Emparray[minOrmax]->id>Emparray[j]->id) {
                        minOrmax=j;
                    }
                }
                else {//降序
                    if (Emparray[minOrmax]->id<Emparray[j]->id) {
                        minOrmax=j;
                    }
                }
            }
            if (i!minOrmax) {
                Worker * temp=Emparray[i];
                Emparray[i]=Emparray[minOrmax];
                Emparray[minOrmax]=temp;
            }
        }
        cout<<"排序成功，结果为："<<endl;
        this->save();
        this->Show_Emp();
    }
}

//清空文件
void WorkerManager::Clean_File() {
    cout<<"是否清空文件？"<<endl;
    cout<<"1、确认"<<endl;
    cout<<"2、取消"<<endl;

    int select=0;
    cin>>select;

    if (select==1) {
        //打开模式ios::trunc如果存在删除文件并重新创建
        ofstream ofs(FILENAME,ios::trunc);
        ofs.close();

        if (this->Emparray!=NULL) {
            for (int i=0;i<this->empnum;i++) {
                if (this->Emparray[i]!=NULL) {
                    delete this->Emparray[i];
                }
            }
            this->empnum=0;
            delete[] this->Emparray;
            this->Emparray=NULL;
            this->FileIsEmpty=true;
        }
        cout<<"清空成功"<<endl;
    }
    system("pause");
    system("cls");
}




void WorkerManager::exitSystem(){
    cout<<"欢迎下次使用"<<endl;
    exit(0);
}


WorkerManager::~WorkerManager(){
    if (this->Emparray!=NULL) {
        for (int i=0;i<this->empnum;i++) {
            if (this->Emparray[i]!=NULL) {
                delete this->Emparray[i];
            }
        }
        delete[] this->Emparray;
        this->Emparray=NULL;
    }
}