Game 3: Space game

Shoot the asteroids

g++ -std=c++11 -Wall -Wextra main.cpp Game.cpp Enemy.cpp Player.cpp Bullet.cpp -o sfml-app -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app