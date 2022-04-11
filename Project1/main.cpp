#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdio.h>

//void GetMixture(const char* word, const int size, char* result, int result_counter, std::vector<const char*>& v, const int length = 1) {
//	if (size == 0 || result_counter >= length) return;
//	for (int i = result_counter; i <= size; ++i) {
//		result[result_counter] = word[i]; 
//		if (result_counter + 1 == length) {
//			result[result_counter + 1] = 0;
//			char* tmp = _strdup(result);
//			v.push_back(tmp);
//		}
//		GetMixture(word, size-1, result, result_counter + 1, v, length);
//	}
//}

void GetMixture(std::vector<const char*>& results, const int size, const char* word, int length, char* Current_Res, int count = 0 ,int startIndx = 0)
{
	if (length == 0) {
		char* x = _strdup(Current_Res);
		results.push_back(x);
	}
	else {
		for (int i = startIndx; i <= size - length; i++) {
			Current_Res[count] = word[i];
			GetMixture(results, size, word, length - 1, Current_Res, count + 1, i + 1);
		}
	}
}

void Mixture(const char* word, std::vector<std::vector<const char*>>& v, const int length = 1) {
	std::vector<const char*> tmp;
	int size = std::strlen(word);
	if (length == size) { 
		tmp.push_back(_strdup(word));
		v.push_back(tmp);
		return;
	}
	char* result = new char[size + 1];
	result[size] = 0;
	GetMixture(tmp, size, word, length, result,0, 0);
	//GetMixture(word, size, 0, result, 0, tmp, length);
	//GetMixture(word, size, result, 0, tmp, length);
	v.push_back(tmp);
	delete[] result;
}

//int MaxSize(std::vector<std::vector<const char*>> v) {
//	int max = std::strlen(v[0][0]);
//	for (int i = 0; i < v.size(); ++i) {
//		
//	}
//	return max;
//}

int main() {
	std::vector<const char*> words;
	words.push_back("abcd");
	std::vector<std::vector<const char*>> all;
	for (size_t i = 0; i < words.size(); ++i) {
		Mixture(words[i], all, 2);
	}
	for (auto it = all[0].begin(); it != all[0].end(); ++it) {
		std::cout << *it << "---";
	}
	std::cout << std::endl << "size:" << all[0].size() << std::endl;
	//for (auto it = all[1].begin(); it != all[1].end(); ++it) {
	//	std::cout << *it << "---";
	//}
	//std::cout << std::endl << "size:" << all[1].size() << std::endl;
	// int max_size = MaxSize(all);
	//        x  y  z
	// void cube[][][];
}