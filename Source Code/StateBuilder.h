// StateBuilder.h
// Kaê Angeli Coutinho

#ifndef __state_builder__
#define __state_builder__

#include "State.h"

using namespace std;

class StateBuilder
{
	private:
		State * state;

	public:
		StateBuilder();
		~StateBuilder();
		StateBuilder * buildName(string name);
		StateBuilder * buildInitial(bool initial);
		StateBuilder * buildFinal(bool final);
		StateBuilder * buildTransitions(vector<Transition *> transitions);
		StateBuilder * buildTransition(string symbols, State * destination);
		State * build();
		State * getBuildingInstance();
		StateBuilder * reset(bool releaseInstance = false);
};

#endif