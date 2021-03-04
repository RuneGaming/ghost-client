#ifndef YUKIO_PLAYER_H
#define YUKIO_PLAYER_H

#include "jmy/jimmy.h"
#include "vec3.hpp"
#include <memory>

class Player
{
public:
	Player();
	Player(Jobj player);

	void update();
	Jobj getPlayerObject();

	Jclass getPlayerSpCLS();

	float getPitch();
	void setPitch(float value);
	float getYaw();
	void setYaw(float value);
	float getPrevYaw();
	void setPrevYaw(float value);
	float getPrevPitch();
	void setPrevPitch(float value);

	vec3 getMotion();
	void setMotion(vec3 motion);
	int getMaxHurtResistanceTime();
	int getHurtResistanceTime();

	bool isInGameFocus();

	float getEyeHeight();

	double getX();
	double getY();
	double getZ();
	vec3 getLocation();

	double getDistanceTo(const std::shared_ptr<Player>& other);

	bool isOnGround();
	bool isInWater();
	float getHealth();

	int getItemInUseCount();
	
	bool isSprinting();
	void setSprinting(bool status = true);
	
	bool isSneaking();
	void setSneaking(bool status = true);

	int currentSlot();
private:
	Jclass m_class;
	Jobj m_playerObj;
};

typedef std::shared_ptr<Player> PlayerPtr;

inline std::unique_ptr<Player> localPlayer;

static void PlayerInit()
{
	localPlayer = std::make_unique<Player>();
}

#endif // !YUKIO_MINECRAFT_H