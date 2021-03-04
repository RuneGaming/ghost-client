#include "jmy/jimmy.h"
#include "player.hpp"
#include "minecraft.hpp"

#include <memory>
#include <vector>

class World
{
public:
	World();

	void update();
	Jobj getWorldObject();

	std::vector<std::shared_ptr<Player>> getPlayers();
	std::shared_ptr<Player> getClosestPlayer();
	float getClosestYaw(PlayerPtr clo, vec3 lclLoc);

private:
	Jobj m_worldObj;
};

inline std::unique_ptr<World> world;

static void WorldInit()
{
	world = std::make_unique<World>();
}