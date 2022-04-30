#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stdlib.h>
#include <time.h>

enum class Alphabet {
	a, b, c, d, e, f, g, h, 
	i, j, k, l, m, n, o, p, 
	q, r, s, t, u, v, w, x,
	y, z
};

class CustomEvent {
	Alphabet type;
	struct date {
		int day;
		int hour;
	};
	date date_time;
	int place;
public:
	CustomEvent(const char& _word) {
		this->type = Alphabet(_word-97);
		date_time.day = rand() % 32;
		date_time.hour = rand() % 24;
		this->place = rand() % 9;
	}
	int GetDay() const {
		return date_time.day;
	}
	int GetHour() const {
		return date_time.hour;
	}
	Alphabet GetType() const {
		return type;
	}
	int GetPlace() const {
		return place;
	}
};

class Events {
	std::vector<std::string> words;
	std::vector<std::list<CustomEvent>> data;
	int*** table;
	size_t size;
	size_t count;
public:
	Events(const int& _size = 32) {
		size = _size;
		count = 0;
		table = new int** [26];
		for (int i = 0; i < 26; i++)
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

	void PrintData() const {
		if (count == 0) std::cout << "Data is empty";
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << "Sequence: " << words[i] << std::endl;
			for (auto it = data[0].begin(); it != data[0].end(); ++it) {
				std::cout << "Event: " << char(int(it->GetType()) + 97) << std::endl;
				std::cout << "Day: " << it->GetDay() << "   Hour: " << it->GetHour() << "   Place:" << it->GetPlace() << std::endl;
			}   
		}
	}
	void Insert(const std::string& word) {
		++count;
		if (count == size) {
			std::cout << "It`s all filled in" << std::endl;
			return;
		}
		words.push_back(word);
		std::list<CustomEvent> sequence;
		for (size_t i = 0; i < word.size(); ++i) {
			sequence.push_back(CustomEvent(word[i]));
		}
		data.push_back(sequence);
		auto it = data[data.size() - 1].begin();
		this->FillTable();
	}
	void FillTable() {
		for (auto it = data[data.size() - 1].begin(); it != data[data.size() - 1].end(); ++it) {
			table[int(it->GetType())][data.size() - 1][it->GetPlace()] += 1;
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
		for (size_t k = 0; k < 26; ++k) {
			std::cout << std::endl << "Table:" << char(int(Alphabet(k)) + 97) << std::endl;
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
	void PrintOneTable(const Alphabet& type) const {
		if (count == 0) std::cout << "Table is empty";
		std::cout << std::endl << "Table for one event: " << char(int(Alphabet(type)) + 97) << std::endl;
		int type_table = int(type);
		for (size_t i = 0; i < count; ++i) {
			PrintPlace(i);
			std::cout << std::endl;
			std::cout << words[i] << "|   ";
			for (size_t j = 0; j < 9; ++j) {
				std::cout << table[type_table][i][j] << "        ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
	}
	void RelativeFrequency(const int& place, const Alphabet& type, const std::string& str, const double& gamma) const{
		int sum = 0;
		bool check = false;
		int type_table = int(type);
		int need = 0;
		for (size_t i = 0; i < words.size(); ++i) {
			if (words[i] == str) {
				check = true;
				need = table[type_table][i][place];
				break;
			}
		}
		if (check == false) {
			std::cout << std::endl << "No matches with your str/type/place";
			return;
		}
		for (size_t i = 0; i < count; ++i) {
			sum += table[type_table][i][place];
		}
		std::cout << "Event: " << char(int(Alphabet(type)) + 97) << std::endl << "Place: " << place << std::endl << "Sequence: " << str;
		std::cout << std::endl << "Number of indicated str/place/type = " << need;
		std::cout << std::endl << "Number of all places with this type = " << sum << std::endl;
		std::cout << "Relative Frequency: " << (double)need / sum << std::endl;
		std::cout << "Target Frequency: " << gamma * sum << std::endl;
	}

	~Events() {
		for (size_t i = 0; i < 26; ++i) {
			for (size_t j = 0; j < size; ++j) {
				delete table[i][j];
			}
			delete [] table[i];
		}
		delete[] table;
	}
};