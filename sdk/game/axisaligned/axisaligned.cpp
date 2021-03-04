#include "axisaligned.hpp"

AxisAlignedBB::AxisAlignedBB() : m_axisObj(NULL)
{
	update();
}

void AxisAlignedBB::update()
{
}

Jobj AxisAlignedBB::getAxisObj()
{
	return m_axisObj;
}
