// DFABuilder.h
// Kaê Angeli Coutinho

#ifndef __dfa_builder__
#define __dfa_builder__

#include "DFA.h"

using namespace std;

class DFABuilder
{
	private:
		DFA * dfa;

	public:
		DFABuilder();
		~DFABuilder();
		DFABuilder * buildName(string name);
		DFABuilder * buildDescription(string description);
		DFABuilder * buildAlphabet(string alphabet);
		DFABuilder * buildStates(vector<State *> states);
		DFABuilder * buildState(State * state);
		DFA * build();
		DFA * getBuildingInstance();
		DFABuilder * reset(bool releaseInstance = false);
};

#endif