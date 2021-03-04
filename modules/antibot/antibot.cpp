#include "antibot.hpp"
#include "player.hpp"
#include "world.hpp"

std::vector<PlayerPtr> legitList;
void AntiBOT::thread()
{
	while (true) 
	{
		for (const auto& player : world->getPlayers())
		{
			if (player->isOnGround())
				settings->antibot.legit.push_back(player); // really simple, if the entity is in the vector, it shouldn't be a bot (advanced bot should be on tho)

			// had to improve it, but i'm not a part of this community anymore :p

			Sleep(3);
		}
		Sleep(1000);
	}
	Sleep(1);
}