#pragma once
#include <iostream>

using namespace std;

namespace elc {

	class Date {
	private:
		 int day;
		 int month;
		 int year;

	public:
		Date() : day(1), month(1), year(1970) {} //default year
		Date(int d, int m, int y) : day(d), month(m), year(y) 
		{
			if (day < 1 || day > 31) throw(invalid_argument("invalid day"));
			if (month < 1 || month > 12) throw(invalid_argument("invalid month"));
			if (year < 1 ) throw(invalid_argument("invalid year"));
			if (month == 2 && day > 28) throw(invalid_argument("i ain't fool, february has 28 days!!"));
		}

		int getDay() { return day; }
		int getMonth() { return month; }
		int  getYear() const { return year; }

		void setDay(unsigned int _d)	{ day = _d; }
		void setMonth(unsigned int _m)	{ day = _m; }
		void setYear(unsigned int _y)	{ day = _y; }


		friend std::ostream& operator<<(std::ostream& out, Date const& date)
		{
			out << date.day << "/" << date.month << "/" << date.year;
			return out;
		}

		Date& operator=(Date other)
		{
			day = other.day;
			month = other.month;
			year = other.year;
			return *this;
		}

		void save(ofstream& out) const
		{
			out.write(reinterpret_cast<const char*>(&day), sizeof(day));
			out.write(reinterpret_cast<const char*>(&month), sizeof(month));
			out.write(reinterpret_cast<const char*>(&year), sizeof(year));
		}

		void load(ifstream& in)
		{
			in.read(reinterpret_cast<char*>(&day), sizeof(day));
			in.read(reinterpret_cast<char*>(&month), sizeof(month));
			in.read(reinterpret_cast<char*>(&year), sizeof(year));
		}

	};
};