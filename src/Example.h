#ifndef SVEN_EXAMPLE_H
#define SVEN_EXAMPLE_H


#include <string>
#include <utility>

class Example {

  std::string Text;
  std::string Translation;
public:
  Example(std::string Text, std::string Translation)
      : Text(std::move(Text)), Translation(std::move(Translation)) {
  }

  const std::string &getText() const {
    return Text;
  }

  const std::string &getTranslation() const {
    return Translation;
  }
};


#endif //SVEN_EXAMPLE_H
