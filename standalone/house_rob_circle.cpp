class Solution {
public:
    int* money;
    int rob(vector<int>& nums) {
        if (nums.size()==0)
            return 0;
        else if (nums.size()==1)
            return nums[0];
        else if (nums.size()==2)
            return max(nums[0],nums[1]);
        else
        {
            // Initialize cumulative results
            money = new int[nums.size()];
            
            // start from [0]->[n-2]
            money[0] = nums[0];
            money[1] = max(nums[0],nums[1]);
            for (int i=2; i<nums.size()-1; i++)
            {
                money[i] = max(money[i-1], money[i-2]+nums[i]);
            }
            int result1 = money[nums.size()-2];
            
            // start from [1]->[n-1]
            money[1] = nums[1];
            money[2] = max(nums[1],nums[2]);
            for (int i=3; i<nums.size(); i++)
            {
                money[i] = max(money[i-1], money[i-2]+nums[i]);
            }
            int result2 = money[nums.size()-1];
            
            return max(result1, result2);
        }
    }
};