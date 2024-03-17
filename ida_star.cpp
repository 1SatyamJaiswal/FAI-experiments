#include<bits/stdc++.h>
using namespace std;

typedef pair<float,pair<int,int>> pi;

void ida(vector<vector<int>>& graph,vector<float>& h,priority_queue<pi, vector<pi>, greater<pi>>& open){
    float f_bound = h[0];
    float f_new = INT_MAX;
    INIT: open.push(make_pair(h[0],make_pair(0,0)));
    while(!open.empty()){
        pair<float, pair<int,int>> curr_state = open.top();
        open.pop();
        float cost = curr_state.first;
        int index = curr_state.second.second;
        float path_cost = cost - h[index];
        cout<<"f-bound: "<<f_bound<<endl;
        if(cost <= f_bound){
            cout<<"On index: "<<index<<" Cost: "<<cost<<endl;
            if(index == 7) {
                cout<<"Goal reached";
                return;
            }
            for(int i=0; i<8; i++){
                if(graph[index][i]!=0){
                    open.push(make_pair(path_cost+h[i]+graph[index][i],make_pair(index,i)));
                    if(path_cost+h[i]+graph[index][i]<=f_bound) cout<<"Explored index: "<<i<<" from "<<index<<" with cost: "<<path_cost+h[i]+graph[index][i]<<endl;
                    else cout<<"Explored index: "<<i<<" from "<<index<<" with cost: "<<path_cost+h[i]+graph[index][i]<<" above limit"<<endl;
                }
            }
        } else {
            f_new = cost;
            cout<<"Cannot Explore Further At Index: "<<index<<" has Cost: "<<cost<<endl;
            int index1 = -1;
            while(!open.empty()){
                pair<float, pair<int,int>> curr_state = open.top();
                if(f_new>curr_state.first){
                    f_new = min(f_new,curr_state.first);
                    index1 = curr_state.second.second;
                }
                open.pop();
            }
            cout<<"Update f_bound from "<<f_bound;
            f_bound = f_new;
            cout<<" to "<<f_bound<<endl;
            goto INIT;
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    vector<vector<int>> graph = {{0,2,3,0,0,0,0,0},
                                 {0,0,0,3,0,0,0,0},
                                 {0,0,0,1,3,0,0,0},
                                 {0,0,0,0,1,3,0,0},
                                 {0,0,0,0,0,0,2,0},
                                 {0,0,0,0,0,0,0,2},
                                 {0,0,0,0,0,0,0,1},
                                 {0,0,0,0,0,0,0,0}};
    vector<float> h = {6,4,4,4,3.5,1,1,0};
    priority_queue<pi, vector<pi>, greater<pi>> open;
    ida(graph,h,open);
}