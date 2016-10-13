//
//  main.cpp
//  weeklyhiho
//
//  Created by shaoxiong on 10/2/16.
//  Copyright © 2016 shaoxiong. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode{
public:
    int wordCnt;        //标记以当前前缀开头的单词有多少个
    TrieNode():wordCnt(0){
        for(int i=0;i<26;++i){
            nexts[i] = NULL;
        }
    }
    TrieNode* nexts[26];
};

class Trie{
public:
    TrieNode* root;
    Trie(){
        root = new TrieNode();
    }
    void insertWord(string word);
    int findWord(string word);
};

inline int getidx(char ch){
    return ch - 'a';
}

void Trie::insertWord(string word){
    int off = 0;
    int slen = word.length();
    TrieNode* parent = root;
    TrieNode* cur = root->nexts[getidx(word[off])];
    while(off < slen && cur){
        ++(cur->wordCnt);
        parent = cur;
        cur = parent->nexts[getidx(word[++off])];
    }
    while(off < slen){
        cur = parent->nexts[getidx(word[off++])] = new TrieNode();
        ++(cur->wordCnt);
        parent = cur;
    }
}

int Trie::findWord(string word){
    int off=0;
    int slen = word.length();
    TrieNode* parent = root;
    TrieNode* cur;
    
    while(off<slen){
        cur = parent->nexts[getidx(word[off])];
        if(!cur){
            break;
        }
        parent = cur;
        ++off;
    }
    return (off == slen) ? (parent->wordCnt) : 0;
}

int main() {
    int n;
    cin>>n;
    string word;
    Trie* trieRoot = new Trie();
    while(n--){
        cin>>word;
        trieRoot->insertWord(word);
    }
    int m;
    cin>>m;
    while(m--){
        cin>>word;
        cout<<trieRoot->findWord(word)<<endl;
    }
    return 0;
}
