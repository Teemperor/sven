#include "Dictionary.h"

std::deque<Word> Dictionary::search(const std::string &S) {
  std::deque<Word> Results;
  for(const Word& W : Words) {
    if (W.containsString(S))
      Results.push_back(W);
  }
  std::sort(Results.begin(), Results.end(), [&S](const Word &A, const Word &B) {
    bool AEq = A.getValue().icmp(S);
    bool BEq = B.getValue().icmp(S);
    if (AEq && !BEq)
      return true;
    if (!AEq && BEq)
      return false;
    if (AEq)
      return A.getID() < B.getID();

    AEq = BEq = false;
    for (auto &T : A.getTranslations()) {
      AEq |= T.icmp(S);
    }
    for (auto &T : B.getTranslations()) {
      BEq |= T.icmp(S);
    }

    if (AEq && !BEq)
      return true;
    if (!AEq && BEq)
      return false;
    if (AEq)
      return A.getID() < B.getID();

    if (A.getValue().size() == B.getValue().size())
      return A.getID() < B.getID();

    return A.getValue().size() < B.getValue().size();
  });
  return Results;
}
