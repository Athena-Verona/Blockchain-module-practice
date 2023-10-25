#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <vector>
#include <limits>
#include <random>
#include <stdexcept>
#include <chrono>
#include <map>
#include <sstream>
#include <fstream>
#include <filesystem>

using std::stof;
using std::stoi;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::copy;
using std::sort;
using std::fixed;
using std::vector;
using std::swap;
using std::runtime_error;
using std::map;
using std::mt19937;


using hrClock = std::chrono::high_resolution_clock; 
typedef std::uniform_int_distribution<int>  int_distribution;

class user{
    private:
    int balance;
    string name, public_key;
    public:
    user() : balance{0}, public_key{"none"}, name{"undefined user"} {}
    inline string get_public() const { return public_key; }
    inline int get_balance() const { return balance; }
    ~user() {}
};
class transaction{
    private: 
    int ID, amount;
    string sender_key, getter_key;
    public:
    transaction() : ID(0), amount(0), sender_key("none"), getter_key("none")
    inline string get_ID() const { return ID; }
    inline string get_sender() const { return sender; }
    inline string get_getter() const { return getter; }
    inline int get_amount() const { return amount; }
    friend std::ostream& operator<<(std::ostream& out, const transaction& v);
    ~transaction() {}
};
void gen_map();