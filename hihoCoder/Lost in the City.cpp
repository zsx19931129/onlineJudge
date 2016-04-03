// 简单枚举整个迷宫，每个位置四个方向
#define MAXN 201
#define PATTERN 4

#include <iostream>
#include <cstdio>

using namespace std;

int n,m;
char cityMap[MAXN][MAXN];
char hi[PATTERN][PATTERN];

bool fitNorth(int i, int j){
	int cx = i-1, cy = j-1;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(cityMap[i + cx][j + cy] != hi[i][j]){
				return false;
			}
		}
	}
	return true;
}

bool fitSouth(int i, int j){
	int cx = i-1, cy = j-1;
	int hx = 2, hy = 2;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(cityMap[i + cx][j + cy] != hi[hx-i][hy-j] ){
				return false;
			}
		}
	}
	return true;
}

bool fitWest(int i, int j){
	int cx = i-1, cy = j-1;
	int hx = 2, hy = 0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(cityMap[i + cx][j + cy] != hi[hx-j][hy+i]){
				return false;
			}
		}
	}
	return true;
}

bool fitEast(int i, int j){
	int cx = i-1, cy = j-1;
	int hx = 0, hy = 2;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(cityMap[i + cx][j + cy] != hi[hx+j][hy-i]){
				return false;
			}
		}
	}
	return true;
}

bool fit(int i,int j){
	if(fitNorth(i,j) || fitSouth(i,j) || fitWest(i,j) || fitEast(i,j)){
		return true;
	}
	return false;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		scanf("%s",cityMap[i]);
	}
	for(int i=0;i<3;i++){
		scanf("%s",hi[i]);
	}

	for(int i=1;i<n-1;i++){
		for(int j=1;j<m-1;j++){
			if(fit(i,j)){
				cout<<i+1<<" "<<j+1<<endl;
			}
		}
	}

	return 0;
}