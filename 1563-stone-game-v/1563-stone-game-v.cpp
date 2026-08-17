class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
      
        
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }
      
        
        vector<vector<int>> dp(n, vector<int>(n, -1));
      
        // Recursive function with memoization to find maximum score
        auto dfs = [&](this auto&& dfs, int left, int right) -> int {
            // Base case: if range is invalid or has only one stone
            if (left >= right) {
                return 0;
            }
          
            // Return memoized result if already computed
            if (dp[left][right] != -1) {
                return dp[left][right];
            }
          
            int maxScore = 0;
            int leftSum = 0;
            int rightSum = prefixSum[right + 1] - prefixSum[left];
          
            // Try all possible split points
            for (int splitPoint = left; splitPoint < right; ++splitPoint) {
                leftSum += stoneValue[splitPoint];
                rightSum -= stoneValue[splitPoint];
              
                if (leftSum < rightSum) {
                    // Bob chooses right part, Alice gets left part's sum
                    // Pruning: if current answer is already greater than maximum possible score
                    if (maxScore > leftSum * 2) {
                        continue;
                    }
                    maxScore = max(maxScore, leftSum + dfs(left, splitPoint));
                } 
                else if (leftSum > rightSum) {
                    // Bob chooses left part, Alice gets right part's sum
                    // Pruning: if current answer is already greater than maximum possible score
                    if (maxScore > rightSum * 2) {
                        break;
                    }
                    maxScore = max(maxScore, rightSum + dfs(splitPoint + 1, right));
                } 
                else {
                    // Left sum equals right sum, Bob can choose either part
                    // Alice gets the sum plus the optimal score from chosen part
                    maxScore = max({maxScore, 
                                   leftSum + dfs(left, splitPoint), 
                                   rightSum + dfs(splitPoint + 1, right)});
                }
            }
          
            // Store and return the result
            dp[left][right] = maxScore;
            return maxScore;
        };
      
        // Start the game with all stones (indices 0 to n-1)
        return dfs(0, n - 1);
    }
};
