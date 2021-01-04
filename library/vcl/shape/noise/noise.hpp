#pragma once

#include "vcl/containers/containers.hpp"

namespace vcl
{
	float noise_perlin(float x,       int octave=5, float persistency=0.3f, float frequency_gain=2.0f);
	float noise_perlin(vec2 const& p, int octave=5, float persistency=0.3f, float frequency_gain=2.0f);
	float noise_perlin(vec3 const& p, int octave=5, float persistency=0.3f, float frequency_gain=2.0f);
}