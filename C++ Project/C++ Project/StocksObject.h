#pragma once
#pragma once
#include <iostream>
using namespace std;

class StocksObject {
public:
	string information, symbol, last_refreshed, interval, time_zone;

	StocksObject(string, string, string, string, string);
	
	string getinformation();
	string getsymbol();
	string getlast_refreshed();
	string getinterval();
	string gettime_zone();
};

StocksObject::StocksObject(string a, string b, string c, string d, string e) {
	information = a;
	symbol = b;
	last_refreshed = c;
	interval = d;
	time_zone = e;

}

string StocksObject::getinformation() {
	return information;
}

string StocksObject::getsymbol() {
	return symbol;
}

string StocksObject::getlast_refreshed() {
	return last_refreshed;
}

string StocksObject::getinterval() {
	return interval;
}

string StocksObject::gettime_zone() {
	return time_zone;
}

class StocksMonthObject: public StocksObject {
public:
	string time_series;
	float open, high, low, close, volume;
	StocksMonthObject(string, string, string, string, string, string, float, float, float, float, float);

	string gettime_series();
	float getopen();
	float gethigh();
	float getlow();
	float getclose();
	float getvolume();
};

StocksMonthObject::StocksMonthObject(string a, string b, string c, string d, string e, string f, 
	float one, float two, float three, float four, float five)
	:StocksObject(a, b, c, d, e)
{
	time_series = f;
	open = one;
	high = two;
	low = three;
	close = four;
	volume = five;
}

string StocksMonthObject::gettime_series() {
	return time_series;
}

float StocksMonthObject::getopen() {
	return open;
}

float StocksMonthObject::gethigh() {
	return high;
}

float StocksMonthObject::getlow() {
	return low;
}

float StocksMonthObject::getclose() {
	return close;
}

float StocksMonthObject::getvolume() {
	return volume;
}

class StocksWeekObject : public StocksObject {
public:
	string time_series;
	float open, high, low, close, volume;
	StocksWeekObject(string, string, string, string, string, string, float, float, float, float, float);

	string gettime_series();
	float getopen();
	float gethigh();
	float getlow();
	float getclose();
	float getvolume();
};

StocksWeekObject::StocksWeekObject(string a, string b, string c, string d, string e, string f,
	float one, float two, float three, float four, float five)
	:StocksObject(a, b, c, d, e) {
	time_series = f;
	open = one;
	high = two;
	low = three;
	close = four;
	volume = five;
}
string StocksWeekObject::gettime_series() {
	return time_series;
}

float StocksWeekObject::getopen() {
	return open;
}

float StocksWeekObject::gethigh() {
	return high;
}

float StocksWeekObject::getlow() {
	return low;
}

float StocksWeekObject::getclose() {
	return close;
}

float StocksWeekObject::getvolume() {
	return volume;
}

class StocksDailyObject : public StocksObject {
public:
	string time_series;
	float open, high, low, close, volume;
	StocksDailyObject(string, string, string, string, string, string, float, float, float, float, float);

	string gettime_series();
	float getopen();
	float gethigh();
	float getlow();
	float getclose();
	float getvolume();
};

StocksDailyObject::StocksDailyObject(string a, string b, string c, string d, string e, string f,
	float one, float two, float three, float four, float five)
	:StocksObject(a, b, c, d, e) {
	time_series = f;
	open = one;
	high = two;
	low = three;
	close = four;
	volume = five;
}
string StocksDailyObject::gettime_series() {
	return time_series;
}

float StocksDailyObject::getopen() {
	return open;
}

float StocksDailyObject::gethigh() {
	return high;
}

float StocksDailyObject::getlow() {
	return low;
}

float StocksDailyObject::getclose() {
	return close;
}

float StocksDailyObject::getvolume() {
	return volume;
}

class StocksHourObject : public StocksObject {
public:
	string time_series;
	float open, high, low, close, volume;
	StocksHourObject(string, string, string, string, string, string, float, float, float, float, float);

	string gettime_series();
	float getopen();
	float gethigh();
	float getlow();
	float getclose();
	float getvolume();
};

StocksHourObject::StocksHourObject(string a, string b, string c, string d, string e, string f,
	float one, float two, float three, float four, float five)
	:StocksObject(a, b, c, d, e) {
	time_series = f;
	open = one;
	high = two;
	low = three;
	close = four;
	volume = five;
}
string StocksHourObject::gettime_series() {
	return time_series;
}

float StocksHourObject::getopen() {
	return open;
}

float StocksHourObject::gethigh() {
	return high;
}

float StocksHourObject::getlow() {
	return low;
}

float StocksHourObject::getclose() {
	return close;
}

float StocksHourObject::getvolume() {
	return volume;
}