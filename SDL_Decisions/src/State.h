#pragma once
class Agent;
class ScenePlanning;
class State {
	virtual void Update(Agent*, ScenePlanning*) = 0;
	virtual void onExit(Agent*, ScenePlanning*) = 0;
	virtual void onEnter(Agent*, ScenePlanning*) = 0;
};

