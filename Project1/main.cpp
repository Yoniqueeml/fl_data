#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <set>
#include "CustomEvent.cpp"

void GetMixture(std::vector<std::string>& results, const std::string& word, size_t length, const std::string& Current_Res, size_t startIndx = 0)
{
	if (length == 0) {
		results.push_back(Current_Res);
	}
	else {
		for (size_t i = startIndx; i <= word.size() - length; i++) {
			GetMixture(results, word, length - 1, Current_Res + word[i], i + 1);
		}
	}
}

void Mixture(const std::string& word, std::vector<std::vector<std::string>>& v, const size_t& length = 1) {
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

void PrintDelimeter(size_t n, std::string str = "----------") {
	if (n == 0) return;
	PrintDelimeter(n - 1, str);
	std::cout << str;
}

size_t FindMaxSubSequences(const double& gamma, const size_t& number_of_days, const std::unordered_map<std::string, int>& data) {
	size_t count = 0;
	double factor = gamma * number_of_days;
	std::cout << std::endl << "Event Frequency is " << factor << std::endl <<  "Eligible subsequences :" << std::endl;
	PrintDelimeter(2);
	std::cout << std::endl;
	for (auto elem : data){
		if (elem.second > factor) {
			std::cout << "Sub - " << elem.first << " | Count - " << elem.second << " |" << std::endl;
			PrintDelimeter(2);
			std::cout << std::endl;
			count++;
		}
	}
	if (count == 0) {
		std::cout << std::endl;
		std::cout << "All the subsequences failed the factor" << std::endl << "Number of eligible subsequences is 0"<< std::endl;
		return 0;
	}
	std::cout << "Number of eligible subsequences is " << count << std::endl;
	return count;
}

void PrintAll(const std::vector<std::string> &words, const std::vector<std::vector<std::string>> &v) {
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << "For: " << words[i] << std::endl;
		for (auto it = v[i].begin(); it != v[i].end(); ++it) {
			std::cout << *it << "/";
		}
		std::cout << std::endl << "size:" << v[i].size() << std::endl;
		PrintDelimeter(1);
		std::cout << std::endl;
	}
	PrintDelimeter(1);
}

void CreateTable(std::unordered_map<std::string, int>& data, const std::vector<std::vector<std::string>> &all) {
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
}


void PrintTable(const std::unordered_map<std::string, int>& data){
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
		std::cout << "Sub - " << it->first << " | Count - " << it->second << " |  ";
		temp++;
	}
	std::cout << std::endl;
	PrintDelimeter(sep_factor+1);
	std::cout << std::endl;
}


int main() {
	srand(time(NULL));
	/*std::vector<std::string> words;
	const size_t length = 2;
	words.push_back("cde");
	words.push_back("abc");
	words.push_back("addab");
	words.push_back("jkropqel123ab");
	words.push_back("bcg");
    words.push_back("cdf");
	words.push_back("abcdfe");
	words.push_back("ydunab");
	std::vector<std::vector<std::string>> all;
	for (size_t i = 0; i < words.size(); ++i) {
		Mixture(words[i], all, length);
	}
	PrintAll(words,all);
	std::unordered_map<std::string, int> data;
	CreateTable(data, all);
	PrintTable(data);
	double gamma = 0.6; 
	FindMaxSubSequences(gamma, words.size(), data);*/
	Events ev;
	ev.Insert("abddddddddddddddddddddddddc");
	ev.Insert("cddddeddddddddddddddddddd");
	ev.Insert("addabddddddddddddddddddddddddddddd");
	ev.PrintOneTable(Alphabet(3));
	ev.RelativeFrequency(3, Alphabet(3), "cddddeddddddddddddddddddd", 0.4);
	//ev.PrintFullTable();
}