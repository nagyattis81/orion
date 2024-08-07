#pragma once

#include "window.hpp"

// TODO ne legyen benne player window

class Player;
class GUI;

class Editor : public Window {
private:
  bool disable = false;
  GUI *gui = nullptr;
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