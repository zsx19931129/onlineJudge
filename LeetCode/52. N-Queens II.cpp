class Solution {
public:
	void backtracking(int depth, int size, vector<int> &posVec, int mask, int &cnt){
		if(depth == size){
			++cnt;
			return;
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
				backtracking(depth+1, size, posVec,  (mask | 1<<i), cnt);
			}
		}
	}

    int totalNQueens(int n) {
        int cnt = 0;
        if(n == 0){
        	return cnt;
        }
        vector<int> posVec(n, -1);
        backtracking(0, n, posVec, 0, cnt);
        return cnt;
    }
};