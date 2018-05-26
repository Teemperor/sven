#ifndef SVEN_DICTIONARY_H
#define SVEN_DICTIONARY_H


#include <iostream>
#include <cassert>
#include <algorithm>
#include <deque>
#include "Word.h"
#include "Example.h"

class Dictionary {

  std::vector<Word> Words;
  std::vector<Example> Examples;
public:

  void addWord(const Word &W) {
    Words.push_back(W);
  }

  void addExample(std::size_t ID, const Example &E) {
    assert(ID == Examples.size());
    Examples.push_back(E);
  }

  Example getExample(std::size_t ID) {
    return Examples.at(ID);
  }

  std::deque<Word> search(const std::string &S);
};


#endif //SVEN_DICTIONARY_H
