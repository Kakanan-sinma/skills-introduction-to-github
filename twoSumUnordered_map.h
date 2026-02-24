vector<int> twoSum(vector<int>& nums,int target){
  unordered_map<int,int> memo;
  for(int i = 0;i < nums.size();i++){
    int complement = target - nums[i];
    if(memo.find(complement) != memo.end()){
      return {memo[complement],i};
    }
    memo[nums[i]] = i;
  }
  return {};
}
