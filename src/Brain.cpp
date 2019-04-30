
#include "Brain.hpp"
#include <utility>

Node *GameBrain::_gaddagInstance = nullptr;

void GameBrain::updateBag(std::vector<char> &tilesToReduce) {
  for (int i = 0; i < (int)tilesToReduce.size(); ++i) {
    try {
      GameBrain::bag[tilesToReduce[i]] -= 1;
      --this->bagSize;
    } catch (const std::exception &e) {
      // ! how on earth did you place a non alphabet character!
      std::cout << e.what() << std::endl;
    }
  }

  GameBrain::game_phase =
      (bagSize <= 7) ? END_GAME_MODE
                     : (bagSize <= 9) ? PREEND_GAME_MODE : MID_GAME_MODE;
}

Node *GameBrain::__get_gaddag() {
  if (GameBrain::_gaddagInstance == nullptr) {
    GameBrain::_gaddagInstance = createGaddag();
  }

  return GameBrain::_gaddagInstance;
}

GameBrain::GameBrain() {
  this->bagSize = 100;
  game_phase = MID_GAME_MODE;
  this->Ptr2G = new BoardToGrammer();

  bag['a'] = 9;
  bag['b'] = 2;
  bag['c'] = 2;
  bag['d'] = 4;
  bag['e'] = 12;
  bag['f'] = 2;
  bag['g'] = 3;
  bag['h'] = 2;
  bag['i'] = 9;
  bag['j'] = 1;
  bag['k'] = 1;
  bag['l'] = 4;
  bag['m'] = 2;
  bag['n'] = 6;
  bag['o'] = 8;
  bag['p'] = 2;
  bag['q'] = 1;
  bag['r'] = 6;
  bag['s'] = 4;
  bag['t'] = 6;
  bag['u'] = 4;
  bag['v'] = 2;
  bag['w'] = 2;
  bag['x'] = 1;
  bag['y'] = 2;
  bag['z'] = 1;
  bag[' '] = 2;
}

void print_vect(const std::vector<char> &msg) {
  std::cout << std::endl;
  for (auto m : msg) {
    std::cout << m << ", ";
  }
  std::cout << std::endl;
}

Move *GameBrain::work_computer_vs_computer() {
  // trial:
  std::cout << "BRAIN 1: ";
  AI_MODE *aimode = new AI_MODE();
  aimode->setTiles(this->tiles);
  print_vect(this->tiles);
  aimode->setBoardToGrammar(*Ptr2G);
  aimode->setBagPointer(&this->bag);
  std::cout << "Debug 1" << std::endl;
  Move *move = aimode->doWork();
  std::cout << "BRAIN 2: ";

  std::cout << "Move Score: " << move->evaluatedScore << std::endl;
  return move;
}

void GameBrain::setTiles(uint8_t t[7]) {
  for (int i = 0; i < 7; i++) {
    uint8_t tile = t[i];
    if (tile == 0) {
      continue;
    } else if (tile == 100) {
      tiles.push_back(' ');
    } else {
      // 1 <= tile <= 26
      tiles.push_back(tile - 1 + 'a');
    }
  }
}
