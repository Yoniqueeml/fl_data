#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <map>

void GetMixture(std::vector<std::string>& results, std::string& word, int length, const std::string& Current_Res, int startIndx = 0)
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

void Mixture(std::string& word, std::vector<std::vector<std::string>>& v, const int length = 1) {
	std::vector<std::string> tmp;
	std::string result;
	GetMixture(tmp, word, length, result);
	v.push_back(tmp);
}

void FindMaxSubSequences(const double& gamma, const int& length, const std::map<std::string, int>& data) {
	double factor = gamma * length;
	bool check = false;
	std::cout << "Eligible subsequences" << std::endl;
	for (auto elem : data){
		if (elem.second > factor) {
			std::cout << "Sub - " << elem.first << "//  Count - " << elem.second << std::endl;
			check = true;
		}
	}
	if (check == false) {
		std::cout << "All the subsequences failed the factor" << std::endl;
	}
}

int main() {
	std::vector<std::string> words;
	const int length = 2;
	const int power = 9;
	words.push_back("12345");
	words.push_back("312");
	std::vector<std::vector<std::string>> all;

	for (size_t i = 0; i < words.size(); ++i) {
		Mixture(words[i], all, length);
	}

	for (int i = 0; i < all.size(); i++) {
		for (auto it = all[i].begin(); it != all[i].end(); ++it) {
			std::cout << *it << "-";
		}
		std::cout << std::endl << "size:" << all[0].size() << std::endl;
	}

	std::map<std::string, int> data;
	for (int i = 0; i < all.size(); ++i) {
		for (int j = 0; j < all[i].size(); ++j) {
			data[all[i][j]] += 1;
		}
	}
	
	for (auto it = data.begin(); it != data.end(); ++it) {
		std::cout << "Sub - " << it->first<< "/// Count - " << it->second << std::endl;
	}
	
	double gamma = 2;
	FindMaxSubSequences(gamma, length, data);
	
}