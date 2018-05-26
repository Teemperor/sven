#include <iostream>
#include <tinyxml.h>
#include <deque>
#include "Dictionary.h"
#include "Example.h"

static const char *Red = "\x1b[31m";
static const char *Green = "\x1b[32m";
//static const char *Yellow = "\x1b[33m";
static const char *Blue = "\x1b[34m";
static const char *Magenta = "\x1b[35m";
//static const char *Cyan = "\x1b[36m";

static std::string color(const char *Color, const std::string &Token) {
  static const char *Reset = "\x1b[0m";
  return Color + Token + Reset;
}

static std::string getValue(TiXmlElement *Elem) {
  if (!Elem)
    return "";

  std::string Result;
  int RC = Elem->QueryStringAttribute("value", &Result);
  assert(RC == 0);
  return Result;
}

static void printResults(Dictionary &Dict, const std::deque<Word> &Results,
   std::size_t Limit) {
  std::size_t Counter = 0;
  for(const Word& W : Results) {
    std::cout << color(Blue, W.getValue()) << "\n";
    for (const std::string &Translation : W.getTranslations())
      std::cout << color(Green, u8" • ") << Translation << "\n";
    for (auto ID : W.getExampleIDs()) {
      auto E = Dict.getExample(ID);
      std::cout << color(Red, u8" ☛ ") << E.getText();
      std::cout << color(Magenta, "  " + E.getTranslation() + "") << "\n";
    }
    std::cout << color(Green, u8"──────────────────────────\n");
    ++Counter;
    if (Counter >= Limit)
      return;
  }
}

void clearScreen() {
  std::cout << "\e[1;1H\e[2J";
}

int cmdLoop(Dictionary &Dict) {
  std::string Line;

  unsigned WordsAtOnce = 3;
  std::deque<Word> LastResults;
  while(true) {
    std::cout << color(Red, "✒ ");
    std::cout.flush();
    if (!std::getline(std::cin, Line))
      break;
    if (Line.empty()) {
      for (unsigned I = 0; I < WordsAtOnce; ++I) {
        LastResults.pop_front();
      }
    } else {
      clearScreen();
      LastResults = Dict.search(Line);
    }

    printResults(Dict, LastResults, WordsAtOnce);
  }
  return 0;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::cerr << "Need to pass a dictionary file!\n";
    return 1;
  }
  TiXmlDocument doc(argv[1]);

  Dictionary Dict;

  std::size_t ExampleID = 0;

  if (doc.LoadFile()) {
    TiXmlHandle hDoc(&doc);
    TiXmlElement *dictElem = doc.FirstChildElement("dictionary");
    if (dictElem) {
      TiXmlElement *wordElem = dictElem->FirstChildElement("word");
      while (wordElem) {

        Word W(getValue(wordElem));

        TiXmlElement *translationElem = wordElem->FirstChildElement("translation");
        while(translationElem) {
          W.addTranslation(getValue(translationElem));
          translationElem = translationElem->NextSiblingElement("translation");
        }

        TiXmlElement *exampleElem = wordElem->FirstChildElement("example");
        while(exampleElem) {
          translationElem = exampleElem->FirstChildElement("translation");
          Example E(getValue(exampleElem), getValue(translationElem));
          Dict.addExample(ExampleID, E);
          W.addExampleID(ExampleID);

          ExampleID++;
          exampleElem = exampleElem->NextSiblingElement("example");
        }

        Dict.addWord(W);
        wordElem = wordElem->NextSiblingElement("word");
      }
    }
  }

  cmdLoop(Dict);
}