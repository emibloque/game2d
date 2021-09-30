#include "GameLayer.h"

GameLayer::GameLayer(Game *game)
    : Layer(game)
{
  //llama al constructor del padre : Layer(renderer)
  init();
}

void GameLayer::init()
{
  scrollX = 0;
  tiles.clear();
  points = 0;
  textPoints = new Text("0", WIDTH * .90, HEIGHT * .08, game);

  background = new Background("res/fondo_2.png", WIDTH * .5, HEIGHT * .5, -1, game);
  backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * .85, HEIGHT * .08, 24, 24, game);

  projectiles.clear(); // Vaciar por si reiniciamos el juego

  enemies.clear();

  loadMap("res/0.txt");
}

void GameLayer::processControls()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    keysToControls(event);
  }

  if (controlShoot)
  {
    Projectile *newProjectile = player->shoot();
    if (newProjectile != NULL)
    {
      projectiles.push_back(newProjectile);
    }
  }

  if (controlMoveX > 0)
  {
    player->moveX(1);
  }
  else if (controlMoveX < 0)
  {
    player->moveX(-1);
  }
  else
  {
    player->moveX(0);
  }

  // Eje Y
  if (controlMoveY > 0)
  {
    player->moveY(1);
  }
  else if (controlMoveY < 0)
  {
    player->moveY(-1);
  }
  else
  {
    player->moveY(0);
  }
}

void GameLayer::keysToControls(SDL_Event event)
{
  if (event.type == SDL_QUIT)
  {
    game->loopActive = false;
    return;
  }

  if (event.type == SDL_KEYDOWN)
  {
    int code = event.key.keysym.sym;
    switch (code)
    {

    case SDLK_ESCAPE:
      game->loopActive = false;
      return;

    case SDLK_1:
      game->scale();
      break;

    case SDLK_d: // derecha
      controlMoveX = 1;
      break;
    case SDLK_a: // izquierda
      controlMoveX = -1;
      break;
    case SDLK_w: // arriba
      controlMoveY = -1;
      break;
    case SDLK_s: // abajo
      controlMoveY = 1;
      break;
    case SDLK_SPACE: // dispara
      controlShoot = true;
      break;
    }
  }
  if (event.type == SDL_KEYUP)
  {
    int code = event.key.keysym.sym;
    switch (code)
    {
    case SDLK_d: // derecha
      if (controlMoveX == 1)
      {
        controlMoveX = 0;
      }
      break;
    case SDLK_a: // izquierda
      if (controlMoveX == -1)
      {
        controlMoveX = 0;
      }
      break;
    case SDLK_w: // arriba
      if (controlMoveY == -1)
      {
        controlMoveY = 0;
      }
      break;
    case SDLK_s: // abajo
      if (controlMoveY == 1)
      {
        controlMoveY = 0;
      }
      break;
    case SDLK_SPACE: // dispara
      controlShoot = false;
      break;
    }
  }
}

void GameLayer::update()
{
  background->update();

  // Generar enemigos
  // newEnemyTime--;
  // if (newEnemyTime <= 0)
  // {
  //   int rX = (rand() % (600 - 500)) + 1 + 500;
  //   int rY = (rand() % (300 - 60)) + 1 + 60;
  //   enemies.push_back(new Enemy(rX, rY, game));
  //   newEnemyTime = 110;
  // }

  player->update();
  for (auto const &enemy : enemies)
  {
    enemy->update();
  }

  for (auto const &projectile : projectiles)
  {
    projectile->update();
  }

  // Colisiones
  for (auto const &enemy : enemies)
  {
    if (player->isOverlap(enemy))
    {
      init();
      return; // Cortar el for
    }
  }

  // Colisiones , Enemy - Projectile

  list<Enemy *> deleteEnemies;
  list<Projectile *> deleteProjectiles;

  for (auto const &projectile : projectiles)
  {
    if (!projectile->isInRender(scrollX))
    {

      bool pInList = std::find(deleteProjectiles.begin(),
                               deleteProjectiles.end(),
                               projectile) != deleteProjectiles.end();

      if (!pInList)
      {
        deleteProjectiles.push_back(projectile);
      }
    }
  }

  for (auto const &enemy : enemies)
  {
    for (auto const &projectile : projectiles)
    {
      if (enemy->isOverlap(projectile))
      {
        bool pInList = std::find(deleteProjectiles.begin(),
                                 deleteProjectiles.end(),
                                 projectile) != deleteProjectiles.end();

        if (!pInList)
        {
          deleteProjectiles.push_back(projectile);
        }

        if (enemy->state != States::DYING)
        {
          enemy->impacted();
          points++;
          textPoints->content = to_string(points);
        }
      }
    }
  }

  for (auto const &enemy : enemies)
  {
    if (enemy->state == States::DEAD)
    {
      bool eInList = std::find(deleteEnemies.begin(),
                               deleteEnemies.end(),
                               enemy) != deleteEnemies.end();

      if (!eInList)
      {
        deleteEnemies.push_back(enemy);
      }
    }
  }

  for (auto const &delEnemy : deleteEnemies)
  {
    enemies.remove(delEnemy);
  }
  deleteEnemies.clear();

  for (auto const &delProjectile : deleteProjectiles)
  {
    projectiles.remove(delProjectile);
    delete delProjectile;
  }
  deleteProjectiles.clear();
}

void GameLayer::draw()
{
  calculateScroll();

  background->draw();

  for (auto const &tile : tiles)
  {
    tile->draw(scrollX);
  }

  for (auto const &projectile : projectiles)
  {
    projectile->draw(scrollX);
  }

  player->draw(scrollX);
  for (auto const &enemy : enemies)
  {
    enemy->draw(scrollX);
  }

  backgroundPoints->draw();
  textPoints->draw();

  SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::loadMap(string name)
{
  char character;
  string line;
  ifstream streamFile(name.c_str());
  if (!streamFile.is_open())
  {
    cout << "Falla abrir el fichero de mapa" << endl;
    return;
  }
  else
  {
    // Por línea
    for (int i = 0; getline(streamFile, line); i++)
    {
      istringstream streamLine(line);
      mapWidth = line.length() * 40; // Ancho del mapa en pixels
      // Por carácter (en cada línea)
      for (int j = 0; !streamLine.eof(); j++)
      {
        streamLine >> character; // Leer character
        cout << character;
        float x = 40 / 2 + j * 40; // x central
        float y = 32 + i * 32;     // y suelo
        loadMapObject(character, x, y);
      }

      cout << character << endl;
    }
  }
  streamFile.close();
}

void GameLayer::loadMapObject(char character, int x, int y)
{
  switch (character)
  {
  case '1':
  {
    player = new Player(x, y, game);
    // modificación para empezar a contar desde el suelo.
    player->y = player->y - player->height / 2;
    break;
  }
  case '#':
  {
    Tile *tile = new Tile("res/bloque_tierra.png", x, y, game);
    // modificación para empezar a contar desde el suelo.
    tile->y = tile->y - tile->height / 2;
    tiles.push_back(tile);
    break;
  }
  case 'E':
  {
    Enemy *enemy = new Enemy(x, y, game);
    enemy->y = enemy->y - enemy->height / 2;
    enemies.push_back(enemy);
    break;
  }
  }
}

void GameLayer::calculateScroll()
{
  scrollX = player->x - 200;
}
