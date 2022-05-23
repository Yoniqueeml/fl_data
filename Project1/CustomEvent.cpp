#include <vector>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

class CustomEvent {
	int type;
	int tick;
	int place;
public:
	CustomEvent(const std::string _t, const int& prev_tick = 0) {
		type = std::stoi(_t);
		tick = rand() % 86400;
		if (tick < prev_tick && tick != 86398) tick += 1;
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
	int*** table_place;
	int*** table_tick;
	size_t size;
	size_t count;
	size_t types;
	void FillTable() {
		for (auto it = data[data.size() - 1].begin(); it != data[data.size() - 1].end(); ++it) {
			int type = it->GetType();
			int place = it->GetPlace();
			table_place[type][data.size() - 1][place] += 1;
		}
		for (auto it = data[data.size() - 1].begin(); it != data[data.size() - 1].end(); ++it) {
			int temp = it->GetTick() / 2160;
			int type = it->GetType();
			table_tick[type][data.size() - 1][temp] += 1;
		}
	}
public:
	Events& operator=(const Events& rhs) {
		if (this == &rhs) return (*this);
		this->~Events();
		this->types = rhs.types;
		this->count = rhs.count;
		this->size = rhs.size;
		this->words = rhs.words;
		this->data = rhs.data;
		for (size_t i = 0; i < types; ++i)
		{
			table_place[i] = new int* [size];
			for (size_t j = 0; j < size; ++j)
			{
				table_place[i][j] = new int[9];
				for (size_t k = 0; k < 9; ++k)
				{
					table_place[i][j][k] = rhs.table_place[i][j][k];
				}
			}
		}                             
		table_tick = new int** [types];
		for (size_t i = 0; i < types; ++i) {
			table_tick[i] = new int* [size];
			for (size_t j = 0; j < size; ++j) {
				table_tick[i][j] = new int[40];
				for (size_t k = 0; k < 40; ++k) {
					table_tick[i][j][k] = rhs.table_tick[i][j][k];
				}
			}
		}
		return *this;
	}
	Events(const size_t& _size = 32, const size_t& _types = 36) {
		size = _size;
		types = _types;
		count = 0;
		table_place = new int** [_types]; // table_place
		for (size_t i = 0; i < _types; ++i)
		{
			table_place[i] = new int* [size];
			for (size_t j = 0; j < size; ++j)
			{
				table_place[i][j] = new int[9];
				for (size_t k = 0; k < 9; ++k)
				{
					table_place[i][j][k] = 0;
				}
			}
		}                                //--
		// table_tick  24 hrs = 86400 tick;  86400/40 = 2160 ticks in one; 2160 ticks == 36minutes
		table_tick = new int** [_types];
		for (size_t i = 0; i < _types; ++i) {
			table_tick[i] = new int* [size];
			for (size_t j = 0; j < size; ++j) {
				table_tick[i][j] = new int[40];
				for (size_t k = 0; k < 40; ++k) {
					table_tick[i][j][k] = 0; 
				}
			}
		}
	}
	std::vector<std::string> TakeData() const {
		return words;
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
		std::vector<std::string> events;
		std::string result;
		for (size_t i = 0; i < word.size(); ++i) {
			if (word[i] == '|') {
				if (result.size() != 0) events.push_back(result);
				result.clear();
			}
			else {
				result += word[i];
				if (i + 1 == word.size()) events.push_back(result);
			}
		}
		std::vector<CustomEvent> sequence;
		if (sequence.size() == 0) {
			sequence.push_back(CustomEvent(events[0], 0));
		}
		for (size_t i = 1; i < events.size(); ++i) {
			sequence.push_back(CustomEvent(events[i], sequence[i-1].GetTick()));
		}
		words.push_back(word);
		data.push_back(sequence);
		count++;
		this->FillTable();
	}
	void PrintSpace(size_t spc) const{
		if (spc == 0) return;
		PrintSpace(spc - 1);
		std::cout << " ";
	}
	void PrintChoose(const size_t i, const std::string& str, const size_t & amount) const {
		size_t space = words[i].size();
		std::cout << " ";
		PrintSpace(space);
		for (size_t k = 0; k < amount; ++k) {
			std::cout << str << k <<"   ";
		}
	}
	void PrintAllPlace() const {
		if (count == 0) std::cout << "Table is empty";
		for (size_t k = 0; k < types; ++k) {
			std::cout << std::endl << "Table for event:" << k << std::endl;
			for (size_t i = 0; i < count; ++i) {
				PrintChoose(i, "place", size);
				std::cout<< std::endl << words[i] << "|   ";
				for (size_t j = 0; j < 9; ++j) {
					std::cout << table_place[k][i][j] << "        ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
		}
	}
	void PrintAllTick() const {
		if (count == 0) std::cout << "Table is empty";
		for (size_t k = 0; k < types; ++k) {
			std::cout << std::endl << "Table for event:" << k << std::endl;
			for (size_t i = 0; i < count; ++i) {
				PrintChoose(i, "tick", 40);
				std::cout << std::endl << words[i] << "|   ";
				for (size_t j = 0; j < 40; ++j) {
					std::cout << table_tick[k][i][j] << "        ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
		}
	}
	void PrintOnePlace(const size_t& _type) const {
		if (count == 0) std::cout << "Table is empty";
		if (_type < 0 && _type>types) {
			std::cout << "No information for this event type";
			return;
		}
		std::cout << std::endl << "Table for event: " << _type << std::endl;
		for (size_t i = 0; i < count; ++i) {
			PrintChoose(i, "place", size);
			std::cout << std::endl;
			std::cout << words[i] << "|   ";
			for (size_t j = 0; j < 9; ++j) {
				std::cout << table_place[_type][i][j] << "        ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
	}
	void PrintOneTick(const size_t& _tick = 0) const {
		if (count == 0) std::cout << "Table is empty";
		if (_tick < 0 && _tick > 86400) {
			std::cout << "No information for this tick";
			return;
		}
		int temp = _tick / 2160;
		size_t d1 = 0;
		size_t d2 = 2160;
		while (d2 < _tick) {
			d2 += 2160;
		}
		d1 = d2 - 2160;
		std::cout << std::endl << "Table for tick_time  " << _tick << "  [" <<d1 << ";"<< d2<<"]" <<std::endl;
		std::cout << "column: " << temp << std::endl;
		for (size_t i = 0; i < count; ++i) {
			std::cout << std::endl;
			std::cout << words[i] << std::endl;
			int tmp = 0;
			for (size_t j = 0; j < types; ++j) {
				std::cout << table_tick[j][i][temp] << "        ";
				tmp++;
				if (tmp == 10) {
					std::cout << std::endl;
					tmp = 0;
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "___________________________________________________________________________________" << std::endl;
	}
	void RelativeFrequencyPlace(const int& place, const int& _type, const std::string& str, const double& gamma) const{
		int sum = 0;
		bool check = false;
		int need = 0;
		for (size_t i = 0; i < words.size(); ++i) {
			if (words[i] == str) {
				check = true;
				need = table_place[_type][i][place];
				break;
			}
		}
		if (check == false) {
			std::cout << std::endl << "No matches with your str/type/place";
			return;
		}
		for (size_t i = 0; i < count; ++i) {
			sum += table_place[_type][i][place];
		}
		std::cout << "Event: " << _type << std::endl << "Place: " << place << std::endl << "Sequence: " << str;
		std::cout << std::endl << "Number of indicated str/place/type = " << need;
		std::cout << std::endl << "Number of all places with this type = " << sum << std::endl;
		std::cout << "Relative Frequency: " << (double)need / sum << std::endl;
		std::cout << "Target Frequency: " << gamma * sum << std::endl;
	}
	void RelativeFrequencyTick(const int& tick, const int& _type, const std::string& str, const double& gamma) const {
		int sum = 0;
		bool check = false;
		int need = 0;
		int temp = tick / 2160;
		for (size_t i = 0; i < words.size(); ++i) {
			if (words[i] == str) {
				check = true;
				need = table_place[_type][i][temp];
				break;
			}
		}
		if (check == false) {
			std::cout << std::endl << "No matches with your str/type/tick";
			return;
		}
		for (size_t i = 0; i < count; ++i) {
			sum += table_place[_type][i][temp];
		}
		std::cout << "Event: " << _type << std::endl << "Tick: " << tick << std::endl << "Sequence: " << str;
		std::cout << std::endl << "Number of indicated str/place/tick = " << need;
		std::cout << std::endl << "Number of all places with this tick-time = " << sum << std::endl;
		std::cout << "Relative Frequency: " << (double)need / sum << std::endl;
		std::cout << "Target Frequency: " << gamma * sum << std::endl;
	}
	~Events() {
		for (size_t i = 0; i < types; ++i) {
			for (size_t j = 0; j < size; ++j) {
				delete table_place[i][j];
			}
			delete [] table_place[i];
		}
		delete[] table_place;
		for (size_t i = 0; i < types; ++i) {
			for (size_t j = 0; j < size; ++j) {
				delete table_tick[i][j];
			}
			delete[] table_tick[i];
		}
		delete[] table_tick;
	}
};
