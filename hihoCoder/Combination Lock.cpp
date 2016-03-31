//线段树，用普通的操作复杂度为O(MN)，创建线段树O(N)，修改和查询的时间复杂度均为O(logn)
#include <iostream>
#include <string>

#define MAXN 50001

using namespace std;



class sTreeNode{
public:
    //区间左右
    int left, right;
    //左右孩子
    int lch, rch;
    //标识这个区间的元素是否都相同，若相同则base等于该字符，否则base = -1, 处理操作1
    int base;
    //整个区间的偏移，处理操作2
    int add;
    //起始值和步进，一次cmd 4 1 1 两次cmd 4 2 2，比如
    int delta, step;
};

int vstr[MAXN];		//记录每个叶子节点的数值
char str[MAXN];
//保证有足够的空间来存储线段树，区间（非叶节点）+(叶节点，n个)，近似完全二叉树，2*n个
sTreeNode tree[MAXN<<2];
int n,m;

//用一个位置索引来模拟翻转数组，每次处理数组的时候都需要在区间的基础上加上这个偏移
int curBegin = 0;

//递归构建线段树
void createSTree(int root, int left, int right){
    //初始化根节点
    tree[root].left = left;
    tree[root].right = right;
    tree[root].base = -1;
    tree[root].add = 0;
    tree[root].delta = 0;
    tree[root].step = 0;
    
    if(left == right){
        tree[root].base = str[left] - 'A';
        tree[root].lch = tree[root].rch = 0;
        return ;
    }
    
    //非叶节点
    tree[root].lch = 2*root;
    tree[root].rch = 2*root + 1;
    
    int mid = (left + right)>>1;
    createSTree(tree[root].lch, left, mid);
    createSTree(tree[root].rch, mid+1, right);
}

//root表示当前节点
//left和right表示此次操作的区间，key表示此次操作k或delta
//type表示此次操作的类型
void updateSTree(int root, int left, int right, int key, int type){
    if(!root)
        return ;
    if(tree[root].right < left || tree[root].left > right)
        return ;
    if(left<=tree[root].left && right>=tree[root].right){
        // 当前的区间被操作的区间覆盖
        if(type == 1){
            tree[root].base = key;
            tree[root].delta = tree[root].step = 0;
            tree[root].add = 0;
        }else if(type == 2){
            tree[root].add += key;
        }else if(type == 4){
            //tree[root].base = -1;		//不应该有这句，三个区间操作互相之间不冲突
            tree[root].delta += key + (tree[root].left-left);
            tree[root].step += 1;
        }
    }else{
        //拆分子区间继续处理，需要把当前区间的信息传递下去
        int mid = (tree[root].left + tree[root].right)>>1;
        
        int tlch = tree[root].lch;
        int trch = tree[root].rch;
        
        if(tree[root].base == -1){
            //如果当前的区间元素不是全部相同
            // lch
            tree[tlch].delta += tree[root].delta;
            tree[tlch].step += tree[root].step;
            tree[tlch].add += tree[root].add;
            // rch
            tree[trch].delta += tree[root].delta + (mid-tree[root].left+1)*tree[root].step;
            tree[trch].step += tree[root].step;
            tree[trch].add += tree[root].add;
        }else{
            tree[tlch].base = tree[trch].base = tree[root].base;
            
            tree[tlch].delta = tree[root].delta;
            tree[trch].step = tree[tlch].step = tree[root].step;
            tree[trch].add = tree[tlch].add = tree[root].add;
            
            tree[trch].delta = tree[root].delta + (mid-tree[root].left+1)*tree[root].step;
        }
        
        //将当前信息传递下去后，当前区间内的字符一定会发生改变，设置base=-1，
        //delta、add、step设置为0，因为信息已经传递给子区间，这里并不需要所谓的lazytag
        tree[root].base = -1;
        tree[root].delta = tree[root].step = 0;
        tree[root].add = 0;
        
        updateSTree(tlch, left, right, key, type);
        updateSTree(trch, left, right, key, type);
    }
}

void getResult(int root){
    if(!root){
        return ;
    }
    if(tree[root].base != -1){
        //说明这个区间的字符都相同，可以得出结果
        int delta = tree[root].delta;
        int tbase = tree[root].base;
        int tadd = tree[root].add;
        int tstep = tree[root].step;
        for(int i=tree[root].left;i<=tree[root].right;i++,delta+=tstep){
            vstr[i] = tbase + tadd + delta;
        }
    }else{
        //需要进一步递归划分子区间
        int mid = (tree[root].left + tree[root].right)>>1;
        //lch
        int tlch = tree[root].lch;
        int trch = tree[root].rch;
        
        tree[tlch].delta += tree[root].delta;
        tree[tlch].step += tree[root].step;
        tree[tlch].add += tree[root].add;
        
        tree[trch].delta += tree[root].delta + (mid-tree[root].left+1)*tree[root].step;
        tree[trch].step += tree[root].step;
        tree[trch].add += tree[root].add;
        
        getResult(tlch);
        getResult(trch);
    }
}

void showResult(){
    getResult(1);
    
    for(int i=0;i<n;i++){
        str[i] = vstr[(i+curBegin)%n]%26 + 'A';
    }
    cout<<str<<endl;
}

int main(){
    cin>>n>>m;
    cin>>str;
    
    createSTree(1, 0, n-1);
    
    int l,r,k, cmdType;
    char x;
    string cmdstr;
    
    for(int i=0;i<m;i++){
        cin>>cmdstr>>cmdType;
        if(cmdType == 3){
            cin>>k;
            curBegin += k;
            curBegin %= n;
        }else if(cmdType == 1){
            cin>>l>>r>>x;
            int trueLeft = (l-1 + curBegin)%n;
            int trueRight = (r-1 + curBegin)%n;
            if(trueLeft <= trueRight){
                updateSTree(1,trueLeft,trueRight,x-'A',cmdType);
            }else{
                updateSTree(1,trueLeft,n-1,x-'A',cmdType);
                updateSTree(1,0,trueRight,x-'A',cmdType);
            }
        }else if(cmdType == 2){
            cin>>l>>r>>k;
            int tl = (l-1 + curBegin)%n;
            int tr = (r-1 + curBegin)%n;
            k%=26;
            if(tl<=tr){
                updateSTree(1, tl, tr, k, cmdType);
            }else{
                updateSTree(1, tl, n-1, k, cmdType);
                updateSTree(1, 0, tr, k, cmdType);
            }
        }else if(cmdType == 4){
            cin>>l>>r;
            int tl = (l-1 + curBegin)%n;
            int tr = (r-1 + curBegin)%n;
            
            if(tl<=tr){
                updateSTree(1, tl, tr, 1, cmdType);
            }else{
                updateSTree(1,tl,n-1,1,cmdType);
                updateSTree(1,0,tr,n-tl+1,cmdType);
            }
        }
    }
    showResult();
    return 0;
}