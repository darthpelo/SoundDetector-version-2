#include "Singleton.hpp"

class Player {
public:
  Player() {};
  ~Player() {};

  void isPlaying(bool value);
  bool canPlay();

private:
  bool flag;
};
