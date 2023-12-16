/*
    Company Tags                : Google, Salesforce, Microsoft, Meta, Amazon
    Frequency                   : 74%
    Leetcode Link               : https://leetcode.com/problems/perfect-squares/
    This question is nothing but just similar to of "Minimum Coins to get sum S (COIN CHANGE - Leetcode : 322)
*/

//Approach-1 (Recusrion ) - Using concept of "Minimum Coins" concept

class Solution {
public:
    int solveUsingRe(int n){
        if(n==0) return 1;
        int sum=INT_MAX;
        for(int i=1;i<=sqrt(n);i++){
            int perfectSquare=i*i;
            int totalSum=1+solveUsingRe(n-perfectSquare);
            sum=min(sum,totalSum);
        }
        return sum;
    }
    //Approach-2 (Recusrion + Memoization)
    int solveUsingMem(int n,vector<int>&dp){
        if(n==0) return 1;
        if(dp[n]!=-1) return dp[n];
        int sum=INT_MAX;
        for(int i=1;i<=sqrt(n);i++){
            int perfectSquare=i*i;
            int totalSum=1+solveUsingMem(n-perfectSquare,dp);
            sum=min(sum,totalSum);
        }
        dp[n]=sum;

        return dp[n];
    }
    //Approach-3 (Tabulation)
    int tabulation(int n){
        vector<int>dp(n+1,0);
       dp[0]=1;
       for(int i=1;i<=n;i++){
           int sum=INT_MAX;
        for(int j=1;j<=sqrt(i);j++){
            int perfectSquare=j*j;
            int totalSum=1+dp[i-perfectSquare];
            sum=min(sum,totalSum);
        }
        dp[i]=sum;

       }
        return dp[n]; 
    }
    int numSquares(int n) {
        // return solveUsingRe(n)-1;
        vector<int>dp(n+1,-1);
        // return solveUsingMem(n,dp)-1;
        return tabulation(n)-1;
    }
};