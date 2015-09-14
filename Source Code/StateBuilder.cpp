// StateBuilder.cpp
// Kaê Angeli Coutinho

#include "StateBuilder.h"

StateBuilder::StateBuilder()
{
	this->state = new State();
}

StateBuilder::~StateBuilder()
{
	//
}

StateBuilder * StateBuilder::buildName(string name)
{
	this->state->setName(name);
	return this;
}

StateBuilder * StateBuilder::buildInitial(bool initial)
{
	this->state->setInitial(initial);
	return this;
}

StateBuilder * StateBuilder::buildFinal(bool final)
{
	this->state->setFinal(final);
	return this;
}

StateBuilder * StateBuilder::buildTransitions(vector<Transition *> transitions)
{
	this->state->setTransitions(transitions);
	return this;
}

StateBuilder * StateBuilder::buildTransition(string symbols, State * destination)
{
	this->state->addTransition(symbols,destination);
	return this;
}

StateBuilder * StateBuilder::buildRecognitionMessage(string recognitionMessage)
{
	this->state->setRecognitionMessage(recognitionMessage);
	return this;
}

State * StateBuilder::build()
{
	return this->state;
}

State * StateBuilder::getBuildingInstance()
{
	return this->state;
}

StateBuilder * StateBuilder::reset(bool releaseInstance)
{
	if(releaseInstance)
	{
		this->state = new State();
	}
	else
	{
		this->state->clear();
	}
	return this;
}