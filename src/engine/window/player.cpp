#include "spdlog/spdlog.h"

#include "../../demo.hpp"
#include "../../engine/music.hpp"

#include "player.hpp"

bool Player::Create(const CretaParameters &cretaParameters) {
  if (!Window::Create(cretaParameters))
    return false;

  demo = Demo::Instance();
  spdlog::info("!!! Demo init");
  if (!demo->Init())
    return false;

  music = Music::Instance();
  if (!music->Load({.path = Demo::MUSIC, .volume = Demo::MUTE ? 0.0f : 1.0f}))
    return false;

  music->SetTime(Demo::OFFSET);
  music->Play();
  return true;
}

void Player::Render() {
  MakeContextCurrent();
  PollEvents();
  const double time = music->GetTime();
  demo->Begin(time);
  demo->Render(time);
  demo->End(time);
  PollEvents();
  SwapBuffers();
}
