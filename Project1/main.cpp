#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void GetMixture(const char* word, const int size, int word_counter, char* result, int result_counter, std::vector<char*> &v ,const int length = 1){
	if (word_counter >= size || result_counter >= length) {
		return;
	}
	GetMixture(word, size, word_counter + 1, result, result_counter, v, length);
	result[result_counter] = word[word_counter];
	result[result_counter + 1] = 0;
	if (result_counter + 1  == length) { 
		char* tmp = _strdup(result);
		v.push_back(tmp);
	}
	GetMixture(word, size, word_counter + 1, result, result_counter + 1, v, length);
}

void Mixture(const char* word, std::vector<std::vector<char*>>& v, const int length =1) {
	std::vector<char*> tmp;
	int size = std::strlen(word);
	char* result = new char[size];
	GetMixture(word, size, 0, result, 0, tmp, length);
	std::reverse(tmp.begin(), tmp.end());
	v.push_back(tmp);
	delete [] result;
}

int main() {
	std::vector<const char*> words;
	words.push_back("abcd");
	words.push_back("kagc");
	std::vector<std::vector<char*>> all;
	for (size_t i = 0; i < words.size(); ++i) {
		Mixture(words[i], all, 2);
	}
	for (auto it = all[0].begin(); it != all[0].end(); ++it) {
		std::cout << *it << std::endl;
	}
	for (auto it = all[1].begin(); it != all[1].end(); ++it) {
		std::cout << *it << std::endl;
	}
}