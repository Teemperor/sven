#ifndef SVEN_USTRING_H
#define SVEN_USTRING_H


#include <string>

class UString {

  std::string Data;
public:
  UString() = default;
  UString(std::string Data) : Data(Data) {
  }
  UString(const char *Data) : Data(Data) {}

  const std::string &str() const {
    return Data;
  }

  bool empty() const {
    return Data.empty();
  }

  void removeAll(const std::string &Token);

  std::size_t size() const {
    return Data.size();
  }

  bool icmp(const UString &Other) const;

  bool contains(const UString &Other) const;
};


#endif //SVEN_USTRING_H
