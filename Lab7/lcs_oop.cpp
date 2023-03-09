/* Longest Common Subsequence */

// COPYRIGHT JIBESH04

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

template <class T>
T max_val(T a, T b){
	return (a > b) ? a : b;
}

template <class P>
void printMatrix(P** m, int n_row, int n_col, string x_label, string y_label){
	cout << setw(4) << " ";
	for(int i = 0; i < n_col; i++)
		cout << setw(4) << y_label.at(i);
	cout<<endl;
	for(int i = 0; i < n_row; i++){
		cout << setw(4) << x_label.at(i);
		for(int j = 0; j < n_col; j++)
			cout << setw(4) << m[i][j];
		cout<<endl;
	}
}

class LCS{
		string s1;
		string s2;
		int m, n;
		int **L;
		string lcs_str;
		void setLongestCommonSubsequence();
		int longestCommonSubsequenceLength();
	public:
		LCS(){}
		LCS(string s1, string s2){
			this -> s1 = s1;
			this -> s2 = s2;
			m = (this -> s1).length();
			n = (this -> s2).length();
			lcs_str = "";
			L = new int*[m + 1];
			for(int i = 0; i <= m; i++)
				L[i] = new int[n + 1];
		}
		~LCS(){
			for(int i = 0; i <= m; i++)
				delete L[i];
			delete L;
		}
		void display();
};

void LCS::setLongestCommonSubsequence(){
	int i = m, j = n;
	string temp = "";
	while(i >= 0 && j >= 0){
		if(L[i][j] == 0)
			break;
		if(L[i][j] == L[i - 1][j])
			i--;
		else if(L[i][j] == L[i][j - 1])
			j--;
		/*
		if(L[i][j] == L[i][j - 1])
			j--;
		else if(L[i][j] == L[i - 1][j])
			i--;
		*/
		else{
			temp += s1.at(i - 1);
			i--;
			j--;
		}
	}
	j = temp.length();
	for(i = j - 1; i >= 0; i--)
		lcs_str += temp.at(i);
}

int LCS::longestCommonSubsequenceLength(){
	int m = s1.length();
	int n = s2.length();
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			if(i == 0 || j == 0)
				L[i][j] = 0;
			else if(s1.at(i - 1) == s2.at(j - 1))
				L[i][j] = 1 + L[i - 1][j - 1];
			else
				L[i][j] = max_val(L[i - 1][j], L[i][j - 1]);
		}
	}
	setLongestCommonSubsequence();
	return L[m][n];
}

void LCS::display(){
	cout<<endl<<"Length of the longest common subsequence is: "<<longestCommonSubsequenceLength()<<endl;
	cout<<endl<<"Longest Common Subsequence: \""<<lcs_str<<"\""<<endl;
	cout<<endl<<"DP Matrix: "<<endl;
	printMatrix(L, m+1, n+1, " " + s1, " " + s2);
}

int main(){
	string s1, s2;
	cout<<"Enter the string X: ";
	cin>>s1;
	cout<<"Enter the string Y: ";
	cin>>s2;
	LCS L1(s1, s2);
	L1.display();
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ g++ longestCommonSubsequence.cpp 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ ./a.out 
Enter the string X: AGGTAB
Enter the string Y: GXTXAYB

Length of the longest common subsequence is: 4

Longest Common Subsequence: "GTAB"

DP Matrix: 
           G   X   T   X   A   Y   B
       0   0   0   0   0   0   0   0
   A   0   0   0   0   0   1   1   1
   G   0   1   1   1   1   1   1   1
   G   0   1   1   1   1   1   1   1
   T   0   1   1   2   2   2   2   2
   A   0   1   1   2   2   3   3   3
   B   0   1   1   2   2   3   3   4
   
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ g++ longestCommonSubsequence.cpp 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ ./a.out 
Enter the string X: aggtab
Enter the string Y: gxtxaayb

Length of the longest common subsequence is: 4

Longest Common Subsequence: "gtab"

DP Matrix: 
           g   x   t   x   a   a   y   b
       0   0   0   0   0   0   0   0   0
   a   0   0   0   0   0   1   1   1   1
   g   0   1   1   1   1   1   1   1   1
   g   0   1   1   1   1   1   1   1   1
   t   0   1   1   2   2   2   2   2   2
   a   0   1   1   2   2   3   3   3   3
   b   0   1   1   2   2   3   3   3   4

*/
