#ifndef __TIMEUTIL_H__
#define __TIMEUTIL_H__

#include "common.h"

using namespace std;


/**
 * @class TimeUtil
 *
 * @brief ʱ�����Ĺ�����
 */


class TimeUtil {

  public:

	/**
	 * ���ص�ǰʱ��
	 *
	 * @return ��ǰʱ��ĳ����ͱ�ʾ
	 */
	static long now() {
	  time_t n ; time(&n); return n;
	};

	/**
	 *  ���ش�����ĸ�ʽ��ʱ���ַ���
	 *
	 * @param dt_YYYYMMDDHHmmSSsss
	 *               ���صĸ�ʽ���ַ���
	 * @param mytime Ҫ��ʽ����ʱ�䣬ȱʡΪ��ǰʱ��
	 *
	 * @return ������Ӧ��ʱ��
	 */
	static long now(char *dt_YYYYMMDDHHmmSSsss,const time_t mytime = 0) {
	    // �õ������뿪ʼ����ʱ��
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



	/// ��Ե�ǰ��ʱ��������
	/// @param dt_YYYYMMDDHHmmSS ��ʾ��ʱ���ַ���
	/// @return ���ŵ�����
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


	/// ���ŵ�ʱ��
	/// @param end ����ʱ�� mmSS (HHmm)
	/// @param start ��ʼʱ�� mmSS (HHmm)
	/// @return ����(������)
	static long elapsed(long start,long end){
	   long b,e;
	   b=long(start/100);
	   e=long(end/100);
	   return (b*60+start-b*100)-(e*60+end-e*100);
	};

	/// ���ŵ�ʱ��
	/// @param end ����ʱ�� mmSS (HHmm)
	/// @param start ��ʼʱ�� mmSS (HHmm)
	/// @return ��ʽ���� mmSS (HHmm)
	static long formatElapsed(long start,long end) {
	   long m=elapsed(start,end);
	   return long(m/60)*100+(m-long(m/60)*60);
	};


	/// �����Ѿ����ŵ�ʱ��(���ӱ�ʾ)
	/// @return ���ط�����
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


	/// ʱ���ַ���������
	/// @param t_YYYYMMDDHHmmSS �õ���
	/// @param s_YYYYMMDDHHmmSS ��ʼʱ����ַ���
	/// @param offset ƫ������
	/// @return Ŀ��ʱ���ַ����ĳ���
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



	/// ʱ���ַ���������
	/// @param t_YYYYMMDD �õ���
	/// @param s_YYYYMMDD ��ʼʱ����ַ���
	/// @param offset ƫ������
	/// @return Ŀ���ַ�����ַ
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



	/// ȡ����ǰ�����ַ���
	/// @param d_YYYYMMDD �õ�ʱ���ʽ'YYYYMMDD'
	static int date(char * d_YYYYMMDD) {
	  time_t now;
	  struct tm  *w;
	  time(&now);
	  w=localtime(&now);
	  return sprintf(d_YYYYMMDD,"%04d%02d%02d",
	    w->tm_year+1900,w->tm_mon+1,w->tm_mday);
	};


	/// ȡ����ǰ�����ַ���
	/// @param d_YYYYMM �õ�ʱ���ʽ'YYYYMM'
	static int month(char * d_YYYYMM) {
	  char buffer[256];
	  memset(buffer,0,sizeof(buffer));
	  int ret = date(buffer);
	  strcpy(d_YYYYMM,buffer);
	  return ret;
	};


	/// ȡ���ϸ��·�
	/// @param d_YYYYMM �õ�ʱ���ʽ'YYYYMM'
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


	/// ȡ�����ϸ��·�
	/// @param d_YYYYMM �õ�ʱ���ʽ'YYYYMM'
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


	/// �ж�ĳ���Ƿ�������
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


	///У�������Ƿ���Ч
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


	/// ���ʱ���Ƿ���Ч
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


	/// ʱ������
	/// @param s_YYYYMMDDHHmmSS �����ʱ��
	/// @param e_YYYYMMDDHHmmSS �ϳٵ�ʱ��
	/// @return ��������
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
	
	/// ʱ������
	/// @param s_YYYYMMDDHHmmSS �����ʱ��
	/// @param e_YYYYMMDDHHmmSS �ϳٵ�ʱ��
	/// @return ��������
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
	
        /// ʱ������
        /// @param s_YYYYMM �����ʱ��
        /// @param e_YYYYMM �ϳٵ�ʱ��
        /// @return ��������
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
	
	// ��ȡ��ǰ������
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



