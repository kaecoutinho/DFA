// DFABuilder.cpp
// Kaê Angeli Coutinho
// MIT license

#include "DFABuilder.h"

DFABuilder::DFABuilder()
{
	this->dfa = new DFA();
}

DFABuilder::~DFABuilder()
{
	//
}

DFABuilder * DFABuilder::buildName(string name)
{
	this->dfa->setName(name);
	return this;
}

DFABuilder * DFABuilder::buildDescription(string description)
{
	this->dfa->setDescription(description);
	return this;
}

DFABuilder * DFABuilder::buildAlphabet(string alphabet)
{
	this->dfa->setAlphabet(alphabet);
	return this;
}

DFABuilder * DFABuilder::buildStates(vector<State *> states)
{
	this->dfa->setStates(states);
	return this;
}

DFABuilder * DFABuilder::buildState(State * state)
{
	this->dfa->addState(state);
	return this;
}

DFA * DFABuilder::build()
{
	return this->dfa;
}

DFA * DFABuilder::getBuildingInstance()
{
	return this->dfa;
}

DFABuilder * DFABuilder::reset(bool releaseInstance)
{
	if(releaseInstance)
	{
		this->dfa = new DFA();
	}
	else
	{
		this->dfa->clear();
	}
	return this;
}
