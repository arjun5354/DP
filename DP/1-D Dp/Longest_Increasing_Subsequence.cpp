/*
 Company Tags  : Microsoft
 Leetcode Link : https://leetcode.com/problems/longest-increasing-subsequence/
*/

class Solution {
public:
    int solveUsingRecursion(vector<int>& nums,int prev,int curr){
        if(curr>=nums.size()) return 0;

        // include
        int include=0;
        if(prev==-1 || nums[curr]>nums[prev]){
            include= 1+solveUsingRecursion(nums,curr,curr+1);
        }
        // exclude
        int exclude=solveUsingRecursion(nums,prev,curr+1);

        int ans=max(include,exclude);
        return ans;
    }
    int solveUsingMem(vector<int>& nums,int prev,int curr,vector<vector<int> >&dp){
        if(curr>=nums.size()) return 0;
         if(dp[curr][prev+1]!=-1) return dp[curr][prev+1];
        // include
        int include=0;
        if(prev==-1 || nums[curr]>nums[prev]){
            include= 1+solveUsingMem(nums,curr,curr+1,dp);
        }
        // exclude
        int exclude=solveUsingMem(nums,prev,curr+1,dp);

        dp[curr][prev+1]=max(include,exclude);
        return dp[curr][prev+1];
    }
    int tabulation(vector<int>& nums){
        int n=nums.size();
        vector<vector<int> >dp(n+1,vector<int>(n+1,0));
        for(int curr=n-1;curr>=0;curr--){
            for(int prev=curr-1;prev>=-1;prev--){

         int include=0;
        if(prev==-1 || nums[curr]>nums[prev]){
            include= 1+dp[curr+1][curr+1];
        }
        // exclude
        int exclude=dp[curr+1][prev+1];

        dp[curr][prev+1]=max(include,exclude);


            }
        }
        return dp[0][0];
    }
    int tabulationSO(vector<int>& nums){
        int n=nums.size();
        // vector<vector<int> >dp(n+1,vector<int>(n+1,0));
        vector<int>currRow(n+1,0);
        vector<int>nextRow(n+1,0);
        for(int curr=n-1;curr>=0;curr--){
            for(int prev=curr-1;prev>=-1;prev--){

            int include=0;
            if(prev==-1 || nums[curr]>nums[prev]){
                include= 1+nextRow[curr+1];
            }
        // exclude
        int exclude=nextRow[prev+1];

        currRow[prev+1]=max(include,exclude);


            }
            // shift
            nextRow=currRow;
        }
        return nextRow[0];
    }
     int solveOptimal(vector<int>& arr) {
        if(arr.size() == 0)
            return 0;
        vector<int> ans;
        ans.push_back(arr[0]);

        for(int i=1; i<arr.size(); i++) {
            if(arr[i] > ans.back()) {
                //include
                ans.push_back(arr[i]);
            }
            else {
                //overwrite
                //find index of just bada element
                int index = lower_bound(ans.begin(), ans.end(), arr[i]) - ans.begin();
                ans[index] = arr[i];
            }
        }
        return ans.size();
    }
    int lengthOfLIS(vector<int>& nums) {
        int curr=0;
        int prev=-1;
        // return solveUsingRecursion(nums,prev,curr);
        vector<vector<int> >dp(nums.size(),vector<int>(nums.size()+1,-1));
        // return solveUsingMem(nums,prev,curr,dp);
        //  return tabulation(nums);
        //  return tabulationSO(nums);
         return solveOptimal(nums);
    }
};