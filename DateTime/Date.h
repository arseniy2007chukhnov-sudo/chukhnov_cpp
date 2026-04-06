#pragma once
#include <iostream>

class DateValueExeption {};
class Date {
private:
	int jdn;
	float jd;
	void to_jul();
	void to_dt();
public:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int getJdn();
	float getJd();
	Date(int y, int mo, int d);
	Date(int y, int mo, int d, int h, int mi, int s);
	/*Date(char* string);*/

};
