// ##########################################
// Source file : ParseConf.cpp
// System      : 公共函数-配置文件解析
// Version     : V1.0
// Language    : ANSI C++
// OS Platform : IBM AIX 6.1
// Authors     : Smart Group
// E_mail      : ligm@sdcncsi.com.cn
// Create      : 20140128
// Update      : 20140128
// Copyright(C): Smart Group
// ##########################################


#ifndef _PARSE_CONF_H_
#define _PARSE_CONF_H_

/*
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fstream>
*/

#include "common.h"
using namespace std;

typedef map<string, string> ResultMap;
typedef vector<string> ResultVector;



class ParseConf
{
  public:
    ParseConf();
	//ParseConf(string file_name);
    ~ParseConf();
    
    //设置当前节点名称
    void    setSection(string section_name);
    
    //扫描节点，经解析节点中对应的值
    bool    scanSection(ResultMap& value);
    
    //判断是不是节点开始
    bool    sectionBegin(char* str);
    
    //判断是不是节点结束
    bool    sectionEnd(char* str);

	//设置配置文件名称
    bool    setConfName(string file_name);
      
    //配置文件名称
    string  conf_name;
  private:
    //根据解析buffer中的值，并将解析后结果放到 value 中
    bool    getValue(const string& buffer, ResultMap& value);
    
    //节点名称
    string  section_name;
    
    //string 类型trim函数
    void    trimString(string& str);
    
    //资费类型trim函数
    int     trim(char* str);
};

#endif
