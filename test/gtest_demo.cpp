#include <gtest/gtest.h>
#include"test.h"

TEST(addTestSuite,TestCase1)
{
    EXPECT_EQ(3,add(1,2));
    EXPECT_LT(3,add(4,2));
    EXPECT_GT(3,add(0,2));
//	EXPECT_GT(0,add(0,2));
  }
   
   TEST(fibTestSuite,TestCase1)
   {
   EXPECT_EQ(1,fib(1));
   EXPECT_EQ(1,fib(2));
   EXPECT_EQ(2,fib(3));
	EXPECT_EQ(34,fib(9));
   }
