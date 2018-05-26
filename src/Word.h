#ifndef SVEN_WORD_H
#define SVEN_WORD_H


#include <string>
#include <vector>
#include <cassert>
#include "UString.h"

class Word {

  static std::size_t IDCounter;
  std::size_t ID = IDCounter++;
  UString Value;
  UString Comment;
  std::vector<UString> Translations;
  std::vector<std::size_t> ExampleIDs;
public:
  explicit Word(std::string V) : Value(std::move(V)) {
    Value.removeAll("|");
  }

  void addTranslation(const std::string &T) {
    Translations.emplace_back(T);
  }

  void setComment(const std::string &C) {
    Comment = C;
  }

  void addExampleID(std::size_t ID) {
    ExampleIDs.push_back(ID);
  }

  std::size_t getID() const {
    return ID;
  }

  const UString &getValue() const {
    return Value;
  }

  const UString &getComment() const {
    return Comment;
  }

  const std::vector<UString> &getTranslations() const {
    return Translations;
  }

  const std::vector<size_t> &getExampleIDs() const {
    return ExampleIDs;
  }

  bool containsString(const std::string &S) const {
    if (Value.contains(S))
      return true;
    for (const auto &T : Translations) {
      if (T.contains(S))
        return true;
    }
    return false;
  }
};


#endif //SVEN_WORD_H
