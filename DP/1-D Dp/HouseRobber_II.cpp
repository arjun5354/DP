/*
    Company Tags                : Airbnb, Microsoft
    Leetcode Link               : https://leetcode.com/problems/house-robber-ii/
*/



// This is the process i do using vector 

class Solution {
public:
    int solveUsingRe(vector<int>&nums,int i,int n){
        if(i>n) return 0;
        int include=nums[i]+solveUsingRe(nums,i+2,n);
        int exclude=solveUsingRe(nums,i+1,n);
        return max(include,exclude);
    }
    int solveUsingMem(vector<int>&nums,int i,int n,vector<int>&dp){
        if(i>n) return 0;
        if(dp[i]!=-1)return dp[i];
        int include=nums[i]+solveUsingMem(nums,i+2,n,dp);
        int exclude=solveUsingMem(nums,i+1,n,dp);
        dp[i]= max(include,exclude);
        return dp[i];
    }
    int tabulation(vector<int>&nums,int i,int n){
    vector<int>dp(n+3,0);
    for(int j=n;j>=i;j--){
     int include=nums[j]+dp[j+2];
     int exclude=dp[j+1];
        dp[j]= max(include,exclude);
         
    }
        return dp[i];
       
    }
    int spaceOpti(vector<int>&nums,int i,int n){
     int next1=0,next2=0;
    for(int j=n;j>=i;j--){
     int include=nums[j]+next2;
     int exclude=next1;
       int curr= max(include,exclude);
        next2=next1;
        next1=curr; 
    }
 return next1;  
    }
    int rob(vector<int>& nums) {
    if(nums.size()==1) return nums[0];
    if(nums.size()==2) return max(nums[0],nums[1]);
    // return max(solveUsingRe(nums,0,nums.size()-2), solveUsingRe(nums,1,nums.size()-1));

    // vector<int>dp1(nums.size()+1,-1);
    // vector<int>dp2(nums.size()+1,-1);
    // return max(solveUsingMem(nums,0,nums.size()-2,dp1), solveUsingMem(nums,1,nums.size()-1,dp2));

    //  return max(tabulation(nums,0,nums.size()-2), tabulation(nums,1,nums.size()-1));
     return max(spaceOpti(nums,0,nums.size()-2), spaceOpti(nums,1,nums.size()-1));
    }
};




// This is the process i do using normal array and memset 


//Approach-1 (Recur + Memo)
class Solution {
public:
    int t[101];
    int solve(vector<int>& nums, int i, int n) {
        if(i > n)
            return 0;
        
        if(t[i] != -1)
            return t[i];
        
        int take = nums[i] + solve(nums, i+2, n); //steals ith house and moves to i+2 (because we can't steal adjacent)
        int skip = solve(nums, i+1, n); //skips this house, now we can move to adjacent next house
        
        return t[i]=max(take, skip);
    }
    
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        if(n == 1)
            return nums[0];
        
        if(n == 2)
            return max(nums[0], nums[1]);
        
        memset(t, -1, sizeof(t));
        
        //case-1 - Take first house 0th index wala house
        
        int take_0th_index_house = solve(nums, 0, n-2);
        
        memset(t, -1, sizeof(t));
        
        //case-2  - Take second house 1st index wala house
        int take_1st_index_house = solve(nums, 1, n-1);
        
        
        return max(take_0th_index_house, take_1st_index_house);
        
        
    }
};



//Approach-2 (Using Bottom Up similar to House Robber-1 and just taking two cases
/*
    Case-1 (Take from 1st House - Hence skip the last house)
    Case-2 (Take from 2nd House - Hence take the last house)
*/
class Solution {
public:
    int n;
    
    int rob(vector<int>& nums) {
        n = nums.size();
        if(n == 1)
            return nums[0];
        
        vector<int> t(n+1, 0);
        //t[i] = Max money gained from i houses
        
        int result1 = 0;
        int result2 = 0;
        
        //Case-1 (Take from 1st House - Hence skip the last house)
        t[0] = 0;
        for(int i = 1; i<=n-1; i++) {
            t[i] = max(t[i-1] , nums[i-1]+ ((i-2 >= 0) ? t[i-2] : 0 ));
        }
        result1 = t[n-1];
        
        t.clear();
        //Case-2 (Take from 2nd House - Hence take the last house)
        t[0] = 0;
        t[1] = 0;
        for(int i = 2; i<=n; i++) {
            t[i] = max(t[i-1] , nums[i-1]+ ((i-2 >= 0) ? t[i-2] : 0 ));
        }
        result2 = t[n];
        
        return max(result1, result2);
        
    }
};




//Approach-3 (Converting Bottom Up to constant space)
class Solution {
public:
    
    //this function is solution of House robber I. We just use it to solve House Robber II
    int solve(vector<int>& nums, int l, int r) {
        
        int prevPrev = 0, prev = 0;
        
        for(int i = l; i<=r; i++) {
            int skip = prev;
            int take = nums[i] + prevPrev;
            
            int temp = max(skip, take);
            
            prevPrev = prev;
            prev     = temp;
        }
        
        return prev;
    }
    
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)
            return nums[0];
        
        if(n == 2)
            return max(nums[0], nums[1]);
        
        int take_first_house = solve(nums, 0, n-2);
        
        int skip_first_house = solve(nums, 1, n-1);
        
        
        return max(take_first_house, skip_first_house);
    }
};