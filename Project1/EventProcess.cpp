#include "SubsequencesInfo.cpp"

template <typename T>
class MaxSub {
	Subsequences<T> db;
public:
	MaxSub(const int& length = 2) {
		Subsequences<T> db(length);
	}
	void FindMaxSub(const std::vector<std::vector<T>>& data, const double& gamma) {
		for (size_t i = 0; i < data.size(); ++i) {
			db.Insert(data[i]);
		}
		db.FindMaxSubSequences(gamma);
	}
};

class EventsTable {
	Events db;
public:
	EventsTable(const size_t& _size = 32, const size_t& _types = 36) {
		db = Events(_size, _types);
	}
	void RelativeFrequencyTick(const std::vector<std::vector<CustomEvent>>& ce, const int& tick, const int& type, const size_t& day_number, const double& gamma){
		if (tick < 0 || tick > 86398) return;
		for (size_t i = 0; i < ce.size(); ++i) {
			db.Insert(ce[i]);
		}
		db.RelativeFrequencyTick(tick, type, db.TakeDataWords()[day_number], gamma);
	}
	void RelativeFrequencyPlace(const std::vector<std::vector<CustomEvent>>& ce, const int& place, const int& type, const size_t& day_number, const double& gamma) {
		if (place < 0 || place >9) return;
		for (size_t i = 0; i < ce.size(); ++i) {
			db.Insert(ce[i]);
		}
		db.RelativeFrequencyPlace(place, type, db.TakeDataWords()[day_number], gamma);
	}
};

template<typename T>
class EventProcess : public EventsTable, public MaxSub<T> {
public:
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