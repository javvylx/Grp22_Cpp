#include <iostream>
#include <string>
#include <sstream>
#include "include/twitcurl.h"
#include "include/oauthlib.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
extern "C" void __imp__set_output_format(void) {};


int tweetSearch(string searchStr) {
	string tmpStr;
	string replyMsg;
	char tmpBuf[1024];
	//creating twitter crawler object
	twitCurl twitterObj;

	//creating output json file to dump tweets
	std::ofstream file_id;
	file_id.open("output.json");

	//will change this part later to take in the keys from a file
	string consumerKey = "GnLXL1pMUMiBLO6BNhxmnRrlo";
	string consumerKeySecret = "KwYkPlnEoFqoDDaHZQW25yxLKCOZOXdf1lHZh5KIHrkaaHIeFJ";
	string myOAuthAccessTokenKey = "722686561997955072-9kev4dceGiQgKOctlF30zfTIeuOZeo2";
	string myOAuthAccessTokenSecret = "TUgs8ZQyRY3j5vqkB08rOnlO9zFUY7uOa19rbZePkqkzX";

	twitterObj.getOAuth().setConsumerKey(consumerKey);
	twitterObj.getOAuth().setConsumerSecret(consumerKeySecret);
	twitterObj.getOAuth().setOAuthTokenKey(myOAuthAccessTokenKey);
	twitterObj.getOAuth().setOAuthTokenSecret(myOAuthAccessTokenSecret);

	if (twitterObj.search(searchStr)) {
		twitterObj.getLastWebResponse(replyMsg);
		file_id << replyMsg.c_str();
		return 0;
		//this line for debugging use
		//cout <<"response: " << replyMsg.c_str() << endl;
	}
	else {
		twitterObj.getLastCurlError(replyMsg);
		cout << "error: " << replyMsg.c_str() << endl;
		return -1;
	}

}

int main() {
	tweetSearch("stock");
}