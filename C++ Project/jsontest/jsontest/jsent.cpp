#pragma warning(disable : 4996)

#include <string>
#include <iostream>
#include <json/json.h>
#include <json/writer.h>
#include <json/value.h>
#include <fstream>
#include "results.h"


using namespace std;


int noun(string n, int sent[2]) { // function
	ifstream inputfilepos;ifstream inputfileneg;
	bool negfound = false; // set boolean value to false first
	bool posfound = false; // set boolean value to false first
	string textfilepos;string textfileneg;
	inputfilepos.open("positive-words.txt"); // open text file
	inputfileneg.open("negative-words.txt"); // open text file
	if (!inputfilepos.is_open()) // checks to make sure file is open
		cout << "Error opening - Positive words file" << endl;

	if (!inputfileneg.is_open()) // checks to make sure file is open
		cout << "Error opening - Negative words file" << endl;

	while (getline(inputfilepos, textfilepos)) { // if foudn in positive file
		if (textfilepos == n) {
			sent[0]++;
			posfound = true;
			//     cout << textfilepos << "- found" << endl; // only put this here to see if this part was being executed
		}
		//    cout << textfilepos;
	}
	inputfilepos.close();
	while (getline(inputfileneg, textfileneg)) { // if found in negative file
		if (textfileneg == n) {
			sent[1]++;
			negfound = true;
			//       cout << textfileneg << "- found" << endl; // only put this here to see if this part was being executed
		}
		//  cout << textfileneg;
	}
	inputfileneg.close();

	return 0;
};
int main()
{
	ifstream myfile("output.json");
	string line;
	Json::Reader reader;// setting up reader to parse
	Json::Value root;
	Json::Value clean;
	results sentiment;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			//cout << line << '\n';
			bool parseSuccess = reader.parse(line, root, false);
			if (parseSuccess)
			{
				const Json::Value mynames = root["statuses"];

				for (int index = 0; index < mynames.size(); ++index)
				{
					//	cout << mynames[index]["user"]["name"] << endl;
						//cout << mynames[index]["created_at"] << endl;
					//	cout << mynames[index]["text"] << endl << endl;
					string s = (mynames[index]["text"]).asString(); // get tweet sentence content
					string str;

					//cout << s << endl;
					Json::Value event;

					event["tweet"]["date"] = mynames[index]["created_at"]; // get timestamp of tweet
					event["tweet"]["user"] = mynames[index]["user"]["name"]; // get username from tweet
					event["tweet"]["content"] = mynames[index]["text"]; // get the tweet content
					clean.append(event);
					int sent[2] = { 0,0 };
					for (auto x : s) // sends each word in the sentence to check
					{
						if (x == ' ')
						{
							noun(str, sent);
							str.erase();
						}
						else
							str = str + x;
					}
					////calculate general tweet
					if (sent[0] == sent[1]) {
						sentiment.upneu();
					}
					else if (sent[0] > sent[1]) {
						sentiment.uppos();
					}
					else {
						sentiment.upneg();
					}
				}
			}

		}
		myfile.close();

	}
	//Building to output to json (cleaned json file)
	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "   ";
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	ofstream outputFileStream("cleaned.json");
	writer->write(clean, &outputFileStream);
	outputFileStream.close();
	//	cout << clean << endl;
		//output of general sentiments
	cout << sentiment;
	//cout << "Sentiment" << endl << "Positive: " << sentiment.getpos() << endl << "Neutral:" << sentiment.getneg() << endl << "Negative: " << sentiment.getneu() << endl << "--------------------" << endl;
	return 0;
}
