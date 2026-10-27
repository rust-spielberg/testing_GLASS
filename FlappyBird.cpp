#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <time.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BIRD_SIZE = 30;
const int PIPE_WIDTH = 50;
const int PIPE_GAP = 150;
const int PIPE_SPEED = 3;

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird");
sf::Texture birdTexture;
sf::Sprite birdSprite;
sf::Texture pipeTexture;
sf::Sprite pipeSprites[2];
sf::SoundBuffer flapBuffer;
sf::Sound flapSound;
sf::Clock clock;
float birdVelocity = 0.0f;
float gravity = 0.5f;
bool isGameOver = false;

void loadResources() {
    birdTexture.loadFromFile("bird.png");
    pipeTexture.loadFromFile("pipe.png");
    flapBuffer.loadFromFile("flap.wav");
    flapSound.setBuffer(flapBuffer);
}

void resetGame() {
    birdVelocity = 0.0f;
    isGameOver = false;
    for (int i = 0; i < 2; i++) {
        pipeSprites[i].setPosition(WINDOW_WIDTH, i * (PIPE_GAP + PIPE_HEIGHT));
    }
}

void update() {
    if (!isGameOver) {
        birdVelocity += gravity;
        birdSprite.move(0, birdVelocity);

        if (clock.getElapsedTime().asSeconds() > 1.0f) {
            clock.restart();
            for (int i = 0; i < 2; i++) {
                pipeSprites[i].move(-PIPE_SPEED, 0);
                if (pipeSprites[i].getPosition().x < -PIPE_WIDTH) {
                    pipeSprites[i].setPosition(WINDOW_WIDTH, i * (PIPE_GAP + PIPE_HEIGHT));
                }
            }
        }

        if (birdSprite.getGlobalBounds().intersects(pipeSprites[0].getGlobalBounds()) ||
            birdSprite.getGlobalBounds().intersects(pipeSprites[1].getGlobalBounds()) ||
            birdSprite.getPosition().y < 0 || birdSprite.getPosition().y > WINDOW_HEIGHT - BIRD_SIZE) {
            isGameOver = true;
        }
    }
}

void render() {
    window.clear();
    window.draw(birdSprite);
    for (int i = 0; i < 2; i++) {
        window.draw(pipeSprites[i]);
    }
    window.display();
}

int main() {
    loadResources();
    birdSprite.setTexture(birdTexture);
    birdSprite.setPosition(WINDOW_WIDTH / 2 - BIRD_SIZE / 2, WINDOW_HEIGHT / 2 - BIRD_SIZE / 2);
    for (int i = 0; i < 2; i++) {
        pipeSprites[i].setTexture(pipeTexture);
        pipeSprites[i].setPosition(WINDOW_WIDTH, i * (PIPE_GAP + PIPE_HEIGHT));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isGameOver) {
                birdVelocity = -10.0f;
                flapSound.play();
            }
        }

        update();
        render();
    }

    return 0;
}