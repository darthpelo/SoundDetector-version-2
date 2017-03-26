#include "Singleton.hpp"

class Player {
public:
  Player() {};
  ~Player() {};

  void startPlay();
  void finished();
  bool isPlaying();

private:
  bool play;
};
