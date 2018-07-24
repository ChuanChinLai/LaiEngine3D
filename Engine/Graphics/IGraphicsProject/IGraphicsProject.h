#pragma once

class IGraphicsProject
{
public:

	IGraphicsProject() {};
	virtual ~IGraphicsProject() {};

	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool Destroy() = 0;

private:

};