#pragma once
#include "WorldState.h"
#include "Action.h"
#include <string>

struct GoapNode{
	WorldState state;
	Action* previusAction;
	float acumulatedCost;
	GoapNode* prevNode;

	GoapNode(Action* act,float costTillNow,GoapNode* prev) {
		state = prev->state;
		state.applyAction(act);
		previusAction = act;
		acumulatedCost = costTillNow + act->cost;
		prevNode = prev;
	}

};