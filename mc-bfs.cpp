#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

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

bool bfs(State& initial, int& open, int& closed) {
    queue<pair<State, vector<State>>> bfsQueue;
    vector<State> visited;

    vector<State> initialPath = {initial};
    bfsQueue.push({initial, initialPath});
    visited.push_back(initial);

    while (!bfsQueue.empty()) {
        pair<State, vector<State>> currentState = bfsQueue.front();
        State curr = currentState.first;
        vector<State> path = currentState.second;
        bfsQueue.pop();
        open--;
        closed++;
        if (isGoal(curr)) {
            cout << "Solution Found" << endl;
            cout << "Path to the goal state:" << endl;
            for (const State& step : path) {
                cout << "Left Bank: " << step.lm << "M " << step.lc << "C " << (step.boat == 0 ? "Boat" : "\t") << "\t\t\t\t";
                cout << "Right Bank: " << step.rm << "M " << step.rc << "C " << (step.boat == 1 ? "Boat" : "") << endl;
            }
            return true;
        }

        vector<State> children;

        if (curr.boat == 0) {
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (i + j <= 2 && i + j > 0) {
                        State newState = {curr.lc - i, curr.lm - j, curr.rc + i, curr.rm + j, 1};
                        if (find(visited.begin(), visited.end(), newState) == visited.end() && isValid(newState)) {
                            children.push_back(newState);
                            visited.push_back(newState);
                            open++;
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (i + j <= 2 && i + j > 0) {
                        State newState = {curr.lc + i, curr.lm + j, curr.rc - i, curr.rm - j, 0};
                        if (find(visited.begin(), visited.end(), newState) == visited.end() && isValid(newState)) {
                            children.push_back(newState);
                            visited.push_back(newState);
                            open++;
                        }
                    }
                }
            }
        }

        for (State& child : children) {
            vector<State> newPath = path;
            newPath.push_back(child);
            bfsQueue.push({child, newPath});
        }
    }

    cout << "No solution found" << endl;
    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    struct State initial = { 3, 3, 0, 0, 0 };
    vector<State> visited;
    vector<State> path;
    int open = 1;
    int closed = 0;
    bfs(initial, open, closed);
    cout<<"Open: "<<open<<" "<<"Closed: "<<closed<<endl;
}
