/*
    Company Tags                : Amazon
    Leetcode Link               : https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
*/


//Approach - 1 (Recursion + Memoization)

class Solution {
public:
    int solveUsingRe(vector<int>& jd, int d,int i){
        /*
        If there is only one day left , then you have to do all remaining jobs in that one day
        and find the max difficulty of that day and return it
        */
        if(d==1){
            int maxD=jd[i];
            for(int idx=i;idx<jd.size();idx++){
                maxD=max(maxD,jd[idx]);
            }
            return maxD;
        }


         int maxD=INT_MIN;
         int finalresult=INT_MAX;
        for(int idx=i;idx<=jd.size()-d;idx++){
            maxD=max(maxD,jd[idx]);
           int result=maxD+solveUsingRe(jd,d-1,idx+1);
            finalresult=min(result,finalresult);
        }
        return finalresult;
    }
    int solveUsingMem(vector<int>& jd, int d,int i, vector<vector<int>>&dp){
        /*
        If there is only one day left , then you have to do all remaining jobs in that one day
        and find the max difficulty of that day and return it
        */
        if(d==1){
            int maxD=jd[i];
            for(int idx=i;idx<jd.size();idx++){
                maxD=max(maxD,jd[idx]);
            }
            return maxD;
        }
       if( dp[i][d]!=-1) return  dp[i][d];

         int maxD=INT_MIN;
         int finalresult=INT_MAX;
        for(int idx=i;idx<=jd.size()-d;idx++){
            maxD=max(maxD,jd[idx]);
           int result=maxD+solveUsingMem(jd,d-1,idx+1,dp);
            finalresult=min(result,finalresult);
        }
        return dp[i][d] =finalresult;
    }
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        if(d>jobDifficulty.size()) return -1;
        // return solveUsingRe(jobDifficulty,d,0);
        vector<vector<int>>dp(jobDifficulty.size()+1,vector<int>(d+1,-1));
 ;       return solveUsingMem(jobDifficulty,d,0,dp);
    }
};