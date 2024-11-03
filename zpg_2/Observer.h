#pragma once
#include "Subject.h"
class Subject;
class Observer
{
	virtual void update(Subject* subject) = 0;
};

