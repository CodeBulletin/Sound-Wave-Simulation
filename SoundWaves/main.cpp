#include "sound.h"

static int width, height;
static int shadermode = 2;
std::string name = "sound wave simulation";
sf::RenderWindow window;
sound sounds;

float t = 0;
void main() {
	sf::VideoMode vid = sf::VideoMode::getDesktopMode();
	width = vid.width;
	height = vid.height;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(vid, name, sf::Style::Fullscreen, settings);
	sf::Event event;
	sf::Shader shader1, shader2, shader3;
	window.setVerticalSyncEnabled(true);
	if (!sf::Shader::isAvailable())
	{
		std::cout << "error Shaders are not Available on your GPU" << std::endl;
		std::cin.get();
	}
	if (!shader1.loadFromFile("wave.frag", sf::Shader::Fragment)) {
	}
	if (!shader2.loadFromFile("rms.frag", sf::Shader::Fragment)) {
	}
	if (!shader3.loadFromFile("int.frag", sf::Shader::Fragment)) {
	}

	sf::VertexArray v(sf::Quads, 4);
	v[3].position = sf::Vector2f(0, 0);
	v[2].position = sf::Vector2f(width, 0);
	v[1].position = sf::Vector2f(width, height);
	v[0].position = sf::Vector2f(0, height);
	float ofset = 400.0f;
	bool mode = true;
	float wavelength = 20.0f;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::Num1) {
					shadermode = 0;
				}
				if (event.key.code == sf::Keyboard::Num2) {
					shadermode = 1;
				}
				if (event.key.code == sf::Keyboard::Num3) {
					shadermode = 2;
				}
				break;
			default:
				break;
			}
		}
		window.clear(sf::Color::Black);

		sounds.clear();
		sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 - height / 3 + 68), wavelength, 1, 1, 0, 1, 0));
		sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 - height / 3), wavelength, 1, 1, 0, 1, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(0, 0), wavelength, 1, 1, 0, 2, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(0, 0), wavelength, 1, 1, 0, 1, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 - height / 3 + 150), wavelength, 1, 1, 0, 0, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 - height / 3 + 150), wavelength - 0.4f, 2, 1, 0, 0, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 - height / 3 + 150), wavelength + 0.4f, 0.5f, 1, 0, 0, 0));
		///*
		//sounds.addSource(PressureSource(sf::Vector2f(0, height / 2 - height / 3), wavelength, 1, 1, 0, 0, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(0, height / 2 + height / 3), wavelength, 1, 1, 0, 0, 0));
		//*/
		//sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 + height / 3 - 150), wavelength, 1, 1, 0, 0, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 + height / 3 - 150), wavelength - 0.4f, 2, 1, 0, 0, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(width/2, height / 2 + height / 3 - 150), wavelength + 0.4f, 0.5, 1, 0, 0, 0));
		//sounds.addSource(PressureSource(sf::Vector2f(0, height / 2), wavelength/4, 1, 1, 0, 0, 0));

		if (shadermode == 0) {
			shader1.setUniform("size", sounds.getSize());
			sounds.setData(shader1, height);
			shader1.setUniform("t", t);
			window.draw(v, &shader1);
		}
		else if (shadermode == 1) {
			shader2.setUniform("size", sounds.getSize());
			sounds.setData(shader2, height);
			shader2.setUniform("t", t);
			window.draw(v, &shader2);
		}
		else if (shadermode == 2) {
			shader3.setUniform("size", sounds.getSize());
			sounds.setData(shader3, height);
			shader3.setUniform("t", t);
			window.draw(v, &shader3);
		}
		t += 0.05;

		/*if (mode) {
			if (ofset >= 2 * std::abs(wavelength)) {
				ofset -= 0.1;
			}
			else {
				mode = false;
			}
		}
		else {
			if (ofset <= 300) {
				ofset += 0.1;
			}
			else {
				mode = true;
			}
		}*/

		window.display();
	}
}