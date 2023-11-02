#include "main.h"

int main() {
    vector<user> Users;
    gen_user(Users);
    vector<transaction> Transactions;
    gen_trans(Users, Transactions);
    
    //before! create a genesis block
    vector<block> Blockchain;
    block Genesis("");
    Blockchain.push_back(Genesis);
    string previous_block = Genesis.get_hash();
    cout << Genesis;

    std::random_device rd;
    mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1200);
    while (true) {
      block Block(previous_block); 
      for (int i=0;i++;i<100){
        int randomNumber = dist(mt);
        Block.add_transaction(Transactions[randomNumber]);
      }
      if ()
      Blockchain.push_back(Block);
      previous_block = Block.get_hash();
    }
}