/*
    Company Tags                : Not known yet but it's worth being asked. Few people mentioned that it was asked in Google but I don't have proof yet
    Leetcode Link               : https://leetcode.com/problems/maximum-profit-in-job-scheduling/
    Similar Leetcode Qn         : Maximum Number of Events That Can Be Attended II (YouTube  : https://www.youtube.com/watch?v=9ykgLt25X9c)
*/

class Solution {
public:
   int  n;
   int getNextIdx( vector<vector<int>>&arr,int s,int target){
       int e=n-1;
       int result=n+1;
       while(s<=e){
           int mid=s+(e-s)/2;
           if(arr[mid][0]>=target){
               result=mid;
            e=mid-1;
           }
           else{
            s=mid+1;
           }
       }
       return result;
   }
   int solveUsingRe( vector<vector<int>>&arr,int i,vector<int>&dp){
       if(i>=n) return 0;
       if(dp[i]!=-1) return dp[i];
       int next=getNextIdx(arr,i+1,arr[i][1]);
       int include=arr[i][2]+solveUsingRe(arr,next,dp);
        int exclude=solveUsingRe(arr,i+1,dp);
        dp[i]=max(include,exclude);

        return dp[i];
   }
   int tabulation( vector<vector<int>>&arr){
         vector<int>dp(n+2,0);// why n+2 bcz in bs result=n+1 so we take n+2 size array
         for(int i=n-1;i>=0;i--){
        int next=getNextIdx(arr,i+1,arr[i][1]);
       int include=arr[i][2]+dp[next];
        int exclude=dp[i+1];
        dp[i]=max(include,exclude);

         }
        return dp[0];
   }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
      n=startTime.size();
     vector<vector<int>>arr(n,vector<int>(3,0));  // {s,e,p}
    for(int i=0;i<n;i++){
        arr[i][0]=startTime[i];
        arr[i][1]=endTime[i];
        arr[i][2]=profit[i];
    }
    auto comp=[&](auto&vec1,auto&vec2){
        return vec1[0] <= vec2[0];
    };
    sort(arr.begin(),arr.end(),comp);
      vector<int>dp(n+1,-1);
    // return solveUsingRe(arr,0,dp);
    return tabulation(arr);
    }
};