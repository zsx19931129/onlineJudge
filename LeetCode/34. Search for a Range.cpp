class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int vlen = nums.size();
        vector<int> ret;
        if(vlen == 0){
            ret.push_back(-1);
            ret.push_back(-1);
            return ret;
        }
        int left = 0, right = vlen-1;
        int idx = -1, mid = -1;
        while(left<=right){
            mid = (left+right)/2;
            if(nums[mid] == target){
                idx = mid;
                break;
            }else if(nums[mid]<target){
                left = mid+1;
            }else{
                right = mid-1;
            }
        }
        
        // cout<<idx<<endl;

        if(idx==-1){
            ret.push_back(-1);
            ret.push_back(-1);
            return ret;
        }

        left = 0, right = idx-1, mid = 0;
        while(left<=right){
            mid = (left+right)/2;
            if(nums[mid] == target){
                right = mid-1;
            }else if(nums[mid]<target){
                left = mid+1;
            }
        }
        int leftBound = (nums[mid] == target) ? mid : mid+1;

        left = idx+1, right = vlen-1, mid = (idx+vlen)/2;
        while(left<=right){
            mid = (left+right)/2;
            if(nums[mid] == target){
                left = mid+1;
            }else if(nums[mid] > target){
                right = mid-1;
            }
        }
        int rightBound = (nums[mid] == target) ? mid : mid-1;

        ret.push_back(leftBound);
        ret.push_back(rightBound);
        return ret;
    }
};