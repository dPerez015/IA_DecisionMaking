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

	void applyAction(Action action) {
		int copyState = state.bits;
		state.bits = 0;
		int position = 1;
		for (int i = 0; i < sizeof(int) * 8; i++) {
			if (action.reaction.mask & position) {
				state.bits = state.bits | (action.reaction.bits&position);
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

	std::string makeString() {
		std::string res = "";
		if (state.bits&WorldStateVariables::AgentAlive)
			res = res + "	El agente esta vivo\n";
		else
			res = res + "	El agente esta muerto\n";
		if (state.bits&WorldStateVariables::AgentArmed)
			res = res + "	El agente tiene arma\n";
		else
			res = res + "	El agente no tiene arma\n";
		if (state.bits&WorldStateVariables::AgentHasBomb)
			res = res + "	El agente tiene un explosivo\n";
		else
			res = res + "	El agente no tiene explosivo\n";
		if (state.bits&WorldStateVariables::BombNearEnemy)
			res = res + "	Hay un explosivo cerca del enemigo\n";
		else
			res = res + "	No hay explosivo cerca del enemigo\n";
		if (state.bits&WorldStateVariables::EnemyAligned)
			res = res + "	El agente esta apuntando al enemigo\n";
		else
			res = res + "	El agente no esta apuntando al enemigo\n";
		if (state.bits&WorldStateVariables::EnemyAlive)
			res = res + "	El enemigo esta vivo\n";
		else
			res = res + "	El enemigo esta muerto\n";
		if (state.bits&WorldStateVariables::EnemyNear)
			res = res + "	El enemigo esta cerca\n";
		else
			res = res + "	El enemigo no esta cerca\n";
		if (state.bits&WorldStateVariables::EnemyVisible) 
			res = res + "	El enemigo es visible\n";
		else
			res = res + "	El enemigo no esta a la vista\n";
		if (state.bits&WorldStateVariables::WeaponCharged)
			res = res + "	El arma esta cargada\n";
		else
			res = res + "	El arma no esta cargada\n";

		return res;
	}
};