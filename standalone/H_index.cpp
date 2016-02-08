class Solution {
public:
    // Descending order
    vector<int> quickSort(vector<int>& vec)
    {
        int n = vec.size();
        if (n==0 || n==1)
            return vec;
            
        int pivot = vec[0];
        int i=0;
        int j=0;
        vector<int> less(n);
        vector<int> more(n);
        for (int k=1; k<n; k++)
        {
            if (vec[k]<pivot)
                less[i++] = vec[k];
            else
                more[j++] = vec[k];
        }
        less.resize(i);
        more.resize(j);
        
        vector<int> result = quickSort(more);
        result.push_back(pivot);
        vector<int> result2 = quickSort(less);
        result.insert(result.end(),result2.begin(),result2.end());
        more.clear();less.clear();result2.clear();
        return result;
    }
    
	/*
	    Cite[] = 6 5 3 1 0 (descending order)
	   Index[] = 1 2 3 4 5 (start from 1)
		             ^
				last position where Cite[i]>=Index[i] ===> H-index==i
	*/
    int hIndex(vector<int>& citations) {
        vector<int> sorted_cite = quickSort(citations);
        int i;
        for (i=0; i<citations.size(); i++)
        {
            if (sorted_cite[i]<i+1) break;
        }
        return i;
    }
};