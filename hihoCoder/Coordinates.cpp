#include <iostream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

struct node{
	int x,y;
};

bool setCmp(const node &n1, const node &n2){
	return (n1.x < n2.x) || ( (n1.x == n2.x) && (n1.y < n2.y) );
}

int main(){
	bool (*fpt)(const node &， const node &) = setCmp;
	set<node, bool (*)(const node &, const node &)> mset(setCmp);
	int p,q;
	cin>>p>>q;
	vector<int> pd,qd;
	for(int i=1;i<=sqrt(p);i++){
		if(p%i == 0){
			pd.push_back(i);
			pd.push_back(p/i);
		}
	}
	for(int i=1;i<=sqrt(q);i++){
		if(q%i == 0){
			qd.push_back(i);
			qd.push_back(q/i);
		}
	}
	for(int i = 0;i<pd.size();i++){
		for(int j=0;j<qd.size();j++){
			mset.insert(node(pd[i], qd[j]));
		}
	}

	set<node>::iterator it;
	for(it = mset.begin();it != mset.end();it++){
		cout<<it->x<<" "<<it->y<<endl;
	}
	return 0;
}