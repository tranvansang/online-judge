#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#define COST_MAX 1000000
#define NTEST 100
#define N 10000
#define NQUERY 1000

int main(){
  srand((unsigned int)time(NULL));
  int ntest = NTEST;
  cout << ntest << endl;
  while(ntest--){
    int n = N;
    //graph
    cout << n << endl;
    for(int i = 2; i <= n; i++){
      int cost = rand() % COST_MAX;
      cout << i << " " << rand() % (i - 1) + 1 << " " << cost << endl;
    }

    //query
    int nquery = NQUERY;
    while(nquery--){
      if (rand() & 1){
        int cost = rand()% COST_MAX;
        cout << "CHANGE "<< rand()%(n - 1) + 1 << " " << cost << endl;
      }else{
        cout << "QUERY " << rand() % n + 1 << " " << rand() % n  + 1<< endl;
      }
    }
    cout << "DONE" << endl;
  }
}