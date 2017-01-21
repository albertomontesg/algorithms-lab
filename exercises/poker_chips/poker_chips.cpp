#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

double compute_award(double k) {
    if (k > 1) {
        return exp2(k-2);
    } else if (k == 1) {
        return 0;
    } else {
        throw runtime_error("k can not be less than 1.");
    }
}

int map_positions_into_vector(vector<int>& stack_heigh, vector<int>& stack_top) {
    int nb_stacks = stack_heigh.size();

    int accum = 1, pos = 0;
    for (int i = nb_stacks - 1; i >= 0; i--) {
        pos += accum * stack_heigh[i];
        accum *= stack_top[i] + 1;
    }
    return pos;
}

int play(vector<vector<int> >& stacks, vector<int>& nb_chips, vector<int>& turn_positions, vector<int>& memory) {

    // Check memory first
    int mem_pos = map_positions_into_vector(turn_positions, nb_chips);
    if (memory[mem_pos] != -1) return memory[mem_pos];

    // Check if there is not more chips at the stack (it is not necessary as memory[0] = 0)

    int nb_stacks = stacks.size();
    map<int, vector<int> > color_map;
    // Check at each of the stacks and see the next poker chips and group them by color
    for (int i = 0; i < nb_stacks; i++) {
        int next_position = turn_positions[i] - 1;
        if (next_position < 0) continue;    // In case a stack is empty
        color_map[stacks[i][next_position]].push_back(i);
    }

    // Iterate over all groups of colors, and compute the maximum award in DP achievable from this
    // stack positions
    int max_award = 0;
    for (auto it = color_map.begin(); it != color_map.end(); it++) {
        vector<int> chips_positions = it->second;
        int nb = chips_positions.size();

        /* Now compute all the possible combinations of extracting these chips (extract all the
        ones with the same colos is not allways the best strategy)
        Example:
        3 3 3 2 2 2 2
        2 2 2 X X 3 X

        If use the strategy to extract all the chips from the same color award = 10
        but if first is removed the 2 with a 3 at the bottom, then the award = 20
        */
        for (int k = 1; k < 1<<nb; k++) {
            int count = 0;

            // Selecting the chips from the same color, see which is the award with the next position
            vector<int> new_positions(turn_positions);

            for (int i = 0; i < nb; i++) {
                if (k & (1<<i)) {
                    count++;
                    new_positions[chips_positions[i]]--;
                }
            }

            int new_award = compute_award(count);

            int award = play(stacks, nb_chips, new_positions, memory);
            max_award = max(max_award, award + new_award);
        }
    }

    // Store result into memory
    memory[mem_pos] = max_award;

    return max_award;
}

void poker_chips() {
    int n; cin >> n;

    vector<int> nb_chips(n);
    vector<vector<int> > stacks(n);
    vector<int> initial_positions(n);

    for (int i = 0; i < n; i++) {
        cin >> nb_chips[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < nb_chips[i]; j++) {
            int c; cin >> c;
            stacks[i].push_back(c);
        }
        initial_positions[i] = nb_chips[i];
    }

    int N_memory = map_positions_into_vector(nb_chips, nb_chips) + 1;
    vector<int> memory(N_memory, -1);
    memory[0] = 0;

    int max_award = play(stacks, nb_chips, initial_positions, memory);
    cout << max_award << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        poker_chips();
    }
}
