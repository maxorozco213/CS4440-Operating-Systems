#include<iostream>
using namespace std;

int main() {
  int n;

  cout << "Enter # of days: ";
  cin >> n;

  for(int i = 1; i <= n; i++) {
    cout << "\nFather is going to sleep and waking up mother to take care of the children";

    for(int j1 = 1; j1 <= 12; j1++) {
      cout << "\nChild # " << j1 << " is being fed breakfast";
    }

    for(int j2 = 1; j2 <= 12; j2++) {
      cout << "\nChild # " << j2 << " is being sent to school.";
    }


  }
}
