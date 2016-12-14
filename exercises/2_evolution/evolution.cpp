#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;


void evolution() {
    int n, q; cin >> n >> q;

    // Store the names and respective ages
    map<string, int> species_idx;
    vector<string> species_name(n);
    vector<int> species_age(n), species_adj(n, -1);

    string name, name_next; int age, limit_age;
    for (int i = 0; i < n; i++) {
        cin >> name >> age;
        species_idx[name] = i;
        species_name[i] = name;
        species_age[i] = age;
    }

    // Store the adjacency map
    int idx, idx_next;
    for (int i = 0; i < n-1; i++) {
        cin >> name >> name_next;
        idx = species_idx[name]; idx_next = species_idx[name_next];
        species_adj[idx] = idx_next;
    }

    // Resolve each query
    int specie_result, upper_specie;
    for (int i = 0; i < q; i++) {
        cin >> name >> limit_age;
        int q_specie = species_idx[name];
        idx_next = idx;

        specie_result = q_specie;
        int count = 0;
        upper_specie = species_adj[specie_result];
        while (upper_specie != -1 && species_age[upper_specie] <= limit_age) {
            count++;
            specie_result = upper_specie;
            upper_specie = species_adj[specie_result];
        }

        string con_str = (i == n-1) ? "\n" : " ";
        cout << species_name[specie_result] << con_str;

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        evolution();
    }
}
