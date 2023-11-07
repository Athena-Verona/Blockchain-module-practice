#include "main.h"

string generateRandomHashKey(int keyLength) {
  //"random" hash generation for sender and getter public keys
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string hashKey;
    for (int i = 0; i < keyLength; ++i) {
        hashKey.push_back(charset[rand() % charset.length()]);
    }
    return hashKey;
}

void gen_user(vector<user>& Users){
  int size = 1200;
  mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
  int_distribution dist(100, 121);
  std::uniform_int_distribution<int> balanceDist(100, 1000000); // Range for user balance
  map<int, string> vardai;
  
  vardai[100]="Gabrisele";
  vardai[101]="Agatsa";
  vardai[102]="Laurisa";
  vardai[103]="Vistorija";
  vardai[104]="Sinsija";
  vardai[105]="Mastas";
  vardai[106]="Dovysdas";
  vardai[107]="Luskas";
  vardai[108]="Aslanas";
  vardai[109]="Ritsa";
  vardai[110]="Pitsa";
  vardai[111]="Roksas";
  vardai[112]="Kroksas";
  vardai[113]="Antanas";
  vardai[114]="Slimonas";
  vardai[115]="Bensas";
  vardai[116]="Sjustas";
  vardai[117]="Kristuspas";
  vardai[118]="Justinsas";
  vardai[119]="Minija";
  vardai[120]="Raspolas";
  vardai[121]="Misgle";

  cout<<"> Vardų ir pavardžių generavimas vyksta..."<<endl;
  string vardas;
  for (int i=0;i<size;i++) {
    vardas=vardai[dist(mt)];
    string hashKey = generateRandomHashKey(64);
    int balance = balanceDist(mt);

    Users.push_back(user(vardas, hashKey, balance));
  }
}

void gen_trans(vector<user>& U, vector<transaction>& T){
  mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
  std::uniform_int_distribution<int> usersDist(0, 1200);

  for (int i=0;i<10000;i++){
    int sender = usersDist(mt);
    int getter = usersDist(mt);
    while (sender == getter) {
      getter = usersDist(mt);
    }

    int balance = usersDist(mt);
    string public1 = U[sender].get_public_key();
    string public2 = U[getter].get_public_key();

    T.push_back(transaction(balance, public1, public2));
  }
}
std::ostream& operator<<(std::ostream& out, const transaction& v){
    out << "Transaction ID: "<< v.ID <<endl<<
    "Sender public key: " << v.sender_key <<endl<<
    "Getter public key: " << v.getter_key <<endl<<
    "Amount spent: " << v.amount << endl;
    return out;
}
std::ostream& operator<<(std::ostream& out, const block& v){
    out << "Prev Block: " << v.prev_block << endl<<
    "Version: " << v.version << endl <<
    "Timestamp: " << std::to_string(v.timestamp) << endl <<
    "Nonce: " << v.nonce << endl <<
    "Merkle hash: " << v.merkle << endl <<
    "Target: " << v.difficultyTarget << endl <<
    "Hash: " << v.header<< endl;
    return out;
}

string hash(string &input) {
    const int hash_size=8;
    uint64_t length = input.length() * hash_size;
    input += char((length >> 56) & 0xFF);
    input += char((length >> 48) & 0xFF);
    input += char((length >> 40) & 0xFF);
    input += char((length >> 32) & 0xFF);
    input += char((length >> 24) & 0xFF);
    input += char((length >> 16) & 0xFF);
    input += char((length >> 8) & 0xFF);
    input += char(length & 0xFF);
 
    int  code_local=46886,var=7;
    int secret_rand;
    uint32_t hash[hash_size]={0};
    for(char c:input)
    {
        for(int i=0;i<hash_size;i++)
        {
            secret_rand=(code_local/var)-(var%10);

            hash[i]=(hash[i]^c)+secret_rand*(i+1);
            hash[i] ^= (hash[i] << 15) | (hash[i] >> 21);
            hash[i] = (hash[i] + 0x85ebca6b) ^ 0xc2b2ae35;
            var++;
        }
    }
    std::stringstream ss;
    for(int i =0;i<hash_size;i++)
    {
        ss<<std::hex<<std::setw(8)<<std::setfill('0')<<hash[i];
    }
    return ss.str();
}
