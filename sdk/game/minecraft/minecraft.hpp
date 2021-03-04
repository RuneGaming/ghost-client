#ifndef YUKIO_MINECRAFT_H
#define YUKIO_MINECRAFT_H

#include "jmy/jimmy.h"
#include <memory>

class Minecraft
{
public:
	Minecraft();
	void update();

	Jobj getClassLoader();
	Jclass getMinecraftClass();
	Jobj getTheMinecraftObject();

private:
	Jclass m_class;
	Jobj m_classLoader;
	Jobj m_theMinecraftObj;
};

inline std::unique_ptr<Minecraft> mc;

static void McInit()
{
	mc = std::make_unique<Minecraft>();
}

#endif // !YUKIO_MINECRAFT_H