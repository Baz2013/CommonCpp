#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include <gtest/gtest.h>
#include"StringUtil.h"

using namespace std;


TEST(splitTest,testCase1)
{
	string exp = "   abde";
	EXPECT_EQ("abde",StringUtil::ltrim(exp));
}
