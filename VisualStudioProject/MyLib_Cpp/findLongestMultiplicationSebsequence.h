#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include <cstdlib>
#include <numeric>

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& values)
{
	os << '[' << values[0];
	for (size_t i = 1; i < values.size(); i++) {
		os << ", " << values[i];
	}
	os << ']';
	return os;
}

// [1, max]
int randomPositiveInterger(int max) {
	return 1 + std::rand() % max;
}

std::vector<int> generateTestCase(int size, int max) {
	std::vector<int> result(size);
	std::generate(result.begin(), result.end(), [max]() {
		return randomPositiveInterger(max);
		});
	std::sort(result.begin(), result.end());
	return result;
}

std::vector<int> findLongestMultiplicationSebsequence(std::vector<int>& sequence) {
	if (sequence.empty()) return {};

	int size = (int)sequence.size();
	std::vector<int> dp(size);
	std::vector<int> p(size);

	dp[0] = 1;
	p[0] = -1;
	int dp_max = 1;
	int index_dp_max = -1;
	for (int i = 1; i < size; i++) {
		int current = sequence[i];
		int maxCount = 1;
		int index_maxCount = -1;
		for (int j = i - 1; j >= 0; j--) {
			if (current % sequence[j] != 0) continue;
			int count = 1 + dp[j];
			if (count > maxCount) {
				maxCount = count;
				index_maxCount = j;
			}
		}
		p[i] = index_maxCount;
		dp[i] = maxCount;
		if (maxCount > dp_max) {
			dp_max = maxCount;
			index_dp_max = i;
		}
	}

	std::vector<int> result;
	int current = index_dp_max;
	while (current != -1) {
		result.push_back(sequence[current]);
		current = p[current];
	}
	std::reverse(result.begin(), result.end());

	return result;
}


std::vector<int> findMaximumWieghtedMultiplicationSebsequence(std::vector<int>& sequence) {
	if (sequence.empty()) return {};

	int size = (int)sequence.size();
	std::vector<int> dp(size);
	std::vector<int> p(size);

	dp[0] = sequence[0];
	p[0] = -1;
	int dp_max = sequence[0];
	int index_dp_max = -1;
	for (int i = 1; i < size; i++) {
		int current = sequence[i];
		int maxSum = 0;
		int index_maxSum = -1;
		for (int j = i - 1; j >= 0; j--) {
			if (current % sequence[j] != 0) continue;
			int sum = current + dp[j];
			if (sum > maxSum) {
				maxSum = sum;
				index_maxSum = j;
			}
		}
		p[i] = index_maxSum;
		dp[i] = maxSum;
		if (maxSum > dp_max) {
			dp_max = maxSum;
			index_dp_max = i;
		}
	}

	std::vector<int> result;
	int current = index_dp_max;
	while (current != -1) {
		result.push_back(sequence[current]);
		current = p[current];
	}
	std::reverse(result.begin(), result.end());

	return result;
}


std::vector<int> testCase1 = { 1, 2, 3, 3, 4, 5, 6, 7, 8, 15 };
std::vector<int> testCase2 = { 7, 8, 14, 28, 800 };
std::vector<int> testCase3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
std::vector<int> testCase4 = { 1, 1, 1, 1, 1 };
std::vector<int> testCase5 = { 1, 1, 1, 3, 6, 13 };
std::vector<int> testCase6 = { 1, 4, 6, 12 };

int test() {

	//std::cout << findLongestMultiplicationSebsequence(testCase1) << std::endl;
	//std::cout << findMaximumWieghtedMultiplicationSebsequence(testCase1) << std::endl << std::endl;

	//std::cout << findLongestMultiplicationSebsequence(testCase2) << std::endl;
	//std::cout << findMaximumWieghtedMultiplicationSebsequence(testCase2) << std::endl << std::endl;

	////std::cout << testCase3 << std::endl;
	////std::cout << getPArray(testCase3) << std::endl;
	//std::cout << findLongestMultiplicationSebsequence(testCase3) << std::endl;
	//std::cout << findMaximumWieghtedMultiplicationSebsequence(testCase3) << std::endl << std::endl;

	//std::cout << findLongestMultiplicationSebsequence(testCase4) << std::endl;
	//std::cout << findMaximumWieghtedMultiplicationSebsequence(testCase4) << std::endl << std::endl;

	//std::cout << findLongestMultiplicationSebsequence(testCase5) << std::endl;
	//std::cout << findMaximumWieghtedMultiplicationSebsequence(testCase5) << std::endl << std::endl;

	////std::cout << testCase6 << std::endl;
	////std::cout << getPArray(testCase6) << std::endl;
	//std::cout << findLongestMultiplicationSebsequence(testCase6) << std::endl;
	//std::cout << findMaximumWieghtedMultiplicationSebsequence(testCase6) << std::endl << std::endl;

	std::srand(42);
	for (int i = 1; i <= 100; i++) {
		std::vector<int> randomTestCase = generateTestCase(10, 10);
		std::cout << "TestCase#" << i << '\n';
		std::cout << randomTestCase << '\n';
		std::vector<int> longestMultiplicationSebsequence = findLongestMultiplicationSebsequence(randomTestCase);
		std::vector<int> maximumWieghtedMultiplicationSebsequence = findMaximumWieghtedMultiplicationSebsequence(randomTestCase);
		for (int ele : longestMultiplicationSebsequence) {
			std::cout << ele << ' ';
		}
		std::cout << '\n';
		for (int ele : maximumWieghtedMultiplicationSebsequence) {
			std::cout << ele << ' ';
		}
		std::cout << '\n' << std::accumulate(maximumWieghtedMultiplicationSebsequence.begin(), maximumWieghtedMultiplicationSebsequence.end(), 0) << "\n\n";
	}

	return 0;
}




