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
    // Copy constructor
    transaction(const transaction& other)
        : amount(other.amount), u1(other.u1), u2(other.u2),
          sender_key(other.sender_key), getter_key(other.getter_key), ID(other.ID) {}

    // Move constructor
    transaction(transaction&& other) noexcept
        : amount(other.amount), u1(std::move(other.u1)), u2(std::move(other.u2)),
          sender_key(std::move(other.sender_key)), getter_key(std::move(other.getter_key)), ID(std::move(other.ID)) {
        // Set the source object to a valid but unspecified state
        other.amount = 0;
        other.sender_key = "none";
        other.getter_key = "none";
        other.ID = "";
    }
    // Copy assignment operator
    transaction& operator=(const transaction& other) {
        if (this != &other) {
            amount = other.amount;
            u1 = other.u1;
            u2 = other.u2;
            sender_key = other.sender_key;
            getter_key = other.getter_key;
            ID = other.ID;
        }
        return *this;
    }
    // Move assignment operator
    transaction& operator=(transaction&& other) noexcept {
        if (this != &other) {
            amount = other.amount;
            u1 = std::move(other.u1);
            u2 = std::move(other.u2);
            sender_key = std::move(other.sender_key);
            getter_key = std::move(other.getter_key);
            ID = std::move(other.ID);

            // Set the source object to a valid but unspecified state
            other.amount = 0;
            other.sender_key = "none";
            other.getter_key = "none";
            other.ID = "";
        }
        return *this;
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

struct HashPointer{
    HashPointer* point;
    transaction* point_t;
    string hash;
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
        difficultyTarget = "0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
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
    void set_merkle() {
        vector<std::pair<HashPointer, HashPointer>> hashPointerPairs;

        int size = TX.size();

        for (int i=0;i<size-1;i++) {
            HashPointer hp1;
            HashPointer hp2;

            hp1.point_t = &TX[i];
            hp2.point_t = &TX[i + 1];

            hp1.hash = TX[i].get_ID();
            hp2.hash = TX[i + 1].get_ID();

            // Create a pair of HashPointers and associate them with the transactions
            hashPointerPairs.emplace_back(hp1, hp2);
        }
        int j = size/2;

        //For each pair of hashpointers, create 
        while (j>1) {
            vector<std::pair<HashPointer, HashPointer>> hashPP2;
            for (int i=0;i<j;i++){
                HashPointer hp1;
                HashPointer hp2;

                hp1.point = &hashPointerPairs[i].first;
                hp2.point = &hashPointerPairs[i+1].first;
                
                hp1.hash = hash(hashPointerPairs[i].first.hash);
                hp2.hash = hash(hashPointerPairs[i+1].first.hash);

                hashPP2.emplace_back(hp1, hp2);
            }
            hashPointerPairs = hashPP2;
            j/=2;
        }
        HashPointer root = hashPointerPairs[0].first;
        root.hash = hash(root.hash);
        merkle = root.hash;
    }
    void add_nonce() { nonce=nonce+1; }
    
    friend std::ostream& operator<<(std::ostream& out, const block& v);
    ~block() {}
};

string generateRandomHashKey(int);
void gen_user(vector<user>&);
void gen_trans(vector<user>&, vector<transaction>&);
