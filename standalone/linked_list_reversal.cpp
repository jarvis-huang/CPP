#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;




struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *nxt, *prev=NULL;
        ListNode *cur = head;
        while (cur->next != NULL)
        {
            // save next
            nxt = cur->next;
            
            // update next ptr 
            if (cur==head)
                cur->next = NULL;
            else
                cur->next = prev;
                
            // save cur for next round
            prev = cur;
            
            // move to next
            cur = nxt;
        }
        // tail node => head node
        cur->next = prev;
        return cur;
    }
};

int main()
{
	ListNode node1(1), node2(2), node3(3), node4(4);
	ListNode* head = &node1, *cur;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;
	cur = head;
	while (cur != NULL)
	{
		cout << cur->val << "->";
		cur = cur->next;
	}
	cout << "NULL" << endl;

	Solution sol;
	cur = sol.reverseList(head);
	while (cur != NULL)
	{
		cout << cur->val << "->";
		cur = cur->next;
	}
	cout << "NULL" << endl;

}

