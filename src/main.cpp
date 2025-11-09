#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    sf::Vector2f windowSize = {800.f, 600.f};

    sf::RenderWindow window(
        sf::VideoMode({(unsigned int)windowSize.x, (unsigned int)windowSize.y}),
        "SFML + OpenGL 2.1"
    );

    std::cout << "OpenGL Version: " 
              << window.getSettings().majorVersion << "." 
              << window.getSettings().minorVersion << std::endl;

    // Check that shaders are available
    if (!sf::Shader::isAvailable()) {
         std::cerr << "Shaders are not available on this system!" << std::endl;
         return -1;
    }

    // Set the frame rate limit
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/grasstexture_0.png"))
    {
        std::cerr << "Failed to load image.png" << std::endl;
        return -1;
    }

    sf::Shader shader;
    std::string vertAddress = "resources/shader.vert";
    std::string fragAddress = "resources/shader.frag";

    if (!shader.loadFromFile(vertAddress, fragAddress))
    {
        std::cerr << "Failed to load shader.vert" << std::endl;
        return -1;
    }

    sf::RectangleShape rectangle(sf::Vector2f(256.f, 256.f));
    rectangle.setTexture(&texture);
    rectangle.setPosition({
        (windowSize.x - rectangle.getSize().x) / 2.f,
        (windowSize.y - rectangle.getSize().y) / 2.f
    });

    shader.setUniform("image", texture);
    shader.setUniform("iResolution", sf::Glsl::Vec2(windowSize.x, windowSize.y));

    // Main loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        // Remainder of main loop
        window.clear(sf::Color::Black);

        window.draw(rectangle, &shader);

        window.display();
    }

    return 0;
}