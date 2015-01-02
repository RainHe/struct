#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
int **max_common_sequency(char *x, int x_length, char *y, int y_length) {
    int **max_length = new int*[x_length];
    for (int i = 0; i < x_length; i++) {
        max_length[i] = new int[y_length];
        for (int j = 0 ; j < y_length; j++) {
            max_length[i][j] = 0;
        }
    }
    int **position = new int*[x_length];
    for (int i = 0; i < x_length; i++) {
        position[i] = new int[y_length];
        for (int j = 0 ; j < y_length; j++) {
            position[i][j] = -2;
        }
    }
    for (int i = 1; i < x_length; i++) {
        for (int j = 1; j < y_length; j++) {
            if (x[i-1] == y[j-1]) {
                max_length[i][j] = max_length[i-1][j-1] + 1;
                position[i-1][j-1] = 0;
            } else if ( max_length[i-1][j] >= max_length[i][j-1] ) {
                max_length[i][j] = max_length[i-1][j];
                position[i-1][j-1] = 1;
            } else {
                max_length[i][j] = max_length[i][j-1];
                position[i-1][j-1] = -1;
            }
        }

    }
    return position;

}

void print_sequency_result(char *x,int **position, int x_length, int y_length) {
    for (int i = x_length-1, j = y_length-1; i >= 0 && j >= 0;) {
        int flag = position[i][j];
        if (flag == 0) {
            cout << x[i] << " ";
            i = i - 1;
            j = j - 1;
        } else if (flag == 1) {
            i = i - 1;
        } else if (flag == -1) {
            j = j - 1;
        } else {
            i = i - 1;
            j = j - 1;
        }
    }

}

int main(int argc, char *argv[])
{
    char *x = "ACEDACAB";
    char *y = "CADCBAB";
    int **position = max_common_sequency(x,9,y,8);
    print_sequency_result(x,position,9,8);
    return 0;
}
