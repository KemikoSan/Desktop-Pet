#pragma once

enum class State : int {
  IDLE,
  WALK,
  SLEEP
};

enum class WalkState : int {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  UP_LEFT,
  UP_RIGHT,
  DOWN_LEFT,
  DOWN_RIGHT
};
