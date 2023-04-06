#include <iostream>
using namespace std;
#define MAX 100

void print_co(int dp[][MAX][2], int l, int h){
    if(l == h){
        cout<<"A"<<l;
        return;
    }
    cout<<"(";
    print_co(dp, l, dp[l][h][1]);
    print_co(dp, dp[l][h][1] + 1, h);
    cout<<")";
}

void mcm(int p[], int n){
    int dp[MAX][MAX][2];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            dp[i][j][0] = dp[i][j][1] = 0;

    for(int i = 1; i < n; i++){
        dp[i][i][0] = 0;
        dp[i][i][1] = 0;
    }

    for(int l = 2; l < n; l++){
        for(int i = 1; i < n - l + 1; i++){
            int j = i + l - 1;
            dp[i][j][0] = INT_MAX;
            for(int k = i; k < j; k++){
                int cost = dp[i][k][0] + dp[k + 1][j][0] + p[i - 1]*p[k]*p[j];
                if(cost < dp[i][j][0]){
                    dp[i][j][0] = cost;
                    dp[i][j][1] = k;
                }
            }
        }
    }
    for(int i = 1; i < n; i++, cout<<endl)
        for(int j = 1; j < n; j++)
            cout<<" "<<dp[i][j][0]<<"|"<<dp[i][j][1]<<" ";
    print_co(dp, 1, n - 1);
    cout<<"Minimum Cost: "<<dp[1][n-1][0]<<endl;
}

int main(){
    int p[] = {4, 1, 2, 3};
    int n = sizeof(p)/sizeof(p[0]);
    mcm(p, n);
    return 0;
}