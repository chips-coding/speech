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


    //初始化容器和属性
    void initSpeech();

    //创建12名选手
    void createSpeaker();

    //开始比赛 比赛整个流程控制函数
    void startSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //显示得分
    void showScore();

    //保存分数
    void saveRecord();

    //读取记录
    void loadRecord();

    //显示往届得分
    void showRecord();

    //清空记录
    void clearRecord();
    ~SpeechManager();

    //判断文件是否为空
    bool fileIsEmpty;

    //存放往届记录的容器
    map<int, vector<string>> m_Record;





    //成员属性
    //保存第一轮比赛选手编号容器
    vector<int> v1;

    //第一轮晋级选手编号容器
    vector<int> v2;

    //胜出前三名选手编号容器
    vector<int> vVictory;

    //存放编号以及对应具体选手容器
    map<int, Speaker> m_Speaker;

    //存放比赛轮数
    int m_Index;


};


#endif //SPEECH_SPEECHMANAGER_H
