#define MAXN 1005
#include <iostream>
#include <cstring>
using namespace std;

int n, p, w, h;
int wordsPerLine = 0;
int linesPerPage = 0;
int charCnt[MAXN]={0};

void init(){
	cin>>n>>p>>w>>h;
	memset(charCnt, 0, sizeof(charCnt));
	for(int i=0;i<n;i++){
		cin>>charCnt[i];
	}
	wordsPerLine = 0;
	linesPerPage = 0;
}

void solve(){
	int curSize = 1;
	for(int i=1;i<=w;i++){
		//以这个字体大小遍历所有段
		wordsPerLine = w / i;
		linesPerPage = h / i;
		if(linesPerPage == 0){
			break;
		}
		int curCnt = 0;
		for(int j=0;j<n;j++){
			int aug = charCnt[j]/wordsPerLine;
			if(charCnt[j]%wordsPerLine != 0){
				aug++;
			}
			curCnt += aug;
		}

		// 计算需要多少页
		int pages = curCnt / linesPerPage;
		if(curCnt % linesPerPage != 0){
			pages++;
		}

		if(pages <= p){
			curSize = i;
		}else {
			break;
		}
	}
	cout<<curSize<<endl;
}

int main(){
	int tasks;
	cin>>tasks;
	while(tasks--){
		init();
		solve();
	}
	return 0;
}