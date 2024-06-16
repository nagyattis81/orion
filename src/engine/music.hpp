#pragma once

class Music {
public:
  static Music *Instance();
  ~Music();

  struct Parameters {
    const char *path = nullptr;
    float volume = 1.0f;
  };

  bool Load(const Parameters &parameters);
  void Play();
  double GetTime() const;
  void SetTime(const double time);

private:
  inline static Music *instance = nullptr;
  unsigned long handle = 0;
};
