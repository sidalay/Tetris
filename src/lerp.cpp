#include "lerp.hpp"

#include <cmath>

float Game::Lerp(float a, float b, float t)
{
  return a * (1.f - t) + b * t;
}

float Game::InvLerp(float a, float b, float v)
{
  return (v - a) / (b - a);
}

float Game::Remap(float iMin, float iMax, float oMin, float oMax, float v)
{
  float t = InvLerp(iMin, iMax, v);
  return Lerp(oMin, oMax, t);
}

float Game::EaseIn(float t) 
{
  return t * t;
}

float Game::EaseOut(float t)
{
  return 1.f - (1.f - t) * (1.f - t);
}

float Game::Smoothstep(float t)
{
  return std::lerp(EaseIn(t), EaseOut(t), t);
}

float Game::Parabola(float t, float k) 
{
  return std::pow(4.f * t * (1.f - t), k);
}

float Game::Triangle(float t)
{
  return 1.f - 2.f * std::abs(t - 0.5f);
}

float Game::ElasticOut(float t) 
{
  return std::sin(-13.f * (t + 1.f) * 3.14f/2.f) * std::pow(2.0, -10.0 * t) + 1.0;
}

float Game::BounceOut(float t)
{
  const float nl{7.5625f};
  const float dl{2.75f};

  if (t < 1.f / dl) {
    return nl * t * t;
  } else if (t < 2.f / dl) {
    t -= 1.5f / dl;
    return nl * t * t + 0.75f;
  } else if (t < 2.5f / dl) {
    t -= 2.25f / dl;
    return nl * t * t + 0.9375f;
  } else {
    t -= 2.625f / dl;
    return nl * t * t + 0.984375f;
  }
}
