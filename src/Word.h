#ifndef SVEN_WORD_H
#define SVEN_WORD_H


#include <string>
#include <vector>
#include <cassert>

class Word {

  static std::size_t IDCounter;
  std::size_t ID = IDCounter++;
  std::string Value;
  std::vector<std::string> Translations;
  std::vector<std::size_t> ExampleIDs;
public:
  explicit Word(std::string Value) : Value(std::move(Value)) {
    assert(!this->Value.empty());
  }

  void addTranslation(const std::string &T) {
    Translations.push_back(T);
  }

  void addExampleID(std::size_t ID) {
    ExampleIDs.push_back(ID);
  }

  std::size_t getID() const {
    return ID;
  }

  const std::string &getValue() const {
    return Value;
  }

  const std::vector<std::string> &getTranslations() const {
    return Translations;
  }

  const std::vector<size_t> &getExampleIDs() const {
    return ExampleIDs;
  }

  bool containsString(const std::string &S) const {
    if (Value.find(S) != std::string::npos)
      return true;
    for (const auto &T : Translations) {
      if (T.find(S) != std::string::npos)
        return true;
    }
    return false;
  }
};


#endif //SVEN_WORD_H
