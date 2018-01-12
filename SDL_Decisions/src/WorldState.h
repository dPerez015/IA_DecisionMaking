#pragma once
#include "WorldStateVariables.h"

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
};