#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <streambuf>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>
#include <bitset>

std::string convertToMorse(std::string buffer) {
 std::map<std::string, std::string> morseDictionary = {
  {"A", ".-"},
  {"B", "-..."},
  { "C", "-.-."},
  { "D", "-.."},
  { "E", "."},
  { "F", "..-."},
  {"G", "--."},
  { "H", "...."},
  { "I", ".."},
  { "J", ".---"},
  { "K", "-.-"},
  { "L", ".-.."},
  { "M", "--"},
  { "N", "-."},
  { "O", "---"},
  {"P", ".--."},
  {"Q", "--.-"},
  {"R", ".-."},
  {"S", "..."},
  {"T", "-"},
  {"U", "..-"},
  {"V", "...-"},
  {"W", ".--"},
  {"X", "-..-"},
  {"Y", "-.--"},
  {"Z", "--.."},
  {"1", ".----"},
  {"2", "..---"},
  {"3", "...--"},
  {"4", "....-"},
  {"5", "....."},
  {"6", "-...."},
  {"7", "--..."},
  {"8", "---.."},
  {"9", "----."},
  {"0", "-----"},
  {" ", "  "},
  {".", "   "}
 };
 int stringIndex = 0, stringSize = buffer.size();
 std::string retval;
 bool endOfFile = false, space = false;
 while(stringIndex < stringSize){
  std::string subString, appendStr;
  bool skip = false;
  if(buffer.compare(stringIndex, 1, ".") == 0) {
   appendStr = morseDictionary["."];
   skip = true;
  } else {
   subString = buffer.substr(stringIndex, 1);
   appendStr = morseDictionary[subString];
  } 
  if(buffer.compare(stringIndex, 1, ".") != 0 && buffer.compare(stringIndex, 1, " ") != 0 && stringIndex != stringSize - 1){
   appendStr.append(" ");
  }
  retval.append(appendStr);
  if(skip){
   stringIndex += 2;
  } else {
   ++stringIndex;
  }
 }
 return retval;
}

std::string convertToUTF8(std::string buffer) {
 std::map<std::string, std::string> morseDictionary = {
  {".-", "A"},
  {"-...", "B"},
  {"-.-.", "C"},
  {"-..", "D"},
  {".", "E"},
  {"..-.", "F"},
  {"--.", "G"},
  {"....", "H"},
  {"..", "I"},
  {".---", "J"},
  {"-.-", "K"},
  {".-..", "L"},
  {"--", "M"},
  {"-.", "N"},
  {"---", "O"},
  {".--.", "P"},
  {"--.-", "Q"},
  {".-.", "R"},
  {"...", "S"},
  {"-", "T"},
  {"..-", "U"},
  {"...-", "V"},
  {".--", "W"},
  {"-..-", "X"},
  {"-.--", "Y"},
  {"--..", "Z"},
  {".----", "1"},
  {"..---", "2"},
  {"...--", "3"},
  {"....-", "4"},
  {".....", "5"},
  {"-....", "6"},
  {"--...", "7"},
  {"---..", "8"},
  {"----.", "9"},
  {"-----", "0"}
 };
 int stringIndex = 0, stringSize = buffer.size();
 std::string retVal;
 while(stringIndex < stringSize - 1) {
  int lengthOfSubstring = 1, endOfSubstring = stringIndex + 1;
  std::string subStrWord;
  if(buffer.compare(stringIndex, 1, " ") != 0) { 
   while(buffer.compare(endOfSubstring, 1, " ") != 0 && endOfSubstring < stringSize - 1){
    ++lengthOfSubstring;
    ++endOfSubstring;
   }
   subStrWord = buffer.substr(stringIndex, lengthOfSubstring);
   std::string subStrToMorse = morseDictionary[subStrWord];
   retVal.append(subStrToMorse);
  } else if(buffer.compare(stringIndex, 1, " ") == 0) {
   while(buffer.compare(endOfSubstring, 1, " ") == 0 && endOfSubstring < stringSize - 1){
    ++lengthOfSubstring;
    ++endOfSubstring;
  }
  if(lengthOfSubstring == 1){
   subStrWord = "";
  } else if(lengthOfSubstring == 2){
   subStrWord = " ";
  } else {
   subStrWord = ". ";
  }
   retVal.append(subStrWord); 
  }
  stringIndex += lengthOfSubstring;
 }
 return retVal;
}

std::string convertFromBaudot(std::string buffer){
 std::map<std::string, std::vector<std::string>> baudotDictionary = {
  {"00000", {"", ""}},
  {"00001", {"E", "3"}},
  {"00010", {"\n", "\n"}},
  {"00011", {"A", "-"}},
  {"00100", {" ", " "}},
  {"00101", {"S", "'"}},
  {"00110", {"I", "8"}},
  {"00111", {"U", "7"}},
  {"01000", {"\r", "\r"}},
  {"01001", {"D", "WHO ARE YOU"}},
  {"01010", {"R", "4"}},
  {"01011", {"J", "BELL"}},
  {"01100", {"N", ","}},
  {"01101", {"F", "!"}},
  {"01110", {"C", ":"}},
  {"01111", {"K", "("}},
  {"10000", {"T", "5"}},
  {"10001", {"Z", "+"}},
  {"10010", {"L", ")"}},
  {"10011", {"W", "2"}},
  {"10100", {"H", "$"}},
  {"10101", {"Y", "6"}},
  {"10110", {"P", "0"}},
  {"10111", {"Q", "1"}},
  {"11000", {"O", "9"}},
  {"11001", {"B", "?"}},
  {"11010", {"G", "&"}},
  {"11100", {"M", "."}},
  {"11101", {"X", "/"}},
  {"11110", {"V", "="}},
 };
 int stringIndex = 0, stringSize = buffer.size();
 bool letters = true;
 std::string retVal;
 while(stringIndex < stringSize - 8){
  std::string subStr = buffer.substr(stringIndex, 8), appendStr;
  if(letters){
   std::string baudotSubstring = subStr.substr(3, 5);
   if(baudotSubstring.compare(0, 5, "11011") == 0){
    letters = false;
   } else {
    appendStr = baudotDictionary[baudotSubstring][0];
   }
  } else {
   std::string baudotSubstring = subStr.substr(3, 5);
   if(baudotSubstring.compare(0, 5, "11111") == 0){
    letters = true;
   } else {
    appendStr = baudotDictionary[baudotSubstring][1]; 
   } 
  }
  retVal.append(appendStr);
  stringIndex += 8;
 }
 return retVal;
}

std::string convertToBaudot(std::string buffer){
 std::map<std::string, std::string> baudotDictionary = {
  {"", "00000"},
  {"E", "00001"},
  {"\n", "00010"},
  {"A", "00011"},
  {" ", "00100"},
  {"S", "00101"},
  {"I", "00110"},
  {"U", "00111"},
  {"\r", "01000"},
  {"D", "01001"},
  {"R", "01010"},
  {"J", "01011"},
  {"N", "01100"},
  {"F", "01101"},
  {"C", "01110"},
  {"K", "01111"},
  {"T", "10000"},
  {"Z", "10001"},
  {"L", "10010"},
  {"W", "10011"},
  {"H", "10100"},
  {"Y", "10101"},
  {"P", "10110"},
  {"Q", "10111"},
  {"O", "11000"},
  {"B", "11001"},
  {"G", "11010"},
  {"M", "11100"},
  {"X", "11101"},
  {"V", "11110"},
 };
 std::map<std::string, std::string> baudotFigureLetterMap = {
  {"", ""},
  { "3", "E"},
  {"\n", "\n"},
  {"-", "A"},
  {" ", " "},
  {"'", "S"},
  {"8", "I"},
  {"7", "U"},
  {"\r", "\r"},
  {"WHO ARE YOU", "D"},
  {"4", "R"},
  {"BELL", "J"},
  {",", "N"},
  {"!", "F"},
  {":", "C"},
  {"(", "K"},
  {"5", "T"},
  {"+", "Z"},
  {")", "L"},
  {"2", "W"},
  {"$", "H"},
  {"6", "Y"},
  {"0", "P"},
  {"1", "Q"},
  {"9", "O"},
  {"?", "B"},
  {"&", "G"},
  {".", "M"},
  {"/", "X"},
  {"=", "V"},
 };
 int stringIndex = 0, stringSize = buffer.size();
 bool letters = true;
 std::string retVal;
 while(stringIndex < stringSize){
  std::string currentChar = buffer.substr(stringIndex, 1), appendStr;
  std::map<std::string, std::string>::iterator findCurrent = baudotFigureLetterMap.find(currentChar);
  if(findCurrent != baudotFigureLetterMap.end() && letters){
   appendStr = "00011011000";
   std::string currentCharConverted = findCurrent->second;
   std::string convertedStr = baudotDictionary[currentCharConverted];
   letters = false;
   appendStr.append(convertedStr);
  } else if(findCurrent != baudotFigureLetterMap.end()){
   std::string currentCharConverted = findCurrent->second;
   appendStr = "000";
   appendStr.append(baudotDictionary[currentCharConverted]);
  } else if(findCurrent == baudotFigureLetterMap.end() && !letters){
   appendStr = "00011111000";
   letters = true;
   appendStr.append(baudotDictionary[currentChar]);
  } else {
   appendStr = "000";
   appendStr.append(baudotDictionary[currentChar]);
  }
  retVal.append(appendStr);
  ++stringIndex;
 }
 return retVal;
}

std::string utf32ToUtf8(std::string buffer){
 int stringIndex = 0, stringSize = buffer.size();
 std::string retVal;
 while(stringIndex < stringSize - 32){
  std::string utf32Substring = buffer.substr(stringIndex, 32), appendStr;
  std::bitset<32> utf32Binary(utf32Substring);
  std::cout << "This is the utf32 binary string: "<< utf32Binary << "\n";
  int bitsetValue = utf32Binary.to_ulong();
  if(bitsetValue < 0x80) {
   std::bitset<8> singleByteUtfCharacter("00000000");
   for(int i = 0; i < 8; ++i){
    singleByteUtfCharacter[i] = utf32Binary[i];
   }
   char singleByteUtf8Character = singleByteUtfCharacter.to_ulong();
   std::cout << "This is the single byte: " << singleByteUtfCharacter << "\n";
   retVal += singleByteUtf8Character;
  } else if(bitsetValue >= 0x80 && bitsetValue < 0x800) {
   std::bitset<16> doubleByteUtfCharacter("0000000000000000");
   for(int i = 0; i < 16; ++i){
    doubleByteUtfCharacter[i] = utf32Binary[i];
   }
   unsigned int valueOfCharacter = doubleByteUtfCharacter.to_ulong();
   retVal.append(1, static_cast<char>(0xC0 | ((valueOfCharacter >> 6) & 0x1f)));
   retVal.append(1, static_cast<char>(0x80 | (valueOfCharacter & 0x3f)));
  } else if(bitsetValue >= 0x800 && bitsetValue < 0x10000) {
   std::bitset<16> doubleByteUtfCharacter("0000000000000000");
   for(int i = 0; i < 16; ++i){
    doubleByteUtfCharacter[i] = utf32Binary[i];
   }
   unsigned int valueOfCharacter = doubleByteUtfCharacter.to_ulong();
   retVal.append(1, static_cast<char>(0xe0 | ((valueOfCharacter >> 12) & 0x0f)));
   retVal.append(1, static_cast<char>(0x80 | ((valueOfCharacter >> 6) & 0x3f)));
   retVal.append(1, static_cast<char>(0x80 | (valueOfCharacter & 0x3f)));
  } else if(bitsetValue >= 0x10000 && bitsetValue < 0x200000){
   std::bitset<24> tripleByteUtfCharacter("000000000000000000000000");
   for(int i = 0; i < 24; ++i){
    tripleByteUtfCharacter [i] = utf32Binary[i];
   }
   char valueOfCharacter = tripleByteUtfCharacter.to_ulong();
   retVal.append(1, static_cast<char>(0xf0 | ((valueOfCharacter >> 18) & 0x07)));
   retVal.append(1, static_cast<char>(0xe0 | ((valueOfCharacter >> 12) & 0x3f)));
   retVal.append(1, static_cast<char>(0x80 | ((valueOfCharacter >> 6) & 0x3f)));
   retVal.append(1, static_cast<char>(0x80 | (valueOfCharacter & 0x3f)));
  }
  stringIndex += 32;
 }
 return retVal;
}

std::string utf8ToUtf32(std::string buffer){
 int stringIndex = 0, stringSize = buffer.size();
 std::string retVal;
 while(stringIndex < stringSize){
  std::bitset<8> utf8Character(buffer[stringIndex]);
  unsigned int valueOfChar = utf8Character.to_ulong();
  int nextChar = 1;
  if(valueOfChar < 0x80){
   std::bitset<32> utf32BitString("00000000000000000000000000000000");
   for(int i = 0; i < 7; ++i){
    utf32BitString[i] = utf8Character[i];
   }
   retVal.append(utf32BitString.to_string());
  } else if(valueOfChar >= 0x80 && valueOfChar < 0x800){
   std::bitset<8> nextByte(buffer[stringIndex + 1]);
   std::bitset<32> utf32BitString("00000000000000000000000000000000");
   for(int i = 0; i < 6; ++i){
    utf32BitString[i] = nextByte[i];
   }
   for(int i = 6; i < 11; ++i){
    utf32BitString[i] = utf8Character[i];
   }
   nextChar = 2;
   retVal.append(utf32BitString.to_string());
  } else if(valueOfChar >= 0x800 && valueOfChar < 0x10000){
   std::bitset<8> nextByte(buffer[stringIndex + 1]);
   std::bitset<8> lastByte(buffer[stringIndex + 2]);
   std::bitset<32> utf32BitString("00000000000000000000000000000000");
   for(int i = 0; i < 8; ++i){
    utf32BitString[i] = utf8Character[i];
   }
   for(int i = 8; i < 16; ++i){
    utf32BitString[i] = nextByte[i];
   }
   for(int i = 16; i < 24; ++i){
    utf32BitString[i] = lastByte[i];
   }
   nextChar = 3;
   retVal.append(utf32BitString.to_string());
  } else if(valueOfChar >= 0x10000){
   std::bitset<8> secondLastByte(buffer[stringIndex + 2]);
   std::bitset<8> nextByte(buffer[stringIndex + 1]);
   std::bitset<8> lastByte(buffer[stringIndex + 3]);
   std::bitset<32> utf32BitString("00000000000000000000000000000000");
   for(int i = 0; i < 8; ++i){
    utf32BitString[i] = utf8Character[i];
   }
   for(int i = 8; i < 16; ++i){
    utf32BitString[i] = nextByte[i];
   }
   for(int i = 16; i < 24; ++i){
    utf32BitString[i] = secondLastByte[i];
   }
   for(int i = 24; i < 32; ++i){
    utf32BitString[i] = lastByte[i];
   }
   nextChar = 4;
   retVal.append(utf32BitString.to_string());
  }
  stringIndex += nextChar;
 }
 return retVal;
}

int main(int argc, char *argv[]){
 std::ifstream file(argv[1]);
 std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
 std::string fileType = argv[2];
 std::string outputFileType = argv[3];
 std::transform(fileType.begin(), fileType.end(), fileType.begin(), [](unsigned char c){ return std::tolower(c);});
 std::transform(outputFileType.begin(), outputFileType.end(), outputFileType.begin(), [](unsigned char c){ return std::tolower(c);});
 if(fileType == "morse"){
  std::string inputStr  = convertToUTF8(buffer);
  if(outputFileType == "morse"){
   std::string outputStr = convertToMorse(inputStr);
   std::ofstream out("outputMorse.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "baudot") {
   std::string outputStr = convertToBaudot(inputStr);
   std::ofstream out("outputBaudot.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf32"){
   std::string outputStr = utf8ToUtf32(inputStr);
   std::ofstream out("outputUtf32.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf8"){
   std::string outputStr = inputStr;
   std::ofstream out("outputUtf8.txt");
   out << outputStr;
   out.close();
  }
 } else if (fileType == "baudot"){
  std::string inputStr = convertFromBaudot(buffer);
  if(outputFileType == "morse"){
   std::string outputStr = convertToMorse(inputStr);
   std::ofstream out("outputMorse.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "baudot") {
   std::string outputStr = convertToBaudot(inputStr);
   std::ofstream out("outputBaudot.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf32"){
   std::string outputStr = utf8ToUtf32(inputStr);
   std::ofstream out("outputUtf32.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf8"){
   std::string outputStr = inputStr;
   std::ofstream out("outputUtf8.txt");
   out << outputStr;
   out.close();
  }
 } else if (fileType == "utf32") {
  std::string inputStr = utf32ToUtf8(buffer);
  if(outputFileType == "morse"){
   std::string outputStr = convertToMorse(inputStr);
   std::ofstream out("outputMorse.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "baudot") {
   std::string outputStr = convertToBaudot(inputStr);
   std::ofstream out("outputBaudot.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf32"){
   std::string outputStr = utf8ToUtf32(inputStr);
   std::ofstream out("outputUtf32.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf8"){
   std::string outputStr = inputStr;
   std::ofstream out("outputUtf8.txt");
   out << outputStr;
   out.close();
  }
 } else {
  std::string inputStr = buffer;
  if(outputFileType == "morse"){
   std::string outputStr = convertToMorse(inputStr);
   std::ofstream out("outputMorse.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "baudot") {
   std::string outputStr = convertToBaudot(inputStr);
   std::ofstream out("outputBaudot.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf32"){
   std::string outputStr = utf8ToUtf32(inputStr);
   std::ofstream out("outputUtf32.txt");
   out << outputStr;
   out.close();
  } else if (outputFileType == "utf8"){
   std::string outputStr = inputStr;
   std::ofstream out("outputUtf8.txt");
   out << outputStr;
   out.close();
  }
 }
 return 0;
}


