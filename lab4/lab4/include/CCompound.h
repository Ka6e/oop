#pragma once
#include <vector>
#include <memory>
#include "../include/CBody.h"

class CCompouned
{
public:
	
private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
};
