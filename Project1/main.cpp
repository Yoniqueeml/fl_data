#include <iostream>
#include <string.h>
#include "EventProcess.cpp"

bool Recognize(const std::string& seq, const std::string& subseq) {
	if (seq.size() == 0 || subseq.size() == 0) return false;
	size_t count = 0;
	for (size_t i = 0; i < seq.size(); ++i) {
		if (subseq[count] == seq[i]) count++;
		if (count == subseq.size()) return true;
	}
	return false;
}

int main() {
	srand(time(0));
	EventProcess ev;
	std::vector<std::string> data;
	data.push_back("1|21|3|15|22|0|31|2|2|2|2|2|2|2|2|");
	data.push_back("1|21|3|15|22|2|2|2|2|2|2|2|2|");
	data.push_back("1|21|3|2|2|2|2|2|2|2|2|");
	data.push_back("1|21|3|2|2|2|2|2|2|2|");
	data.push_back("1|21|3|15|22|0|31|2|2|2|2|2|2|2|2|");
	data.push_back("1|21|3|2|2|2|2|2|2|2|2|2|2|2|2|2|");
	/*data.push_back("1|21||");
	data.push_back("1|21|3");
	data.push_back("1|2");
	data.push_back("1|2");
	data.push_back("1|");
	data.push_back("1|2");*/
	for (size_t i = 0; i < data.size(); ++i) {
		ev.Insert(data[i]);
	}
	ev.DoSomething();
}