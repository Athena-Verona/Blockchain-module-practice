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
void processBlock(const string &block, int unicodeValue, int bitCount, string &output)
{
    vector<string> subblocks;
    output.clear();

    size_t blockSize = (block.size() == 256) ? 64 : 256;
    for (size_t i = 0; i < block.size(); i += blockSize)
    {
        string subblock = block.substr(i, blockSize);
        subblocks.push_back(subblock);
    }

    for (const string &subblock : subblocks)
    {
        string shiftedSubblock;
        int value = (unicodeValue / 13 + bitCount) % 5;
        for (size_t i = 0; i < subblock.size(); i += 18)
        {
            string subblockPart = subblock.substr(i, 18);
            int shiftAmount = i % 8 + value;
            string shiftedPart = subblockPart.substr(shiftAmount) + subblockPart.substr(0, shiftAmount);
            shiftedSubblock += shiftedPart;
        }

        vector<string> nibbles;
        // 64bit sukarpymas į 16x4bit
        for (size_t i = 0; i < shiftedSubblock.size(); i += 4)
        {
            string nibble = shiftedSubblock.substr(i, 4);
            nibbles.push_back(nibble);
        }
        for (const string &nibble : nibbles)
        {
            std::bitset<8> bits(nibble);
            std::stringstream stream;
            stream << std::hex << bits.to_ulong();
            string hexNibble = stream.str();
            output += hexNibble;
        }
    }
}
string hash(string input){
        int unicodeValue = 0;
        int bitCount1 = input.size() * 8;
        int bitCount = input.size();

        for (int i = 0; i < input.size(); i++){
            if(i == input.size() / 2)
                unicodeValue += static_cast<int>(input[i]) * 17;

            unicodeValue += static_cast<int>(input[i]);
        }
        int targetBitCount = (bitCount1 < 256) ? 256 : ((bitCount1 / 256) + 1) * 256;
        string binaryInput;
        for (char c : input)
        {
            std::bitset<8> binaryChar(c);
            binaryInput += binaryChar.to_string();
        }
        int number = bitCount;
        while (binaryInput.size() < targetBitCount)
        {
            std::bitset<8> binary(number);
            binaryInput += binary.to_string();
            number += bitCount + static_cast<int>(input[0]);
        }
        vector<string> blocks;
        for (size_t i = 0; i < input.size(); i += 256)
        {
            string block = binaryInput.substr(i, 256);
            blocks.push_back(block);
        }

        string output;
        for (const string &block : blocks)
        {
            int blockBitCount = block.size();

            processBlock(block, unicodeValue, bitCount, output);
        }
        blocks.clear();
        return output;
    }