
#include <iostream>
#include<ChcocGL.h>

class SandBox:public ChocoGL::Application
{
public:
	SandBox();
	~SandBox();

private:

};

SandBox::SandBox()
{
}

SandBox::~SandBox()
{
}

ChocoGL::Application* ChocoGL::CreatApplication() {
	return new SandBox();
}

