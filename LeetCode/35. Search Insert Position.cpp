class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int vlen = nums.size();
        if(vlen == 0){
        	return 0;
        }
        int left = 0, right = vlen-1, mid = 0;
        while(left<=right){
        	mid = (left + right)/2;
        	if(nums[mid] == target){
        		return mid;
        	}else if(nums[mid] < target){
        		left = mid + 1;
        	}else{
        		right = mid - 1;
        	}
        }
        return (nums[mid] > target) ? mid : mid + 1;
    }
};