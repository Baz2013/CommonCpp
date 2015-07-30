#include"StringUtil.h"

/*
 *功能 :得到一个命令执行的输出行
 *参数 :
 *返回值 :执行结果的
 */
int StringUtil::command(const string &cmd,
		vector<string> &lines
		){
	FILE *pipe;
	char buffer[2048];

	lines.clear();
	if((pipe = popen(cmd.c_str(),"r")) == NULL){
		return -1;
	}
	//标准I/O函数库提供了popen函数，它启动另外一个进程去执行一个shell命令行
	while(fgets(buffer,sizeof(buffer),pipe) != NULL){

		buffer[2047] = 0;
		lines.push_back(buffer);
	}
	pclose(pipe);

	return lines.size();
}

/*
 *功能 :填充字符串
 *参数 :
 *返回值 :string类型,处理后的字符串
 */
string StringUtil::pad(const char *str,         //源字符串
		const int length,        //预期长度
		const char *stuff, //要填充的字符
		const bool left   //是否在左边填充(反之在右边)
		) {
	size_t len = strlen(str);
	if( len >= length ){
		return str;
	}
	if( strlen(stuff) <= 0){
		return str;
	}

	size_t len_stuff = strlen(stuff);
	string buffer;
	for(int i = 0 ;i < ((length - len)/len_stuff); ++i){
		buffer += stuff;
	}
	buffer += stuff;
	buffer = string(buffer.c_str(),buffer.c_str() + (length -len));

	return (left ? (buffer + str) : (str + buffer));
}

/*
 *功能 : 替换字符串
 *参数 : 源字符串,查找字符串,替换字符串
 *返回值 :bool类型,是否进行了替换
 */
bool StringUtil::replace(string &in,
		const string &search,
		const string &replacement
		){
	bool bRet = false;
	string::size_type pos = 0;
	while( pos < in.length() && (pos = in.find(search,pos)) != string::npos ){
		bRet = true;
		in.replace(pos,search.length(),replacement);
		pos += replacement.length();
	}

	return bRet;
}

/*
 *功能 : 替换字符串
 *参数 : 源字符串,查找字符串,替换字符串
 *返回值 :string 类型,处理后的字符串
 */
string StringUtil::replace(const string &in,
		const string &search,
		const string &replacement
		){
	string i = in;
	replace(i,search,replacement);

	return i;
}

/*
 * 功能 : 按指定分隔符切分字符串
 * 参数 : 源字符串,分隔符,结果容器,是否需要trim
 * 返回值 : size_t 类型
 */
size_t StringUtil::split(const string &str,
		const string &delim,
		vector<string> &result,
		bool needTrim
		){
	if(str.length() == 0)
		return 0;

	if(delim.length() == 0){
		result.push_back(str);
		return 1;
	}

	size_t c = 0;
	for( size_t i ,pos = 0; ;pos = i + delim.length()){
		i = str.find(delim,pos);
		if(i == string::npos)
			result.push_back(str.substr(pos));
		else
			result.push_back(str.substr(pos,i - pos));

		if(needTrim)
			trim(result[result.size() - 1]);
		c++;
		if(i == string::npos)
			break;
	}

	return c;
}

string & StringUtil::ltrim(string &str){
	string::iterator pos = str.begin();
	for(; pos != str.end() && (*pos == ' ' || *pos == '\t'); pos++)
		;
	if(pos != str.begin())
		str.erase(str.begin(),pos);

	return str;
}

string & StringUtil::rtrim(string &str){
	string::reverse_iterator pos = str.rbegin();
	for(;pos != str.rend() && (*pos == ' ' || *pos == '\t');pos++)
		;
	if(pos != str.rbegin()){
		str.erase(pos.base(),str.end());
	}

	return str;
}

string & StringUtil::trim(string &str){

	return rtrim(ltrim(str));
}

/*
 *功能 : 删除特定字符
 *参数 : 待处理字符串 , 去除的字符
 *返回值 : 返回字符串长度
 */
int StringUtil::eraseChar(char *str,const char &ch){

	int i,j,length;
	length = strlen(str);

	for(i = 0,j = 0;i < length;i++){
		if(str[i] != ch){
			if(i != j)
				str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
	return j;
}

/*
 *功能 : 删除字符串中指定的字符
 *参数 : 待处理字符串 , 去除的字符
 *返回值 : 返回字符串长度
 */
int StringUtil::eraseChar(string &str,const char &ch){
	int len = str.length();
	char *tmp = new char[len+1];
	memcpy(tmp,str.c_str(),len);
	tmp[len+1] = '\0';
	eraseChar(tmp,ch);
	//cout<<tmp<<endl;
	str = tmp;

	delete[] tmp;

	return 0;
}

string & StringUtil::toUpperCase(string &str){

	for(string::iterator str_iter = str.begin(); str_iter != str.end() ;str_iter++){
		*str_iter = toupper(*str_iter);
	}

	return str;
}

string & StringUtil::toLowerCase(string &str){

	for(string::iterator str_iter = str.begin(); str_iter != str.end() ;str_iter++){
		*str_iter = tolower(*str_iter);
	}

	return str;
}

/*
 *功能 : (忽略大小写)比较字符串
 *参数 : 需要比较的两个字符串
 *返回值 :boo值 (是否相等)
 */
bool StringUtil::equalsIgnoreCase(const string str1,const string str2){

	if(str1.length() != str2.length())
		return false;

	string::const_iterator iter1 = str1.begin();
	string::const_iterator iter2 = str2.begin();
	for(;iter1 != str1.end(); iter1++,iter2++){
		if(toupper(*iter1) != toupper(*iter2))
			return false;
	}
	return true;
}

string StringUtil::repeat(const int count,const string &chr){
	string buffer = "";
	for(int i = 0 ;i < count;i++){
		buffer = buffer + chr;
	}
	return buffer;
}

/**
 *函数功能 : 左对齐字符串
 *返回值 : 字符串长度
 */
int StringUtil::lalign(char *str,
		const int strlength,
		const char stuff){
	int i,length;
	//ltrim(str);

	length = strlen(str);
	if(length == strlength)
		return length;
	if(length < strlength){
		for(i = 1;i < strlength - length ;i++)
			str[i+length-1] = stuff;
		str[i+length-1] = '\0';
	}
	else
		str[strlength] = '\0';

	return strlen(str);
}

int StringUtil::rtrim(char *str){
	int len = strlen(str);
	for(int i = len - 1;i >= 0;i--){
		if(str[i] == ' ')
			str[i] = '\0';
		else
			break;
	}
	return strlen(str);
}

int StringUtil::ltrim(char *str){
	int i,j;
	int len = strlen(str);
	for(i = 0;i < len; i++){
		if(str[i] != ' ' && str[i] != '\t')
			break;
	}

	if(i > 0)
	{
		for(j = 0;j < len;j++)
		{
			str[j] = str[j+i];
		}
		str[j] = 0;
	}

	return strlen(str);
}

int StringUtil::trim(char *str)
{
	ltrim(str);
	rtrim(str);
	return strlen(str);
}

char * StringUtil::trim(const char *str)
{
	static char s[1024];
	memset(s,0,sizeof(s));
	strcpy(s,str);
	trim(s);
	return s;
}

/*alpha function */
string StringUtil::number2str(int number){
	stringstream ss;
	ss<<number;
	return ss.str();
}

string StringUtil::number2str(double number){
	stringstream ss;
	ss<<number;
	return ss.str();
}

string StringUtil::number2str(float number){
	stringstream ss;
	ss<<number;
	return ss.str();
}

/**
* 判断一个字符串是否全部是数字
*/
bool StringUtil::isdigitStr(const string &num){
	if(num.length() == 0)
		return false;
	size_t len = num.length();
	for(int i = 0;i < len;i++){
		if(!isdigit(num[i])){
			return false;
		}
	}
	return true;
}

/**
* 判断一个字符串是否全部是数字
*/
bool StringUtil::isdigitStr(const char *num){
	if(NULL == num)
		return false;
	size_t len = strlen(num);
	for(int i = 0;i < len;i++){
		if(!isdigit(num[i])){
			return false;
		}
	}

	return true;
}

