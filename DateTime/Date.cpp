#include "Date.h"
#include <sstream>
#include <vector>
#include <stdexcept>

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
Date::Date(const std::string& str) {
	std::string date_part, time_part;
	size_t t_pos = str.find('T');
	if (t_pos != std::string::npos) {
		date_part = str.substr(0, t_pos);
		time_part = str.substr(t_pos + 1);
	}
	else {
		date_part = str;
		time_part = "";
	}

	std::vector<int> d_vals, t_vals;
	std::string token;
	std::istringstream d_ss(date_part), t_ss(time_part);

	while (std::getline(d_ss, token, '-')) d_vals.push_back(std::stoi(token));
	if (!time_part.empty()) {
		while (std::getline(t_ss, token, ':')) t_vals.push_back(std::stoi(token));
	}

	if (d_vals.size() != 3) throw DateValueExeption();
	if (!time_part.empty() && t_vals.size() != 3) throw DateValueExeption();

	year = d_vals[0]; month = d_vals[1]; day = d_vals[2];
	hour = time_part.empty() ? 0 : t_vals[0];
	min = time_part.empty() ? 0 : t_vals[1];
	sec = time_part.empty() ? 0 : t_vals[2];

	if (year < 0 && year > 9999 && month < 1 && month > 12 && day < 1 && day > 31 &&
		hour < 0 && hour > 23 && min < 0 && min > 59 && sec < 0 && sec > 59) {
		throw DateValueExeption();
	}
	to_jul();
}

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
	hour = 0; min = 0; sec = 0;
}
int Date::get_jd() const
{
	return jd;
}
Date& Date::operator =(const Date& date2) {
	year = date2.year;
	month = date2.month;
	day = date2.day;
	hour = date2.hour;
	min = date2.min;
	sec = date2.sec;
	to_jul();
	return *this;
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

std::ostream& operator <<(std::ostream& out, const Date& d)
{
	out << d.year << "-" << (d.month < 10 ? "0" : "") << d.day << "-" << (d.month < 10 ? "0" : "") << d.day << "T" << (d.hour < 10 ? "0" : "") << d.hour << ":" << (d.min < 10 ? "0" : "") << d.min << ":" << (d.sec < 10 ? "0" : "") << d.sec << ";";
	return out;
}
Date Date::get_easter() const {  
	int a = year % 19;
	int b = year % 4;
	int c = year % 7;
	int d = (19 * a + 15) % 30;
	int e = (2 * b + 4 * c + 6 * d + 6) % 7;
	Date Easter(year, 3, 22);
	Easter += (d + e + 13);
	if (*this > Easter) {
		int next_year = year + 1;
		a = next_year % 19;
		b = next_year % 4;
		c = next_year % 7;
		d = (19 * a + 15) % 30;
		e = (2 * b + 4 * c + 6 * d + 6) % 7;
		Date new_Easter(next_year, 3, 22);
		new_Easter += (d + e + 13);
		return new_Easter;
	}
	return Easter;
}