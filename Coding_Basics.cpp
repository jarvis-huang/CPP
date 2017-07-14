==========================================
==== Trees
==========================================
BST: keep min/max, validate, swap two
BFS: queue
DFS: stack
check: root==NULL, left/right==NULL

==========================================
==== Subset/Combination
==========================================
first sort if order required
solution clear
scan all elements, foreach, choose between "use it" or "not use it"
fetch all solution vectors and if "use it" append to end of each solution, if "not use", leave original solution

==========================================
==== Divide-and-Conquer w/ Memoization
==========================================
solve one/more subproblems (unrelated) and combine into current solution
key: discarding efficiency
use it: trees
---
Memoization: store current solution for later reuse.
Store current solution ASA it's complete. Use previous solution ASA it's available.
For example, in a recursive function, check previous solution at the beginning and store current solution before returning.

==========================================
==== DP
==========================================
bottom-to-top
start from dp[0], dp[1], etc which are known easily
repeated compute future dp's from previous dp's
think about all possible ways to reach current state
alternative to recursion
O(N)
Example: 292, 279

==========================================
==== Counting problem <-> Sorting problem
==========================================
# of elements < self == self position in sorted list (insert before first element >= self)

==========================================
==== Binary search (in a sorted array)
==========================================
bin_search(vec, target, left_index (li), right_index (ri))
1) check if contains (true/false) or index of match (-1 for no match) ==> base algo
		while (li<=ri)
		{
			mi = mid_index = (left_index+right_index)/2;
			if (target==vec[mi])
				return 'mi' or true
			else if (target<vec[mi])
				ri = mi-1;
			else
				li = mi+1;
		}
		return -1 or false
2) look for index to insert (first element >= target)
		while (li<=ri)
		{
			mi = mid_index = (left_index+right_index)/2;
			if (target<=vec[mi])
				ri = mi-1;
			else
				li = mi+1;
		}
		return li; // insert at end <=> li==n
	if searching for first element > target, change (target<=vec[mi]) to (target<vec[mi]), return li
3) (last element<target)  + 1 == (first element>=target)
   (last element<=target) + 1 == (first element> target)
   
==========================================
==== Merge Sort (linked list)
==========================================   
// merge two lists (assume both lists have at least one node)
ListNode* dummy = new ListNode(0);
head = dummy;
while(true)
{
	if (head1->val<=head2->val)
	{
		head->next = head1;
		head1 = head1->next;
	}
	else
	{
		head->next = head2;
		head2 = head2->next;                
	}
	head = head->next;
	if (head1==NULL)
	{
		head->next = head2;
		break;
	}
	if (head2==NULL)
	{
		head->next = head1;
		break;
	}

	return dummy->next;
		

==========================================
==== common STL and their functions
==========================================
unordered_set<T> myset
myset.insert(T); // insert one element
myset.emplace(T); // insert one element
myset.find(T)==myset.end()
---
unordered_map<T1,T2> mymap
mymap.insert({T1,T2});
mymap.emplace(T1,T2); // insert one element
mymap.find(T)==mymap.end()
---
std::vector<int> v { 34,23 }; // uniform initialization
std::pair <std::string,double> product2 ("tomatoes",2.30);
---
vector: empty, size, at, [], front, back, push_back, pop_back, insert, erase, clear
list: empty, size, front, back, push_front, pop_front, push_back, pop_back, insert, erase, clear
stack: empty, size, top, push, pop
queue: empty, size, front, back, push, pop
deque: empty, size, at, [], front, back, push_front, pop_front, push_back, pop_back, clear
map: empty, size, at, [], insert, erase, clear, find, count
set: empty, size, insert, erase, clear, find, count
string: empty, length, at, [], append, push_back, pop_back, +=, insert, erase, find, substr
---
queue/stack do not have clear() function.
queue/stack do not have iterators.
---
map, set // implemented as balanced binary tree
unordered_map, unordered_set // implemented as hash table
---
vectors and deques are similar, but deque allows efficient insertion and removal at the front of the structure as well as the back.
vectors and deques both support [] operator.
Deques also do not guarantee that their elements are contiguous in memory so the [] operator (indexing) may not be as efficient.
---
unordered_map, unordered_set can't have pair<> as elements.
---
string.find(string)==string::npos
---
To allocate a 2d array[sizeY][sizeX]:
int **ary = new int*[sizeY];
for(int i = 0; i < sizeY; ++i) {
    ary[i] = new int[sizeX];
}
---
#include <algorithm>
sort(vec.begin(),vec.end())


==========================================
==== Permutation and Combination (77)
==========================================

==========================================
==== Advice
==========================================
Start with simpler solutions, don't make it too complex
However, must carefully consider all corner cases.
Pay attention to . or ->
Pay attention to <T> in container<T>
Review OOP.
---
int y= x & -x; // lowest bit 1 remains 1, the rest bits set to 0
               // also the maximum 2^int divisible by x (12->4, 3->1, 8->8, 0->0, ...)
int y= x ^ -x; // lowest bit 1 and below are set to 0, the rest bits set to 1
int y= x | -x; // lowest bit 1 and above are set to 1, the rest bits set to 0
---
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
srand (time(NULL));
v1 = rand() % 100;        // v1 in the range 0 to 99 (rand() returns an integer [0, RAND_MAX])
v2 = rand() % 100 + 1;    // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;  // v3 in the range 1985-2014
---
enum Color { red, yellow, green = 20, blue };
Color mycolor;
---
switch(grade)
{
   case 'A' :
      cout << "Excellent!" << endl; 
      break;
   case 'B' :
   case 'C' :
      cout << "Well done" << endl;
      break;
   default :
      cout << "Invalid grade" << endl;
}
---
Four directions:
int x; // cur x
int y; // cur y
vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    for (auto &dir : dirs) {
    int xx = x + dir[0], yy = y + dir[1];
    if (xx < 0 || xx >= rows || yy < 0 || yy >= cols) continue;
    // do something with (xx,yy)
}
---
#include <assert.h>
assert(boolean expression);

==========================================
==== Recursion
==========================================


==========================================
==== Integer overflow
==========================================
