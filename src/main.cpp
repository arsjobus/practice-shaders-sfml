#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath> // for sinf

int main() {
    sf::Vector2f windowSize = {1280.f, 720.f};

    sf::RenderWindow window(
        sf::VideoMode({(unsigned int)windowSize.x, (unsigned int)windowSize.y}),
        "SFML + OpenGL 2.1"
    );

    std::cout << "OpenGL Version: " 
              << window.getSettings().majorVersion << "." 
              << window.getSettings().minorVersion << std::endl;

    if (!sf::Shader::isAvailable()) {
         std::cerr << "Shaders are not available on this system!" << std::endl;
         return -1;
    }

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/grasstexture_0.png"))
    {
        std::cerr << "Failed to load image.png" << std::endl;
        return -1;
    }
    texture.setSmooth(true);
    texture.generateMipmap();

    sf::Shader shader;
    std::string vertAddress = "resources/basic-shader.vert";
    std::string fragAddress = "resources/basic-shader.frag";

    if (!shader.loadFromFile(vertAddress, fragAddress))
    {
        std::cerr << "Failed to load shader.vert" << std::endl;
        return -1;
    }

    sf::RectangleShape rectangle(sf::Vector2f(512.f, 512.f));
    rectangle.setTexture(&texture);

    // Set origin to center so scaling happens around the center
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});

    shader.setUniform("image", texture);
    shader.setUniform("iResolution", sf::Glsl::Vec2(windowSize.x, windowSize.y));

    sf::Clock clock; // track elapsed time for animation

    // Main loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        // Compute pulsating scale
        float time = clock.getElapsedTime().asSeconds();
        float scale = 1.f + 0.25f * std::sinf(time * 2.f * 3.14159f); // pulsate between 0.75x and 1.25x
        rectangle.setScale({scale, scale});

        shader.setUniform("time", time);
        
        window.clear(sf::Color::Black);
        window.draw(rectangle, &shader);
        window.display();
    }

    return 0;
}
