#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

int main() {
	float b; // distance between point and center of cycle
	float cycleRadius;

	// Input screen
	cout << "Chuong trinh ve trochoid voi tham so b va r \n";
	cout << "Trong do:\n";
	cout << "\t r la ban kinh duong tron\n";
	cout << "\t b la khoang cach tu tam duong tron den diem ve\n";
	cout << "Nhap r = "; cin >> cycleRadius;
	cout << "Nhap b = "; cin >> b;
		
	// Initialize the screen
	// Window Attr
	int windowWidth = 1280, windowHeight = 720;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Screen");

	// Root Coordinate
	float x0 = 0, y0 = windowHeight / 2;

	// Time tracking 
	Clock clock;
	float t = 0; // Time in program

	// Cycle
	CircleShape cycle(cycleRadius);
	cycle.setFillColor(Color::Transparent);
	cycle.setOutlineThickness(2);
	cycle.setOutlineColor(Color::White);

	// Road
	Vertex road[]{
		Vertex(Vector2f(0, y0 + cycleRadius), Color::White),
		Vertex(Vector2f(windowWidth, y0 + cycleRadius), Color::White),
	};

	// Point
	float pointRadius = 8;
	CircleShape point(pointRadius);
	point.setFillColor(Color::Red);

	// Orbit Tracking
	vector <Vector2f> orbit;

	// Main loop
	while (window.isOpen()) {

		Event event;

		// Event handle
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		Time elapsed = clock.restart();
		t += elapsed.asSeconds();

		// point movement
		float x_point = cycleRadius*t - b*sin(t);
		float y_point = - cycleRadius + b*cos(t); // positive reverse
		
		cycle.setPosition(cycleRadius*t - cycleRadius, y0 - cycleRadius);
		point.setPosition(x_point - pointRadius, y0 + y_point - pointRadius + cycleRadius);
		orbit.push_back(Vector2f(x_point, y0 + y_point + cycleRadius));

		// Render
		window.clear();

		window.draw(road, 2, Lines);
		window.draw(cycle);
		window.draw(point);

		// Draw Orbit
		for (int i = 1; i < orbit.size(); i++) {
			Vertex line[]{
				Vertex(orbit[i], Color::White),
				Vertex(orbit[i - 1], Color::White),
			};
			window.draw(line, 2, Lines);
		}

		window.display();
	}
	return 0;
}