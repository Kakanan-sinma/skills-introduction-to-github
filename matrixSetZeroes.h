void setZeroes(vector<vector<int>>& matrix){
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<bool> row_marked(rows,false);
  vector<bool> col_marked(cols,false);

  for(int r = 0;r < rows;r++){
    for(int c = 0;c < cols;c++){
      if(matrix[r][c] == 0){
        row_marked[r] = true;
        col_marked[c] = true;
      }
    }
  }
  for(int r = 0;r < rows;r++){
    for(int c = 0;c < cols;c++){
      if(row_marked[r] || col_marked[c]){
        matrix[r][c] = 0;
      }
    }
  }
  return;
}
