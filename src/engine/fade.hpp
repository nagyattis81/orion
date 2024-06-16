#pragma once

class Fade {
public:
  bool Init();
  void Add(const double startTime, const double endTime,
           const float startTransparency, const float endTransparency);
  void Render(const double time);
};