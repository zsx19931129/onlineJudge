//
//  main.cpp
//  codeJamTest
//
//  Created by shaoxiong on 8/26/16.
//  Copyright © 2016 shaoxiong. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

vector<string> splitByDelim(string inputStr, string delim){
    vector<string> ret;
    size_t pos = 0;
    string token;
    while((pos = inputStr.find(delim)) != string::npos){
        token = inputStr.substr(0, pos);
        ret.push_back(token);
        inputStr.erase(0, pos + delim.length());
    }
    ret.push_back(inputStr);
    return ret;
}

int stringToInt(string inputStr, int base=10){
    return stoi(inputStr, nullptr, base);
}

string stringJoinByDelim(vector<string> stringVec, string delim){
    size_t vlen = stringVec.size();
    if(vlen == 0){
        return "";
    }
    string ret = stringVec[0];
    for(size_t i=1;i<vlen;++i){
        ret += (delim + stringVec[i]);
    }
    return ret;
}

vector<int> getDV(string divide){
    vector<int> ret;
    vector<string> splitStrs = splitByDelim(divide, "-");
    for(int i=0;i<splitStrs.size();++i){
        ret.push_back(stringToInt(splitStrs[i]));
    }
    return ret;
}

vector<string> getSplitedPN(string pn, vector<int> dv){
    vector<string> ret;
    string token;
    for(int i=0;i<dv.size();++i){
        token = pn.substr(0, dv[i]);
        ret.push_back(token);
        pn.erase(0, dv[i]);
    }
    return ret;
}

vector<pair<int, int>> getWordVec(vector<string> splitedPN){
    vector<pair<int, int>> ret;
    string token;
    for(int i=0;i<splitedPN.size();++i){
        token = splitedPN[i];
        char lastChar = token[0];
        int lastCnt = 1;
        for(int j=1;j<token.length();++j){
            if(token[j] == lastChar){
                ++lastCnt;
            }else{
                ret.push_back(make_pair(lastCnt, lastChar-'0'));
                lastChar = token[j];
                lastCnt = 1;
            }
        }
        ret.push_back(make_pair(lastCnt, lastChar-'0'));
    }
    return ret;
}

string getWords(vector<pair<int, int>> wordVec){
    string ret = "";
    string numArr[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string cntArr[11] = {"", "", "double", "triple", "quadruple", "quintuple", "sextuple", "septuple", "octuple", "nonuple", "decuple"};
    
    bool first = true;
    for(int i=0;i<wordVec.size();++i){
        pair<int, int> cur = wordVec[i];
        int cnt = cur.first, num = cur.second;
        
        if(!first){
            ret += " ";
        }else{
            first = false;
        }
        if(cnt == 1){
            ret += numArr[num];
        }else if(cnt>10){
            string token = numArr[num];
            for(int j=1;j<cnt;++j){
                token += (" " + numArr[num]);
            }
            ret += token;
        }else{
            ret += (cntArr[cnt] + " " + numArr[num]);
        }
    }
    return ret;
}

int main(int argc, const char * argv[]) {
    ifstream in("A-large-practice.in");
    streambuf *cinbuf = cin.rdbuf();    // save old buf
    cin.rdbuf(in.rdbuf());              // redirect std::cin to in.txt


    ofstream out("A-large-practice.out");
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());
    
    
    int T;
    cin>>T;
    
    for(int i=1;i<=T;++i){
        string phoneNumber, divide;
        cin>>phoneNumber>>divide;
        vector<int> dv = getDV(divide);
        vector<string> splitedPN = getSplitedPN(phoneNumber, dv);
        vector<pair<int, int>> wordVec = getWordVec(splitedPN);
        string output = getWords(wordVec);
        cout<<"Case #"<<i<<": "<<output<<endl;
    }
    
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    return 0;
}
