/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if(!root){
        	return ret;
        }
        queue<pair<TreeNode*, int>> q;
        vector<int> layer;
        q.push(make_pair(root, 0));
        layer.push_back(root->val);
        int curLayer = 0;
        pair<TreeNode*, int> curNode;
        while(!q.empty()){
			curNode = q.front();
        	q.pop();
        	if(curNode.second > curLayer){
        		curLayer = curNode.second;
        		ret.push_back(layer);
        		layer.clear();
        	}
        	layer.push_back(curNode.first->val);
        	if(curNode.first->left){
        		q.push(curNode.first->left);
        	}
        	if(curNode.first->right){
        		q.push(curNode.first->right);
        	}
        }
        if(layer.size()>0){
        	ret.push_back(layer);
        }
        return ret;
    }
};