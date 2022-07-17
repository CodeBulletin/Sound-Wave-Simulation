#pragma once

#include "Pressure.h"

class sound {
private:
	std::vector<PressureSource> PressureSources;
public:
	sound() {}
	void clear() {
		PressureSources.clear();
	}
	void addSource(const PressureSource& p) {
		PressureSources.push_back(p);
	}
	void setData(sf::Shader& shader, const float& height) {
		int i = 0;
		for (PressureSource p : PressureSources) {
			shader.setUniform("Points[" + std::to_string(i) + "]", p.getPointsData(height));
			shader.setUniform("AmpFreqPha[" + std::to_string(i) + "]", p.getPontValue());
			i++;
		}
	}
	int getSize() {
		return PressureSources.size();
	}
};