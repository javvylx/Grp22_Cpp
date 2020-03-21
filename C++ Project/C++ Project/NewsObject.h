#pragma once
#include <iostream>
using namespace std;

class NewsObject {
public:
	string author, content, description, publishedAt, sourceID, sourceName, title, url, urlToImage;
	NewsObject(string, string, string, string, string, string, string, string, string);

	string getauthor();
	string getcontent();
	string getdescription();
	string getpublishedAt();
	string getSourceID();
	string getsourceName();
	string gettitle();
	string geturl();
	string geturltoimage();
};

NewsObject::NewsObject(string a, string b, string c, string d, string e, string f, string g, string h, string i) {
	author = a;
	content = b;
	description = c;
	publishedAt = d;
	sourceID = e;
	sourceName = f;
	title = g;
	url = h;
	urlToImage = i;
}

string NewsObject::getauthor() {
	return author;
}

string NewsObject::getcontent() {
	return content;
}

string NewsObject::getdescription() {
	return description;
}

string NewsObject::getpublishedAt() {
	return publishedAt;
}

string NewsObject::getSourceID() {
	return sourceID;
}

string NewsObject::getsourceName() {
	return sourceName;
}

string NewsObject::gettitle() {
	return title;
}

string NewsObject::geturl() {
	return url;
}

string NewsObject::geturltoimage() {
	return urlToImage;
}