// 将题中条件转化成一个泛化背包问题，每个英雄可以看作一组商品，一组商品的不同等级对应不同商品，每组商品只能选一个
// 已知条件组合，转化成c[lvl]，英雄等级lvl消耗的金币数量， w[lvl]，英雄等级为lvl时产生的价值
// 对每一个商品，枚举可能到达的最高等级
#define max(x,y) ({			\
	typeof(x) _x = (x);		\
	typeof(y) _y = (y);		\
	(void) (&_x == &_y);	\
	_x > _y ? _x : _y;		\
})
#define MAXN 31
#define MAXM 20001
#include <iostream>
#include <cmath>

using namespace std;

int n,m;
int c[MAXN], w[MAXN];			// 存储每个分组第一个商品(1级的权重)
int dp[MAXN][MAXM];				// dp[0][0...m]初始化为0

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j] = max(dp[i-1][j],dp[i][j]);		//表示不放入第i组商品
			int curc = c[i];
			int curw = w[i];
			while(j > curc){
				dp[i][j] = max(dp[i-1][j-curc] + curw, dp[i][j]);	//放入第i组商品的某一个
				curc = floor(1.07*curc);
				curw += w[i];
			}
		}
	}
	cout<<dp[n][m]<<endl;
	return 0;
}