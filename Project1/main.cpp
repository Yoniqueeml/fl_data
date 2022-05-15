#include <iostream>
#include <string.h>
#include "CustomEvent.cpp"
#include "SubsequencesInfo.cpp"

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
	srand(time(NULL));
	/*Subsequences cube(2);
	cube.Insert("abc");
	cube.Insert("zxac");
	cube.Insert("vgh");
	cube.PrintTable();*/

	// __________________


	Events ev;
	ev.Insert("]");
	ev.Insert("abdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddc");
	ev.Insert("cddddedddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
	ev.Insert("addabddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
	ev.PrintOneTable(3);
	ev.RelativeFrequency(3, 3, "addabddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd", 0.4);
	//ev.PrintFullTable();
	std::string templ = "privet,kakdela";
	std::string sub = "pkda";
	std::cout << Recognize(templ, sub);
}