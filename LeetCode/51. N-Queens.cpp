class Solution {
public:
	void backtracking(vector<int> posVec, int mask, int depth, int size, vector<vector<string>> &ret, const vector<string> &strTable){
		if(depth == size){
			vector<string> item;
			for(int i=0;i<size;++i){
				item.push_back(strTable[posVec[i]]);
			}
			ret.push_back(item);
		}
		for(int i=0;i<size;++i){
			bool legal = true;
			for(int j=0;j<depth;++j){
				if( (depth - j) == abs(i - posVec[j]) ){
					legal = false;
					break;
				}
			}
			if(!legal){
				continue;
			}
			if((1<<i & mask) == 0){
				posVec[depth] = i;
				backtracking(posVec, (mask | 1<<i), depth+1, size, ret, strTable);
			}
		}
	}
    vector<vector<string>> solveNQueens(int n) {
    	vector<vector<string>> ret;
    	if(n == 0){
    		return ret;
    	}
    	vector<int> posVec(n, -1);
		vector<string> strTable;
		for(int i=0;i<n;++i){
			string temp(n, '.');
			temp[i] = 'Q';
			strTable.push_back(temp);
		}
		backtracking(posVec, 0, 0, n, ret, strTable);
		cout<<ret.size()<<endl;
		return ret;
    }
};