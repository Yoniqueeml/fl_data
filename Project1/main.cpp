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

#define cube
#define freq
int main() {
	srand(time(0));
#ifdef cube
	EventProcess d;
	size_t days=3;
	std::vector<std::vector<int>> data(days);
	data[0] = { 0, 2, 5, 1, 3 };
	data[1] = { 0, 2, 5, 4, 7 };
	data[2] = { 1, 5, 4, 7 };
	d.FindMaxSub(data, 0.4);
#endif
#ifdef freq
	EventProcess ev;
	std::vector<std::vector<CustomEvent>> data2;
	std::vector<int> types = { 5, 0, 1, 2, -1, 5, 0 };
	std::vector<int> placs = { 0, 0, 1, 2, -1, 0, 0 };
	std::vector<int> ticks = { 0, 0, 0, 2, -1, 0, 0 };
	size_t day = 0;
	size_t i = 0;
	while (i < types.size()) {
		std::vector<CustomEvent> tmp;
		data2.push_back(tmp);
		while (i < types.size() && types[i] != -1) {
			data2[day].push_back(CustomEvent(types[i], placs[i], ticks[i]));
			i++;
		}
		day++;
		++i;
	}
	ev.RelativeFrequencyPlace(data2, 0, 5, 0, 0.2);
#endif
}