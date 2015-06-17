#ifndef _TEST_H_
#define _TEST_H_
#include<iostream>
#include<string>
#include<vector>
using namespace std;
  
int add(int a,int b){
	  
	    return (a+b);
}
  
int fib(int n){
	  
	    if( 1 == n || 2 == n ){
			        return 1;
					    }
		  
		    return fib(n-1) + fib(n-2);
}
  
#endif
