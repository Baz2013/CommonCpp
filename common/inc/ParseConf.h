// ##########################################
// Source file : ParseConf.cpp
// System      : ��������-�����ļ�����
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
    
    //���õ�ǰ�ڵ�����
    void    setSection(string section_name);
    
    //ɨ��ڵ㣬�������ڵ��ж�Ӧ��ֵ
    bool    scanSection(ResultMap& value);
    
    //�ж��ǲ��ǽڵ㿪ʼ
    bool    sectionBegin(char* str);
    
    //�ж��ǲ��ǽڵ����
    bool    sectionEnd(char* str);

	//���������ļ�����
    bool    setConfName(string file_name);
      
    //�����ļ�����
    string  conf_name;
  private:
    //���ݽ���buffer�е�ֵ���������������ŵ� value ��
    bool    getValue(const string& buffer, ResultMap& value);
    
    //�ڵ�����
    string  section_name;
    
    //string ����trim����
    void    trimString(string& str);
    
    //�ʷ�����trim����
    int     trim(char* str);
};

#endif
