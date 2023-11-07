#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <vector>
#include <limits>
#include <random>
#include <chrono>
#include <map>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <functional>

using std::time;
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

string hash(string&);

class user{
    private:
    int balance;
    string name, public_key;
    public:
    user() : balance{0}, public_key{"none"}, name{"undefined user"} {}
    user(string vardas, string key, int balance) : balance{balance}, public_key{key}, name{vardas} {}
    inline string get_public_key() const { return public_key; }
    inline int get_balance() const { return balance; }
    void update_balance(int money) { balance += money; }
    ~user() {}
};

class transaction{
    private: 
    int amount;
    user u1, u2;
    string sender_key, getter_key, ID;
    public:
    transaction() : ID(""), amount(0), sender_key("none"), getter_key("none") {}
    transaction(int amount, string pub1, string pub2, user sender, user getter) : u1(sender), u2(getter), amount(amount), sender_key(pub1), getter_key(pub2) {
        string input = std::to_string(amount) + pub1 + pub2;
        ID = hash(input);
    }
    inline string get_ID() const { return ID; }
    inline string get_sender() const { return sender_key; }
    inline string get_getter() const { return getter_key; }
    inline int get_amount() const { return amount; }
    void update_balances() {
        u2.update_balance(amount);
        u1.update_balance(-1*amount);
    }
    friend std::ostream& operator<<(std::ostream& out, const transaction& v);
    ~transaction() {}
};

class block {
    private: 
    vector<transaction> TX;
    string version;
    long int nonce;
    time_t timestamp;
    string prev_block;
    string merkle;
    string difficultyTarget;
    string header;
    public:
    block(string previous) {
        prev_block = previous;
        merkle = "";
        version = "0100000";
        nonce = 0;
        timestamp = time(nullptr);
        difficultyTarget = "00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
        headerHash();
    }
    block(string previous, string target) {
        prev_block = previous;
        merkle = "";
        version = "0100";
        timestamp = time(nullptr);
        difficultyTarget = target;
        headerHash();
    } 
    void headerHash(){
        string input = std::to_string(nonce) + version + prev_block + merkle + difficultyTarget + std::to_string(timestamp);
        header = hash(input);
    }
    void add_transaction(transaction T){
        TX.push_back(T);
        string transaction_id = T.get_ID();
        merkle = merkle + hash(transaction_id);
    }
    inline string get_time() const { return std::to_string(timestamp); }
    inline string get_version() const { return version; }
    inline string get_previous() const { return prev_block; }
    inline string get_merkle_hash() const { return merkle; }
    inline string get_hash() const { return header; }
    inline string get_target() const { return difficultyTarget; }
    inline long int get_nonce() const { return nonce; }
    void set_merkle() { merkle = hash(merkle); }
    void add_nonce() { nonce=nonce+1; }
    friend std::ostream& operator<<(std::ostream& out, const block& v);
    ~block() {}
};

string generateRandomHashKey(int);
void gen_user(vector<user>&);
void gen_trans(vector<user>&, vector<transaction>&);
