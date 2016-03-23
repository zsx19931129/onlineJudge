#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
using namespace std;

enum queryStatus{redundancy = 0, newprefix, newword};

class TrieNode{
public:
    // 标记节点个数
    int wordCnt;
    // // 该节点子节点中最大的标记节点个数，用于判断是否是重复元素
    // int maxCnt;
    //标记是否是标记节点
    bool flag;
    TrieNode(){
        wordCnt = 0;
        flag = false;
    }
    // 存该节点的子节点
    map<char, TrieNode*> hashChildNode;
};

class Trie{
public:
    TrieNode* root;
    Trie(){
        root = new TrieNode();
    }
    // 查询是否冗余
    queryStatus queryWord(string word);
    // 根据查询结果判别插入新单词的类别是否需要加新分支
    void insertWordPrefix(string word);
    void insertWord(string word);
    int findWordCnt(string word);
};

queryStatus Trie::queryWord(string word){
    int off = 0;
    int slen = word.length();
    TrieNode* parent = root;
    TrieNode* cur;
    while(off < slen){
        cur = parent->hashChildNode[word[off]];
        if(!cur)
            break;
        off++;
        parent = cur;
    }
    if(off == slen){
        if(parent->flag)
            return redundancy;
        else return newprefix;
        
    }else{
        return newword;
    }
}

void Trie::insertWordPrefix(string word){
    int off = 0;
    int slen = word.length();
    TrieNode* parent = root;
    TrieNode* cur;
    while(off < slen){
        cur = parent->hashChildNode[word[off++]];
        (cur->wordCnt)++;
        parent = cur;
    }
    parent->flag = true;
}

void Trie::insertWord(string word){
    int off = 0;
    int slen = word.length();
    TrieNode* parent = root;
    TrieNode* cur = root->hashChildNode[word[off]];
    //前半部分
    while(cur){
        (cur->wordCnt)++;
        parent = cur;
        cur = cur->hashChildNode[word[++off]];
    }
    //后半部分
    while(off < slen){
        parent->hashChildNode[word[off++]] = cur = new TrieNode();
        (cur->wordCnt)++;
        parent = cur;
    }
    parent->flag = true;
}

int Trie::findWordCnt(string word){
    int off=0;
    int slen = word.length();
    TrieNode* parent = root;
    TrieNode* cur;
    
    while(off<slen){
        cur = parent->hashChildNode[word[off]];
        if(!cur)
            break;
        parent = cur;
        off++;
    }
    if(off == slen){
        return parent->wordCnt;
    }else{
        return 0;
    }
}

int main()
{
    int n,m;
    cin>>n;
    string is;
    
    Trie* myTrie = new Trie();
    
    for(int i=0;i<n;i++){
        cin>>is;
        queryStatus res = myTrie->queryWord(is);
        if(res == redundancy){
            //continue;
            //如果出现相同的单词，应该将其视作不同的单词
            myTrie->insertWordPrefix(is);
        }
        else if(res == newprefix)
            myTrie->insertWordPrefix(is);
        else if(res == newword)
            myTrie->insertWord(is);
    }
    
    cin>>m;
    
    for(int i=0;i<m;i++){
        cin>>is;
        int cnt = myTrie->findWordCnt(is);
        cout<<cnt<<endl;
    }
    
    return 0;
}