#pragma once
/*����ݽ�����������*/
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
		static SpeechManager _sm;//��ֻ֤����һ��ȫ�ַ��ʵ�
		return _sm;
	}

	/*�˵���ʾ*/
	void ShowMenu();
	/*��ʼ������*/
	void InitSpeech();
	/*����12��ѡ��*/
	void createSpeaker();
	/*��ʼ����*/
	void startSpeech();
	/*��ǩ*/
	void speechDraw();
	/*����*/
	void speechContest();
	/*��ʾ�������*/
	void showResults();
	/*�������*/
	void saveRecord();
	/*�����¼*/
	void loadRecord();
	/*�鿴�����¼*/
	void showRecord();
	/*��ռ�¼*/
	void clearRecord();
	/*ϵͳ�˳�*/
	void ExitSystem();
public:
	/*��һ�ֱ���ѡ�ֱ��*/
	std::vector<int> vec_1;
	/*�ڶ��ֱ���ѡ�ֱ��*/
	std::vector<int> vec_2;
	/*ʤ��ǰ����ѡ�ֱ������*/
	std::vector<int> vec_victory;
	/*��ű���Լ�����ѡ������*/
	std::map<int, Speaker> sSpeaker;
	/*�������ѡ����Ϣ����*/
	std::map<int, std::vector<std::string>> pastSpeaker;
	/*��������*/
	int contestNum;
	/*�ж��ļ��Ƿ�Ϊ��*/
	bool FileIsEmpty;
private:
	SpeechManager();
	~SpeechManager();
	SpeechManager(const SpeechManager&) = delete; //ɾ���������캯��
	SpeechManager& operator=(const SpeechManager&) = delete; //ɾ����ֵ�����
};

#endif // !

