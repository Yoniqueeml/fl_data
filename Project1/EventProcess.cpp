#include "CustomEvent.cpp"
#include "SubsequencesInfo.cpp"

class EventProcess {
	Events db;
	Subsequences db2;
	void Task0() const{
		double gamma;
		system("cls");
		std::cout << "Input gamma: ";
		std::cin >> gamma;
		std::cout << std::endl;
		db2.FindMaxSubSequences(gamma);
	}
	void Task1() const {
		size_t type;
		size_t place;
		size_t day_number;
		double gamma;
		system("cls");
		std::cout << "Input type: ";
		std::cin >> type;
		std::cout << std::endl << "Input place: ";
		std::cin >> place;
		std::cout << std::endl << "Input day_number: ";
		std::cin >> day_number;
		std::cout << std::endl;
		std::cout << std::endl << "Input gamma: ";
		std::cin >> gamma;
		std::cout << std::endl;
		if (day_number < 0 || day_number > db.TakeData().size()) return;
		db.RelativeFrequencyPlace(place, type, db.TakeData()[day_number], gamma);
	}
	void Task2() const {
		size_t type;
		size_t tick;
		size_t day_number;
		double gamma;
		system("cls");
		std::cout << "Input type: ";
		std::cin >> type;
		std::cout << std::endl << "Input tick: ";
		std::cin >> tick;
		std::cout << std::endl << "Input day_number: ";
		std::cin >> day_number;
		std::cout << std::endl;
		std::cout << std::endl << "Input gamma: ";
		std::cin >> gamma;
		std::cout << std::endl;
		if (day_number < 0 || day_number > db.TakeData().size()) return;
		db.RelativeFrequencyTick(tick, type, db.TakeData()[day_number], gamma);
	}
public:
	EventProcess(const size_t& types = 36, const size_t& size =32, const size_t& length=2) {
		Events db_t(size, types);
		Subsequences db2_t(length);
		db = db_t;
		db2 = db2_t;
	}
	void Insert(const std::vector<std::string>& ui) {
		for (size_t i = 0; i < ui.size(); ++i) {
			db.Insert(ui[i]);
			db2.Insert(ui[i]);
		}
	}
	void DoSomething() const{
		system("cls");
		std::cout << "Input number:" << std::endl << "0 - see all subsequences of certain length (u'll input gamma for frequency)" << std::endl
			<< "1 - see sequences with certain type+place(u'll input type and place, day number and gamma)" << std::endl
			<< "2 - see sequences with certain type+tick(u'll input type and tick, day number and gamma)" << std::endl;
		size_t choice;
		std::cin >> choice;
		if (choice > 2) return;
		if (choice == 0) Task0();
		else if (choice == 1) Task1();
		else Task2();
	}
	/*bool Recognize(const std::string& seq, const std::string& subseq, const int& _tiy) {
		if (seq.size() == 0 || subseq.size() == 0) return false;
		int temp = db.SeqInTable(seq);
		if (temp == -1) return false;
		size_t count = 0;
		for (size_t i = 0; i < seq.size(); ++i) {
			if (subseq[count] == seq[i] && db.TakeData()[temp][count].GetType() == _tiy) count++;
			if (count == subseq.size()) return true;
		}
		return false;
	}*/
};