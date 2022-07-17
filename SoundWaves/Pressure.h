#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <math.h>
#define PI 3.14159f

class PressureSource {
private:
	float wavelength, freq, amplitude, phase, type, slope, speed;
	sf::Vector2f pos;
public:
	PressureSource() {}
	PressureSource(const sf::Vector2f& pos, const float& wavelength, const float& speed, const float& amplitude, const float& phase, std::optional<float> type = {}, std::optional<float> slope = {}) {
		this->pos = pos;
		this->wavelength = wavelength;
		this->speed = speed;
		this->freq = speed / wavelength;
		this->amplitude = amplitude;
		this->phase = phase;
		this->type = type.value_or(0);
		this->slope = slope.value_or(0);
	}
	sf::Glsl::Vec4 getPointsData(const float& height) {
		return sf::Glsl::Vec4(pos.x, height - pos.y, type, slope);
	}
	sf::Glsl::Vec3 getPontValue() {
		return sf::Glsl::Vec3(amplitude, freq, phase);
	}
};