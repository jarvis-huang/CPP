#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Mat {
    vector< vector<T> > data;
public:
    Mat(int nr, int nc)
    {
        data.resize(nr, vector<int>(nc));
    }

    ~Mat()
    {
        int nr = getRows();
        for (int i = 0; i<nr; i++)
            data[i].clear();
        data.clear();
    }

    void init(vector< vector<T> > d)
    {
        int nr = getRows();
        int nc = getCols();
        if (d.size() != nr || d[0].size() != nc)
            return;
           
        for (int i = 0; i<nr; i++)
            for (int j = 0; j<nc; j++)
                data[i][j] = d[i][j];
    }

    T at(int i, int j)
    {
        int nr = getRows();
        int nc = getCols();
        if (i >= nr || j >= nc)
            return NULL;
        else
            return data[i][j];
    }

    int getRows()
    {
        return data.size();
    }
    int getCols()
    {
        vector<int> t = data[0];
        return t.size();
    }
    void set(int i, int j, T val)
    {
        int nr = getRows();
        int nc = getCols();
        if (i >= nr || j >= nc)
            return;
        else
            data[i][j] = val;
    }
    void print()
    {
        int nr = getRows();
        int nc = getCols();
        for (int i = 0; i<nr; i++)
        {
            for (int j = 0; j<nc; j++)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector< vector<int> > mtx(3, vector<int>(3, 1));
    Mat<int> m(3, 3);
    m.init(mtx);
    m.print();
    cout << "---" << endl;
    m.set(1, 0, 2); m.set(1, 1, 2); m.set(1, 2, 2);
    m.set(2, 0, 3); m.set(2, 1, 3); m.set(2, 2, 3);
    m.print();
    return 0;
}