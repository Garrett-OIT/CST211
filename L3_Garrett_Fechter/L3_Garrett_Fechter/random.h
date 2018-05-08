#ifndef RANDOM_H
#define RANDOM_H	

#include <time.h>
#include <iostream>

/********************
* Class: Random
* Takes a range and every time getRand is called it seeds and returns a random num
* from 0 to range
* m_range- the range for the random number
* 		Random() default ctor, range is set to 100
*		Random(int range)  ctor with range
*		Random(const Random & copy)  copy ctor
*	Random & operator = (const Random & rhs) op =
*		int getRand()  get the random between 0 and m_range
*		~Random() empty dtor
********************/
class Random 
{
	public:
		Random();//default ctor, range is set to 100
		Random(int range);//ctor with range
		Random(const Random & copy);//copy ctor
		Random & operator = (const Random & rhs);//op =
		int getRand();//get the random between 0 and m_range
		~Random();//empty dtor
	private:
		int m_range;
};

#endif