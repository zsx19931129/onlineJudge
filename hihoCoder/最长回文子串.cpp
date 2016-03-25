// manacher算法，O(n)时间复杂度判断最长回文子串，改进了中心扩展判断的方法，利用了子串的对称性
// 回文串 plalindrome

// #define min(x, y) ((a)<(b))?(a):(b)
// 参考Linux内核中的MIN宏定义，可以避免传入a++,b++之类导致的副作用
#define min(x, y) ({		\
	typeof(x) _x = (x);		\	
	typeof(y) _y = (y);		\
	(void) (&_x == &_y);	\	//C没有类型比较操作，比较地址可以利用编译器发现类型不一致错误
	_x < _y ? _x : _y;		\
})

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 重新包装原串，合并奇偶情况，中间和开头结尾加#，为防止在扩张中越界，再在开头末尾加入$
void capsuleStr(string &str){
	string temp(str);
	str = "$";
	for(int i=0;i<temp.length();i++){
		str += "#" + temp[i];
	}
	str += "#$";
}

int manacher(string str){
	int maxplen = 1;
	capsuleStr(str);
	int slen = str.length();
	// 记录以每个位置为中心的回文串长度
	vector<int> plen(slen, 1);
	// 记录当前所有回文覆盖的最右的位置，和对应的索引
	int rmost = 1, rmostIdx = 1;
	//首尾的$不计算
	for(int i=1;i<slen-1;i++){
		if(rmost > i){
			// 如果当前i在覆盖范围内，存在回文长度下限
			// 利用对称性，与id对称的元素的回文长度相同，但是如果边界超过rmost，需要截取
			// plen[2*rmostIdx - i]， 对称元素长度 rmostIdx - (i - rmostIdx)
			// plen[rmostIdx]-2*(i -rmostIdx) 截取边界
			plen[i] = min(plen[2*rmostIdx - i], plen[rmostIdx]-2*(i -rmostIdx));
		}
		//基于中心扩展开始比较
		int curOff = plen[i]/2 + 1;
		while(str[i + curOff] == str[i - curOff]){
			plen[i] += 2;
			curOff++;
		}
		int curRmost = i + curOff - 1;
		if(curRmost > rmost){
			rmost = curRmost;
			rmostIdx = i;
		}
		// 计算出原串中的长度
		int oriLen = (plen[i]-1)/2;
		if(oriLen > maxplen){
			maxplen = oriLen;
		}
	}
	return maxplen;
}

int main(){
	int n;
	cin>>n;
	string str;
	for(int i=0;i<n;i++){
		cin>>str;
		int maxPldLength = manacher(str);
		cout<<maxPldLength;
	}
	return 0;
}