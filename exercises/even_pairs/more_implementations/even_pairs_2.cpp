#include <vector>
#include <iostream>

using namespace std;

void do_test(){
    int n; cin >> n;
    vector<int> bits(n);
    for (int i =0; i < n; i++)
        cin >> bits [i];

    // Calculate the result
    int counter = 0;
    for (int i =0; i < n; i++){
        int sum = 0;
        for (int j = i; j < n; j++){
            sum += bits[j]
            
            if (sum%2 == 0)
                counter++;
        }
        cout << counter << endl;
    }
}

int main() {
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_test();
    }
}
