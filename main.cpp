#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>

using std::cout;
using std::string;
using std::endl;
using std::cin;


int main() {
    string read_pavadinimas;
    char c;
    cout << "> Ivestis ranka ar is failo? Ranka: 1, failo: 2" << endl;
    cin >> c;
    string inputString;
    if (c=='2') {
        cout << "> Kurį failą norėtumėte atidaryti?" << endl;
        cin >> read_pavadinimas;
        FILE *open_f;
        open_f=fopen(read_pavadinimas.c_str(),"r");
        do{ 
            try{
                if (open_f==NULL) { 
                    throw std::runtime_error("> Tokio failo nėra! Įveskite iš naujo.\n");
                }
            }
            catch (const std::runtime_error& e) {
                cout << e.what();
                cin >> read_pavadinimas;
                open_f=fopen(read_pavadinimas.c_str(),"r");
            }
        } while (open_f==NULL);
        std::ifstream inputFile(read_pavadinimas);
        cout << "> Failo skaitymas vyksta..." << endl;
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        inputString = buffer.str();
        inputFile.close();
    }
    else {
        cout << "Iveskite reiksme, kuria noretumete hash'inti" << endl;
        cin >> inputString;
    }
    cout << "> Vykdomas hash algoritmas..." << endl;
    std::string binaryString = "";
    // Convert the original string to binary representation
    for (char c : inputString) {
        std::bitset<8> binaryChar(c);
        binaryString += binaryChar.to_string();
    }

    int asciiSum = 0;
    for (char c : inputString) {
        asciiSum += static_cast<int>(c); // Add the ASCII value of the character
    }
    //add 0 and 1 until it is 256 bit long
    if (binaryString.length() < 256) {
        int n = 256 - binaryString.length();
        int k = 0.7 * n;
        int y = 256 - k;
        for (int i = 0; i < k; i++){
            binaryString = "1" + binaryString;
        }
        for (int i = 0; i < y; i++){
            binaryString = "0" + binaryString;
        }
    }
    // Number of blocks total (begins from 128)
    int blocksNumber = binaryString.length() / 2;
    while (asciiSum > 1000){
        asciiSum /= 10;
    }
    for (int i= 0;i < (asciiSum/3)+1 ; i++){
        std::vector<std::string> blocks(blocksNumber);
        for (int i = 0; i < blocksNumber; i++) {
            blocks[i] = binaryString.substr(i, 1) + binaryString.substr(binaryString.length() - i - 1, 1);
        }
        binaryString = "";
        while (!blocks.empty()) {
            binaryString += blocks.front();
            binaryString += blocks.back();
            blocks.erase(blocks.begin());
            blocks.pop_back();
        }
    }
    std::stringstream hexStream;
    for (size_t i = 0; i < binaryString.length(); i += 7){
        std::string binaryNibble = binaryString.substr(i, 7);
        int decimalValue = std::bitset<7>(binaryNibble).to_ulong();
        hexStream << std::hex << decimalValue;
    }
    string hexString = hexStream.str();
    if (hexString.length() > 64) {
        hexString = hexString.substr(0, 64);
    }
    std::cout << "Maisos funkcijos rezultatas: " << hexString << std::endl;
    return 0;
}