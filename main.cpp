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
    string T;
    std::random_device rd;
    mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10000);

    while (!Transactions.empty()) {
      block Block(previous_block); 
      std::shuffle(Transactions.begin(), Transactions.end(), mt);
      for (int i=0;i<100;i++){
        transaction trans = Transactions.back();
        Transactions.pop_back();
        Block.add_transaction(trans);
        Block.set_merkle();
      }
      T = Block.get_target();
      string H = Block.get_hash();
      //jei T bus mazesnis uz H, reiskia, daugiau 0 pradzioje, tesis tolyn. 
      while (std::lexicographical_compare(T.begin(), T.end(), H.begin(), H.end())){
        Block.add_nonce();
        Block.headerHash();
        H = Block.get_hash();
      }
      
      cout << Block << endl;
      Blockchain.push_back(Block);
      previous_block = Block.get_hash();
    }
}