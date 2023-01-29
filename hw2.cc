#include <iostream>
using namespace std;

int sumSquaresUpTo(int n) {
  // write your loop in terms of n
  int sum = 0;
  for(int i = 1; i <= n; i++){
     sum += i*i;  
  }
  //cout << "the summation is " << sum << "\n";

  return sum;
}

int main() {
  // write a for loop that prints 100, 50, 25, 12, 6, 3, 1 (keep dividing by 2)
  for(int i = 100; i > 0; i/=2) {
    cout << i << ", ";
  }
  cout << "\n";
  // write a for loop that counts 10 9 8 7 6 5 4 3 2 1 0
  for(int i = 10; i >= 0; i--){
    cout<< i << " ";
  }
  cout << "\n";
  cout << sumSquaresUpTo(5) << '\n'; // 1*1 + 2*2 + 3*3 + 4*4 + 5*5 = ???
  cout << sumSquaresUpTo(7) << '\n';


}