#include "cmp_player_physics.h"
#include <system_physics.h>
#include "cmp_arrow.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <engine.h>
#include <LevelSystem.h>
#include "cmp_hurt_player.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

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

void PlayerPhysicsComponent::fire() const {
	if (Keyboard::isKeyPressed(Keyboard::X))
	{	
		int direction = 1;
		if (_direction)
		{
			direction = -1;
		}

		Vector2f spawnArrow = _parent->getPosition();
		spawnArrow.x += 40.0f*direction;

		auto arrow = _parent->scene->makeEntity();
		arrow->setPosition(spawnArrow);
		//  arrow->addComponent<HurtComponent>();
		arrow->addComponent<ArrowComponent>();

		auto s = arrow->addComponent<ShapeComponent>();
		s->getShape().setOrigin(50.f*direction, 8.f);;
		s->setShape<sf::RectangleShape>(Vector2f(10.f, 2.f));
		s->getShape().setFillColor(Color::Blue);

		auto p = arrow->addComponent<PhysicsComponent>(true, Vector2f(10.f*direction, 2.f));
		p->impulse(sf::rotate(Vector2f(20.f*direction, 0), -_parent->getRotation()));
		p->setRestitution(.4f);
		p->setFriction(.005f);
	}
}

void PlayerPhysicsComponent::update(double dt) {

  const auto pos = _parent->getPosition();

  _firetime -= dt;
  if (_firetime <= 0.f) {
	  fire();
	  _firetime = 3.f;
  }

  //Teleport to start if we fall off map.
  if (pos.y > ls::getHeight() * ls::getTileSize()) {
    teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
  }

  if (Keyboard::isKeyPressed(Keyboard::Left) ||
      Keyboard::isKeyPressed(Keyboard::Right)) {
    // Moving Either Left or Right
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
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
      setVelocity(Vector2f(getVelocity().x, 0.f));
      teleport(Vector2f(pos.x, pos.y - 2.0f));
      impulse(Vector2f(0, -6.f));
    }
  }



  // Handle Dash
  if (_direction == false & (Keyboard::isKeyPressed(Keyboard::C))) //If player is facing right and c is pressed then dash right
  {
	  setVelocity(Vector2f(700.f, 0.f));
	  move(Vector2f(pos.x + 200.f, pos.y));
	  impulse(Vector2f(600.f, 0));
  }
  else if (_direction == true & (Keyboard::isKeyPressed(Keyboard::C))) //If player is facing left and c is pressed then dash left
  {
	  setVelocity(Vector2f(-700.f, 0.f));
	  move(Vector2f(pos.x - 200.f, pos.y));
	  impulse(Vector2f(-600.f, 0));
	  
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
