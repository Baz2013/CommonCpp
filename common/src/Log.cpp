#include "Log.h"

//using namespace std;

#define DATE_TYPE_LENGTH 8

LOG::LOG()
{
    ;
}
LOG::~LOG()
{
    if (log_file.is_open())
    {
        log_file.close();
    }
}

void    LOG::inital(string& applicationName, int domain){
    setApplication(applicationName, domain);
    
    string localTime = getLoacalTime();
    
    setLoacalTime(localTime);
    
    setLogPath(getenv("PWD"));
    setLogFileName(localTime);
    
    openLogFile();
}

void LOG::inital(const string& applicationName, const int domain){
	int tmp = domain;
	string name = applicationName;
	inital(name,tmp);
}


void LOG::inital(const string& applicationName ){
	int tmp = 0;
	string name = applicationName;
	inital(name,tmp);
}

//ÖØÔØÏÂ insertLog º¯Êý
//add by gucb
void LOG::insertLog(const char *fmt, ...)
{
        va_list args;
        string logtxt;
        char buff[2048];

        memset(buff,0x00,sizeof(buff));
        va_start(args, fmt);
        vsprintf(buff, fmt, args);

        logtxt = buff;
        insertLog(logtxt);
}

void    LOG::insertLog(string logMessage){
    string  localTime = getLoacalTime();
    char    pid[64] = "";
    sprintf(pid, "%d", getpid());
    if (!(strncmp(nowTime.c_str(), localTime.c_str(), DATE_TYPE_LENGTH)))
    {
        if (log_file.is_open())
        {
            log_file << localTime + " [ "  << pid << " ] "<< logMessage;
            log_file << endl;
        }
    }
    else 
    {
        log_file.close();
        setLogFileName(localTime);
        openLogFile();
        if (log_file.is_open())
        {
            log_file << localTime + " [ "  << pid << " ] "<< logMessage;
            log_file << endl;
        }
    }
}


void    LOG::setLogFileName(string localTime){
    logFileName = logPath + "/" + applicationName + "_" + localTime.substr(0, DATE_TYPE_LENGTH) + ".log";
    #ifdef debug
        cout << __LINE__ << ": applicationName: " << applicationName << endl;
        cout << "logFileName is: " << logFileName << endl;
    #endif
}


inline void  LOG::openLogFile(){
    log_file.open(logFileName.c_str(),ios::app);
}

void    LOG::setLogPath(string path){
    logPath = path+"/log";
    #ifdef debug
        cout << "logPath is: " << logPath << endl;
    #endif
}


void    LOG::setApplication(string& applicationName, int domain){
    char tmpDomain[3] = "";
    memset(tmpDomain, 0x00, sizeof(tmpDomain));
    sprintf(tmpDomain, "%d", domain);
    
    #ifdef debug
        cout << "tmpDomain is: " << tmpDomain << endl;
    #endif
    
    this->applicationName = applicationName + "_" + tmpDomain;
    
    #ifdef debug
        cout << "applicationName is: " << applicationName << endl;
    #endif
    
}

string  LOG::getLoacalTime(){
    time_t      timep;
    struct tm   *p;
    char        localTime[32];
    time(&timep);
    p = localtime(&timep);

    //fileName = name + "_" + (1900+p->tm_year) + (1+p->tm_mon) + (p->tm_mday) + (p->tm_hour);
    sprintf(localTime,"%d%02d%02d %02d:%02d:%02d",
        (1900+p->tm_year), (1+p->tm_mon), (p->tm_mday), (p->tm_hour), (p->tm_min), (p->tm_sec));
    
    #ifdef debug
        cout << "localTime is: " << localTime << endl;
    #endif
    return localTime;
}

inline void    LOG::setLoacalTime(string time){
    nowTime = time.substr(0,DATE_TYPE_LENGTH);
    #ifdef debug
        cout << "nowTime is: " << nowTime << endl;
    #endif
}
/*
void    LOG::setLogFileName(string nowTime){
    logFileName = applicationName + "_" + nowTime;
    #ifdef debug
        cout << "logFileName is " << logFileName << endl;
    #endif
}
*/
