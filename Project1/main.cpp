#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void GetMixture(char* word, const int size, int word_counter, char* result, int result_counter, std::vector<char*> &v ,const int length = 1){
	if (word_counter >= size || result_counter >= length) {
		return;
	}
	GetMixture(word, size, word_counter + 1, result, result_counter, v, length);
	result[result_counter] = word[word_counter];
	result[result_counter + 1] = 0;
	if (result_counter  == length - 1) { 
		char* tmp = _strdup(result);
		v.push_back(tmp);
	}
	GetMixture(word, size, word_counter + 1, result, result_counter + 1, v, length);
}

int main() {
	char word[] = "kape";
	char result[5];
	std::vector<char*> vec;
	GetMixture(word, 4, 0, result, 0, vec, 2);
	std::reverse(vec.begin(), vec.end());
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << std::endl;
	}
}