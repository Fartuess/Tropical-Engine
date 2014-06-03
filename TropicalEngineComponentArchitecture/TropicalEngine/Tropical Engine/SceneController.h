#pragma once
#include "singleton.h"
class SceneController :
	public Singleton<SceneController>
{
public:
	SceneController(void);
	~SceneController(void);
};

