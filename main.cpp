#include "main.h"

int main() {
    vector<user> Users;
    gen_user(Users);
    vector<transaction> Transactions;
    gen_trans(Users, Transactions);
    
    vector<block> Blockchain;
    //before! create a genesis block
    block Genesis("");
    Blockchain.push_back(Genesis);
    
    string previous_block = Genesis.get_hash();
    string T;

    std::random_device rd;
    mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10000);

    while (!Transactions.empty()) {
      block Block(previous_block);
      transaction trans;

      //shuffle transaction pool
      std::shuffle(Transactions.begin(), Transactions.end(), mt);
      //CREATE A COPY OF TRANSACTIONS
      std::vector<transaction> CopyTrans = Transactions;

      //try candidates
      while (true){
        transaction trans;
        bool blockGood = true;
        std::shuffle(CopyTrans.begin(), CopyTrans.end(), mt);

        for (int i=0;i<128;i++){
          //HERE I WOULD WORK WITH THE COPY OF POOL
          trans = CopyTrans.back();
          CopyTrans.pop_back();
          Block.add_transaction(trans);
          trans.update_balances();
        }

        Block.set_merkle();
        T = Block.get_target();
        string H = Block.get_hash();

        //pradedamas laiko skaiciavimas
        const int timeLimitSeconds = 5;
        auto startTime = std::chrono::high_resolution_clock::now();

        //tikrinamas ar hash<T
        while (std::lexicographical_compare(T.begin(), T.end(), H.begin(), H.end())){
          //pridedamas nonce, skaiciuojamas is naujo hashas
          Block.add_nonce();
          Block.headerHash();
          H = Block.get_hash();

          //skaiciuojamas laikas
          auto currentTime = std::chrono::high_resolution_clock::now();
          auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

          if (elapsedTime >= timeLimitSeconds) {
            std::cout << "Bloko skaiciavimai truko > 5 sekundes. Bandomas kitas kandidatas" << std::endl;
            blockGood = false;
            break;
          }
        }
        if (blockGood) break;
      }
      //UPDATE THE ORIGINAL TRANSACTIONS
      Transactions = std::move(CopyTrans);
      //add block to chain
      Blockchain.push_back(Block);
      cout << Block << endl;
      previous_block = Block.get_hash();
    }
}