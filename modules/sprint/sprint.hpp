#pragma once
#ifndef YUKIO_MODULE_SPRINT_H
#define YUKIO_MODULE_SPRINT_H

#include "module.h"

class Sprint : public Module
{
private:
	bool set = false;
public:
	void onUpdate();
};

#endif // !YUKIO_MODULE_SPRINT_H