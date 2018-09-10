//
//  saveData.cpp
//  libcurl
//
//  Created by Ruoqiao Jiang on 2018/5/11.
//  Copyright © 2018年 Ruoqiao Jiang. All rights reserved.
//
#include "stdafx.h"
#include "saveData.h"
#include <string>
#include <regex>
#include <iostream>


std::string dataText::getCompanyNumberT1(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u53f7)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyNumberT1 = m.format("$2");
	}
	return companyNumberT1;
}

std::string dataText::getCompanyNumber(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u53f7:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyNumber = m.format("$2");
	}
	return companyNumber;
}

std::string dataText::getCompanyNameT1(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u79f0)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyNameT1 = m.format("$2");
	}
	return companyNameT1;
}

std::string dataText::getCompanyName(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u79f0:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyName = m.format("$2");
	}
	return companyName;
}

std::string dataText::getCompanySytle(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u578b:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companySytle = m.format("$2");
	}
	return companySytle;
}

std::string dataText::getCompanyAdress(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u6240:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyAdress = m.format("$2");
	}
	return companyAdress;
}

std::string dataText::getCompanyHoster(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u4eba:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyHoster = m.format("$2");
	}
	return companyHoster;
}

std::string dataText::getCompanyBuildTime(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u95f4:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyBuildTime = m.format("$2");
	}
	return companyBuildTime;
}

std::string dataText::getCompanyBuildMomey(void)
{
	//    temData = dataOfJson;
	std::smatch m;
	std::regex e("(\u672c:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyBuildMomey = m.format("$2");
	}
	return companyBuildMomey;
}

std::string dataText::getCompanyRunTime(void)
{
	temData = dataOfJson;
	std::cout << temData << std::endl;
	std::smatch m;
	std::regex e("(\u9650:)([^ ]*?)(\n\n)");
	while (std::regex_search(temData, m, e))
	{
		for (auto x = m.begin(); x != m.end(); x++)
		{
			//            std::cout << x->str() << " r";
		}
		//        std::cout << "--> ([^ ]*) match " << m.format("$2") <<std::endl;
		temData = m.suffix().str();
		companyRunTime = m.format("$2");
	}
	return companyRunTime;
}

//现在不改
std::string dataText::getCompanyRunRange(void)
{
	std::smatch m;
	std::regex e("(\u56f4:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companyRunRange = m.format("$2");
	}
	return companyRunRange;
}

std::string dataText::getCompanySignIn(void)
{
	std::smatch m;
	std::regex e("(\u5173:)([^ ]*?)(\n\n)");
	if (std::regex_search(dataOfJson, m, e))
	{
		companySignIn = m.format("$2");
	}
	return companySignIn;
}

std::string dataText::getCompanyCheckTime(void)
{
	std::smatch m;
	std::regex e("(\u95f4:)([^ ]*?)(\n\n)");
	while (std::regex_search(dataOfJson, m, e))
	{
		for (auto x = m.begin(); x != m.end(); x++)
		{
			//            std::cout << x->str() << " r";
		}
		//        std::cout << "--> ([^ ]*) match " << m.format("$2") <<std::endl;
		dataOfJson = m.suffix().str();
		companyCheckTime = m.format("$2");
	}
	return companyCheckTime;
}
