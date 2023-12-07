/* Company Tags                : GOOGLE
    Leetcode Link               : https://leetcode.com/problems/longest-string-chain/
*/

/*
  NOTE - Since this problem is a variant of LIS (only difference is that we can pick the element/word in any order)
  So we sort the input in ascending order of their length to get the longest string chain as per condition.
  Also, since it's variant of LIS, it can be solved using all those methods by which LIS could be solved.
*/



class Solution {
public:
    int solveUsingRe(vector<vector<int>>&pairs,int i,int p){
        if(i>=pairs.size()) return 0;
        
        int include=0;
        if(p==-1 || pairs[p][1]<pairs[i][0])
             include=1+solveUsingRe(pairs,i+1,i);
        int exclude=solveUsingRe(pairs,i+1,p);

        return max(include,exclude);
    }

    int solveUsingMem(vector<vector<int>>&pairs,int i,int p, vector<vector<int>>&dp){
        if(i>=pairs.size()) return 0;
        if(dp[i][p+1]!=-1) return dp[i][p+1];
        int include=0;
        if(p==-1 || pairs[p][1]<pairs[i][0])
             include=1+solveUsingMem(pairs,i+1,i,dp);
        int exclude=solveUsingMem(pairs,i+1,p,dp);

        dp[i][p+1]= max(include,exclude);
        return dp[i][p+1];
    }
    int tabulation(vector<vector<int>>&pairs){
       vector<vector<int>>dp(pairs.size()+1,vector<int>(pairs.size()+1,0));
       for(int i=pairs.size()-1;i>=0;i--){
           for(int p=pairs.size()-1;p>=-1;p--){

             
                int include=0;
                if(p==-1 || pairs[p][1]<pairs[i][0])
                    include=1+dp[i+1][i+1]; // ***yah galti karunga here we have to do i+1(p+1)
                int exclude=dp[i+1][p+1];

                dp[i][p+1]= max(include,exclude);

           }
       }
  return dp[0][0];
    }

    int spaceOptimisation(vector<vector<int>>&pairs){
    //    vector<vector<int>>dp(pairs.size()+1,vector<int>(pairs.size()+1,0));
    vector<int>curr(pairs.size()+1,0);
    vector<int>next(pairs.size()+1,0);
       for(int i=pairs.size()-1;i>=0;i--){
           for(int p=pairs.size()-1;p>=-1;p--){

             
                int include=0;
                if(p==-1 || pairs[p][1]<pairs[i][0])
                    include=1+next[i+1]; // ***yah galti karunga here we have to do i+1(p+1)
                int exclude=next[p+1];

                curr[p+1]= max(include,exclude);

           }
           next=curr;
       }
  return next[0];
    }
    int spaceOptimisation2(vector<vector<int>>&pairs){
    vector<int>curr(pairs.size()+1,0);
    // vector<int>next(pairs.size()+1,0);
       for(int i=pairs.size()-1;i>=0;i--){
           for(int p=pairs.size()-1;p>=-1;p--){

             
                int include=0;
                if(p==-1 || pairs[p][1]<pairs[i][0])
                    include=1+curr[i+1]; // ***yah galti karunga here we have to do i+1(p+1)
                int exclude=curr[p+1];

                curr[p+1]= max(include,exclude);

           }
       }
  return curr[0];
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end());
        // return solveUsingRe(pairs,0,-1);
        vector<vector<int>>dp(pairs.size()+1,vector<int>(pairs.size()+1,-1));
        // return solveUsingMem(pairs,0,-1,dp);

        // return tabulation(pairs);
        return spaceOptimisation2(pairs);
    }
};