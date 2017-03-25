#include "Player.hpp"

void Player::isPlaying(bool value) {
  flag = value;
}

bool Player::canPlay() {
  return flag;
}
