class Solution {
public:
    string simplifyPath(string path) {
        vector<string> vec;
        
        // search for "/"
        int start = 0;
        int end;
        for (int i=1; i<path.length(); i++)
        {
            if (path[i]=='/' || i==path.length()-1)
            {
                if (path[i]=='/')
                    end = i;
                else
                    end = i+1;
                
                string s = path.substr(start+1,end-start-1);
                if (s=="." | s=="")
                {
                    // do nothing
                }
                else if (s=="..")
                {
                    if (!vec.empty()) vec.pop_back();
                }
                else
                {
                    vec.push_back(s);
                }
                start = end;
            }
        }
        
        // print full path
        string result = "/";
        for (int i=0; i<vec.size(); i++)
        {
            result.append(vec[i]);
            if (i!=vec.size()-1)
                result.append("/");
        }
        vec.clear();
        return result;
    }
};