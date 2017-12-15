#pragma once
#include "State.h"
#include <iostream>
#include "AtBank.h"
#include "AtHome.h"
#include "AtSaloon.h"
#include "Agent.h"
#include "ScenePlanning.h"	
class AtBank;
class AtHome;
class AtSaloon;
class Agent;
class ScenePlanning;

class Mining : State{
public:
	static void Update(Agent*, ScenePlanning*);
	static void onExit(Agent*, ScenePlanning*);
	static void onEnter(Agent*, ScenePlanning*);
};

