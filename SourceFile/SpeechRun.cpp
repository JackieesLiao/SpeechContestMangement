#include<iostream>
#include"SpeechManage.h"
using std::cout;
using std::cin;
using std::endl;
int choice = 0;
int main()
{
	// 设置随机数种子为当前时间
	srand(static_cast<unsigned int>(time(0)));
	/*初始化*/
	SpeechManager::getInstanse().InitSpeech();
	SpeechManager::getInstanse().createSpeaker();
	SpeechManager::getInstanse().loadRecord();
	/*for (auto it = SpeechManager::getInstanse().sSpeaker.begin();
		it != SpeechManager::getInstanse().sSpeaker.end(); it++)
	{
		cout << "选手编号：" << it->first << " 选手姓名" << it->second.m_name<<" 分数1："<<it->second.m_score[0] <<endl;
	}*/
	while (true)
	{
       SpeechManager::getInstanse().ShowMenu();
	   cout << "请输入您的选择：" ;

	   cin >> choice;
	   switch (choice)
	   {
	   case 1:
		   SpeechManager::getInstanse().startSpeech();
		   break;
	   case 2:
		   SpeechManager::getInstanse().showRecord();
		   break;
	   case 3:
		   SpeechManager::getInstanse().clearRecord();
		   break;
	   case 4:
		   SpeechManager::getInstanse().ExitSystem();
		   break;
	   default:
		   system("cls");
		   break;
	   }


	}

	return 0;
}