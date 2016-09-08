class Solution {
public:
	inline void swap(int &a, int &b){
		int tmp = a;
		a = b;
		b = tmp;
	}
    string getPermutation(int n, int k) {
        vector<int> numVec(n);
        for(int i=0;i<n;++i){
        	numVec[i] = i+1;
        }
        vector<int> factorialTable(n+1);
        factorialTable[0] = factorialTable[1] = 1;
        for(int i=2;i<=n;++i){
        	factorialTable[i] = i*factorialTable[i-1];
        }
        int tmp = k;
        for(int i=0;i<n-2;++i){
        	sort(numVec.begin()+i, numVec.end());
        	int permcnt = factorialTable[n-1-i];
        	int num = tmp/permcnt;
        	swap(numVec[i], numVec[i+num]);
        	tmp = tmp - num*permcnt;
        	if(tmp % permcnt == 0){
        		tmp += permcnt;
        	}
        }
        if(k>=2){
        	int a, b;
			(numVec[n-2]<numVec[n-1]) ? (a = numVec[n-2], b = numVec[n-1]) : (a = numVec[n-1], b = numVec[n-2]);
        	if(k&1){
        		numVec[n-2] = a;
        		numVec[n-1] = b;
        	}else{
        		numVec[n-2] = b;
        		numVec[n-1] = a;
        	}
        }
        string ret = "";
        for(int i=0;i<n;++i){
        	ret += char('0' + numVec[i]);
        }
        return ret;
    }
};