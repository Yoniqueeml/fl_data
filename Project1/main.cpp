#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <set>

void GetMixture(std::vector<std::string>& results, std::string& word, size_t length, const std::string& Current_Res, size_t startIndx = 0)
{
	if (length == 0) {
		results.push_back(Current_Res);
	}
	else {
		for (int i = startIndx; i <= word.size() - length; i++) {
			GetMixture(results, word, length - 1, Current_Res + word[i], i + 1);
		}
	}
}

void Mixture(std::string& word, std::vector<std::vector<std::string>>& v, const size_t length = 1) {
	if (word.size() < length || length == 0) return;
	std::vector<std::string> tmp;
	std::string result;
	if (word.size() == length) {
		tmp.push_back(word);
		v.push_back(tmp);
		return;
	}
	GetMixture(tmp, word, length, result);
	v.push_back(tmp);
}

void FindMaxSubSequences(const double& gamma, const size_t& number_of_days, const std::map<std::string, int>& data) {
	double factor = gamma * number_of_days;
	bool check = false;
	std::cout << std::endl;
	std::cout << "Eligible subsequences:" << std::endl << "_____________________" << std::endl;
	for (auto elem : data){
		if (elem.second > factor) {
			std::cout << "Sub - " << elem.first << " | Count - " << elem.second << " |" << std::endl << "_____________________" << std::endl;
			check = true;
		}
	}
	if (check == false) {
		std::cout << "All the subsequences failed the factor" << std::endl;
	}
}

int main() {
	std::vector<std::string> words;
	const size_t length = 2;
	words.push_back("gabrw");
	words.push_back("sadf");
	words.push_back("zcvgab");
	std::vector<std::vector<std::string>> all;
	for (size_t i = 0; i < words.size(); ++i) {
		Mixture(words[i], all, length);
	}
	for (size_t i = 0; i < all.size(); i++) {
		for (auto it = all[i].begin(); it != all[i].end(); ++it) {
			std::cout << *it << "-";
		}
		std::cout << std::endl << "size:" << all[i].size() << std::endl <<"__________" <<std::endl;
	}
	std::cout << "_____________________" << std::endl;
	std::map<std::string, int> data;
	std::set<std::string> check;
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
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::cout << "Sub - " << it->first<< " | Count - " << it->second << " |" << std::endl;
	}
	std::cout << "_____________________" << std::endl;
	double gamma = 0.6;
	FindMaxSubSequences(gamma, words.size(), data);
}