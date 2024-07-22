#include "player-window.hpp"

PlayerWindow *PlayerWindow::Instance() {
  if (!instance)
    instance = new PlayerWindow();
  return instance;
}