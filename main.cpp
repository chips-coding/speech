#include <iostream>

#include "ctime"
using namespace std;

#include "SpeechManager.h"

int main() {
    //���������
    srand((unsigned int) time(NULL));
    //�������������
    SpeechManager sm;

/*    //����12������
    for (map<int, Speaker>::iterator it = sm.m_Speaker.begin();it != sm.m_Speaker.end(); it++) {
        cout << "ѡ������" << it->first << "������ " << it->second.m_Name << "������ " << it->second.m_Score[0] << endl;
    }*/
    int choice = 0; //���ڴ洢�û�����
    while (true) {
        sm.show_Menu();
        cout << "����������ѡ��:" << endl;
        cin >> choice;

        switch (choice) {
            case 1: //��ʼ����
                sm.startSpeech();
                break;
            case 2: //�鿴���������¼
                sm.showRecord();
                break;
            case 3: //��ձ�����¼
                sm.clearRecord();
                break;
            case 0: //�˳�ϵͳ
                sm.exitSystem();
                break;
            default:
                system("cls"); //����
                break;

        }
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
