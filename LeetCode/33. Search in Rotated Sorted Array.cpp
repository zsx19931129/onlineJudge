class Solution {
public:
    int search(vector<int>& nums, int target) {
        int vlen = nums.size();
        if(vlen==0){
            return -1;
        }
        int left=0, right=vlen-1;
        int startIdx = -1;
        while(left!=right){
            int mid = (left + right)/2;
            if(nums[mid]>=nums[left] && nums[mid]<=nums[right]){
                break;
            }
            if(nums[mid] > nums[right]){
                left = mid+1;
            }else{
                right = mid;
            }
        }
        startIdx = left;
        
        // cout<<startIdx<<endl;
        left=0, right=vlen-1;
        int idxMod = -1;
        while(left<=right){
            int mid = (left+right)/2;
            idxMod = (mid+startIdx)%vlen;
            if(nums[idxMod] == target){
                return idxMod;
            }else if(nums[idxMod]<target){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        return -1;
    }
};