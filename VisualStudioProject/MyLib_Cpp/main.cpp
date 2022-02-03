#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct State {
    int A, O, L;
};

int main() {
    int N;
    while (cin >> N) {
        int A, O, L;

        queue<State> states;
        for (int i = 0; i < N; i++) {
            cin >> A >> O >> L;
            states.push({ A, O, L });
        }

        queue<State> queue;
        int currentTime = 0;
        for (;;) {
            while (!states.empty() && states.front().A == currentTime) {
                State& state = states.front();
                states.pop();
                if (queue.size() <= state.L) {
                    if (state.O != 0) {
                        queue.push(state);
                    }
                }
                else {
                    if (states.empty()) {
                        cout << -1 << endl;
                        goto leave;
                    }
                }
            }
            if (!queue.empty()) {
                queue.front().O--;
                if (queue.front().O <= 0) {
                    if (states.empty()) {
                        cout << currentTime << endl;
                        goto leave;
                    }
                    queue.pop();
                }
            }
            currentTime++;
        }

        leave:;

    }

    return 0;
}


