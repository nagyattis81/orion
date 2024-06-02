#pragma once

class Music {
public:
  static Music *Instance();
  ~Music();

  bool Load(const char *path);
  void Play();
  double GetTime() const;

private:
  inline static Music *instance = nullptr;
  unsigned long handle = 0;
};
