bool isValid(string s){
  if(s.length == 0) return true;
  unordered_map<char,char> closeToOpen = {
    {')','('},
    {']','['},
    {'}','{'}
  };
  stack<char> st;
  for(char c : s){
    if(closeToOpen.count(c)){
      if(st.empty() || closeToOpen[c] != st.top()){
        return false;
      }
      st.pop();
    }else{
      st.push(c);
    }
  }
  return st.empty();
}
