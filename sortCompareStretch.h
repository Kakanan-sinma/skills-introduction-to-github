vector<vector<int>> merge(vector<vector<int>& intervals){
  if(intervals.empty()) return {};
  sort(intervals.begin(),intervals.end());
  vector<vector<int> merged;
  merged.push_back(intervals[0]);
  for(int i = 1;i < intervals.size();i++){
    vector<int>& lastMerged = intervals.back();
    int nextStart = intervals[i][0];
    int nextEnd = intervals[i][1];

    if(lastMerged[1] >= nextStart){
      lastMerged[1] = max(lastMerged[1],nextEnd);
    }else{
      merged.push_back(intervals[i]);
    }
  }
  return merged;
}
