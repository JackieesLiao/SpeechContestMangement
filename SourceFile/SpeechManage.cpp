/*
 -----演讲管理------ 
功能：
1. 提供菜单页面给用户交互
2. 对比赛流程进行控制
3. 文件的读写交互

*/
#include<iostream>
#include"Speaker.h"
#include"SpeechManage.h"
using std::cout;
using std::cin;
using std::endl;
void printCurrentTime();
SpeechManager::SpeechManager()
{
	this->InitSpeech();
	
	this->createSpeaker();
	
	this->loadRecord();
}
SpeechManager::~SpeechManager()
{

}
void SpeechManager::ShowMenu()
{
	std::vector<std::string> funcions =
	{
		"\t开始演讲比赛    \t",
		"\t查看往届比赛记录\t",
		"\t清空比赛记录     \t",
		"\t退出比赛程序     \t"

	};
	cout << " \t\t\t-----------------------------Welcome---------------------------- \t\t\t" << endl;
	for (int i=0;i<funcions.size();i++)
	{
		cout <<" \t\t\t\----------------" << i+1<<"."<<funcions[i]<<"---------------- \t\t\t" << endl;
	}
}
void  SpeechManager::InitSpeech()
{
	this->vec_1.clear();
	this->vec_2.clear();
	this->vec_victory.clear();
	this->sSpeaker.clear();
	this->contestNum = 1;
	this->pastSpeaker.clear();

}
void SpeechManager::createSpeaker()
{
	std::string str = "ABCDEFGHIJKL";
	for (int i = 0; i < str.size(); i++)
	{
		std::string speakerName;
		speakerName += str[i];
		Speaker sp;
		sp.m_name = speakerName;
		for (int i = 0; i < 2; i++)
		{
			sp.m_score.push_back(0);
		}
		/*存放12名选手编号*/
		this->vec_1.push_back(i + 10001);

		this->sSpeaker.insert(std::make_pair(i + 10001, sp));
	}
	
}
/*开始比赛*/
 void SpeechManager::startSpeech()
{
	/*第一轮比赛*/
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showResults();

	/*第二轮比赛*/
	this->contestNum++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showResults();
	//4.保存分数到文件中
	this->saveRecord();

	this->InitSpeech();
	this->createSpeaker();
	this->loadRecord();
 //   比赛轮数循环
	//for (int round = 1; round <= 2; round++)
	//{
	//	this->contestNum = round;

	//	// 抽签
	//	this->speechDraw();

	//	// 比赛
	//	this->speechContest();

	//	// 显示晋级结果
	//	this->showResults();

	//	//保存记录

	//	this->saveRecord();
	//}
	printCurrentTime();
	cout << "本届比赛正式结束。" << endl;
	system("pause");
	system("cls");

}
//抽签
void SpeechManager::speechDraw()
{
	cout << "第<<" << this->contestNum << ">>轮比赛" << endl;
	cout << "-------进入抽签>>>>>>>>" << endl;\
	
	cout << "抽签后演讲顺序如下" << endl;
	if (this->contestNum == 1)
	{
		std::random_shuffle(vec_1.begin(), vec_1.end());
		for (auto it1 = vec_1.begin(); it1 != vec_1.end(); it1++)
		{
			cout << *it1 << " ";
		}
		cout << endl;
	}
	else
	{
		std::random_shuffle(vec_2.begin(), vec_2.end());
		for (auto it2 = vec_2.begin(); it2 != vec_2.end(); it2++)
		{
			cout << *it2 << " ";
		}
		cout << endl;
	}
}
/*比赛*/
/*
*  
    创建比赛选手编号容器

	根据比赛轮数进行划分
 
	1.遍历所有比赛选手
	1.1 十名评委打分
    1.2 成绩从大到小排序
	1.3 去除最高分
	1.4 去除最低分
	1.5 求总分再取平均分
*/
void SpeechManager::speechContest()
{
	cout << "第" << this->contestNum << "轮比赛正式开始" << endl;
	std::multimap<double, int,std::greater<double>> groupScores; //存放小组成绩
	std::vector<int> ssp; //选手编号
	int num = 0;//控制小组人数：需要为6
	if (this->contestNum == 1)
	{
		ssp = vec_1;
	}
	else
	{
		ssp = vec_2;
	}
	for (std::vector<int>::iterator itx = ssp.begin(); itx != ssp.end(); itx++)
	{
		num++;
		std::deque<double> d_score;
		for (int i = 0; i < 10; i++)
		{
			double score = (std::rand() % 401 + 600) / 10.f;
		
			d_score.push_back(score);
		}
		std::sort(d_score.begin(), d_score.end(), std::greater<double>());
		d_score.pop_front(); //去除最高分
		d_score.pop_back(); //去除最低分
		double sums = std::accumulate(d_score.begin(), d_score.end(), 0.0f);
		double avg = sums / (double)d_score.size();

		this->sSpeaker[*itx].m_score[this->contestNum - 1] = avg;

		/*cout << "编号：" << *itx << "  姓名:" << this->sSpeaker[*itx].m_name << "    平均分 "<<avg<<endl;*/
		groupScores.insert(std::make_pair(avg,*itx)); //key 得分 value 编号
		if (num%6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (auto it = groupScores.begin(); it != groupScores.end(); it++)
			{
				cout << "编号：" << it->second << "  姓名：" << 
					this->sSpeaker[it->second].m_name << " 成绩:" <<
					this->sSpeaker[it->second].m_score[this->contestNum - 1]<<endl;
		    }
			int count = 0; //取出每组的前三名
			for (auto it = groupScores.begin(); it != groupScores.end()&&count<3; it++,count++)
			{
				if (this->contestNum == 1)
				{
					vec_2.push_back((*it).second);
				}
				else if (this->contestNum == 2)
				{
				   vec_victory.push_back((*it).second);
				}
			}
			groupScores.clear();
		}
	
	}
	cout << endl;
	cout << "第" << this->contestNum << "轮比赛正式结束。" << endl;
    system("pause");
}
/*显示晋级结果*/
 void SpeechManager::showResults()
{
	cout<< "---------第" << this->contestNum << "轮晋级选手信息如下-------" << endl;
	std::vector<int> vec_promotion;
	if (this->contestNum == 1)
	{
		vec_promotion = vec_2;
	}
	else
	{
		vec_promotion = vec_victory;
	}
	/*this->contestNum - 1  是因为比赛就两轮，而下标从0开始*/
	for (auto it = vec_promotion.begin(); it != vec_promotion.end(); it++)
	{
		cout << "编号：" << *it << "  姓名：" << this->sSpeaker[*it].m_name <<
			"  分数:" << this->sSpeaker[*it].m_score[this->contestNum - 1] << endl;
		
	}
	cout << endl;
	system("pause");
	system("cls");
	this->ShowMenu();
}
/*保存分数*/
void SpeechManager::saveRecord()
{
	std::ofstream ofs;
    ofs.open("D:\\Dev\\SpeechContest\\score.csv",  std::ios::app);
	if (ofs.is_open())
	{
		
		/*遍历第二轮晋级选手，将其编号、姓名、分数保存到文件里*/
		for (auto it = vec_victory.begin(); it != vec_victory.end(); it++)
		{
			ofs << *it  << "," <<
				this->sSpeaker[*it].m_score[1]<< ",";
			
		}
		ofs << endl; //必须换行
	    ofs.close();

	    cout << "记录已经保存。" << endl;
	}
	else
	{
		cout << "文件打开失败。" << endl;
	}	
	this->FileIsEmpty = false;//文件创建成功且有记录
	
}
/*导入记录*/
void SpeechManager::loadRecord()
{  
	int index = 0;//届数
	std::ifstream ifs("D:\\Dev\\SpeechContest\\score.csv", std::ios::in);
	if (!ifs.is_open())
	{
		this->FileIsEmpty = true; 
		cout << "文件打开失败。" << endl;
		ifs.close();
		return;
	}
	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->FileIsEmpty = true;
		cout << "文件被清空。" << endl;
		ifs.close();
		return;
	}

	//文件有效
	this->FileIsEmpty = false;
	ifs.putback(ch);//放回取出的ch

	std::string data;//存放读的记录
	/*
	* score.txt 数据样式
	ID:10002,SCORE:86.675 
    ID:10009,SCORE:81.3 
    ID:10007,SCORE:78.55 

	*/
	while (ifs >> data)
	{
		int pos = -1;//查到","的位置，初始为 -1
		int start = 0;//需要读取的字符串首位置
		
		std::vector<std::string> vec_temp_str;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				/*全读完了*/
				break;
			}
			/*
	      substr(start, pos - start);
			
        // return [_Off, _Off + _Count) as new string, default-constructing its allocator
          return basic_string{*this, _Off, _Count};
   
	    //从 data 字符串中提取一个子串。它从 start 索引开始，长度为 pos - start
			*/
		std::string temp_str = data.substr(start, pos - start);
		vec_temp_str.push_back(temp_str);
		
		start = pos + 1; //"," 下一个字符串位置

		}
		/*this->pastSpeaker.insert(std::make_pair(index,vec_temp_str));
		index++;*/
		if (vec_temp_str.size() >= 6)
		{
			try
			{
				float score1 = std::stof(vec_temp_str[1]);
				float score2 = std::stof(vec_temp_str[3]);
				float score3 = std::stof(vec_temp_str[5]);

				vec_temp_str[1] = std::to_string(score1);
				vec_temp_str[3] = std::to_string(score2);
				vec_temp_str[5] = std::to_string(score3);

				this->pastSpeaker.insert(std::make_pair(index, vec_temp_str));
				index++;
			}
			catch (const std::exception& e)
			{
				std::cerr << "转换得分失败: " << e.what() << std::endl;
			}
		}
	}
	
	ifs.close();


}
/*查看往届记录*/
void SpeechManager::showRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或为空。" << endl;
	}
	//map里 key： index  value :  vector<string>
	//for (std::map<int, std::vector<std::string>>::iterator it = this->pastSpeaker.begin(); it != this->pastSpeaker.end(); it++)
	//{
	//	cout << "第" << it->first << "届" ;  // 输出key

	//	for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
	//	{
	//	   /*
	//	   * score.txt 数据样式
	//         ID: 10002, SCORE: 86.675。
	//	   */
	//		int pos = it2->find("ID:"); //pos=0
	//		int start = pos + 3;
	//		int end = it2->find(",");
	//		int id = std::stoi(it2->substr(start, end - start));


	//		start = end + 6;
	//		end = it2->find("。", start);
	//		double score = std::stod(it2->substr(start, end - start));

	//		// 输出ID和SCORE  
	//		cout << "ID:" << id << ", " << "SCORE:" << score << endl;
	//
	//	}
	//}

	
	for (std::map<int, std::vector<std::string>>::iterator it = pastSpeaker.begin(); it != pastSpeaker.end(); ++it)
	{
		cout << "第" << it->first << "届 ";
		std::vector<std::string> values = it->second;
		cout << "冠军编号:" << values[0] << " 得分:" << values[1] << " "
			<< "亚军编号:" << values[2] << " 得分:" << values[3] << " "
			<< "季军编号:" << values[4] << " 得分:" << values[5] << endl;
	}
	
	system("pause");
	system("cls");
}
/*清空记录*/
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		std::ofstream ofs("score.txt", std::ios::trunc);
		ofs.close();

		//初始化属性
		this->InitSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();


		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}
void SpeechManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void printCurrentTime()
{
	// 获取当前时间
	time_t currentTime;
	time(&currentTime);

	// 将时间转换为本地时间
	struct tm localTime;
	localtime_s(&localTime, &currentTime);

	// 提取时间的各个部分
	int year = localTime.tm_year + 1900;  // 年份需要加上 1900
	int month = localTime.tm_mon + 1;     // 月份从 0 开始，需要加上 1
	int day = localTime.tm_mday;          // 日期
	int hour = localTime.tm_hour;         // 小时
	int minute = localTime.tm_min;        // 分钟
	int second = localTime.tm_sec;        // 秒钟

	// 打印当前系统时间
	std::cout << "现在是: " << year << "-" << month << "-" << day << " "
		<< hour << ":" << minute << ":" << second << std::endl;
}
