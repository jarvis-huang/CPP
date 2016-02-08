#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <utility> // pair
#include <unordered_set>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define NNUMS 10
#define NMAX 40

/*
int quickSelect(vector<int>& nums, int k)
-- returns k-th smallest element in nums as if nums were sorted
-- k is zero based, in the range of [0, nums.size()-1]
*/

class Solution {
public:
	// k must be in the range of [0, nums.size()-1]
	int quickSelect(vector<int>& nums, int k)
	{
		int n = nums.size();
		assert(n > 0 && k >= 0 && k < n);

		// hardcode termination condition
		if (n == 1)
			return nums[0];

		int pivot = nums[0];
		vector<int> left;
		vector<int> right;
		int result;
		for (int i = 1; i < n; i++)
		{
			int x = nums[i];
			if (x < pivot)
				left.push_back(x);
			else
				right.push_back(x);
		}
		int len_left = left.size();
		if (k == len_left) // is pivot
			return pivot;
		else if (k < len_left) // search in left
		{
			right.clear();
			result = quickSelect(left, k);
			left.clear();
		}
		else // search in the right
		{
			left.clear();
			result = quickSelect(right, k-len_left-1);
			right.clear();
		}
		return result;
	}
};


void main(int argc, char** argv)
{
	// generate a random testcase vector. size=NNUMS, range=[0,NMAX).
	srand(time(NULL));
	vector<int> vec(NNUMS, 0);
	cout << "vec = [";
	for (int i = 0; i < NNUMS; i++)
	{
		vec[i] = rand() % NMAX;
		if (i == NNUMS-1)
			cout << vec[i];
		else
			cout << vec[i] << " ";
	}
	cout << "]" << endl;

	// Test quickSelect
	Solution sol;
	for (int k = 0; k < NNUMS; k++)
	{
		int x = sol.quickSelect(vec, k);
		cout << k << "-th element of vec = " << x << endl;
	}
}