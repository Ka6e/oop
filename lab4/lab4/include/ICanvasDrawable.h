#pragma once
#include "../include/ICanvas.h"
#include <memory>

class ICanvasDrawable
{
public:
	virtual void Draw(std::shared_ptr<ICanvas> canvas) = 0;
	virtual ~ICanvasDrawable() = default;
};
