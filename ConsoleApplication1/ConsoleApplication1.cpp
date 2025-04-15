#include <SFML/Graphics.hpp>
#include<iostream>

class GravitySolarSystem {

	sf::Vector2f position;
	float Force;
	sf::CircleShape Sun;


public:
	GravitySolarSystem(float positon_x, float positon_y, float Force)
	{
		position.x = positon_x;
		position.y = positon_y;
		this->Force = Force;


		Sun.setPosition(position);
		Sun.setFillColor(sf::Color::Yellow);
		Sun.setRadius(25);
	}
	void render(sf::RenderWindow& wind) {
		wind.draw(Sun);
	}
	sf::Vector2f get_position() {
		return position;
	}
	float get_Force() {
		return Force;
	}
};

class Planet {

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::CircleShape planet;


public:
	Planet(float positon_x,float velocity_x, float positon_y,float velocity_y)
	{
		position.x = positon_x;
		position.y = positon_y;
		velocity.x = velocity_x;
		velocity.y = velocity_y;


		planet.setPosition(position);
		planet.setFillColor(sf::Color::Blue);
		planet.setRadius(12);
	}
	void render(sf::RenderWindow& wind) {
		planet.setPosition(position);
		wind.draw(planet);
	}
	void update_Physics(GravitySolarSystem &Sun) {
		float distance_x = Sun.get_position().x - position.x;
		float distance_y = Sun.get_position().y - position.y;
		float netDistance = sqrt(distance_x * distance_x + distance_y * distance_y);
		
		
		float inverse = 1.0f / netDistance;
		
		float normalised_x = inverse * distance_x;
		float normalised_y = inverse * distance_y;


		float inverse_square_final = inverse * inverse;

		float accleration_x = normalised_x * Sun.get_Force();
		float accleration_y = normalised_y * Sun.get_Force();

		velocity.x += accleration_x;
		velocity.y += accleration_y;

		position.x += velocity.x;
		position.y += velocity.y;


	}
	

};




int main()

{
	unsigned int width = 1600;
	unsigned int height = 1000;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "Simulation");
	window->setFramerateLimit(75);
	
	GravitySolarSystem source(800, 500, 0.1f);
	Planet earth(500, 0.0f, 500, 2.3f);


	

	while (window->isOpen()) {
		while (const std::optional event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					window->close();
				}
			}
		}
		
		


		

		


		window->clear();

		earth.update_Physics(source);
		source.render(*window);
		earth.render(*window);
		
		

		window->display();
	}
	delete window;
	return 0;
}