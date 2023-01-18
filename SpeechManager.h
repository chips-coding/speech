//
// Created by Administrator on 2023/1/17.
//

#ifndef SPEECH_SPEECHMANAGER_H
#define SPEECH_SPEECHMANAGER_H

#include <iostream>

using namespace std;

#include <string>
#include <vector>
#include <map>
#include "Speaker.h"
#include "algorithm"
#include "deque"
#include "functional"
#include "numeric"
#include "fstream"

class SpeechManager {
public:

    SpeechManager();

    void show_Menu();

    void exitSystem();


    //��ʼ������������
    void initSpeech();

    //����12��ѡ��
    void createSpeaker();

    //��ʼ���� �����������̿��ƺ���
    void startSpeech();

    //��ǩ
    void speechDraw();

    //����
    void speechContest();

    //��ʾ�÷�
    void showScore();

    //�������
    void saveRecord();

    //��ȡ��¼
    void loadRecord();

    //��ʾ����÷�
    void showRecord();

    //��ռ�¼
    void clearRecord();
    ~SpeechManager();

    //�ж��ļ��Ƿ�Ϊ��
    bool fileIsEmpty;

    //��������¼������
    map<int, vector<string>> m_Record;





    //��Ա����
    //�����һ�ֱ���ѡ�ֱ������
    vector<int> v1;

    //��һ�ֽ���ѡ�ֱ������
    vector<int> v2;

    //ʤ��ǰ����ѡ�ֱ������
    vector<int> vVictory;

    //��ű���Լ���Ӧ����ѡ������
    map<int, Speaker> m_Speaker;

    //��ű�������
    int m_Index;


};


#endif //SPEECH_SPEECHMANAGER_H
