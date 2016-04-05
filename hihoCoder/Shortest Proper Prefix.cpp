// 前缀树 trie
#include <iostream>
#include <string>

using namespace std;

struct trieNode{
    int cnt;		//以这个trieNode结尾的前缀的单词数量
    bool last;		//标识是否是最后一个节点
    trieNode* child[26];
    trieNode(int c, bool l):cnt(c), last(l){
        for(int i=0;i<26;i++){
            child[i] = NULL;
        }
    }
};

struct trie{
    trieNode * root;
    trie(){
        root = new trieNode(0, false);			//所有前缀的根节点
    }
    void insertStr(string str){
        int slen = str.length();
        int off = 0;
        trieNode *parent = root;
        root->cnt += 1;							//每增加一个单词就加1
        trieNode *cur = root->child[str[0]-'a'];
        while(cur){
            //这个while循环处理所有已经包含的前缀
            cur->cnt += 1;						//这个单词每个字母对应的节点+1
            off++;
            if(off == slen){
                parent = cur;
                break;
            }
            parent = cur;
            cur = cur->child[str[off]-'a'];
        }
        while(off<slen){
            parent->child[str[off] - 'a'] = new trieNode(1, false);		//访问为1
            parent = parent->child[str[off] - 'a'];
            off++;
        }
        // 结尾标记赋值为true
        parent->last = true;
    }
};

int n;
int res = 0;		//存储最短前缀数量
trie myTrie;		//前缀树

//深度优先遍历找到所有符合条件的前缀
void dfs(const trieNode *root){
    //当前节点满足解，直接返回不再搜索
    if(root->cnt <= 5 && (root != myTrie.root) ){
        res++;
        return ;
    }
    for(int i=0;i<26;i++){
        if(root->child[i]){
            dfs(root->child[i]);
        }
    }
}

int main(){
    string str;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str;
        myTrie.insertStr(str);
    }
    dfs(myTrie.root);
    cout<<res<<endl;
    return 0;
}