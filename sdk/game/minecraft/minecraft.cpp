#include "minecraft.hpp"

Minecraft::Minecraft()
{
	this->update();
}

void Minecraft::update()
{
	Jclass launchcls = jmy_findclass("net/minecraft/launchwrapper/Launch");
	Jid classLoaderFID = jmy_getfieldid(launchcls, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");

	m_classLoader = jmy_getstaticobjfield(launchcls, classLoaderFID);
	m_class = jmy_findclassfromcl("net/minecraft/client/Minecraft", m_classLoader);

	Jid theMinecraftFID = jmy_getfieldid(m_class, "field_71432_P", "Lnet/minecraft/client/Minecraft;");
	m_theMinecraftObj = jmy_getstaticobjfield(m_class, theMinecraftFID);
}

Jobj Minecraft::getClassLoader()
{
	return this->m_classLoader;
}

Jclass Minecraft::getMinecraftClass()
{
	return this->m_class;
}

Jobj Minecraft::getTheMinecraftObject()
{
	return this->m_theMinecraftObj;
}