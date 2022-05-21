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
#ifdef task1
	Subsequences cube(2);
	cube.Insert("123|321|2|4");
	cube.Insert("2|5|6|4");
	cube.Insert("24|12|13|2|4");
	cube.FindMaxSubSequences(0.8);
#endif
#ifdef task2
	Events ev;
	ev.Insert("2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|");
	ev.Insert("2|2|22|2|2|2|2|2||2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|");
	ev.Insert("2|2|2|2|2|2|2|2|2|2|22|2|2|2|2|2|2|2||2|2|2|2|2|2|2|");
	ev.Insert("2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|");
	ev.PrintAllTick();
	//ev.RelativeFrequencyTick(500, 3, "addabddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", 0.4);
	//ev.PrintFullTable();
	ev.Insert("2|");
	std::string templ = "privet,kakdela";
	std::string sub = "pkda";
	//std::cout << Recognize(templ, sub);
#endif
	std::vector<std::string> data;
	data.push_back("1|21|3|15|22|0|31|2|2|2|2|2|2|2|2|");
	data.push_back("3|17|2|4|4|2|2|2|2|2|2|2|");
	data.push_back("2|4|2|2|2|2|2|3|2|2|0|2|1|2|2|2|2|");
	data.push_back("2|4|5|13|2|2|2|2|2|2|2|");
	data.push_back("2|4|2|2|2|2|2|2|2|2|2|2|2|2|2|2|2|");
	EventProcess ev(data);
	ev.DoSomething();
}