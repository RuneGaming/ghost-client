#include "jmy/jimmy.h"
#include "player.hpp"
#include "minecraft.hpp"

#include <memory>
#include <vector>

struct _axisaligned {
	double minX, minY, minZ,
		maxX, maxY, maxZ;
};

class AxisAlignedBB
{
public:
	AxisAlignedBB();

	void update();
	Jobj getAxisObj();

private:
	Jobj m_axisObj;
};

inline std::unique_ptr<AxisAlignedBB> axisaligned;

static void AxisInit()
{
	axisaligned = std::make_unique<AxisAlignedBB>();
}