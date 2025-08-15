#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

const int WINDOW_SIZE = 400;
const int GRID_SIZE = 20;

struct SnakeSegment { int x, y; };

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake Game");

    vector<SnakeSegment> snake = {{5,5},{4,5},{3,5}};
    int dirX = 1, dirY = 0;
    sf::Clock clock;
    float speed = 0.2;

    SnakeSegment food = {rand()%20, rand()%20};
    int score = 0;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Up && dirY == 0){ dirX=0; dirY=-1; }
                if(event.key.code == sf::Keyboard::Down && dirY == 0){ dirX=0; dirY=1; }
                if(event.key.code == sf::Keyboard::Left && dirX == 0){ dirX=-1; dirY=0; }
                if(event.key.code == sf::Keyboard::Right && dirX == 0){ dirX=1; dirY=0; }
            }
        }

        if(clock.getElapsedTime().asSeconds() > speed){
            clock.restart();
            SnakeSegment newHead = {snake[0].x + dirX, snake[0].y + dirY};
            // Collision with walls
            if(newHead.x<0 || newHead.x>=WINDOW_SIZE/GRID_SIZE || newHead.y<0 || newHead.y>=WINDOW_SIZE/GRID_SIZE){
                window.close();
            }
            // Collision with self
            for(auto &seg : snake) if(seg.x==newHead.x && seg.y==newHead.y) window.close();
            snake.insert(snake.begin(), newHead);
            if(newHead.x==food.x && newHead.y==food.y){
                score++; food.x=rand()%20; food.y=rand()%20;
            } else { snake.pop_back(); }
        }

        window.clear(sf::Color::Black);
        sf::RectangleShape block(sf::Vector2f(GRID_SIZE-2, GRID_SIZE-2));
        block.setFillColor(sf::Color::Green);
        for(auto &seg : snake){ block.setPosition(seg.x*GRID_SIZE, seg.y*GRID_SIZE); window.draw(block); }
        block.setFillColor(sf::Color::Red); block.setPosition(food.x*GRID_SIZE, food.y*GRID_SIZE); window.draw(block);
        window.display();
    }

    return 0;
}
