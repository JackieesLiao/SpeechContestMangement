#pragma once
/*设计选手类*/
#ifndef _SPEAKER_
#define _SPEAKER_
#include<iostream>
#include<vector>
#include<string>
using std::cout;
using std::cin;
using std::endl;
class Speaker
{
public:

	std::string m_name;
	std::vector<double> m_score;
};

#endif
