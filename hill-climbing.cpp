#include<bits/stdc++.h>
using namespace std;

void print(vector<vector<int>>& board){
    int n = board.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}

int possible_attacks(vector<int>& state,vector<vector<int>>& board){
    int n = board.size();
    vector<vector<int>> board_state(board);
    int attacking = 0;
    int row, col;
    for (int i = 0; i < n; i++) {
        for(int j=0; j<n; j++){
            board_state[j][i] = 0;
        }
        board_state[state[i]][i] = 1;
        row = state[i], col = i-1;
        while (col >= 0) {
            if(board_state[row][col] == 1) attacking++;
            col--;
        }
  
        row = state[i], col = i + 1;
        while (col < n) {
            if(board_state[row][col] == 1) attacking++;
            col++;
        }
  
        row = state[i] - 1, col = i - 1;
        while (col >= 0 && row >= 0) {
            if(board_state[row][col] == 1) attacking++;
            col--;
            row--;
        }
  
        row = state[i] + 1, col = i + 1;
        while (col < n && row < n) {
            if(board_state[row][col] == 1) attacking++;
            col++;
            row++;
        }
  
        row = state[i] + 1, col = i - 1;
        while (col >= 0 && row < n) {
            if(board_state[row][col] == 1) attacking++;
            col--;
            row++;
        }
  
        row = state[i] - 1, col = i + 1;
        while (col < n && row >= 0) {
            if(board_state[row][col] == 1) attacking++;
            col++;
            row--;
        }
    }
  
    return ceil(attacking/(float)2);
}

void heuristic(vector<vector<int>>& board,vector<vector<int>>& h){
    int n = board.size();
    vector<int> state(n,-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[j][i]==1) state[i] = j;
        }
    }
    for(int i=0;i<n;i++){
        cout<<state[i]<<" "<<endl;
    }
    for(int i=0;i<n;i++){
        int temp = state[i];
        for(int j=0;j<n;j++){
            state[i] = j;
            h[i][j] = possible_attacks(state, board);
        }
        state[i] = temp;
    }
    print(h);
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    vector<vector<int>> board = {{1,0,0,0},
                                 {0,0,1,0},
                                 {0,1,0,0},
                                 {0,0,0,1}
                                };
    int n = board.size();
    vector<vector<int>> h(n,vector<int> (n,0));
    heuristic(board,h);
}