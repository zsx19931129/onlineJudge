class Solution {
public:
    string getLineString(vector<string> &lineWords, int maxWidth){
        int vlen = lineWords.size();
        string ret;
        if(vlen == 1){
            ret += lineWords[0];
            ret += string(maxWidth - lineWords[0].length(), ' ');
            return ret;
        }
        int space = 0;
        for(int i=0;i<vlen;++i){
            space += lineWords[i].size();
        }
        space = maxWidth - space;
        int cnt = vlen - 1;
        ret += lineWords[0];
        for(int i=1;i<vlen;++i){
            int tmp = space / cnt;
            if(space % cnt){
                ++tmp;
            }
            ret += string(tmp, ' ');
            ret += lineWords[i];
            space -= tmp;
            --cnt;
        }
        return ret;
    }
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int vlen = words.size();
        vector<string> ret;
        int i = 0;
        while(i<vlen){
            vector<string> lineWords;
            int len = 0;
            bool first = true;
            int j = i;
            while(j<vlen){
                if(!first){
                    len += 1;
                }else{
                    first = false;
                }
                len += words[j].size();
                if(len > maxWidth){
                    break;
                }
                lineWords.push_back(words[j]);
                ++j;
            }
            string line;
            if(j == vlen){
                line += lineWords[0];
                for(int k=1;k<lineWords.size();++k){
                    line += ' ';
                    line += lineWords[k];
                }               
                line += string(maxWidth-line.length(), ' ');
            }else{
                line = getLineString(lineWords, maxWidth);
            }
            ret.push_back(line);
            i = j;
        }
        return ret;
    }
};