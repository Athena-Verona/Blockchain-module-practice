#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

int main() {
    std::string inputString = "";
    std::string binaryString = "";

    // Convert the original string to binary representation
    for (char c : inputString) {
        std::bitset<8> binaryChar(c);
        binaryString += binaryChar.to_string();
    }

    std::cout << "Original String: " << inputString << std::endl;
    //std::cout << "Binary Representation: " << binaryString << std::endl;

    //add 0 and 1 until it is 256 bit long
    bool addOne = true;
    while (binaryString.length() < 256) {
        if (addOne) {
            binaryString = "0" + binaryString;
            addOne = false;
        }
        else { binaryString = "1" + binaryString;
            addOne = true;
        }
    }

    //int blockSize = 2; // Number of bits in each block
    int blocksNumber = binaryString.length() / 2;

    //// Divide the binary string into blocks of size 'blockSize'
    //std::vector<std::string> blocks(blocksNumber);
    //for (int i = 0; i < blocksNumber; i++) {
    //    blocks[i] = binaryString.substr(i * 2, 2);
    //}

    std::vector<std::string> blocks(blocksNumber);
    for (int i = 0; i < blocksNumber; i++) {
    blocks[i] = binaryString.substr(i, 1) + binaryString.substr(binaryString.length() - i - 1, 1);
    }
    // Create a new binary string by interleaving bits from the front and the end
    std::string mixedBinaryString = "";
    while (!blocks.empty()) {
        mixedBinaryString += blocks.front();
        mixedBinaryString += blocks.back();
        blocks.erase(blocks.begin());
        blocks.pop_back();
    }
    // Output the mixed binary string
    std::cout << "Original Binary String: " << binaryString << std::endl;
    std::cout << "Mixed Binary String:    " << mixedBinaryString << std::endl;

    std::stringstream hexStream;
    for (size_t i = 0; i < mixedBinaryString.length(); i += 7){
        std::string binaryNibble = mixedBinaryString.substr(i, 7);
        int decimalValue = std::bitset<7>(binaryNibble).to_ulong();
        std::cout << decimalValue << " ";
        hexStream << std::hex << decimalValue;
    }

    std::string hexString = hexStream.str();
    if (hexString.length() > 64) {
        hexString = hexString.substr(0, 64);
    }
    std::cout << "Hexadecimal Representation: " << hexString << std::endl;
    return 0;
}