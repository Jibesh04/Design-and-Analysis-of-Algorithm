#include <iostream>
using namespace std;

void lcs(string s1, string s2){
    int m = s1.size(), n = s2.size();
    int dp[m + 1][n + 1];
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    for(int i = 0; i <= m; i++, cout<<endl)
        for(int j = 0; j <= n; j++)
            cout<<" "<<dp[i][j];
    cout<<"Length: "<<dp[m][n]<<endl;
    string temp = "";
    int i = m, j = n;
    while(i >= 0 && j >= 0){
        if(dp[i][j] == 0)
            break;
        if(dp[i][j] == dp[i - 1][j])
            i--;
        else if(dp[i][j] == dp[i][j - 1])
            j--;
        else{
            temp += s1[i - 1];
            i--, j--;
        }
    }
    for(int i = temp.size() - 1; i >= 0; i--)
        cout<<temp[i];
    cout<<endl;
}

int main(){
    string s1 = "AXTTB";
    string s2 = "TXBXA";
    lcs(s1, s2);
    return 0;
}