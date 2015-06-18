#ifndef _LOG_H_
#define _LOG_H_

/*
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
*/

#include "common.h"

using namespace std;

class LOG
{
  public:
    LOG();
    ~LOG();
    
    void    inital(string& applicationName, int domain);
    void    inital(const string& applicationName,const int domain);
    void    inital(const string& applicationName);
    void    insertLog(string logMessgae);
    void    setLogPath(string path);
    void    setApplication(string& applicationName, int domain);
    void    insertLog(const char *fmt, ...); //gucb add 2015-03-09
  private:
    string      getLoacalTime();
    inline void setLoacalTime(string time);
    inline void openLogFile();
    void        getLogFileName();
    void        setLogFileName(string localTime);
    
    string      applicationName;
    string      logPath;
    string      logFileName;
    string      nowTime;
    string      logTime;
    ofstream    log_file;
};

#endif
