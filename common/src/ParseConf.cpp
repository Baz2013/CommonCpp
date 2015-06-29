// ##########################################
// Source file : ParseConf.cpp
// System      : ��������-�����ļ�����
// ##########################################


#include "ParseConf.h"

//using namespace std;

const string WHITE_SPACE(" \t\n\r");

//���캯�� CHECK_PATH Ϊ����������һ��Ҫ��
ParseConf::ParseConf()
{
    string conf_path = "";
    conf_path = getenv("CHECK_PATH");
    //cout << conf_path << endl;
    conf_name = conf_path + "/DATABASE.conf";
    //cout << "conf_name:" << conf_name << endl;
}

/*
ParseConf::ParseConf(string file_name)
{
    string conf_path = "";
    conf_path = getenv("CHECK_PATH");

    conf_name = conf_path + "/" + file_name;
    #ifdef debug
        cout << "conf_name:" << conf_name << endl;
    #endif
}
*/

bool ParseConf::setConfName(string file_name)
{
    string conf_path = "";
    conf_path = getenv("CHECK_PATH");
    

    if (conf_path.empty())
        return false;
     

    conf_name = conf_path + "/conf/" + file_name;
    
    #ifdef debug
        cout << "conf_name:" << conf_name << endl;
    #endif

    return true;
}
ParseConf::~ParseConf()
{
    ;
}

void ParseConf::setSection(string section_name)
{
    this->section_name = section_name;
}


bool ParseConf::getValue(const string& buffer, ResultMap& value)
{
    bool isOk = true;
    string  key;
    string  tmpVaue;
    string::size_type pos;
    string line = buffer;

   // CryptUtil::decrypt_pakage(line);

    assert(!line.empty());
    
    pos = line.find('=');
    if ((pos == string::npos) || ((pos + 1) > line.length()))
    {
        return false;
    }
    else
    {
        key = line.substr(0, pos);
        tmpVaue = line.substr(++pos);
        trimString(key);
        trimString(tmpVaue);
        //cout << __LINE__ << ":" << key << "," << tmpVaue << endl;
        value.insert(map<string,string>::value_type(key, tmpVaue));
    }
    return true;
}


bool ParseConf::scanSection(ResultMap& value)
{
    ifstream i_open;
    char    buffer[512];
    int     flag = 0; //0 seciton��  1��section��  2 section����
    
    i_open.open(conf_name.c_str());
    
    if (i_open.is_open())
    {
        while (! i_open.eof() ) {
            memset(buffer, 0x00, sizeof(buffer));
            i_open.getline (buffer, 256);
            trim(buffer);

            //�޳�ע���� ע����#��ͷ
            trim(buffer);
            if (buffer[0] == '#')
                continue;
            
            //����ڿ�ʼ�ڵ��ͽ����ڵ��ѯ��֮ǰ�����������ݽ��н���
            if (sectionBegin(buffer))
            {
                flag = 1;
            }
            
            if (sectionEnd(buffer))
            {
                flag = 2;
                i_open.close();
                break;
            }
            if (flag == 1)
            {
                getValue(buffer, value);
            }
            //cout << "flag:" << flag << endl;
        }
    }
    
    if (i_open.is_open())
    {
        i_open.close();
    }
    
    if (flag == 0)
    {
        return false;
    }
    return true;
}

bool ParseConf::sectionBegin(char* str)
{
    char tmpValue[124];
    sprintf(tmpValue, "%s%s%s", "<", section_name.c_str(), ">");
    //cout << __FUNCTION__ << tmpValue << "," << str << endl;
    if (strcmp(tmpValue, str)==0)
    {
        return true;
    }
    return false;
}

bool ParseConf::sectionEnd(char* str)
{
    char tmpValue[124];
    sprintf(tmpValue, "%s%s%s", "</", section_name.c_str(), ">");
    
    //cout << "tmpValue:" << tmpValue << "," << str <<  endl;
    if (strcmp(tmpValue, str) == 0)
    {
        return true;
    }
    return false;
}

void ParseConf::trimString(string& str)
{
    string::size_type pos;
    pos = str.find_first_not_of(WHITE_SPACE);
    if (pos != string::npos)
    {
        str = str.substr(pos);
        pos = str.find_last_not_of(WHITE_SPACE);
        if (pos != string::npos)
        {
                str = str.substr(0, pos + 1);
        }
    }
    else
    {
        str = "";
    }
}

int ParseConf::trim(char* str)
{
    int startn, endn;
    for(startn=0; str[startn]==32||str[startn]==9; ++startn);

    for(endn=strlen(str)-1; endn>=startn && (str[endn]==32||str[endn]==9||str[endn]==10||str[endn]==13); endn--);


    endn+=1-startn;

    if(startn)  memmove(str, str+startn, endn);

    str[endn]='\0';

    return endn;
}
