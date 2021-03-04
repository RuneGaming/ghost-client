#include "aimassist.hpp"
#include "player.hpp"
#include "world.hpp"
#include <future>

PlayerPtr lastTarget, target = nullptr;
DWORD timer;

vec3 target_pos, my_pos = { 0, 0, 0 };
float lastClosestYaw;

void AimAssist::thread() // I release the aim assist cuze I had to rewrite it because it was poorly coded and made. (still bypass AC's checks tho)
{	
	timer = GetTickCount64();
	while (true) 
	{
		Sleep(1);
		if (localPlayer->getPlayerObject() && world->getWorldObject())
		{
			PlayerPtr closestplayer = target;
			if ((GetTickCount() - timer) >= 20)
			{
				if (closestplayer == nullptr)
				{
					target = world->getClosestPlayer();
				}
				else if (localPlayer->getDistanceTo(closestplayer) >= settings->aimassist.dist)
				{
					target = world->getClosestPlayer();
				}
			}

			if (closestplayer != nullptr)
			{
				if (localPlayer->getDistanceTo(closestplayer) <= settings->aimassist.dist)
				{
					if ((GetTickCount() - timer) >= 20)
					{
						target_pos = closestplayer->getLocation();
						target_pos.y += (target_pos.y + 1.62) / 2;
						my_pos = localPlayer->getLocation();
					}

					float my_yaw = localPlayer->getYaw();
					float my_pitch = localPlayer->getPitch();

					auto angles = my_pos.getAngles(target_pos);
					auto fovyaw = wrapTo180(-(my_yaw - angles.first));
					auto fovpitch = wrapTo180(-(my_pitch - angles.second));

					if (abs(wrapTo180(-(my_yaw - angles.first))) <= settings->aimassist.fov /*fov*/)
					{
						my_yaw += (fovyaw / (100 - (((settings->aimassist.speed/*speed*/ / 10) - 1) * 10)));

						localPlayer->setYaw(my_yaw);
						Sleep(1);
						localPlayer->setPrevYaw(my_yaw);

						if ((GetTickCount() - timer) >= 20)
							lastClosestYaw = abs(world->getClosestYaw(closestplayer, my_pos));

						if (lastClosestYaw <= 15.0f && lastClosestYaw >= 5.0f)
						{
							localPlayer->setPitch(my_pitch - fRand(0.009, 0.08));
						}
					}
				}
			}
		}

		if ((GetTickCount() - timer) >= 20)
			timer = GetTickCount64();

		Sleep(1);
	}
}
