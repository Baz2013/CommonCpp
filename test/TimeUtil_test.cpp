#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include <gtest/gtest.h>
#include "TimeUtil.h"

using namespace std;

TEST(isLeapYearTest,testCase1)
{
		long year = 2004;
		EXPECT_EQ(true,TimeUtil::isLeapYear(year));
}

TEST(validDateTest,teseCase2)
{
	long day = 20150619;
	EXPECT_EQ(true,TimeUtil::validDate(day));
}

TEST(validDateTest,teseCase3)
{
	long day = 20151619;
	EXPECT_EQ(false,TimeUtil::validDate(day));
}
