// C++ Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#define CURL_STATICLIB
#include <curl\curl.h>
#include <cpr/cpr.h>
#include <json/json.h>
using namespace std;

#include "NewsObject.h"
#include "StocksObject.h"

#include <limits.h>

void make_newsmap(map<int, NewsObject*>&newsHashMap) {
	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;
	string defacto = "https://newsapi.org/v2/top-headlines?";
	string country = "country=";
	string user_country = "sg";
	string q = "&q=";
	string user_q = "";
	string leftover = "&category=business&apiKey=1e86e5f07d6a4928b8a2075788d360ee";
	string url = defacto + country + user_country + q + user_q + leftover;
	//string url = "https://newsapi.org/v2/top-headlines?country=sg&category=business&apiKey=1e86e5f07d6a4928b8a2075788d360ee";
	auto r = cpr::Get(cpr::Url{ url });

	const auto rawJsonLength = static_cast<int>(r.text.length());
	const unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(r.text.c_str(), r.text.c_str() + rawJsonLength, &root,
		&err)) {
		cout << "News Error in parsing. Check internet connection." << endl;
	}

	//cout << root["articles"][0] << endl;
	
	int counter = 0;
	//string author, content, description, publishedAt, source, title, url, urlToImage;
	for (Json::Value::ArrayIndex i = 0; i < root["articles"].size(); i++)
	{
		string author, content, description, publishedAt, sourceID, sourceName, title, url, urlToImage;
		author = root["articles"][i]["author"].asString();
		content = root["articles"][i]["content"].asString();
		description = root["articles"][i]["description"].asString();
		publishedAt = root["articles"][i]["publishedAt"].asString();
		sourceID = root["articles"][i]["source"]["id"].asString();
		sourceName = root["articles"][i]["source"]["name"].asString();
		title = root["articles"][i]["title"].asString();
		url = root["articles"][i]["url"].asString();
		urlToImage = root["articles"][i]["urlToImage"].asString();

		newsHashMap.insert(make_pair(counter, new NewsObject(author, content, description, publishedAt, sourceID, sourceName, title, url, urlToImage)));
		counter++;
	}


}

int make_Mstocksmap(map<int, StocksMonthObject*>& MstocksHashMap, string user_symbol) {
	
	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;	

	string defacto = "https://www.alphavantage.co/query?function=TIME_SERIES_MONTHLY&";
	string api_symbol = "symbol=";
	string leftover = "&datatype=json&apikey=82FVGVX8TQDW2B6V";

	string url = defacto + api_symbol + user_symbol + leftover;

	auto r = cpr::Get(cpr::Url{ url });
	const auto rawJsonLength = static_cast<int>(r.text.length());
	const unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(r.text.c_str(), r.text.c_str() + rawJsonLength, &root, &err)) {
		cout << "Error in parsing. Check internet connection." << std::endl;
	}

	if (root["Meta Data"] == Json::nullValue) {
		cout << "Invalid symbol. Please try again." << endl;
		return -1;
	}

	string information, symbol, last_refreshed, interval, time_zone;
	string time_series;
	float open, high, low, close, volume;
	int counter = 0;
	information = root["Meta Data"]["1. Information"].asString();
	symbol = root["Meta Data"]["2. Symbol"].asString();
	last_refreshed = root["Meta Data"]["3. Last Refreshed"].asString();
	time_zone = root["Meta Data"]["4. Time Zone"].asString();
	for (auto const& id : root.getMemberNames()) {
		time_series = id;
	}
	interval = "Monthly";

	for (auto const& id : root[time_series].getMemberNames()) {
		open = stof(root[time_series][id]["1. open"].asString());
		high = stof(root[time_series][id]["2. high"].asString());
		low = stof(root[time_series][id]["3. low"].asString());
		close = stof(root[time_series][id]["4. close"].asString());
		volume = stof(root[time_series][id]["5. volume"].asString());
		MstocksHashMap.insert(make_pair(counter, new StocksMonthObject(information, symbol, last_refreshed, interval, time_zone, time_series, open, high, low, close, volume)));
		counter++;
	}
}

int make_Wstocksmap(map<int, StocksWeekObject*>& WstocksHashMap, string user_symbol) {

	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;

	string defacto = "https://www.alphavantage.co/query?function=TIME_SERIES_WEEKLY&";
	string api_symbol = "symbol=";
	string leftover = "&datatype=json&apikey=82FVGVX8TQDW2B6V";

	string url = defacto + api_symbol + user_symbol + leftover;


	auto r = cpr::Get(cpr::Url{ url });
	const auto rawJsonLength = static_cast<int>(r.text.length());
	const unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(r.text.c_str(), r.text.c_str() + rawJsonLength, &root, &err)) {
		cout << "Error in parsing. Check internet connection." << std::endl;
	}

	if (root["Meta Data"] == Json::nullValue) {
		cout << "Invalid symbol. Please try again." << endl;
		return -1;
	}

	string information, symbol, last_refreshed, interval, time_zone;
	string time_series;
	float open, high, low, close, volume;
	int counter = 0;
	information = root["Meta Data"]["1. Information"].asString();
	symbol = root["Meta Data"]["2. Symbol"].asString();
	last_refreshed = root["Meta Data"]["3. Last Refreshed"].asString();
	time_zone = root["Meta Data"]["4. Time Zone"].asString();
	for (auto const& id : root.getMemberNames()) {
		time_series = id;
	}
	interval = "Weekly";

	for (auto const& id : root[time_series].getMemberNames()) {
		open = stof(root[time_series][id]["1. open"].asString());
		high = stof(root[time_series][id]["2. high"].asString());
		low = stof(root[time_series][id]["3. low"].asString());
		close = stof(root[time_series][id]["4. close"].asString());
		volume = stof(root[time_series][id]["5. volume"].asString());
		WstocksHashMap.insert(make_pair(counter, 
			new StocksWeekObject(information, symbol, last_refreshed, interval, time_zone, time_series, open, high, low, close, volume)));
		counter++;
	}
}

int make_Dstocksmap(map<int, StocksDailyObject*>& DstocksHashMap, string user_symbol) {

	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;

	string defacto = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&";
	string api_symbol = "symbol=";
	string leftover = "&datatype=json&apikey=82FVGVX8TQDW2B6V";

	string url = defacto + api_symbol + user_symbol + leftover;

	auto r = cpr::Get(cpr::Url{ url });
	const auto rawJsonLength = static_cast<int>(r.text.length());
	const unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(r.text.c_str(), r.text.c_str() + rawJsonLength, &root, &err)) {
		cout << "Error in parsing. Check internet connection." << std::endl;
	}
	if (root["Meta Data"] == Json::nullValue) {
		cout << "Invalid symbol. Please try again." << endl;
		return -1;
	}
	string information, symbol, last_refreshed, interval, time_zone;
	string time_series;
	float open, high, low, close, volume;
	int counter = 0;
	information = root["Meta Data"]["1. Information"].asString();
	symbol = root["Meta Data"]["2. Symbol"].asString();
	last_refreshed = root["Meta Data"]["3. Last Refreshed"].asString();
	time_zone = root["Meta Data"]["4. Time Zone"].asString();
	for (auto const& id : root.getMemberNames()) {
		time_series = id;
	}
	interval = "Daily";

	for (auto const& id : root[time_series].getMemberNames()) {
		open = stof(root[time_series][id]["1. open"].asString());
		high = stof(root[time_series][id]["2. high"].asString());
		low = stof(root[time_series][id]["3. low"].asString());
		close = stof(root[time_series][id]["4. close"].asString());
		volume = stof(root[time_series][id]["5. volume"].asString());
		DstocksHashMap.insert(make_pair(counter,
			new StocksDailyObject(information, symbol, last_refreshed, interval, time_zone, time_series, open, high, low, close, volume)));
		counter++;
	}
}

int make_Hstocksmap(map<int, StocksHourObject*>& HstocksHashMap, string user_symbol) {

	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;

	string defacto = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&";
	string api_symbol = "symbol=";
	string leftover = "&interval=60min&datatype=json&apikey=82FVGVX8TQDW2B6V";

	string url = defacto + api_symbol + user_symbol + leftover;

	auto r = cpr::Get(cpr::Url{ url });
	const auto rawJsonLength = static_cast<int>(r.text.length());
	const unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(r.text.c_str(), r.text.c_str() + rawJsonLength, &root, &err)) {
		cout << "Error in parsing. Check internet connection." << endl;
	}

	if (root["Meta Data"] == Json::nullValue) {
		cout << "Invalid symbol. Please try again." << endl;
		return -1;
	}

	string information, symbol, last_refreshed, interval, time_zone;
	string time_series;
	float open, high, low, close, volume;
	int counter = 0;
	information = root["Meta Data"]["1. Information"].asString();
	symbol = root["Meta Data"]["2. Symbol"].asString();
	last_refreshed = root["Meta Data"]["3. Last Refreshed"].asString();
	time_zone = root["Meta Data"]["4. Time Zone"].asString();
	for (auto const& id : root.getMemberNames()) {
		time_series = id;
	}
	interval = "Hourly";

	for (auto const& id : root[time_series].getMemberNames()) {
		open = stof(root[time_series][id]["1. open"].asString());
		high = stof(root[time_series][id]["2. high"].asString());
		low = stof(root[time_series][id]["3. low"].asString());
		close = stof(root[time_series][id]["4. close"].asString());
		volume = stof(root[time_series][id]["5. volume"].asString());
		HstocksHashMap.insert(make_pair(counter,
			new StocksHourObject(information, symbol, last_refreshed, interval, time_zone, time_series, open, high, low, close, volume)));
		counter++;
	}
}
std::vector<double> predictStock(map<int, StocksDailyObject*>& DstocksHashMap) {

	// create an ofstream for the file output (see the link on streams for
	// more info)
	ofstream outputFile;
	ofstream fs;
	fstream fout;
	// create a name for the file output
	fout.open("ml_data.csv", ios::out | ios::app);
	map<int, StocksDailyObject*>::iterator ids;
	for (ids = DstocksHashMap.begin(); ids != DstocksHashMap.end(); ids++) {
		fout << ids->second->getopen() << endl;
	}

	outputFile.close();

	double avgChange = 0.00;
	double avgPrice = 0.00;
	double movingAvgPrice = 0.00;
	double movingAvgPriceTotal = 0.00;
	int count = 1;
	double previous = 0.0;
	//for (ids = DstocksHashMap.begin(); ids != DstocksHashMap.end(); ids++) {
	//	if (ids->second->getopen() <= previous) {
	//		previous = ids->second->getopen();
	//	}
	//}
	vector<double> movingAverage;
	//List<Double> movingAverage = new ArrayList<>();
	for (ids = DstocksHashMap.begin(); ids != DstocksHashMap.end(); ids++) {
		double each = ids->second->getopen();
		if (previous != 0) {
			avgChange += (previous - each);
		}
		if (count % 100 == 0) {
			double currentMovingAvgPrice = movingAvgPrice / 100;
			movingAvgPriceTotal += currentMovingAvgPrice;
			movingAverage.push_back(currentMovingAvgPrice);
			movingAvgPrice = 0;
		}
		avgPrice += each;
		movingAvgPrice += each;
		previous = each;
		count++;
	}

	avgPrice = avgPrice/movingAverage.size();
	avgChange = avgChange / movingAverage.size();
	double currentMovingAvgPrice = movingAvgPrice / (count % 100);
	movingAvgPriceTotal += currentMovingAvgPrice;

	movingAverage.push_back(currentMovingAvgPrice);
	movingAvgPrice = movingAvgPriceTotal / movingAverage.size();


	double closing1 = movingAverage.back() + avgChange;
	double closing2 = closing1 + avgChange;
	double closing3 = closing2 + avgChange;

	vector<double> Prediction;
	Prediction.push_back(closing1);
	Prediction.push_back(closing2);
	Prediction.push_back(closing3);

	return Prediction;
}

int main()
{
	/*
		To teammates: the following commented out session are for-loops that helps to print the values that you need
		It has been sectioned into 6 distinct parts.
		News - newsHashMap
		Stocks - MstocksHashmap etc etc
		Prediction - PredictionMap
		Simply uncomment the for-loops to print out the values

		=======  ==     ==    ========  ========  ======    ========
		==       ==     ==    ==        ==        ==   ==   ==
		==       =========    ========  ========  ==  ==    ========
		==       ==     ==    ==        ==        ====            ==
		=======  ==     ==    ========  ========  ==  ==    ========

	*/
	string user_input_symbol = "MSFT";
    cout << "Hello World!\n";
	map<int, NewsObject*> newsHashMap;
	make_newsmap(newsHashMap);
	map<int, NewsObject*>::iterator it;
	//for (it = newsHashMap.begin(); it != newsHashMap.end(); it++) {
	//	cout << it->first << ": " << it->second->getauthor() << endl;
	//	cout << it->first << ": " << it->second->getcontent() << endl;
	//	cout << it->first << ": " << it->second->getdescription() << endl;
	//	cout << it->first << ": " << it->second->getpublishedAt() << endl;
	//	cout << it->first << ": " << it->second->getSourceID() << endl;
	//}

	map<int, StocksMonthObject*> MstocksHashMap;
	make_Mstocksmap(MstocksHashMap, user_input_symbol);
	map<int, StocksMonthObject*>::iterator ims;
	//for (ims = MstocksHashMap.begin(); ims != MstocksHashMap.end(); ims++) {
	//	cout << ims->first << ": " << ims->second->getinformation() << endl;
	//	cout << ims->first << ": " << ims->second->getopen() << endl;
	//}

	map<int, StocksWeekObject*> WstocksHashMap;
	make_Wstocksmap(WstocksHashMap, user_input_symbol);
	map<int, StocksWeekObject*>::iterator iws;
	//for (iws = WstocksHashMap.begin(); iws != WstocksHashMap.end(); iws++) {
	//	cout << iws->first << ": " << iws->second->getinformation() << endl;
	//	cout << iws->first << ": " << iws->second->getopen() << endl;
	//}

	map<int, StocksDailyObject*> DstocksHashMap;
	make_Dstocksmap(DstocksHashMap, user_input_symbol);
	map<int, StocksDailyObject*>::iterator ids;
	//for (ids = DstocksHashMap.begin(); ids != DstocksHashMap.end(); ids++) {
	//	cout << ids->first << ": " << ids->second->getinformation() << endl;
	//	cout << ids->first << ": " << ids->second->gettime_series() << endl;
	//	cout << ids->first << ": " << ids->second->getinterval() << endl;
	//	cout << ids->first << ": " << ids->second->getopen() << endl;
	//}

	map<int, StocksHourObject*> HstocksHashMap;
	make_Hstocksmap(HstocksHashMap, user_input_symbol);
	map<int, StocksHourObject*>::iterator ihs;
	//for (ihs = HstocksHashMap.begin(); ihs != HstocksHashMap.end(); ihs++) {
	//	cout << ihs->first << ": " << ihs->second->getinformation() << endl;
	//	cout << ihs->first << ": " << ihs->second->getopen() << endl;
	//}

	map<int, int> PredictionMap;
	vector<double> Prediction = predictStock(DstocksHashMap);
	//cout << "Output of begin and end: ";
	//for (auto i = Prediction.begin(); i != Prediction.end(); ++i)
	//	cout << *i << " ";
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
