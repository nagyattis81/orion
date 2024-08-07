#pragma once

#include "../gui.hpp"
#include "window.hpp"

// TODO delete this file

class Player;

class Editor : public Window {
private:
  bool disable = false;
  GUI gui;
  Player *player = nullptr;
  CreateParameters *playerCreateParameters = nullptr;

  bool Load(CreateParameters &createParameters);
  void Save();

public:
  Editor(const bool enable);
  void SetPlayer(Player *player);
  bool Create(const CreateParameters *createParameters) override;
  bool Render();
  void Delete();
  CreateParameters *GetPlayerCreateParameters(const char *title);
};