#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <utility> // pair

using namespace std;

struct TreeNode {
	int val;
	char op; // '+', '-', '*', '/'
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};


class TwentyFour {
public:
	vector<TreeNode*> solution;

	TreeNode* solve(int n1, int n2, int n3, int n4) {
		vector<int> nums{ n1, n2, n3, n4 };
		queue<vector<int>> perm = gen_perm(nums);

		/*
		// Test permutation
		while (!perm.empty())
		{
			vector<int> vec = perm.front();
			for (int i = 0; i < vec.size(); i++)
			cout << vec[i] << " ";
			cout << endl;
			perm.pop();
		}
		*/

		solution.clear();

		// each permutation, generate all it trees
		while (!perm.empty())
		{
			//cout << "A";
			vector<TreeNode*> vec = gen_all_trees(perm.front());
			for (int i = 0; i < vec.size(); i++) // for each tree
			{
				if (vec[i]->val == 24) // good tree, save it
					solution.push_back(vec[i]);
			}
			perm.pop();
		}

		return NULL;
	}

	// a collection (vector) of trees
	vector<TreeNode*> gen_all_trees(vector<int> nums)
	{
		int n = nums.size();
		//cout << "gen trees for: "; print_vec(nums);
		if (n == 1)
		{
			TreeNode* nd = new TreeNode(nums[0]);
			nd->op = ' ';
			//cout << "done gen trees for: "; print_vec(nums);
			return vector<TreeNode*>(1, nd);
		}

		vector<int> left_nums;
		vector<int> right_nums;
		vector<TreeNode*> result;

		for (int i = 0; i < n-1; i++) // n-1 possible operators
		{
			left_nums.push_back(nums[i]);
			right_nums.insert(right_nums.end(), nums.begin() + i + 1, nums.end());
			//cout << "left="; print_vec(left_nums);
			vector<TreeNode*> left_trees = gen_all_trees(left_nums);
			//cout << "left tree size=" << left_trees.size() << endl;
			//cout << "right="; print_vec(right_nums);
			vector<TreeNode*> right_trees = gen_all_trees(right_nums);
			//cout << "right tree size=" << right_trees.size() << endl;
			right_nums.clear();

			// combine each left tree with each right tree to form a new tree
			for (int j = 0; j < left_trees.size(); j++)
			{
				for (int k = 0; k < right_trees.size(); k++)
				{
					//cout << "combining trees\n";
					TreeNode* nd = new TreeNode(left_trees[j]->val + right_trees[k]->val);
					nd->op = '+';
					nd->left = left_trees[j];
					nd->right = right_trees[k];
					result.push_back(nd);
					nd = new TreeNode(left_trees[j]->val - right_trees[k]->val);
					nd->op = '-';
					nd->left = left_trees[j];
					nd->right = right_trees[k];
					result.push_back(nd);
					nd = new TreeNode(left_trees[j]->val * right_trees[k]->val);
					nd->op = '*';
					nd->left = left_trees[j];
					nd->right = right_trees[k];
					result.push_back(nd);	
					// avoid div by 0
					if (right_trees[k]->val != 0)
					{
						nd = new TreeNode(left_trees[j]->val / right_trees[k]->val);
						nd->op = '/';
						nd->left = left_trees[j];
						nd->right = right_trees[k];
						result.push_back(nd);
					}
				}
			}
			left_trees.clear();
			right_trees.clear();
		}
		left_nums.clear();
		right_nums.clear();
		//cout << "done gen trees for: "; print_vec(nums);
		return result;
	}

	string getString(TreeNode* root) {
		
		if (root->left == NULL && root->right == NULL)
			return to_string(root->val);
		else
			return "(" + getString(root->left) + string(1, root->op) + getString(root->right) + ")";
	}

	void print_solution()
	{
		cout << "===SOLUTION===\n";
		for (int i = 0; i < solution.size(); i++)
		{
			cout << getString(solution[i]) << endl;
		}
		cout << "===END SOLUTION===\n";
	}

	// Debug helper func
	void print_vec(vector<int> vec)
	{
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i] << " ";
		cout << endl;
	}

	queue<vector<int>> gen_perm(vector<int> nums)
	{
		queue<vector<int>> perm;
		queue<vector<int>> temp;
		for (auto x : nums)
		{
			if (perm.empty())
				perm.push(vector<int>(1, x));
			else
			{
				// pop all elements from perm into temp
				while (!perm.empty())
				{
					temp.push(perm.front());
					perm.pop();
				}

				while (!temp.empty())
				{
					vector<int> vec = temp.front();
					// insert x into each position of vec and produce a new vector, insert into perm
					for (int j = 0; j < vec.size(); j++)
					{
						vector<int> new_vec;
						new_vec.insert(new_vec.end(), vec.begin(), vec.begin() + j);
						new_vec.push_back(x);
						new_vec.insert(new_vec.end(), vec.begin() + j, vec.end());
						perm.push(new_vec);
					}

					// Add to end
					vector<int> new_vec = vec;
					new_vec.push_back(x);
					perm.push(new_vec);
					
					// remove original
					temp.pop();
				}
			}
		}

		return perm;
	}
};

void main(int argc, char** argv)
{
	string nums[] = { argv[1], argv[2], argv[3], argv[4] };
	TwentyFour sol;
	sol.solve(stoi(nums[0]), stoi(nums[1]), stoi(nums[2]), stoi(nums[3]));
	sol.print_solution();
}