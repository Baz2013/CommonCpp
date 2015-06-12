#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<sstream>
#include<cstring>
#include<cstdio>

using namespace std;

class StringUtil {

    public:
        static int command(const string &cmd ,     //命令
                    vector<string> &lines          //命令输出行
                );

        static string pad(const char *str,         //源字符串
                          const int length,        //预期长度
                          const char *stuff = " ", //要填充的字符
                          const bool left = true   //是否在左边填充(反之在右边)
                );

        static bool replace(string &in,               //源字符串
                            const string &search,     //查找字符串
                            const string &replacement //
                );

        static string replace(const string &in,         //源字符串
                              const string &search,     //查找字符串
                              const string &replacement //替换字符串
                );

        static size_t split(const string &str,       //源字符串
                            const string &delim,     //分隔符
                            vector<string> &result,  //处理结果
                            bool needTrim            //是否去掉空格
                );
        static string & ltrim(string &str);
        static string & rtrim(string &str);
        static string & trim(string &str);

        static int eraseChar(char *str,          //待处理字符串
                             const char &ch      //要删除的字符
                );
        static int eraseChar(string &str,          //待处理字符串
                             const char &ch      //要删除的字符
                );
        static string & toUpperCase(string &str); //将字符串中的字母转换成大写
        static string & toLowerCase(string &str);

        static bool equalsIgnoreCase(const string str1,const string str2);

        static string repeat(const int count,const string &ch);

        static int lalign(char *str,    //待处理字符串
                            const int strlength,    //处理的长度
                            const char stuff = ' '
                        );

        static int rtrim(char *str);
        static int ltrim(char *str);
        static int trim(char *str);
        static char * trim(const char *str);

        static string number2str(int number);
        static string number2str(float number);
        static string number2str(double number);
        static string charToString(const char *ch);
};

#endif
