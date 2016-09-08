class Solution {
public:
    int lengthOfLastWord(string s) {
        int ret = 0, charCnt = 0;
        int slen = s.length();
        int i=0;
        while(i<slen){
            if(s[i] == ' '){
                ret = charCnt;
                charCnt = 0;
                ++i;
                while(i<slen && s[i] == ' '){
                    ++i;
                }
            }else{
                ++charCnt;
                ++i;
            }
        }
        if(s[slen-1] != ' '){
            ret = charCnt;
        }
        return ret;
    }
};