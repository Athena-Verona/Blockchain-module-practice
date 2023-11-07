#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    string A = "000cc0f10300c300304d1906645924664651190664592466465119066459246";
    string B = "00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
    //returns True if A is less than B
    if (std::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end())) cout << "A is less than B";
    if (std::lexicographical_compare(B.begin(), B.end(), A.begin(), A.end())) cout << "B is less than A";
    return 0;
}