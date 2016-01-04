//Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0.

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n_rows = matrix.size();
        int n_cols = matrix.at(0).size();
        
        vector<bool> row_map(n_rows, 0);
        vector<bool> col_map(n_cols, 0);
        
        // First pass - mark rows and cols with zeros
        for (int i=0; i<n_rows; i++)
        {
            for (int j=0; j<n_cols; j++)
            {
                if (matrix[i][j]==0)
                {
                    row_map[i] = 1;
                    col_map[j] = 1;
                }
            }
        }
        
        // Second pass - set each element in marked rows/cols to zero
        for (int i=0; i<n_rows; i++)
        {
            for (int j=0; j<n_cols; j++)
            {
                if (row_map[i] == 1 && col_map[j] == 1)
                {
                    matrix[i][j]==0;
                }
            }
        }   
    }
};