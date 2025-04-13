#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

const float SCALE = 100.0f; // 1 metro = 100 píxeles

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Protector de Pantalla DVD");
    window.setFramerateLimit(60);

    // Crear mundo sin gravedad
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    // Pelota dinámica
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(4.0f, 3.0f); // En el centro (8m x 6m world)
    b2Body* ball = world.CreateBody(&ballDef);

    b2CircleShape ballShape;
    ballShape.m_radius = 0.5f; // 0.5 metros = 50 píxeles

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &ballShape;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 1.0f; // rebote perfecto
    ball->CreateFixture(&fixtureDef);

    // Velocidad inicial
    ball->SetLinearVelocity(b2Vec2(5.0f, 3.0f));

    // Bordes del mundo (piso, techo, paredes)
    float width = 8.0f;  // metros (800 px)
    float height = 6.0f; // metros (600 px)

    b2EdgeShape borders[4];
    b2BodyDef borderDef;
    borderDef.type = b2_staticBody;

    // Piso
    borders[0].SetTwoSided(b2Vec2(0, 0), b2Vec2(width, 0));
    // Derecha
    borders[1].SetTwoSided(b2Vec2(width, 0), b2Vec2(width, height));
    // Techo
    borders[2].SetTwoSided(b2Vec2(width, height), b2Vec2(0, height));
    // Izquierda
    borders[3].SetTwoSided(b2Vec2(0, height), b2Vec2(0, 0));

    for (int i = 0; i < 4; ++i) {
        b2Body* edge = world.CreateBody(&borderDef);
        edge->CreateFixture(&borders[i], 0.0f);
    }

    // Visual
    sf::CircleShape ballSprite(ballShape.m_radius * SCALE);
    ballSprite.setFillColor(sf::Color::White);
    ballSprite.setOrigin(ballSprite.getRadius(), ballSprite.getRadius());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, 8, 3);

        b2Vec2 pos = ball->GetPosition();
        ballSprite.setPosition(pos.x * SCALE, pos.y * SCALE);

        window.clear(sf::Color::Black);
        window.draw(ballSprite);
        window.display();
    }

    return 0;
}