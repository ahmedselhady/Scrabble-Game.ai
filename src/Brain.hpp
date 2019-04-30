#pragma once

#include <unordered_map>
#include <vector>
#include "./AI_MODE/AI_MODE.hpp"
#include "./Definitions.hpp"
#include "./MoveGeneration/Gaddag.h"
#include "./MoveGeneration/LoadGaddag.h"
#include "./MoveGeneration/LoadNode.h"

class GameBrain {
 private:
  int bagSize;
  std::vector<char> tiles;
  BoardToGrammer *Ptr2G;
  static Node *_gaddagInstance;
  static inline Node *createGaddag() {
    LoadGaddag gaddagConstructor;
    Node *gaddagRoot = gaddagConstructor.constructGaddag();
    return gaddagRoot;
  }

 public:
  static Node *__get_gaddag();

  std::unordered_map<char, int> bag;
  GamePhase game_phase;

  GameBrain();
  void setTiles(uint8_t[]);
  void updateBag(std::vector<char> &);
  Move *work_computer_vs_computer();
  void work_human_vs_computer();
};