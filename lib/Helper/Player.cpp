#include "Player.hpp"

void Player::startPlay() {
  play = true;
}

void  Player::finished() {
  play = false;
}

bool Player::isPlaying() {
  return play;
}
