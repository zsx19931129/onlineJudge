// 动态规划经典问题，最长公共子序列的变体，用一个辅助数组，可以标识出以某个字符结果的公共
// 后缀长度，当后缀大于3，则更新dp数组，在这里又出现重复子问题，用另一个dp辅助数组解决，将
// 时间复杂度从O(n^3)降到O(n^2)，dp[][][2]，第一维是正常dp int，第二维是为了计算最优划分

#define max(x, y) ({		\
typeof(x) _x = (x);         \
typeof(y) _y = (y);         \
(void) (&_x == &_y);        \
 _x > _y ? _x : _y;         \
})

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
	string str1, str2;
	cin>>str1>>str2;
	int slen1 = str1.length();
	int slen2 = str2.length();

	//为方便下标从1开始
	str1 = " " + str1;
	str2 = " " + str2;

	//预处理后缀数组
	vector<vector<int> > suffix(slen1 + 1, vector<int>(slen2 + 1, 0));
	for(int i=1;i<=slen1;i++){
		for(int j=1;j<=slen2;j++){
			if(str1[i] == str2[j]){
				suffix[i][j] = suffix[i-1][j-1] + 1;
			}else{
				suffix[i][j] = 0;
			}
		}
	}

	//dp lcs
	vector<vector<vector<int> > > dp(slen1+1, 
		vector<vector<int> >(slen2+1,vector<int>(2,0)));

	for(int i=1;i<=slen1;i++){
		for(int j=1;j<=slen2;j++){
			dp[i][j][1] = 0;
			if(suffix[i][j] >= 3){
				dp[i][j][1] = max(dp[i][j][1], dp[i-3][j-3][0] + 3);
				if(suffix[i][j]>3){
					dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-1][1] + 1);
				}
			}
			dp[i][j][0] = max(dp[i-1][j][0], dp[i][j-1]);
			dp[i][j][0] = max(dp[i][j][0], dp[i][j][1]);
		}
	}

	cout<<dp[slen1][slen2][0]<<endl;
}