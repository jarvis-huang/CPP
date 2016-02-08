class Solution {
public:
    int* money;
    int rob(vector<int>& nums) {
        if (nums.size()==0)
            return 0;
        else if (nums.size()==1)
            return nums[0];
        else
        {
            money = new int[nums.size()];
            money[0] = nums[0];
            money[1] = max(nums[0],nums[1]);
            for (int i=1; i<nums.size(); i++)
            {
                money[i] = max(money[i-1], money[i-2]+nums[i]);
            }
            return money[nums.size()-1];
        }
    }
};