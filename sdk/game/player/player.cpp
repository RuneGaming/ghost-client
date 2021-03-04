#include "minecraft.hpp"
#include "player.hpp"
#include "axisaligned.hpp"
#include "settings.hpp"
#include <iostream>

Player::Player() : m_playerObj(NULL) // LocalPlayer
{
    m_class = jmy_findclassfromcl("net/minecraft/client/entity/EntityPlayerSP", mc->getClassLoader());
    update();
}

Player::Player(Jobj playerObj)
{
    m_playerObj = playerObj;
    m_class = jmy_findclassfromcl("net/minecraft/client/entity/EntityPlayerSP", mc->getClassLoader());
}

void Player::update()
{
    const char* sig = settings->misc.version.find("1.7") != std::string::npos ? "Lnet/minecraft/client/entity/EntityClientPlayerMP;" : "Lnet/minecraft/client/entity/EntityPlayerSP;";
    Jid thePlayerFID = jmy_getfieldid(mc->getMinecraftClass(), "field_71439_g", sig);
     /* 1.8 = Lnet/minecraft/client/entity/EntityPlayerSP;
     1.7 = Lnet/minecraft/client/entity/EntityClientPlayerMP;
     others mapping should works for 1.8.9 forge */
    m_playerObj = jmy_getobjfield(mc->getTheMinecraftObject(), thePlayerFID);
}

Jobj Player::getPlayerObject()
{
    return m_playerObj;
}

Jclass Player::getPlayerSpCLS()
{
    return jmy_findclassfromcl("net/minecraft/client/entity/EntityClientPlayerMP", mc->getClassLoader());
}

Jfloat Player::getPitch()
{
    return jmy_getfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70125_A", "F"));
}

void Player::setPitch(float value)
{
    jmy_setfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70125_A", "F"), value);
}

Jfloat Player::getYaw()
{
    return jmy_getfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70177_z", "F"));
}

void Player::setYaw(float value)
{
    jmy_setfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70177_z", "F"), value);
}

float Player::getPrevYaw()
{
    return jmy_getfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70126_B", "F"));
}

void Player::setPrevYaw(float value)
{
    jmy_setfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70126_B", "F"), value);
}

float Player::getPrevPitch()
{
    return jmy_getfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70127_C", "F"));
}

void Player::setPrevPitch(float value)
{
    jmy_setfloatfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70127_C", "F"), value);
}

float Player::getEyeHeight()
{
    return this->getY() + 1.62f;
}

double Player::getX()
{
    return jmy_getdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70165_t", "D"));
}

double Player::getY()
{
    return jmy_getdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70163_u", "D"));
}

double Player::getZ()
{
    return jmy_getdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70161_v", "D"));
}

vec3 Player::getLocation()
{
    return vec3{
        this->getX(),
        this->getY(),
        this->getZ(),
    };
}

double Player::getDistanceTo(const std::shared_ptr<Player>& other)
{
    return getLocation().distance(other->getLocation());
}

vec3 Player::getMotion()
{
    double X = jmy_getdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70159_w", "D")); // %age / 100.0
    double Y = jmy_getdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70181_x", "D")); // same
    double Z = jmy_getdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70179_y", "D")); // %age / 100.0

    return vec3{ X, Y, Z };
}

int Player::getMaxHurtResistanceTime()
{
    Jid max_hurt_resistant_time_fid = jmy_getfieldid(this->m_class, "field_70771_an", "I");
    int max_hurt_resistant_time = jmy_getintfield(this->m_playerObj, max_hurt_resistant_time_fid);
    return max_hurt_resistant_time;
}

int Player::getHurtResistanceTime()
{
    Jid hurt_resistant_time_fid = jmy_getfieldid(this->m_class, "field_70172_ad", "I");
    int hurt_resistant_time = jmy_getintfield(this->m_playerObj, hurt_resistant_time_fid);
    return hurt_resistant_time;
}

void Player::setMotion(vec3 motion)
{
    jmy_setdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70159_w", "D"), motion.x);
    jmy_setdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70181_x", "D"), motion.y);
    jmy_setdoublefield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70179_y", "D"), motion.z);
}

bool Player::isInGameFocus()
{
    return jmy_getboolfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_71415_G", "Z"));
}

bool Player::isOnGround()
{
    return jmy_getboolfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70122_E", "Z"));
}

bool Player::isInWater()
{
    return jmy_getboolfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_70171_ac", "Z"));
}

float Player::getHealth()
{
    /* todo */
    // field_70735_aL
    return .0f;
}

int Player::getItemInUseCount()
{
    return jmy_getintfield(this->m_playerObj, jmy_getfieldid(this->m_class, "field_71072_f", "I"));
}

bool Player::isSprinting()
{
    return jmy_getboolfield(this->m_playerObj, jmy_getfieldid(this->getPlayerSpCLS(), "field_71171_cn", "Z"));
}

void Player::setSprinting(bool status)
{
}

bool Player::isSneaking()
{
    return jmy_getboolfield(this->m_playerObj, jmy_getfieldid(this->getPlayerSpCLS(), "field_71170_cm", "Z"));
}

void Player::setSneaking(bool status)
{
}

int Player::currentSlot()
{
    return 0;
}