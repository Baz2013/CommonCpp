#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include <gtest/gtest.h>
#include"StringUtil.h"
#include"TimeUtil.h"

using namespace std;


TEST(splitTest,testCase1)
{
	string exp = "   abde";
	EXPECT_EQ("abde",StringUtil::ltrim(exp));
}

TEST(padTest,testCase2)
{
	string src = "abcd";
	string dst = "####abcd";
	string pad_str = "#";
	EXPECT_EQ(dst,StringUtil::pad(src.c_str(),8,pad_str.c_str()));
}

TEST(replaceTest,testCase3)
{
//	string src = "abcccdccc";
	string dst = "ab###d###";
	EXPECT_EQ(dst,StringUtil::replace("abcccdccc","c","#"));
}

TEST(toUpperCase,testCase4)
{
	string src = "abcd";
	string dst = "ABCD";
	EXPECT_EQ(dst,StringUtil::toUpperCase(src));
}

TEST(toUpperCase1,testCase5)
{
	string src = "ABCD";
	string dst = "ABCD";
	EXPECT_EQ(dst,StringUtil::toUpperCase(src));
}

TEST(toLowerCaseTest,testCase6)
{
	string src = "ABcD";
	string dst = "abcd";
	EXPECT_EQ(dst,StringUtil::toLowerCase(src));
}
