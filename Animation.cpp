#include "Animation.h"

Animation::Animation(string filename, float actorWidth, float actorHeight,
                     float fileWidth, float fileHeight,
                     int updateFrecuence, int totalFrames, bool loop, Game *game)
{
  texture = game->getTexture(filename);

  this->loop = loop;
  this->actorWidth = actorWidth;
  this->actorHeight = actorHeight;
  this->fileWidth = fileWidth;
  this->fileHeight = fileHeight;
  this->updateFrecuence = updateFrecuence;
  this->totalFrames = totalFrames;
  this->game = game;

  updateTime = 0; // última actualización
  currentFrame = 0;

  // Calcular lo que mide un fotograma/frame
  frameWidth = fileWidth / totalFrames;
  frameHeigt = fileHeight;

  // Rectangulo de recorte de fotograma
  source.x = 0;
  source.y = 0;
  source.w = frameWidth;
  source.h = frameHeigt;
}

bool Animation::update()
{
  updateTime++;
  if (updateTime > updateFrecuence)
  {
    updateTime = 0;
    currentFrame++;

    if (currentFrame >= totalFrames)
    {
      currentFrame = 0;
      if (!loop)
      {
        return true;
      }
    }
  }

  source.x = currentFrame * frameWidth;
  return false;
}

void Animation::draw(int x, int y)
{ // Donde se va a pegar en el renderizador
  SDL_Rect destination;
  destination.x = x - actorWidth / 2;
  destination.y = y - actorHeight / 2;
  destination.w = actorWidth;
  destination.h = actorHeight;
  // Modificar para que la referencia sea el punto central

  SDL_RenderCopyEx(game->renderer,
                   texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}
