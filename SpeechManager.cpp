//
// Created by Administrator on 2023/1/17.
//

#include "SpeechManager.h"


using namespace std;

SpeechManager::SpeechManager() {
    //初始化容器属性
    this->initSpeech();

    //创建12名选手
    this->createSpeaker();

    //加载往届记录
    this->loadRecord();
}

void SpeechManager::show_Menu() {
    cout << "************************" << endl;
    cout << "*****欢迎参加演讲比赛******" << endl;
    cout << "******1.开始演讲比赛******" << endl;
    cout << "******2.查看往届记录******" << endl;
    cout << "******3.清空比赛记录******" << endl;
    cout << "******0.退出比赛程序******" << endl;
    cout << "************************" << endl;
    cout << endl;
}

void SpeechManager::exitSystem() {
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

void SpeechManager::initSpeech() {
    //容器都置空
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();

    //初始化比赛轮数
    this->m_Index = 1;

    //将记录的容器也清空
    this->m_Record.clear();


}

void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++) {
        string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.m_Name = name;

        for (int j = 0; j < 2; j++) {
            sp.m_Score[j] = 0;
        }

        //创建选手编号，并且放入到v1容器中
        this->v1.push_back(i + 10001);

        //选手编号以及对应选手放入map容器中
        this->m_Speaker.insert(make_pair(i + 10001, sp));
    }
}

void SpeechManager::startSpeech() {

    //第一轮开始比赛

    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示晋级结果
    this->showScore();
    //第二轮开始比赛
    this->m_Index++;
    //1、抽签
    this->speechDraw();
    //2、比赛
    this->speechContest();
    //3、显示晋级结果
    this->showScore();

    //4.保存分数到文件中
    this->saveRecord();

    //重置比赛，获取记录
    //初始化容器和属性
    this->initSpeech();

    //创建12名选手
    this->createSpeaker();

    //加载往届记录
    this->loadRecord();

    cout << "本届比赛完毕！" << endl;
    system("pause");
    system("cls");

}

void SpeechManager::speechDraw() {
    cout << "第<<" << this->m_Index << ">> 轮比赛选手正在抽签 " << endl;
    cout << "--------------------" << endl;
    cout << "抽签后演讲顺序如下：" << endl;

    if (this->m_Index == 1) {
        //第一轮比赛
        random_shuffle(v1.begin(), v1.end());
        for (int &it: v1) {
            cout << it << " ";
        }
        cout << endl;
    } else {
        //第二轮比赛
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
    cout << "------------第" << this->m_Index << "轮比赛正式开始--------" << endl;

    //准备临时容器，存放小组成绩
    multimap<double, int, greater<double>> groupScore;

    int num = 0; //记录人员个数 6人一组

    vector<int> v_Src; //比赛选手容器
    if (this->m_Index == 1) {
        v_Src = v1;
    } else {
        v_Src = v2;
    }

    //遍历所有选手进行比赛
    for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
        num++;
        //评委打分
        deque<double> d;
        for (int i = 0; i < 10; i++) {
            double score = ((rand() % 401 + 600)) / 10.f; //60~100

            //cout << score << " "; 测试
            d.push_back(score);
        }
        //cout << endl; 测试

        //降序排序
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front(); //去除最高分
        d.pop_back(); //去除最低分

        double sum = accumulate(d.begin(), d.end(), 0.0f); //0.0f表示从0.0（double型）开始加
        double avg = sum / (double) d.size();

        //打印平均分
        // cout << "编号：" << *it << "姓名：" << this->m_Speaker[*it].m_Name << "获取平均分：" << avg << endl;

        //将平均分放到map容器里
        //*it是vector<int>元素，所以*it代表int型的key
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

        //将打分数据放入到临时小组容器中
        groupScore.insert(make_pair(avg, *it)); //key是得分，value是具体选手编号
        //每6人取出前三名
        if (num % 6 == 0) {
            cout << "第" << num / 6 << "小组比赛名次：" << endl;
            for (multimap<double, int, greater<double>>::iterator itd = groupScore.begin();
                 itd != groupScore.end(); itd++) {
                cout << "编号：" << itd->second << "姓名：" << this->m_Speaker[itd->second].m_Name << "成绩："
                     << this->m_Speaker[itd->second].m_Score[this->m_Index - 1] << endl;
            }

            //取走前三名
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator itm = groupScore.begin();
                 itm != groupScore.end() && count < 3; itm++, count++) {
                if (this->m_Index == 1) {
                    v2.push_back(itm->second);
                } else {
                    vVictory.push_back(itm->second);
                }
            }
            groupScore.clear(); //小组容器清空
            cout << endl;
        }
    }
    cout << "---------第" << this->m_Index << "轮比赛完毕----------" << endl;
    system("pause");

}

void SpeechManager::showScore() {
    cout << "-------------第" << this->m_Index << "轮晋级选手信息-------------" << endl;

    vector<int> v;
    if (this->m_Index == 1) {
        v = v2;
    } else {
        v = vVictory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << "选手编号：" << *it
             << "姓名：" << this->m_Speaker[*it].m_Name
             << "得分：" << this->m_Speaker[*it].m_Score[m_Index - 1] << endl;
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

    //关闭
    ofs.close();
    cout << "记录已保存" << endl;

    //更改文件不为空状态
    this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {
    ifstream ifs("speech.csv", ios::in); //读文件

    if (!ifs.is_open()) {
        this->fileIsEmpty = true;
//        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    //文件清空情况
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
//        cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch); //将上面读取的单个字符 放回来 ；没有这一句将损失一个字符

    string data;
    int index = 0;

    while (ifs >> data) {

        vector<string> v; //存放6个人的字符串

        int pos = -1; //查到，","位置的变量
        int start = 0;

        while (true) {
            pos = data.find(",", start);
            if (pos == -1) {
                //没有找到情况
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
        cout << "文件为空或不存在" << endl;
    } else {
        for (int i = 0; i < this->m_Record.size(); i++) {
            cout << "第" << i + 1 << "届 " <<
                 "冠军编号 " << this->m_Record[i][0] << "得分 " << this->m_Record[i][1] << " "
                  "亚军编号 "<< this->m_Record[i][2] << "得分 " << this->m_Record[i][3] << " "
                  "季军编号 " << this->m_Record[i][4] << "得分 "<< this->m_Record[i][5] << endl;
        }
    }

    system("pause");
    system("cls");
}

void SpeechManager::clearRecord() {
    cout << "确认清空？" << endl;
    cout << "1、确认" << endl;
    cout << "2、返回" << endl;

    int select = 0;
    cin >> select;

    if (select == 1) {
        //打开模式ios::trunc 如果存在删除文件并重新创建
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        //初始化属性
        this->initSpeech();

        //创建选手
        this->createSpeaker();

        //获取往届记录
        this->loadRecord();

        cout << "清空成功！" << endl;
    }
    system("pause");
    system("cls");
}

SpeechManager::~SpeechManager() {

}
















