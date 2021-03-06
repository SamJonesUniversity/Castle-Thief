#include "cmp_player_physics.h"
#include <system_physics.h>
#include "cmp_arrow.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <engine.h>
#include <LevelSystem.h>
#include "cmp_hurt_player.h"
#include "cmp_hurt_enemy.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

sf::SoundBuffer buffer;
sf::Sound sound; 

sf::Texture arroww;

double _elapsed = 0;
bool loaded = false;

bool PlayerPhysicsComponent::isGrounded() const {
  auto touch = getTouching();
  const auto& pos = _body->GetPosition();
  const float halfPlrHeigt = _size.y * .5f;
  const float halfPlrWidth = _size.x * .52f;
  b2WorldManifold manifold;
  for (const auto& contact : touch) {
    contact->GetWorldManifold(&manifold);
    const int numPoints = contact->GetManifold()->pointCount;
    bool onTop = numPoints > 0;
    // If all contacts are below the player.
    for (int j = 0; j < numPoints; j++) {
      onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
    }
    if (onTop) {
      return true;
    }
  }

  return false;
}

void PlayerPhysicsComponent::update(double dt) {	

  const auto pos = _parent->getPosition();

  _elapsed -= dt;
  _firetime -= dt;

  if (_elapsed <= 0.f) {
	  //dash();
	  _candash = true; 
  }
  if (_elapsed <= 1.8f && _dampener)
  {
	  setVelocity(Vector2f(0.f, 0.f));
	  _dampener = false;
  }

  // Handle Dash
  if (_candash && Keyboard::isKeyPressed(Keyboard::C) && (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)))
  {
	if (!buffer.loadFromFile("res/sounds/dash.wav")) {
		std::cout << "File could not load" << std::endl;
	}
	sound.setBuffer(buffer);
	sound.play();

	if (_direction == false) //If player is facing right then dash right
	{
	
		setVelocity(Vector2f(700.f, 0.f));
		move(Vector2f(pos.x + 200.f, pos.y));
		impulse(Vector2f(600.f, 0));
	}
	else if (_direction == true) //If player is facing left  then dash left
	{
		setVelocity(Vector2f(-700.f, 0.f));
		move(Vector2f(pos.x - 200.f, pos.y));
		impulse(Vector2f(-600.f, 0));
	}

	_elapsed = 2.f;
	_candash = false;
	_dampener = true;
  }

  if (_firetime <= 0.f) {
	  _canfire = true;
  }

  //handles arrow code
  if (_canfire && Keyboard::isKeyPressed(Keyboard::X))
  {
	  arroww.loadFromFile("res/arrow.png");
	  int direction = 1;
	  if (_direction)
	  {
		  direction = -1;
	  }
	 
	  if (!buffer.loadFromFile("res/sounds/shoot.wav")) {
		  std::cout << "Could not load file" << std::endl;
	  }
	  sound.setBuffer(buffer);
	  sound.play();


	  Vector2f spawnArrow = _parent->getPosition();
	  spawnArrow.x += 40.0f*direction;

	  auto arrow = _parent->scene->makeEntity();
	  arrow->setPosition(spawnArrow);
	  arrow->addComponent<HurtComponentEnemy>();
	  arrow->addComponent<ArrowComponent>();

	  auto s = arrow->addComponent<SpriteComponent>();
	  s->getSprite().setOrigin(15.f*direction, 20.f);;
	  s->getSprite().setTexture(arroww);
	  if (!_direction)
	  {
		  s->getSprite().setTextureRect(IntRect(0, 0, 32, 32));
	  }
	  else
	  {
		  s->getSprite().setTextureRect(IntRect(32, 0, 32, 32));

	  }

	  auto p = arrow->addComponent<PhysicsComponent>(true, Vector2f(10.f*direction, 2.f));
	  p->impulse(sf::rotate(Vector2f(20.f*direction, 0), -_parent->getRotation()));
	  p->setRestitution(.4f);
	  p->setFriction(.005f);

	  _firetime = 2.f;
	  _canfire = false;
  }

  //Teleport to start if we fall off map.
  if (pos.y > ls::getHeight() * ls::getTileSize()) {
    teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
  }

  if (Keyboard::isKeyPressed(Keyboard::Left) ||
      Keyboard::isKeyPressed(Keyboard::Right)) {
    // Moving Either Left or Right
    if (Keyboard::isKeyPressed(Keyboard::Right)) 
	{
      if (getVelocity().x < _maxVelocity.x - 800)
        impulse({(float)(dt * _groundspeed), 0});
	     _direction = false; //User is facing right
    } else {
      if (getVelocity().x > -_maxVelocity.x + 800)
        impulse({-(float)(dt * _groundspeed), 0});
	    _direction = true; //User is facing left
    }
  } else {
    // Dampen X axis movement
    dampen({0.9f, 1.0f});
  }

  // Handle Jump
  if (Keyboard::isKeyPressed(Keyboard::Z)) {
    _grounded = isGrounded();
    if (_grounded) {
		if (!buffer.loadFromFile("res/sounds/jump.wav")) {
			std::cout << "File Could not load" << std::endl;
		}

		sound.setBuffer(buffer);
		sound.play();

      setVelocity(Vector2f(getVelocity().x, 0.f));
      teleport(Vector2f(pos.x, pos.y - 2.0f));
      impulse(Vector2f(0, -6.f));
    }
  } 

  //Are we in air?
  if (!_grounded) {
    // Check to see if we have landed yet
    _grounded = isGrounded();
    // disable friction while jumping
    setFriction(0.f);
  } else {
    setFriction(0.1f);
  }

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
                                               const Vector2f& size)
    : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(1000.f, 400.f);
  _groundspeed = 40.f;
  _grounded = false;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
	}
