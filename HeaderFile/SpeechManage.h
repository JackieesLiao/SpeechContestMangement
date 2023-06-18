#pragma once
/*设计演讲比赛管理类*/
#ifndef _SPEECHMANAGER_
#define _SPEECHMANAGER_
#include<iostream>
#include"Speaker.h"
#include<vector>
#include<deque>
#include<map>
#include<string>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
#include<ctime>
#include<cstdint>
using std::cout;
using std::cin;
using std::endl;
class SpeechManager
{
public:
	static SpeechManager& getInstanse()
	{
		static SpeechManager _sm;//保证只创建一个全局访问点
		return _sm;
	}

	/*菜单显示*/
	void ShowMenu();
	/*初始化比赛*/
	void InitSpeech();
	/*创建12名选手*/
	void createSpeaker();
	/*开始比赛*/
	void startSpeech();
	/*抽签*/
	void speechDraw();
	/*比赛*/
	void speechContest();
	/*显示晋级结果*/
	void showResults();
	/*保存分数*/
	void saveRecord();
	/*导入记录*/
	void loadRecord();
	/*查看往届记录*/
	void showRecord();
	/*清空记录*/
	void clearRecord();
	/*系统退出*/
	void ExitSystem();
public:
	/*第一轮比赛选手编号*/
	std::vector<int> vec_1;
	/*第二轮比赛选手编号*/
	std::vector<int> vec_2;
	/*胜出前三名选手编号容器*/
	std::vector<int> vec_victory;
	/*存放编号以及具体选手容器*/
	std::map<int, Speaker> sSpeaker;
	/*往届晋级选手信息容器*/
	std::map<int, std::vector<std::string>> pastSpeaker;
	/*比赛轮数*/
	int contestNum;
	/*判断文件是否为空*/
	bool FileIsEmpty;
private:
	SpeechManager();
	~SpeechManager();
	SpeechManager(const SpeechManager&) = delete; //删除拷贝构造函数
	SpeechManager& operator=(const SpeechManager&) = delete; //删除赋值运算符
};

#endif // !

