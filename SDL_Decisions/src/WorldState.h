#pragma once
#include "WorldStateVariables.h"
#include "Action.h"

struct WorldState {
	MaskedBitArray state;
	void add(int position, bool value) {
		state.add(position, value);
	}
	bool checkEqualsMasked(WorldState otherState) {
		int position = 1;
		//sizeof(int)*8 = numero de bits de la mantisa
		for (int i = 0; i < sizeof(int) * 8; i++) {
			if (state.mask | position) {
				if ((state.bits | (otherState.state.bits | position)) == 0) {
					return false;
				}
			}
			position *= 2;
		}
		return true;
	}
	bool checkEquals(WorldState otherState) {
		return state.bits == otherState.state.bits;
	}

	void applyAction(Action* action) {
		int copyState = state.bits;
		state.bits = 0;
		int position = 1;
		for (int i = 0; i < sizeof(int) * 8; i++) {
			if (action->reaction.mask & position) {
				state.bits = state.bits | (action->reaction.bits&position);
			}
			else {
				state.bits = state.bits | (copyState & position);
			}
			position*=2;
		}
	}

	bool checkAction(Action* action) {
		int position = 1;
		for (int i = 0; i < sizeof(int) * 8; i++) {
			if (action->preConditions.mask & position) {
				if ((action->preConditions.bits & position) != (state.bits & position)) {
					return false;
				}
			}
			position *= 2;
		}
		return true;
	}
};