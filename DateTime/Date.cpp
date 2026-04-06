#include "Date.h"

Date::Date(int y, int mo, int d) 
{
	if (y <= 9999 and y >=0 )
		year = y;
	else
		throw DateValueExeption();
	if (mo > 0 and mo < 13)
		month = mo;
	else
		throw DateValueExeption();
	if (d > 0 and d < 32)
		day = d;
	else
		throw DateValueExeption();
	hour = 0;
	min = 0;
	sec = 0;
	to_jul();
}

Date::Date(int y, int mo, int d, int h, int mi, int s)
{
	if (y <= 9999 and y >= 0)
		year = y;
	else
		throw DateValueExeption();
	if (mo >0 and mo < 13)
		month = mo;
	else
		throw DateValueExeption();
	if (d > 0 and d < 32)
		day = d;
	else
		throw DateValueExeption();
	if (h >= 0 and h <= 23)
		hour = h;
	else
		throw DateValueExeption();
	if (mi >= 0 and mi <= 59)
		min = mi;
	else
		throw DateValueExeption();
	if (s >= 0 and s <= 59)
		sec = s;
	else
		throw DateValueExeption();
	to_jul();
}
//Date::Date(char* string)
//{
//	
//}
void Date::to_jul()
{
	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;
	jdn = day + ((153 * m + 2) / 5) + 365 * y + ((y) / 4) - 32083;
	jd = jdn + ((hour - 12) / 24) + (min / 1440) + (sec / 86400);
}
void Date::to_dt()
{
	int c = jdn + 32082;
	int d = ((4 * c + 3) / 1461);
	int e = c - ((1461 * d) / 4);
	int m = ((5 * e + 2) / 153);
	day = e - ((153 * m + 2) / 5) + 1;
	month = m + 3 - 12 * (m / 10);
	year = d - 4800 + (m / 10);
}
int Date::get_jd() const
{
	return jd;
}
int Date::operator -(const Date& date2) const
{
	int raz = jdn - date2.get_jd();
	if (raz >= 0)
		return raz;
	else
		return -raz;
}
void Date::operator +=(int d)
{
	jdn += d;
	to_dt();
}
bool Date::operator >(const Date& date2) const
{
	return jd > date2.get_jd();
}
bool Date::operator <=(const Date& date2) const
{
	return !(*this > date2);
}
bool Date::operator <(const Date& date2) const
{
	return jd < date2.get_jd();
}
bool Date::operator >=(const Date& date2) const
{
	return !(*this < date2);
}
bool Date::operator ==(const Date& date2) const
{
	return jd == date2.get_jd();
}
bool Date::operator !=(const Date& date2) const
{
	return !(*this == date2);
}
int Date::get_dw() const 
{
	return jdn % 7;
}
//std::istream& operator >>(std::istream& in, Date& d)
//{
//	in >> ;
//	return in;
//}
std::ostream& operator <<(std::ostream& out, const Date& d)
{
	out << d.year << "-" << d.month << "-" << d.day << "T" << d.hour << ":" << d.min << ":" << d.sec<< ";";
	return out;
}