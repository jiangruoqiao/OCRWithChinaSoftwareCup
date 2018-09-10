#pragma once
//
//  saveData.hpp
//  libcurl
//
//  Created by 蒋若峤 on 2018/5/11.
//  Copyright © 2018年 蒋若峤. All rights reserved.
//
#pragma once
#include <string>
#include <regex>
#include <iostream>


class dataText
{
public:
	std::string temData;
	std::string dataOfJson;
	std::string companyNumber;
	std::string companyName;
	std::string companySytle;
	std::string companyAdress;
	std::string companyHoster;
	std::string companyBuildTime;
	std::string companyBuildMomey;
	std::string companyRunTime;
	std::string companyRunRange;
	std::string companySignIn;
	std::string companyCheckTime;
	std::string companyNameT1;
	std::string companyNumberT1;
	std::string getCompanyNumberT1(void);
	std::string getCompanyNameT1(void);
	std::string getCompanyNumber(void);
	std::string getCompanyName(void);
	std::string getCompanySytle(void);
	std::string getCompanyAdress(void);
	std::string getCompanyHoster(void);
	std::string getCompanyBuildTime(void);
	std::string getCompanyBuildMomey(void);
	std::string getCompanyRunTime(void);
	std::string getCompanyRunRange(void);
	std::string getCompanySignIn(void);
	std::string getCompanyCheckTime(void);
};
/* saveData_hpp */