//
// Created by Administrator on 2023/1/17.
//

#include "SpeechManager.h"


using namespace std;

SpeechManager::SpeechManager() {
    //��ʼ����������
    this->initSpeech();

    //����12��ѡ��
    this->createSpeaker();

    //���������¼
    this->loadRecord();
}

void SpeechManager::show_Menu() {
    cout << "************************" << endl;
    cout << "*****��ӭ�μ��ݽ�����******" << endl;
    cout << "******1.��ʼ�ݽ�����******" << endl;
    cout << "******2.�鿴�����¼******" << endl;
    cout << "******3.��ձ�����¼******" << endl;
    cout << "******0.�˳���������******" << endl;
    cout << "************************" << endl;
    cout << endl;
}

void SpeechManager::exitSystem() {
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}

void SpeechManager::initSpeech() {
    //�������ÿ�
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();

    //��ʼ����������
    this->m_Index = 1;

    //����¼������Ҳ���
    this->m_Record.clear();


}

void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++) {
        string name = "ѡ��";
        name += nameSeed[i];

        Speaker sp;
        sp.m_Name = name;

        for (int j = 0; j < 2; j++) {
            sp.m_Score[j] = 0;
        }

        //����ѡ�ֱ�ţ����ҷ��뵽v1������
        this->v1.push_back(i + 10001);

        //ѡ�ֱ���Լ���Ӧѡ�ַ���map������
        this->m_Speaker.insert(make_pair(i + 10001, sp));
    }
}

void SpeechManager::startSpeech() {

    //��һ�ֿ�ʼ����

    //1����ǩ
    this->speechDraw();
    //2������
    this->speechContest();
    //3����ʾ�������
    this->showScore();
    //�ڶ��ֿ�ʼ����
    this->m_Index++;
    //1����ǩ
    this->speechDraw();
    //2������
    this->speechContest();
    //3����ʾ�������
    this->showScore();

    //4.����������ļ���
    this->saveRecord();

    //���ñ�������ȡ��¼
    //��ʼ������������
    this->initSpeech();

    //����12��ѡ��
    this->createSpeaker();

    //���������¼
    this->loadRecord();

    cout << "���������ϣ�" << endl;
    system("pause");
    system("cls");

}

void SpeechManager::speechDraw() {
    cout << "��<<" << this->m_Index << ">> �ֱ���ѡ�����ڳ�ǩ " << endl;
    cout << "--------------------" << endl;
    cout << "��ǩ���ݽ�˳�����£�" << endl;

    if (this->m_Index == 1) {
        //��һ�ֱ���
        random_shuffle(v1.begin(), v1.end());
        for (int &it: v1) {
            cout << it << " ";
        }
        cout << endl;
    } else {
        //�ڶ��ֱ���
        random_shuffle(v2.begin(), v2.end());
        for (int &it: v2) {
            cout << it << " ";
        }
        cout << endl;
    }


    cout << "----------------" << endl;
    system("pause");
    cout << endl;
}

void SpeechManager::speechContest() {
    cout << "------------��" << this->m_Index << "�ֱ�����ʽ��ʼ--------" << endl;

    //׼����ʱ���������С��ɼ�
    multimap<double, int, greater<double>> groupScore;

    int num = 0; //��¼��Ա���� 6��һ��

    vector<int> v_Src; //����ѡ������
    if (this->m_Index == 1) {
        v_Src = v1;
    } else {
        v_Src = v2;
    }

    //��������ѡ�ֽ��б���
    for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
        num++;
        //��ί���
        deque<double> d;
        for (int i = 0; i < 10; i++) {
            double score = ((rand() % 401 + 600)) / 10.f; //60~100

            //cout << score << " "; ����
            d.push_back(score);
        }
        //cout << endl; ����

        //��������
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front(); //ȥ����߷�
        d.pop_back(); //ȥ����ͷ�

        double sum = accumulate(d.begin(), d.end(), 0.0f); //0.0f��ʾ��0.0��double�ͣ���ʼ��
        double avg = sum / (double) d.size();

        //��ӡƽ����
        // cout << "��ţ�" << *it << "������" << this->m_Speaker[*it].m_Name << "��ȡƽ���֣�" << avg << endl;

        //��ƽ���ַŵ�map������
        //*it��vector<int>Ԫ�أ�����*it����int�͵�key
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

        //��������ݷ��뵽��ʱС��������
        groupScore.insert(make_pair(avg, *it)); //key�ǵ÷֣�value�Ǿ���ѡ�ֱ��
        //ÿ6��ȡ��ǰ����
        if (num % 6 == 0) {
            cout << "��" << num / 6 << "С��������Σ�" << endl;
            for (multimap<double, int, greater<double>>::iterator itd = groupScore.begin();
                 itd != groupScore.end(); itd++) {
                cout << "��ţ�" << itd->second << "������" << this->m_Speaker[itd->second].m_Name << "�ɼ���"
                     << this->m_Speaker[itd->second].m_Score[this->m_Index - 1] << endl;
            }

            //ȡ��ǰ����
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator itm = groupScore.begin();
                 itm != groupScore.end() && count < 3; itm++, count++) {
                if (this->m_Index == 1) {
                    v2.push_back(itm->second);
                } else {
                    vVictory.push_back(itm->second);
                }
            }
            groupScore.clear(); //С���������
            cout << endl;
        }
    }
    cout << "---------��" << this->m_Index << "�ֱ������----------" << endl;
    system("pause");

}

void SpeechManager::showScore() {
    cout << "-------------��" << this->m_Index << "�ֽ���ѡ����Ϣ-------------" << endl;

    vector<int> v;
    if (this->m_Index == 1) {
        v = v2;
    } else {
        v = vVictory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "ѡ�ֱ�ţ�" << *it
             << "������" << this->m_Speaker[*it].m_Name
             << "�÷֣�" << this->m_Speaker[*it].m_Score[m_Index - 1] << endl;
    }

    cout << endl;
    system("pause");
    system("cls");
    this->show_Menu();
}


void SpeechManager::saveRecord() {
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";

    }
    ofs << endl;

    //�ر�
    ofs.close();
    cout << "��¼�ѱ���" << endl;

    //�����ļ���Ϊ��״̬
    this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {
    ifstream ifs("speech.csv", ios::in); //���ļ�

    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
//        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    //�ļ�������
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
//        cout << "�ļ�Ϊ��" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //�ļ���Ϊ��
    this->fileIsEmpty = false;
    ifs.putback(ch); //�������ȡ�ĵ����ַ� �Ż��� ��û����һ�佫��ʧһ���ַ�

    string data;
    int index = 0;

    while (ifs >> data) {

        vector<string> v; //���6���˵��ַ���

        int pos = -1; //�鵽��","λ�õı���
        int start = 0;

        while (true) {
            pos = data.find(",", start);
            if (pos == -1) {
                //û���ҵ����
                break;
            }
            string temp = data.substr(start, pos - start);
            v.push_back(temp);
//            cout << temp << endl;
            start = pos + 1;
        }
        this->m_Record.insert(make_pair(index, v));
        index++;
    }
    ifs.close();
}

void SpeechManager::showRecord() {
    if (this->fileIsEmpty) {
        cout << "�ļ�Ϊ�ջ򲻴���" << endl;
    } else {
        for (int i = 0; i < this->m_Record.size(); i++) {
            cout << "��" << i + 1 << "�� " <<
                 "�ھ���� " << this->m_Record[i][0] << "�÷� " << this->m_Record[i][1] << " "
                  "�Ǿ���� "<< this->m_Record[i][2] << "�÷� " << this->m_Record[i][3] << " "
                  "������� " << this->m_Record[i][4] << "�÷� "<< this->m_Record[i][5] << endl;
        }
    }

    system("pause");
    system("cls");
}

void SpeechManager::clearRecord() {
    cout << "ȷ����գ�" << endl;
    cout << "1��ȷ��" << endl;
    cout << "2������" << endl;

    int select = 0;
    cin >> select;

    if (select == 1) {
        //��ģʽios::trunc �������ɾ���ļ������´���
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //��ʼ������
        this->initSpeech();

        //����ѡ��
        this->createSpeaker();

        //��ȡ�����¼
        this->loadRecord();

        cout << "��ճɹ���" << endl;
    }
    system("pause");
    system("cls");
}

SpeechManager::~SpeechManager() {

}
















