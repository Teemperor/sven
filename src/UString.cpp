#include "UString.h"

static void replaceAll(std::string& Str, const std::string& From, const std::string& To) {
  if(From.empty())
    return;
  size_t start_pos = 0;
  while((start_pos = Str.find(From, start_pos)) != std::string::npos) {
    Str.replace(start_pos, From.length(), To);
    start_pos += To.length();
  }
}

static void makeLowercase(std::string &Str) {
  for (char &c : Str) {
    if (c >= 'A' && c <= 'Z') {
      c += ('a' - 'A');
    }
  }
  replaceAll(Str, "Ä", "ä");
  replaceAll(Str, "Å", "å");
  replaceAll(Str, "Ö", "ö");
}

static bool icmp(std::string A, std::string B) {
  makeLowercase(A);
  makeLowercase(B);
  return A == B;
}

bool UString::contains(const UString &Other) const {
  std::string LowerData = Data;
  makeLowercase(LowerData);

  std::string OtherData = Other.Data;
  makeLowercase(OtherData);

  return LowerData.find(OtherData) != std::string::npos;
}

bool UString::icmp(const UString &Other) const {
  return ::icmp(Data, Other.Data);
}

void UString::removeAll(const std::string &Token) {
  replaceAll(Data, Token, "");
}
