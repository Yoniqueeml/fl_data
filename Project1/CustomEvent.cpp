#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stdlib.h>
#include <time.h>

class CustomEvent {
	int type;
	int tick;
	int place;
public:
	CustomEvent(const char& _word, const int& types, const int& prev_tick = 0) {
		type = rand()%types;
		tick = rand() % 100 + 1 + prev_tick / 2;
		place = rand() % 9;
	}
	int GetTick() const {
		return tick;
	}
	int GetType() const {
		return type;
	}
	int GetPlace() const {
		return place;
	}
};

class Events {
	std::vector<std::string> words;
	std::vector<std::vector<CustomEvent>> data;
	int*** table;
	size_t size;
	size_t count;
	size_t types;
public:
	Events(const int& _size = 32, const int& _types = 36) {
		size = _size;
		types = _types;
		count = 0;
		table = new int** [_types];
		for (int i = 0; i < _types; i++)
		{
			table[i] = new int* [size];
			for (int j = 0; j < size; j++)
			{
				table[i][j] = new int[9];
				for (int k = 0; k < 9; k++)
				{
					table[i][j][k] = 0;
				}
			}
		}
	}
	std::vector<std::vector<CustomEvent>> TakeData() const {
		return data;
	}
	int SeqInTable(const std::string& str) const {
		if (str.size() == 0) return -1;
		for (size_t i = 0; i < words.size(); ++i) {
			if (words[i] == str) return i;
		}
		return false;
	}
	void PrintData() const {
		if (count == 0) std::cout << "Data is empty";
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << "Sequence: " << words[i] << std::endl;
			for (auto it = data[0].begin(); it != data[0].end(); ++it) {
				std::cout << "Event: " << it->GetType() << std::endl;
				std::cout << "Tick: " << it->GetTick() << "   Place:" << it->GetPlace() << std::endl;
			}   
		}
	}
	void Insert(const std::string& word) {
		if (count + 1 == size) {
			std::cout << "It`s all filled in" << std::endl;
			return;
		}
		std::vector<CustomEvent> sequence;
		if (sequence.size() == 0) {
			sequence.push_back(CustomEvent(word[0], types));
		}
		for (size_t i = 1; i < word.size(); ++i) {
			sequence.push_back(CustomEvent(word[i], types, sequence[i-1].GetTick()));
		}
		words.push_back(word);
		data.push_back(sequence);
		auto it = data[data.size() - 1].begin();
		count++;
		this->FillTable();
	}
	void FillTable() {
		for (auto it = data[data.size() - 1].begin(); it != data[data.size() - 1].end(); ++it) {
			table[it->GetType()][data.size() - 1][it->GetPlace()] += 1;
		}
	}
	void PrintSpace(size_t spc) const{
		if (spc == 0) return;
		PrintSpace(spc - 1);
		std::cout << " ";
	}
	void PrintPlace(const size_t i) const {
		size_t space = words[i].size();
		std::cout << " ";
		PrintSpace(space);
		for (size_t k = 0; k < 9; ++k) {
			std::cout << "place" << k <<"   ";
		}
	}
	void PrintFullTable() const {
		if (count == 0) std::cout << "Table is empty";
		for (size_t k = 0; k < types; ++k) {
			std::cout << std::endl << "Table for event:" << k << std::endl;
			for (size_t i = 0; i < count; ++i) {
				PrintPlace(i);
				std::cout<< std::endl << words[i] << "|   ";
				for (size_t j = 0; j < 9; ++j) {
					std::cout << table[k][i][j] << "        ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
		}
	}
	void PrintOneTable(const int& _type) const {
		if (count == 0) std::cout << "Table is empty";
		if (_type < 0 && _type>types) {
			std::cout << "No information for this event type";
			return;
		}
		std::cout << std::endl << "Table for event: " << _type << std::endl;
		for (size_t i = 0; i < count; ++i) {
			PrintPlace(i);
			std::cout << std::endl;
			std::cout << words[i] << "|   ";
			for (size_t j = 0; j < 9; ++j) {
				std::cout << table[_type][i][j] << "        ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
	}
	void RelativeFrequency(const int& place, const int& _type, const std::string& str, const double& gamma) const{
		int sum = 0;
		bool check = false;
		int need = 0;
		for (size_t i = 0; i < words.size(); ++i) {
			if (words[i] == str) {
				check = true;
				need = table[_type][i][place];
				break;
			}
		}
		if (check == false) {
			std::cout << std::endl << "No matches with your str/type/place";
			return;
		}
		for (size_t i = 0; i < count; ++i) {
			sum += table[_type][i][place];
		}
		std::cout << "Event: " << _type << std::endl << "Place: " << place << std::endl << "Sequence: " << str;
		std::cout << std::endl << "Number of indicated str/place/type = " << need;
		std::cout << std::endl << "Number of all places with this type = " << sum << std::endl;
		std::cout << "Relative Frequency: " << (double)need / sum << std::endl;
		std::cout << "Target Frequency: " << gamma * sum << std::endl;
	}

	~Events() {
		for (size_t i = 0; i < types; ++i) {
			for (size_t j = 0; j < size; ++j) {
				delete table[i][j];
			}
			delete [] table[i];
		}
		delete[] table;
	}
};

class EventProcess {
	Events db;
public:
	bool Recognize(const std::string& seq, const std::string& subseq, const int& _tiy) {
		if (seq.size() == 0 || subseq.size() == 0) return false;
		int temp = db.SeqInTable(seq);
		if (temp == -1) return false;
		size_t count = 0;
		for (size_t i = 0; i < seq.size(); ++i) {
			if (subseq[count] == seq[i] && db.TakeData()[temp][count].GetType() == _tiy) count++;
			if (count == subseq.size()) return true;
		}
		return false;
	}

};