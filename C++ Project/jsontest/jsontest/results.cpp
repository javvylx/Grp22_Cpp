#include<iostream>
#include "results.h"

using namespace std;

results::results() {
	positive = 0;
	negative = 0;
	neutral = 0;
}
void results::uppos() {
	positive += 1;
}
void results::upneg() {
	negative += 1;
}
void results::upneu() {
	neutral += 1;
}
int results::getpos() {
	return positive;
}
int results::getneg() {
	return negative;
}
int results::getneu() {
	return neutral;
}


ostream& operator<<(ostream& out, const results& result) {
	out << "Sentiment" << endl << "Positive: " << result.positive << endl << "Neutral:" << result.neutral << endl << "Negative: " << result.negative << endl << "--------------------" << endl;
	return out;
}
