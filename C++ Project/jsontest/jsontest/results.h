#include <iostream>

using namespace std;

class results {
private:
	int positive;
	int negative;
	int neutral;
public:
	void uppos();
	void upneg();
	void upneu();
	int getpos();
	int getneg();
	int getneu();
	results();
	friend ostream& operator<<(ostream&, const results&);
};
