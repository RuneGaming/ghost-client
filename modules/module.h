#pragma once
#ifndef YUKIO_MODULE_H
#define YUKIO_MODULE_H


#include <memory>
#include <vector>

class Module
{
public:
	virtual void onUpdate() = 0;
};

inline std::vector<std::unique_ptr<Module>> modules;

#endif // !YUKIO_MODULE_H