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

    string name, name_next; int age, current_age, limit_age;
    for (int i = 0; i < n; i++) {
        cin >> name >> age;
        species_idx[name] = i;
        species_name[i] = name;
        species_age[i] = age;
    }

    // Store the adjacency map
    int idx, idx_next;
    for (int i = 0; i < n; i++) {
        cin >> name >> name_next;
        idx = species_idx[name]; idx_next = species_idx[name_next];
        species_adj[idx] = idx_next;
    }

    // Resolve each query
    for (int i = 0; i < q; i++) {
        cin >> name >> limit_age;
        idx = species_idx[name];
        idx_next = idx;

        do {
            idx = idx_next;
            idx_next = species_adj[idx];
            if (idx_next == -1) break;
            current_age = species_age[idx_next];
        } while (current_age < limit_age);

        string con_str = (i == n-1) ? "\n" : " ";
        cout << species_name[idx] << con_str;

    }

    // map<string, int> species_age;
    // map<string, string> species_relations;
    // string key, key_r; int age;
    // for (int i = 0; i < n; i++) {
    //     cin >> key >> age;
    //     species_age[key] = age;
    // }
    //
    // // Store the map with the relations
    // for (int i = 0; i < n - 1; i++) {
    //     cin >> key >> key_r;
    //     species_relations[key] = key_r;
    // }
    //
    // // For each query
    // string specie, next_specie;
    // int limit_age, current_age;
    // for (int i = 0; i < q; i++) {
    //     cin >> specie >> limit_age;
    //
    //     next_specie = specie;
    //     current_age = species_age[specie];
    //
    //     while (current_age <= limit_age) {
    //         specie = next_specie;
    //         auto search = species_relations.find(specie);
    //         if (search == species_relations.end()) break;
    //         next_specie = search->second;
    //         current_age = species_age[next_specie];
    //     }
    //
    //     string con_str = (i == n-1) ? "\n" : " ";
    //     cout << specie << con_str;
    // }

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        evolution();
    }
}
