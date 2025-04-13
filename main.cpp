#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML + Box2D funcionando");
    window.setFramerateLimit(60);

    // Crear el mundo físico
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // Crear un cuerpo dinámico (la pelota)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5.0f, 5.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 1.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.6f;
    body->CreateFixture(&fixtureDef);

    // Representación visual
    sf::CircleShape ball(shape.m_radius * 100.0f);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ball.getRadius(), ball.getRadius());

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, 8, 3);

        b2Vec2 pos = body->GetPosition();
        ball.setPosition(pos.x * 100.0f, pos.y * 100.0f);

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }

    return 0;
}