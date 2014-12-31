#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int **sequency_list(int *sequency, const int length) {
    int **max = new int*[length];
    //fill(max,max+length,new int[length]);
    for(int i = 0; i<length; i++) {
        max[i] = new int[length];
        for (int j = 0; j < length; j++) {
            max[i][j] = 0;
        }
    }
    int **position = new int*[length];
    //fill(position,position+length,new int[length]);
    for(int i = 0; i<length; i++) {
        position[i] = new int[length];
        for (int j = 0; j < length; j++) {
            position[i][j] = 0;
        }
    }
    for (int l=1; l<length; l++) {
        int i = 0;
        int j = i + l;
        
        for (; i<=j && j < length; i++,j=i+l) {
            for (int k = i; k<j; k++) {
                cout << "before max i " << i << " j " << j << " max : " << max[i][j] << endl;
                int max_fre = max[i][k] + max[k+1][j] + sequency[i]*sequency[k+1]*sequency[j+1];
                cout << "after  max i " << i << " j " << j << " max : " << max[i][j] << " max_fre : " << max_fre << endl;
                if (max[i][j] == 0 || max_fre < max[i][j]) {
                    max[i][j] = max_fre;
                    position[i][j] = k;
                    cout << " from " << i << " to " << j << " min length : " << max[i][j] << endl;
                }
            }
        }
    }
    return position;
    
}

void print_position(int **position, int start, int end, const char *sequency_char) {
    //cout << "start" << start << " end  " << end << endl;
    if (start == end) {
        cout << sequency_char[start];
    }else {
        cout << "(";
        int p = position[start][end];
        print_position(position,start,p, sequency_char);
        print_position(position,p+1,end, sequency_char);
        cout << ")";
    } 
    
}
int main(int argc, char *argv[])
{
    int n = 10;
    int sequency[] = {10,5,3,4,3,6,4,5,3,8};
    const char *sequency_chars = "ABCDEFGHI";
    int **position = sequency_list(sequency,n - 1);
    cout << "****************************************" << endl;
    for(int i = 0; i<n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            cout << " from " << i << " to " << j << " min length : " << position[i][j] << endl;
        }

    }
    print_position(position, 0, n-2, sequency_chars);
    return 0;
}
