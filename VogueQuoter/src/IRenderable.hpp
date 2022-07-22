#pragma once
class IRenderable
{
public:
	virtual ~IRenderable() = default;
	
	virtual void Render(bool* isOpen) = 0;
};

