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
	Date(int y, int mo, int d);
	Date(int y, int mo, int d, int h, int mi, int s);
	/*Date(char* string);*/
	int get_jd() const;
	int operator -(const Date& date2) const;
	void operator +=(int d);
	bool operator >(const Date& date2) const;
	bool operator <=(const Date& date2) const;
	bool operator <(const Date& date2) const;
	bool operator >=(const Date& date2) const;
	bool operator ==(const Date& date2) const;
	bool operator !=(const Date& date2) const;
	//friend std::istream& operator >>(std::istream& in, Date& d);
	friend std::ostream& operator <<(std::ostream& out, const Date& d);
	int get_dw() const;
};
