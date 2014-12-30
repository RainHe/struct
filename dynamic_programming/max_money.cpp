#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
using namespace std;

int *max_money(int *price, int max) {
    int *max_price = new int[max];
    int *max_position = new int[max];
    fill(max_price, max_price + max, 0);
    fill(max_position, max_position + max, 0);
    for (int i = 1; i <= max; i++) {
        int m_price = 0;
        for(int j = 1; j <= i; j++) {
            int pri = 0;
            if (i - j == 0) {
                pri = price[i-1];
            } else {
                pri = price[i-j-1];
            }
            int f_price = max_price[j-1] + pri;
            if (f_price > m_price) {
                m_price = f_price;
                max_position[i-1] = j - 1;
            }
        }
        max_price[i-1] = m_price;
    }
    for(int i = 0; i<max; i++) {
        cout << " price " << max_price[i]<<endl;
    }
    return max_position;

}

void print_plan(int *max_position, int max) {
    if (max > 0) {
        int position = max_position[max - 1];
        cout << " split size : " << position + 1 << endl;
        print_plan(max_position, max-position-1);
    }
}
int main(int argc, char *argv[])
{
    //int prices[10] = {1,5,8,9,10,17,17,20,24,30};
    int n = 6;
    int prices[10] = {2,6,7,9,10,17,17,20,24,30};
    int *max_position = max_money(prices,n);
    for (int i = 0; i<n; i++) {
        cout << max_position[i] << endl;
    }
    print_plan(max_position,n);
    return 0;
}
