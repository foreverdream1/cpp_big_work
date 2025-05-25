#include "workerManager.h"
#include <cstdlib>  
#include<iostream>
#include <string>

#include "boss.h"
#include "employee.h"
#include "manager.h"
#include<set>

WorkerManager::WorkerManager(){
    //��ʼ������
    this->empnum=0;
    //��ʼ������ָ��
    this->Emparray=nullptr;
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    //�ļ����������
    if (!ifs.is_open()) {
        cout<<"�ļ�������"<<endl;//�������
        this->empnum=0;//��ʼ������
        this->FileIsEmpty=true;//��ʼ���ļ�Ϊ�ձ�־
        this->Emparray=NULL;//��ʼ������
        char ch;
        ifs>>ch;
        if (ifs.eof())
        ifs.close();//�ر��ļ�
        return ;
    }
    //�ļ����ڣ�����Ϊ��
    char ch;
    ifs>>ch;
    if (ifs.eof()) {
        cout<<"�ļ�Ϊ��!"<<endl;
        this->empnum=0;
        this->FileIsEmpty=true;
        this->Emparray=NULL;
        ifs.close();
        return ;
    }

    int num=this->get_EmpNum();
    cout<<"ְ������Ϊ:"<<num<<endl;//���Դ���
    this->empnum=num;//���³�Ա����

    //����ְ������������
    this->Emparray=new Worker *[this->empnum];
    //��ʼ��ְ��
    init_Emp();
    //���Դ���
    for (int i=0;i<this->empnum;i++) {
        cout<<"ְ����ţ�"<<this->Emparray[i]->id
        <<"\t������"<<this->Emparray[i]->name
        <<"\t   `��λ��"<<this->Emparray[i]->getDeptName()<<endl;
    }
}

void WorkerManager::Show_Menu(){
    cout<<"**********************************"<<endl;
    cout<<"********* 1.���ְ�� *************"<<endl;
    cout<<"********* 2.��ʾְ�� *************"<<endl;
    cout<<"********* 3.ɾ��ְ�� *************"<<endl;
    cout<<"********* 4.�޸�ְ�� *************"<<endl;
    cout<<"********* 5.����ְ�� *************"<<endl;
    cout<<"********* 6.�˳�ϵͳ *************"<<endl;
    cout<<"********* 7.����ļ� *************"<<endl;
    cout<<"********* 8.ͳ������ *************"<<endl;
    cout<<"**********************************"<<endl;
    cout<<endl;
}
void WorkerManager::Add_Emp() {
    cout << "����������ְ��������" << endl;
    int addNum = 0;
    cin >> addNum;

    // ��֤��������
    if (addNum <= 0) {
        cout << "�������" << endl;
        system("pause");
        system("cls");
        return;
    }

    // �����¿ռ��С
    int newSize = this->empnum + addNum;

    // �����¿ռ�
    Worker** newSpace = new Worker*[newSize](); // ��ʼ��Ϊnullptr

    // ����ԭ������
    if (this->Emparray != NULL) {
        for (int i = 0; i < this->empnum; i++) {
            newSpace[i] = this->Emparray[i];
        }
    }

    // Ԥ�ȼ�������ID���ڼ���ظ�
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

    // �����Ա��
    for (int i = 0; i < addNum; i++) {
        cout << "�������" << i + 1 << "��ְ����id��" << endl;
        int id;
        cin >> id;

        // ���ID�Ƿ��Ѵ���
        while (existingIds.find(id) != existingIds.end()) {
            cout << "id�Ѵ��ڣ����������룺" << endl;
            cin >> id;
        }
        existingIds.insert(id); // ��ӵ��Ѵ���ID����

        cout << "�������" << i + 1 << "��ְ����������" << endl;
        string name;
        cin >> name;

        cout << "��ѡ���ְ���ĸ�λ:" << endl;
        cout << "1����ְͨ��" << endl;
        cout << "2������" << endl;
        cout << "3���ϰ�" << endl;
        int dSelect;
        cin >> dSelect;

        // ��֤��λѡ��
        while (dSelect < 1 || dSelect > 3) {
            cout << "�������������ѡ��(1-3):" << endl;
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

    // �ͷ�ԭ�пռ�
    delete[] this->Emparray;

    // ���³�Ա����
    this->Emparray = newSpace;
    this->empnum = newSize;
    this->FileIsEmpty = false;

    cout << "�ɹ����" << addNum << "��ְ��" << endl;
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
        //��¼����
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
        //���ݲ�ͬ�Ĳ���ID������ͬ�Ķ���
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
                cout<<"�������"<<endl;
                break;
        }
        //�����������
        this->Emparray[index]=worker;
        index++;
    }
}

void WorkerManager::Show_Emp() {
    if (this->FileIsEmpty) {
        cout<<"�ļ������ڻ��"<<endl;
    }
    else {
        //���ö�̬���ýӿ�
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

//ɾ��ְ��
void WorkerManager::Del_Emp() {
    if (this->FileIsEmpty) {
        cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
    }
    else {
        cout<<"������ɾ��ְ����id��"<<endl;
        int id=0;
        cin>>id;
        int index=this->IsExist(id);
        if (index!=-1) {//indexλ����������Ҫɾ��
            for (int i=index;i<this->empnum-1;i++) {
                //����ǰ��
                this->Emparray[i]=this->Emparray[i+1];
            }
            this->empnum--;
            this->save();//���浽�ļ���
            cout<<"ɾ���ɹ�"<<endl;
            system("pause");
            system("cls");
        }
        else {
            cout<<"ɾ��ʧ��,δ�ҵ���ְ��"<<endl;
        }
    }
}

//�޸�ְ��
void WorkerManager::Mod_Emp() {
    if (this->FileIsEmpty) {
        cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
    }
    else {
        cout<<"�������޸�ְ���ı��:"<<endl;
        int id=0;
        cin>>id;

        int ret=this->IsExist(id);
        if (ret!=-1) {
            //���ҵ���ŵ�ְ��

            delete this->Emparray[ret];
            int newId=0;
            string Newname="";
            int dSelect=0;

            cout<<"�鵽��"<<id<<"��ְ������������ְ��id"<<endl;
            cin>>newId;
            cout<<"��������ְ��������"<<endl;
            cin>>Newname;

            cout<<"�������λ:"<<endl;
            cout<<"1����ְͨ��"<<endl;
            cout<<"2������"<<endl;
            cout<<"3���ϰ�"<<endl;
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
                    cout<<"������������������λ"<<endl;
                    break;
            }
            //�������ݵ�������
            this->Emparray[ret]=worker;

            cout<<"�޸ĳɹ�"<<endl;

            //���浽�ļ���
            this->save();
        }
        else {
            cout<<"�޸�ʧ�ܣ����޴���"<<endl;
        }
        system("pause");
        system("cls");
    }
}

//����ְ��
void WorkerManager::Find_Emp() {
    if (this->FileIsEmpty) {
        cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
    }
    else {
        cout<<"��������ҵķ�ʽ:"<<endl;
        cout<<"1����ְ��id����"<<endl;
        cout<<"2������������"<<endl;

        int select=0;
        cin>>select;


        if (select==1) {
            int id;
            cout<<"��������ҵ�ְ��id:"<<endl;
            cin>>id;

            int res=IsExist(id);
            if (res!=-1) {
                cout<<"���ҳɹ�����ְ����Ϣ���£�"<<endl;
                this->Emparray[res]->showInfo();
            }
            else {
                cout<<"����ʧ�ܣ����޴���"<<endl;
            }
        }
        else if (select==2) {
            string name;
            cout<<"��������ҵ�����"<<endl;
            cin>>name;

            bool flag=false;//���ҵ��ı�־
            for (int i=0;i<empnum;i++) {
                if (Emparray[i]->name==name) {
                    cout<<"���ҳɹ���ְ��idΪ��"
                    <<Emparray[i]->id<<"ְ������Ϊ��"<<Emparray[i]->name<<endl;

                    flag=true;

                    this->Emparray[i]->showInfo();
                }
            }
            if (flag==false) {
                //���޴���
                cout<<"����ʧ�ܣ����޴���"<<endl;
            }

        }
        else {
            cout<<"����ѡ������"<<endl;
        }
    }
    system("pause");
    system("cls");
}

//����ְ��
void WorkerManager::Sort_Emp() {
    if (this->FileIsEmpty) {
        cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
    }
    else {
        cout<<"��ѡ������ʽ��"<<endl;
        cout<<"1����ְ��id��������"<<endl;
        cout<<"2����ְ��id���н���"<<endl;

        int select=0;
        cin>>select;
        for (int i=0;i<empnum;i++) {
            int minOrmax=i;
            for (int j=i+1;j<empnum;j++) {
                if (select==1) {//����
                    if (Emparray[minOrmax]->id>Emparray[j]->id) {
                        minOrmax=j;
                    }
                }
                else {//����
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
        cout<<"����ɹ������Ϊ��"<<endl;
        this->save();
        this->Show_Emp();
    }
}

//����ļ�
void WorkerManager::Clean_File() {
    cout<<"�Ƿ�����ļ���"<<endl;
    cout<<"1��ȷ��"<<endl;
    cout<<"2��ȡ��"<<endl;

    int select=0;
    cin>>select;

    if (select==1) {
        //��ģʽios::trunc�������ɾ���ļ������´���
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
        cout<<"��ճɹ�"<<endl;
    }
    system("pause");
    system("cls");
}




void WorkerManager::exitSystem(){
    cout<<"��ӭ�´�ʹ��"<<endl;
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