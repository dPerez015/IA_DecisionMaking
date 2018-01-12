#pragma once
#include "WorldState.h"
#include "Action.h"
#include <string>

struct GoapNode{
	WorldState state;
	Action previusAction;
	float acumulatedCost;
	GoapNode* prevNode;

	GoapNode(Action* act,float costTillNow,GoapNode* prev) {
		state = prev->state;
		previusAction.cost = act->cost;
		previusAction.definition = act->definition;
		previusAction.preConditions = act->preConditions;
		previusAction.reaction = act->reaction;
		state.applyAction(previusAction);
		//previusAction = act;
		acumulatedCost = costTillNow + previusAction.cost;
		prevNode = prev;
	}
	GoapNode(WorldState start) {
		state = start;
		//previusAction = null;
		acumulatedCost = 0;
		prevNode = nullptr;
	}

};