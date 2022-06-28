#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include "CustomEvent.cpp"

template<>
struct std::hash<CustomEvent> {
	size_t operator()(const CustomEvent& ce) const{
		std::string result;
		result += ce.GetPlace();
		result += ce.GetTick();
		result += ce.GetType();
		return std::hash<std::string>()(result);
	}
};
template<>
struct std::equal_to<CustomEvent> {
	size_t operator()(const CustomEvent& lhs, const CustomEvent& rhs) const {
		return ((lhs.GetPlace() == rhs.GetPlace()) && (lhs.GetTick() == rhs.GetTick()) && (lhs.GetType() == rhs.GetType()));
	}
};
template <typename T, typename hasher = std::hash<T>, typename KeyEqual = std::equal_to<T>>
class Subsequences {
	std::vector<std::vector<T>> all;
	std::unordered_map<T, int, hasher, KeyEqual> data;
	size_t length;
	size_t types;
	size_t days;
	size_t count;
	template <typename T>
	void RefreshTable() {
		std::set<T> check;
		for (size_t j = 0; j < all[count].size(); ++j) {
			if (check.find(all[count][j]) == check.end()) {
				check.insert(all[count][j]);
				data[all[count][j]] += 1;
			}
			else continue;
		}
		check.clear();
	}
	template <typename T>
	void CreateTableWithNewLength() {
		std::set<T> check;
		data.clear();
		for (size_t i = 0; i < all.size(); ++i) {
			for (size_t j = 0; j < all[i].size(); ++j) {
				if (check.find(all[i][j]) == check.end()) {
					check.insert(all[i][j]);
					data[all[i][j]] += 1;
				}
				else continue;
			}
			check.clear();
		}
	}
	template <typename T>
	void Mixture(const std::vector<T>& data) {
		if (length == 0) return;
		std::vector<T> tmp = data;
		std::vector<std::vector<T>> fixed_length;
		std::vector<T> ar;
		GetMixture(fixed_length, ar, tmp, length);
		all.push_back(tmp);
	}
	template <typename T>
	void GetMixture(std::vector<std::vector<T>>& results, std::vector<T>& cur_res, std::vector<T>& word, size_t _length, size_t startIndx = 0)
	{
		if (_length == 0) {
			results.push_back(cur_res);
		}
		if (startIndx >= word.size()) return;
		else {
			for (size_t i = startIndx; i <= word.size() - _length; i++) {
				if (i >= word.size()) return;
				cur_res.push_back(word[i]);
				GetMixture(results, cur_res, word, _length - 1, i + 1);
				cur_res.pop_back();
			}
		}
	}
	void PrintDelimeter(size_t n, std::string str = "----------") const {
		if (n == 0) return;
		PrintDelimeter(n - 1, str);
		std::cout << str;
	}
public:
	Subsequences(const int& _length = 2, const int& _types = 36, const int& _size = 32) {
		length = _length;
		types = _types;
		days = _size;
		count = 0;
	}
	void NewLength(const size_t& _length) {
		length = _length;
		CreateTableWithNewLength();
	}
	template <typename T>
	void Insert(const std::vector<T>& data) {
		Mixture(data);
		RefreshTable<T>();
		count++;
	}

	size_t FindMaxSubSequences(const double& gamma) const {
		size_t count = 0;
		double factor = gamma * (double(this->count + 1));
		std::cout << gamma;
		std::cout << std::endl << "Event Frequency is " << factor << std::endl << "Eligible subsequences :" << std::endl;
		PrintDelimeter(2);
		std::cout << std::endl;
		for (auto elem : data) {
			if (elem.second > factor) {
				std::cout << "Sub - " << elem.first << "  Count - " << elem.second << " |" << std::endl;
				PrintDelimeter(2);
				std::cout << std::endl;
				count++;
			}
		}
		if (count == 0) {
			std::cout << std::endl;
			std::cout << "All the subsequences failed the factor" << std::endl << "Number of eligible subsequences is 0" << std::endl;
			return 0;
		}
		std::cout << "Number of eligible subsequences is " << count << std::endl;
		return count;
	}
	void PrintAll() const {
		for (size_t i = 0; i < all.size(); i++) {
			for (auto it = all[i].begin(); it != all[i].end(); ++it) {
				std::cout << *it << "/";
			}
			std::cout << std::endl << "size:" << all[i].size() << std::endl;
			PrintDelimeter(1);
			std::cout << std::endl;
		}
		PrintDelimeter(1);
	}
	void PrintTable() const {
		int sep_factor;
		if (data.size() > 3) sep_factor = 8;
		else if (data.size() < 2) sep_factor = 4;
		else sep_factor = 6;
		size_t temp = 0;
		PrintDelimeter(sep_factor);
		std::cout << std::endl;
		for (auto it = data.begin(); it != data.end(); ++it) {
			if (temp == 4) {
				temp = 0;
				std::cout << std::endl;
			}
			std::cout << "Sub - " << it->first << "  Count - " << it->second << " |  ";
			temp++;
		}
		std::cout << std::endl;
		PrintDelimeter(sep_factor + 1);
		std::cout << std::endl;
	}
};
