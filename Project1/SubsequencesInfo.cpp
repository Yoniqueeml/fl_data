#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

class Subsequences {
	std::vector<std::string> words;
	std::vector<std::vector<std::string>> all;
	std::unordered_map<std::string, int> data;
	size_t length;
	size_t types;
	size_t days;
	size_t count;
	void RefreshTable() {
		std::set<std::string> check;
		for (size_t j = 0; j < all[count].size(); ++j) {
			if (check.find(all[count][j]) == check.end()) {
				check.insert(all[count][j]);
				data[all[count][j]] += 1;
			}
			else continue;
		}
		check.clear();
	}
	void CreateTableWithNewLength() {
		std::set<std::string> check;
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
	void Mixture() {
		if (words[count].size() < length || length == 0) return;
		std::vector<std::string> tmp;
		std::string result;
		for (size_t i = 0; i < words[count].size(); ++i) {
			if (words[count][i] == '|') {
				if (result.size() != 0) tmp.push_back(result);
				result.clear();
			}
			else {
				result += words[count][i];
				if (i + 1 == words[count].size()) tmp.push_back(result);
			}
		}
		std::vector<std::vector<std::string>> fixed_length;
		std::vector<std::string> ar;
		GetMixture(fixed_length, ar, tmp, length);
		tmp.clear();
		for (size_t i = 0; i < fixed_length.size(); ++i) {
			result.clear();
			for (size_t j = 0; j < fixed_length[i].size(); ++j) {
				result += fixed_length[i][j];
				result += "|";
			}
			tmp.push_back(result);
		}
		all.push_back(tmp);
	}
	void GetMixture(std::vector<std::vector<std::string>>& results, std::vector<std::string>& cur_res, std::vector<std::string>& word, size_t _length, size_t startIndx = 0)
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

	void Insert(const std::string& str) {
		words.push_back(str);
		Mixture();
		RefreshTable();
		count++;
	}

	size_t FindMaxSubSequences(const double& gamma) const{
		size_t count = 0;
		double factor = gamma * (double(words.size())+1);
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
			std::cout << "For: " << words[i] << std::endl;
			for (auto it = all[i].begin(); it != all[i].end(); ++it) {
				std::cout << *it << "/";
			}
			std::cout << std::endl << "size:" << all[i].size() << std::endl;
			PrintDelimeter(1);
			std::cout << std::endl;
		}
		PrintDelimeter(1);
	}
	void PrintTable() const{
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
