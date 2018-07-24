#pragma once

class IGraphicsTopic
{
public:
	
	IGraphicsTopic() {};
	virtual ~IGraphicsTopic() {};

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool Destroy() = 0;

private:

};