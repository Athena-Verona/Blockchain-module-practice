#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

int main() {
    std::string inputString = "K";
    std::string binaryString = "";

    // Convert the original string to binary representation
    for (char c : inputString) {
        std::bitset<8> binaryChar(c);
        binaryString += binaryChar.to_string();
    }

    int asciiSum = 0;
    std::cout << "Original String: " << inputString << std::endl;
    for (char c : inputString) {
        asciiSum += static_cast<int>(c); // Add the ASCII value of the character
    }

    std::cout << "The sum of ASCII values is: " << asciiSum << std::endl;

    //add 0 and 1 until it is 256 bit long
    //bool addOne = true;
    //while (binaryString.length() < 256) {
    //    //if (addOne) {
    //        binaryString = "0" + binaryString;
    //    //    addOne = false;
    //    //}
    //    //else { binaryString = "1" + binaryString;
    //    //    addOne = true;
    //    //}
    //}
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
    //int blockSize = 2; // Number of bits in each block
    int blocksNumber = binaryString.length() / 2;
    while (asciiSum > 1000){
        asciiSum /= 10;
    }
    for (int i= 0;i < (asciiSum/3)+1 ; i++){
        std::vector<std::string> blocks(blocksNumber);
        for (int i = 0; i < blocksNumber; i++) {
            blocks[i] = binaryString.substr(i, 1) + binaryString.substr(binaryString.length() - i - 1, 1);
        }
        // Create a new binary string by interleaving bits from the front and the end
        binaryString = "";
        while (!blocks.empty()) {
            binaryString += blocks.front();
            binaryString += blocks.back();
            blocks.erase(blocks.begin());
            blocks.pop_back();
        }
    }
    // Output the mixed binary string
    std::cout << "Mixxed Binary String: " << binaryString << std::endl;

    std::stringstream hexStream;
    for (size_t i = 0; i < binaryString.length(); i += 7){
        std::string binaryNibble = binaryString.substr(i, 7);
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