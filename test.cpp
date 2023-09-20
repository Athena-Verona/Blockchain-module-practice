#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <iostream>

int main() {
    std::string inputString = "Labuka, maziuk!";
    std::string binaryString = "";

    // Convert the original string to binary representation
    for (char c : inputString) {
        std::bitset<8> binaryChar(c);
        binaryString += binaryChar.to_string();
    }

    std::cout << "Original String: " << inputString << std::endl;
    std::cout << "Binary Representation: " << binaryString << std::endl;

    //// Reverse the binary string back to the original string
    //std::string reversedString = "";
    //for (size_t i = 0; i < binaryString.length(); i += 8) {
    //    std::string binaryChar = binaryString.substr(i, 8);
    //    char originalChar = static_cast<char>(std::bitset<8>(binaryChar).to_ulong());
    //    reversedString += originalChar;
    //}
    //std::cout << "Reversed String: " << reversedString << std::endl;
    std::stringstream hexStream;
    for (size_t i = 0; i < binaryString.length(); i += 4){
        std::string binaryNibble = binaryString.substr(i, 4);
        int decimalValue = std::bitset<4>(binaryNibble).to_ulong();
        std::cout << decimalValue << " ";
        hexStream << std::hex << decimalValue;
    }

    std::string hexString = hexStream.str();
    std::cout << "Hexadecimal Representation: " << hexString << std::endl;
    return 0;
}
