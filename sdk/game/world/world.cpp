#include "world.hpp"
#include <iostream>

World::World()
{
	update();
}

void World::update()
{
	Jid worldfid = jmy_getfieldid(mc->getMinecraftClass(), "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
	m_worldObj = jmy_getobjfield(mc->getTheMinecraftObject(), worldfid);
}

Jobj World::getWorldObject()
{
	return m_worldObj;
}

std::vector<std::shared_ptr<Player>> World::getPlayers()
{
	Jclass clazz = jmy_findclassfromcl("net/minecraft/client/multiplayer/WorldClient", mc->getClassLoader());
	Jid player_entities = jmy_getfieldid(clazz, "field_73010_i", "Ljava/util/List;");
	Jclass list_cls = jmy_findclass("java/util/List");
	
	std::vector<std::shared_ptr<Player>> res;
	Jobj obj_player_entities = jmy_getobjfield(this->m_worldObj, player_entities);

	if (!obj_player_entities)
		return res;

	Jclass arraylistcls = jmy_findclass("java/util/ArrayList");
	Jid elemsid = jmy_getfieldid(arraylistcls, "elementData", "[Ljava/lang/Object;");
	Jid sizeid = jmy_getfieldid(arraylistcls, "size", "I");

	
	int size = jmy_getintfield(obj_player_entities, sizeid);
	Jobj array = jmy_getobjfield(obj_player_entities, elemsid);
	Jobj* array_player_list = (Jobj*)malloc(size * sizeof(Jobj));
	jmy_getobjarrayelems(array, array_player_list, 0, size);

	if (!array_player_list)
		return res;

	for (int i = 0; i < size; i++)
	{
		Jobj player = array_player_list[i];
		
		if (player != localPlayer->getPlayerObject())
			res.push_back(std::make_shared<Player>(player));
	}

	free((void*)array_player_list);

	return res;
}

std::shared_ptr<Player> World::getClosestPlayer()
{
	double dist = (std::numeric_limits<double>::max)();
	std::shared_ptr<Player> target = nullptr;

	for (const auto& player : this->getPlayers())
	{
		Sleep(1);
		if (localPlayer->getDistanceTo(player) <= dist)
		{
			dist = localPlayer->getDistanceTo(player);
			target = player;
		}
	}

	return target;
}

float World::getClosestYaw(PlayerPtr clo, vec3 lclLoc)
{
	vec3 cp_pos = clo->getLocation();

	double distance = sqrt(pow(cp_pos.x - lclLoc.x, 2) + pow(cp_pos.y - lclLoc.y, 2) + pow(cp_pos.z - lclLoc.z, 2));
	double distanceX = cp_pos.x - lclLoc.x;
	double distanceZ = cp_pos.z - lclLoc.z;

	float dif = (float)atan2((float)distanceZ, (float)distanceX) * 180.00f / M_PI - 90.00f;

	dif = fmodf(dif - localPlayer->getYaw(), 360.f);
	if (dif >= 180.0f) dif -= 360.0f;
	if (dif < -180.0f) dif += 360.0f;

	return dif;
}