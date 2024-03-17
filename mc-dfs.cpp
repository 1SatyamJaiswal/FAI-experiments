#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct State {
    int lc;
    int lm;
    int rc;
    int rm;
    int boat;

    bool operator==(const State& other) const {
        return lc == other.lc && lm == other.lm && rc == other.rc && rm == other.rm && boat == other.boat;
    }

};

bool isValid(State& state) {
    if ((state.lc >= 0 && state.rc >= 0 && state.lm >= 0 && state.rm >= 0 && state.rc <= 3 && state.lc <= 3 && state.rm <= 3 && state.lm <= 3) && (state.rm==0 || state.rm >= state.rc) && (state.lm==0 || state.lm >= state.lc)) {
        return true;
    }
    else {
        return false;
    }
}

bool isGoal(State& state) {
    if (state.lc == 0 && state.lm == 0 && state.rc == 3 && state.rm == 3 && state.boat == 1) {
        return true;
    }
    else {
        return false;
    }
}

void dfs(State& state, vector<State>& visited, vector<State>& path, int& open, int& closed) {
    if (isGoal(state)) {
        cout << "Goal State Reached" << endl;
        cout << "Path to the goal state:" << endl;
        for (const State& step : path) {
            cout << "Left Bank: " <<step.lm<< "M "<<step.lc<<"C "<<(step.boat==0 ? "Boat":"\t")<<"\t\t\t\t"; 
            cout <<"Right Bank: " <<step.rm<<"M "<<step.rc<<"C "<<(step.boat==1 ? "Boat ":"") <<endl; 
        }
        cout << "Left Bank: " <<state.lm<< "M "<<state.lc<<"C "<<(state.boat==0 ? "Boat":"\t")<<"\t\t\t\t"; 
        cout <<"Right Bank: " <<state.rm<<"M "<<state.rc<<"C "<<(state.boat==1 ? "Boat ":"") <<endl;
        return;
    }
    if (isValid(state)) {
        if (find(visited.begin(), visited.end(), state) == visited.end()) {
            visited.push_back(state);
            path.push_back(state);
            open++;
            cout<<"Open: "<<open<<" "<<"Closed: "<<closed<<endl;
            State newState;
            if (state.boat == 1) {
                for (int i = 0; i <= 2; i++) {
                    for (int j = 0; j <= 2; j++) {
                        if (i + j <= 2 && i + j > 0) {
                            newState = { state.lc + i, state.lm + j, state.rc - i, state.rm - j, 0 };
                            newState.boat = 0;
                            dfs(newState, visited, path, open, closed);
                        }
                    }
                }
            }
            else {
                for (int i = 0; i <= 2; i++) {
                    for (int j = 0; j <= 2; j++) {
                        if (i + j <= 2 && i + j > 0) {
                            newState = { state.lc - i, state.lm - j, state.rc + i, state.rm + j, 1 };
                            newState.boat = 1;
                            dfs(newState, visited, path, open, closed);
                        }
                    }
                }
            }
            path.pop_back();
            closed++;
            cout<<"Open: "<<open<<" "<<"Closed: "<<closed<<endl;
        }
        else {
            return;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    struct State initial = { 3, 3, 0, 0, 0 };
    vector<State> visited;
    vector<State> path;
    int open = 0;
    int closed = 0;
    dfs(initial, visited, path, open, closed);
}
