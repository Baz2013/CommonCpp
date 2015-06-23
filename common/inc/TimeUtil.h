#ifndef __TIMEUTIL_H__
#define __TIMEUTIL_H__

#include "common.h"

using namespace std;


/**
 * @class TimeUtil
 *
 * @brief 时间计算的工具类
 */


class TimeUtil {

  public:

	/**
	 * 返回当前时间
	 *
	 * @return 当前时间的长整型表示
	 */
	static long now() {
	  time_t n ; time(&n); return n;
	};

	/**
	 *  返回带毫秒的格式化时间字符串
	 *
	 * @param dt_YYYYMMDDHHmmSSsss
	 *               返回的格式化字符串
	 * @param mytime 要格式化的时间，缺省为当前时间
	 *
	 * @return 返回相应的时间
	 */
	static long now(char *dt_YYYYMMDDHHmmSSsss,const time_t mytime = 0) {
	    // 得到带毫秒开始处理时间
      struct tm *w;
      struct timeval  first;
      struct timezone tzp;
      time_t now = mytime;
      if (mytime ==0)
        time(&now);

      w = localtime(&now);

      gettimeofday(&first,&tzp);

      sprintf(dt_YYYYMMDDHHmmSSsss, "%4d%02d%02d%02d%02d%02d%03d",
         w->tm_year + 1900,w->tm_mon + 1, w->tm_mday,
         w->tm_hour, w->tm_min, w->tm_sec,
         first.tv_usec/1000);
	    ;
	    return now;
	};



	/// 相对当前的时间流逝量
	/// @param dt_YYYYMMDDHHmmSS 表示的时间字符串
	/// @return 流逝的秒数
	static long elapsed(const char *dt_YYYYMMDDHHmmSS) {
	  struct tm t;
	  time_t t1,t2;
	  char tmp[10];

	  time(&t1);

	  memcpy(tmp,dt_YYYYMMDDHHmmSS,4   );  tmp[4]=0;  t.tm_year=atoi(tmp)-1900;
	  memcpy(tmp,dt_YYYYMMDDHHmmSS+4,2 );  tmp[2]=0;  t.tm_mon =atoi(tmp)-1;
	  memcpy(tmp,dt_YYYYMMDDHHmmSS+6,2 );  tmp[2]=0;  t.tm_mday=atoi(tmp);
	  memcpy(tmp,dt_YYYYMMDDHHmmSS+8,2 );  tmp[2]=0;  t.tm_hour=atoi(tmp);
	  memcpy(tmp,dt_YYYYMMDDHHmmSS+10,2);  tmp[2]=0;  t.tm_min =atoi(tmp);
	  memcpy(tmp,dt_YYYYMMDDHHmmSS+12,2);  tmp[2]=0;  t.tm_sec =atoi(tmp);

	  t.tm_isdst = -1;
	  t2=mktime(&t);

	  return (long)(difftime(t1,t2)/(60));
	};


	/// 流逝的时间
	/// @param end 截至时间 mmSS (HHmm)
	/// @param start 开始时间 mmSS (HHmm)
	/// @return 秒数(分钟数)
	static long elapsed(long start,long end){
	   long b,e;
	   b=long(start/100);
	   e=long(end/100);
	   return (b*60+start-b*100)-(e*60+end-e*100);
	};

	/// 流逝的时间
	/// @param end 截至时间 mmSS (HHmm)
	/// @param start 开始时间 mmSS (HHmm)
	/// @return 格式化成 mmSS (HHmm)
	static long formatElapsed(long start,long end) {
	   long m=elapsed(start,end);
	   return long(m/60)*100+(m-long(m/60)*60);
	};


	/// 今日已经流逝的时间(分钟表示)
	/// @return 返回分钟数
	static long elapsed() {
	  time_t now;
	  struct tm  *w;
	  char buffer[5];
	  long formal_value;
	  time(&now);
	  w=localtime(&now);
	  sprintf(buffer,"%02d%02d",w->tm_hour,w->tm_min);
	  formal_value = atol(buffer);
	  return (long)((formal_value/100)*60+formal_value%100);
	};


	/// 时间字符串加秒数
	/// @param t_YYYYMMDDHHmmSS 得到的
	/// @param s_YYYYMMDDHHmmSS 起始时间的字符串
	/// @param offset 偏移秒数
	/// @return 目标时间字符串的长度
	static const int addSeconds(char *t_YYYYMMDDHHmmSS,
	                            const char *s_YYYYMMDDHHmmSS,
	                            const long offset
	                            ){
	  struct tm t;
	  time_t t2;
	  char tmp[25];

	  memcpy(tmp,s_YYYYMMDDHHmmSS,4);     tmp[4]=0;  t.tm_year =atoi(tmp)-1900;
	  memcpy(tmp,s_YYYYMMDDHHmmSS+4,2);   tmp[2]=0;  t.tm_mon  =atoi(tmp)-1;
	  memcpy(tmp,s_YYYYMMDDHHmmSS+6,2);   tmp[2]=0;  t.tm_mday =atoi(tmp);
	  memcpy(tmp,s_YYYYMMDDHHmmSS+8,2);   tmp[2]=0;  t.tm_hour =atoi(tmp);
	  memcpy(tmp,s_YYYYMMDDHHmmSS+10,2);  tmp[2]=0;  t.tm_min  =atoi(tmp);
	  memcpy(tmp,s_YYYYMMDDHHmmSS+12,2);  tmp[2]=0;  t.tm_sec  =atoi(tmp);
	  t.tm_isdst = -1;  t2=mktime(&t);

	  t2 += offset;
	  t = *(localtime(&t2));

	  sprintf(t_YYYYMMDDHHmmSS,"%04d%02d%02d%02d%02d%02d\0",
	          t.tm_year+1900, t.tm_mon+1, t.tm_mday,
	          t.tm_hour,t.tm_min,t.tm_sec);

	  return strlen(t_YYYYMMDDHHmmSS);
	};



	/// 时间字符串加天数
	/// @param t_YYYYMMDD 得到的
	/// @param s_YYYYMMDD 起始时间的字符串
	/// @param offset 偏移天数
	/// @return 目标字符串地址
	static const int addDays(char *t_YYYYMMDD,
	                         const char *s_YYYYMMDD,
	                         long offset
	                         ){
	  char buffer[256]; memset(buffer,0,sizeof(buffer));
	  strncpy(buffer,s_YYYYMMDD,8);
	  strncpy(buffer+8,"000000",6);

	  addSeconds(t_YYYYMMDD,buffer,offset*3600*24);
	  t_YYYYMMDD[8]=0;

	  return strlen(t_YYYYMMDD);
	};



	/// 取到当前日期字符串
	/// @param d_YYYYMMDD 得到时间格式'YYYYMMDD'
	static int date(char * d_YYYYMMDD) {
	  time_t now;
	  struct tm  *w;
	  time(&now);
	  w=localtime(&now);
	  return sprintf(d_YYYYMMDD,"%04d%02d%02d",
	    w->tm_year+1900,w->tm_mon+1,w->tm_mday);
	};


	/// 取到当前日期字符串
	/// @param d_YYYYMM 得到时间格式'YYYYMM'
	static int month(char * d_YYYYMM) {
	  char buffer[256];
	  memset(buffer,0,sizeof(buffer));
	  int ret = date(buffer);
	  strcpy(d_YYYYMM,buffer);
	  return ret;
	};


	/// 取得上个月份
	/// @param d_YYYYMM 得到时间格式'YYYYMM'
	static int last_month(char * d_YYYYMM) {
	  time_t now;
	  struct tm  *w;
	  time(&now);
	  w=localtime(&now);
	  if (w->tm_mon == 0)
	    return sprintf(d_YYYYMM,"%04d%02d",
	           w->tm_year+1899,12);
	  else
	    return sprintf(d_YYYYMM,"%04d%02d",
	           w->tm_year+1900,w->tm_mon);
	};


	/// 取得上上个月份
	/// @param d_YYYYMM 得到时间格式'YYYYMM'
	static int last2_month(char * d_YYYYMM) {
	  time_t now;
	  struct tm  *w;
	  time(&now);
	  w=localtime(&now);
	  if (w->tm_mon == 0)
	    return sprintf(d_YYYYMM,"%04d%02d",w->tm_year+1899,11);
	  if (w->tm_mon == 1)
	    return sprintf(d_YYYYMM,"%04d%02d",w->tm_year+1899,12);
	  else
	    return sprintf(d_YYYYMM,"%04d%02d",w->tm_year+1900,w->tm_mon - 1);
	};


	/// 判断某年是否是闰年
	/// @param y_YYYY
	static bool isLeapYear(long y_YYYY) {
	  bool ret;
	  if (y_YYYY%4==0) {
	    if (y_YYYY%100==0) {
	      if (y_YYYY%400==0)
	        ret=true;
	      else
	        ret=false;
	    }
	    else
	      ret=true;
	  }
	  else
	    ret=false;
	  return ret;
	};


	///校验日期是否有效
	/// @param d_YYYYMMDD 20050124
	static bool validDate(long d_YYYYMMDD) {
	  long year  = (long) (d_YYYYMMDD/10000);
	  long month = (long)((d_YYYYMMDD-long(d_YYYYMMDD/10000)*10000)/100);
	  long day   = (long) (d_YYYYMMDD%100);

	  if ( year>99 ) {
	  	if ( (year>2200) || (year<1950) ) return -1;
	  } else {
	    if ( year<50 ) return false;
	  }

	  if ( (month >12) || (month <1) ) return false;
	  if ( (   day>31) || (day   <1) ) return false;

	  switch (month) {
	  case 2:
	    if (isLeapYear(year))	    	
	      {if (day>29) return false;}
	    else
	      {if (day>28) return false;}
	    break;
	  case 4:
	  case 6:
	  case 9:
	  case 11:
	    if (day>30)
	      return false;
	    break;
	  }

	  return true;
	};


	/// 检查时间是否有效
	/// @param t_HHmm 2312
	static bool validTime(long t_HHmm) {
	  long temp;
	  if ((int(t_HHmm/100)<0)||(int(t_HHmm/100)>23))
	     return false;

	  temp=t_HHmm-int(t_HHmm/100)*100;
	  if ((temp<0)||(temp>=60))
	    return false;

	  return true;
	};


	/// 时间差计算
	/// @param s_YYYYMMDDHHmmSS 较早的时间
	/// @param e_YYYYMMDDHHmmSS 较迟的时间
	/// @return 返回秒数
	static long timediff(const char * s_YYYYMMDDHHmmSS,const char * e_YYYYMMDDHHmmSS) {
	    struct tm t;
	    time_t t1,t2;
	    char tmp[10];

	    memcpy(tmp,s_YYYYMMDDHHmmSS,4   ); tmp[4]=0; t.tm_year =atoi(tmp)-1900;
	    memcpy(tmp,s_YYYYMMDDHHmmSS+4,2 ); tmp[2]=0; t.tm_mon  =atoi(tmp)-1;
	    memcpy(tmp,s_YYYYMMDDHHmmSS+6,2 ); tmp[2]=0; t.tm_mday =atoi(tmp);
	    memcpy(tmp,s_YYYYMMDDHHmmSS+8,2 ); tmp[2]=0; t.tm_hour =atoi(tmp);
	    memcpy(tmp,s_YYYYMMDDHHmmSS+10,2); tmp[2]=0; t.tm_min  =atoi(tmp);
	    memcpy(tmp,s_YYYYMMDDHHmmSS+12,2); tmp[2]=0; t.tm_sec  =atoi(tmp);

	    t.tm_isdst=0;        
	    t1=mktime(&t);
	
	    memcpy(tmp,e_YYYYMMDDHHmmSS,4);    tmp[4]=0; t.tm_year =atoi(tmp)-1900;
	    memcpy(tmp,e_YYYYMMDDHHmmSS+4,2);  tmp[2]=0; t.tm_mon  =atoi(tmp)-1;
	    memcpy(tmp,e_YYYYMMDDHHmmSS+6,2);  tmp[2]=0; t.tm_mday =atoi(tmp);
	    memcpy(tmp,e_YYYYMMDDHHmmSS+8,2);  tmp[2]=0; t.tm_hour =atoi(tmp);
	    memcpy(tmp,e_YYYYMMDDHHmmSS+10,2); tmp[2]=0; t.tm_min  =atoi(tmp);
	    memcpy(tmp,e_YYYYMMDDHHmmSS+12,2); tmp[2]=0; t.tm_sec  =atoi(tmp);

	    t2=mktime(&t);

	    return (long)difftime(t2,t1);
	};
	
	/// 时间差计算
	/// @param s_YYYYMMDDHHmmSS 较早的时间
	/// @param e_YYYYMMDDHHmmSS 较迟的时间
	/// @return 返回天数
	static int daydiff(const char * s_YYYYMMDDHHmmSS,const char * e_YYYYMMDDHHmmSS) {
	    struct tm t;
	    time_t t1,t2;
	    char tmp[10];
	    int hhmiss;

	    memcpy(tmp,s_YYYYMMDDHHmmSS,4   ); tmp[4]=0; t.tm_year =atoi(tmp)-1900;
	    memcpy(tmp,s_YYYYMMDDHHmmSS+4,2 ); tmp[2]=0; t.tm_mon  =atoi(tmp)-1;
	    memcpy(tmp,s_YYYYMMDDHHmmSS+6,2 ); tmp[2]=0; t.tm_mday =atoi(tmp);
	    t.tm_hour = 0;
	    t.tm_min  = 0;
	    t.tm_sec  = 0;

	    t.tm_isdst=0;        
	    t1=mktime(&t);        

	    memcpy(tmp,e_YYYYMMDDHHmmSS,4);    tmp[4]=0; t.tm_year =atoi(tmp)-1900;
	    memcpy(tmp,e_YYYYMMDDHHmmSS+4,2);  tmp[2]=0; t.tm_mon  =atoi(tmp)-1;
	    memcpy(tmp,e_YYYYMMDDHHmmSS+6,2);  tmp[2]=0; t.tm_mday =atoi(tmp);
	    
	    memcpy(tmp,e_YYYYMMDDHHmmSS+8,6);  tmp[6]=0; hhmiss =atoi(tmp);
	    t2=mktime(&t);
	    
        if (hhmiss==0)
        {
            return (int)difftime(t2,t1)/86400 /* 24*3600 */;
        }
        else
        {
            return (int)difftime(t2,t1)/86400 /* 24*3600 */ + 1;
        }        
	    return 0;
	};
	
        /// 时间差计算
        /// @param s_YYYYMM 较早的时间
        /// @param e_YYYYMM 较迟的时间
        /// @return 返回月数
        static int monthdiff(const char * s_YYYYMM, const char * e_YYYYMM) {			
            int s_year = atoi(s_YYYYMM);
            int e_year = atoi(e_YYYYMM);

            int diffYear = e_year / 100 - s_year / 100;
            int diffMonth = e_year % 100 - s_year % 100;
        
            if(diffMonth<0)
            {
                --diffYear;
                diffMonth += 12;
            }
            return (diffYear * 12 + diffMonth);
        };
	
	// 获取当前的星期
	// @param date YYYYMMDD
	// @return week
	static int getweek(const long &date)
	{
		struct tm t;
		t.tm_year = date / 10000 - 1900;
		t.tm_mon = date % 10000 / 100 - 1;
		t.tm_mday = date % 100;
		t.tm_hour = 0;
		t.tm_min = 0;
		t.tm_sec = 0;
		t.tm_isdst = 0;
		if (mktime(&t) == (time_t) - 1)
		{
			return -1;
		}
		else if (t.tm_wday == 0)
		{
			return 7;
		}
		else
		{
			return t.tm_wday;
		}
	}
	
};


#endif //__TIMEUTIL_H__



