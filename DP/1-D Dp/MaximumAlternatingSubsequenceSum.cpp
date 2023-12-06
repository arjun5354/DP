/*                                  
    Company Tags                : META, GOOGLE, AMAZON
    Leetcode Link               : https://leetcode.com/problems/maximum-alternating-subsequence-sum/

*/

// Using vector

class Solution {
public:
    long long solveUsingRe(vector<int>&nums,long long i,bool flag){
        if(i>=nums.size()) return 0;
        long long skip=solveUsingRe(nums,i+1,flag);
        long long val=nums[i];
        if(flag==false) val=-val;
        long long take=solveUsingRe(nums,i+1,!flag)+val;

        return max(skip,take);
    }
    long long solveUsingMem(vector<int>&nums,long long i,bool flag, vector<vector<long long> >&dp){
        if(i>=nums.size()) return 0;
        if(dp[i][flag]!=-1) return dp[i][flag];
        long long skip=solveUsingMem(nums,i+1,flag,dp);
        long long val=nums[i];
        if(flag==false) val=-val;
        long long take=solveUsingMem(nums,i+1,!flag,dp)+val;

        dp[i][flag]= max(skip,take);
        return dp[i][flag];
    }
    long long tabulation(vector<int>&nums){
         vector<vector<long long> >dp(nums.size()+1,vector<long long>(2,0));
         for(int i=nums.size()-1;i>=0;i--){
             for(int flag=0;flag<2;flag++){

        long long skip=dp[i+1][flag];
        long long val=nums[i];
        if(flag==false) val=-val;
        long long take=dp[i+1][!flag]+val;

        dp[i][flag]= max(skip,take);

             }
         }
        return dp[0][true];
    }
    long long spaceOpti(vector<int>&nums){
         vector<long long>curr(2,0);
         vector<long long>next(2,0);
         for(int i=nums.size()-1;i>=0;i--){
             for(int flag=0;flag<2;flag++){

        long long skip=next[flag];
        long long val=nums[i];
        if(flag==false) val=-val;
        long long take=next[!flag]+val;

        curr[flag]= max(skip,take);

             }
             next=curr;
         }
        return next[true];
    }
    long long maxAlternatingSum(vector<int>& nums) {
        // return solveUsingRe(nums,0,true);
        vector<vector<long long> >dp(nums.size()+1,vector<long long>(2,-1));
        // return solveUsingMem(nums,0,true,dp);
        // return tabulation(nums);
        return spaceOpti(nums);
    }
};




//Approach-1 (Recursion + Memo) (Time Complexity - n*2 : We visit all states of t once)
class Solution {
public:
    int n;
    long long t[1000001][2];
    long long solve(int idx, vector<int>& nums, bool iseven) {
        
        if(idx >= n) {
            return 0;
        }
        if(t[idx][iseven] != -1)
            return t[idx][iseven];
        
        long long skip = solve(idx+1, nums, iseven);
        
        long long val = nums[idx];
        if(iseven == false) {
            val = -val;
        }
        
        long long take = solve(idx+1, nums, !iseven) + val;
        
        return t[idx][iseven] = max(skip, take);
        
    }
    
    long long maxAlternatingSum(vector<int>& nums) {
        n = nums.size();
        memset(t, -1, sizeof(t));
        return solve(0, nums, true);
    }
};


//Approach-2 (Bottom Up) -- T.C : O(n), space : O(n)
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        
        vector<vector<long>> t(n, vector<long>(2, 0));

        t[0][0] = max(-nums[0], 0);
        t[0][1] = max(nums[0], 0);
            
        for(int i = 1; i < n; i++) {
            
            t[i][0] = max(t[i-1][1] - nums[i], t[i-1][0]);
            
            t[i][1] = max(t[i-1][0] + nums[i], t[i-1][1]);
            
            
        }
        
        return max(t[n-1][0], t[n-1][1]);
    }
};

//Approach-3 (Same as Approach-2 - Only difference is that I have used 1 based indexing to make it general to other Botto Up)
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        
        vector<vector<long>> t(n+1, vector<long>(2, 0));
            
        for(int i = 1; i < n+1; i++) {
            
            t[i][0] = max(t[i-1][1] - nums[i-1], t[i-1][0]);
            
            t[i][1] = max(t[i-1][0] + nums[i-1], t[i-1][1]);
            
            
        }
        
        return max(t[n][0], t[n][1]);
    }
};