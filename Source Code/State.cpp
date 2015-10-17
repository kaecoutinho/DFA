// State.cpp
// Kaê Angeli Coutinho
// MIT license

#include "State.h"

const State * State::ERROR_STATE = NULL;
const string State::ERROR_STATE_NAME = "ERROR";
const int State::EQUAL_STRINGS = 0;

State::State(string name, bool initial, bool final, vector<Transition *> transitions, string recognitionMessage)
{
	this->name = name;
	this->initial = initial;
	this->final = final;
	this->transitions = transitions;
	this->recognitionMessage = recognitionMessage;
}

State::~State()
{
	this->clear();
}

string State::getInfo()
{
	ostringstream stringStream;
	stringStream << "State" << endl;
	stringStream << "\t name: " << this->name << endl;
	stringStream << "\t initial: " << ((this->initial) ? "yes" : "no") << endl;
	stringStream << "\t final: " << ((this->final) ? "yes" : "no") << endl;
	stringStream << "\t transitions: " << ((this->transitions.size() > 0) ? "" : "none");
	for(int index = 0; index < this->transitions.size(); index++)
	{
		if(index != this->transitions.size() - 1)
		{
			stringStream << "{" << ((this->transitions[index]->getSymbols().length() > 0) ? "{" : "none");
			for(int letterIndex = 0; letterIndex < this->transitions[index]->getSymbols().length(); letterIndex++)
			{
				if(letterIndex != this->transitions[index]->getSymbols().length() - 1)
				{
					stringStream << this->transitions[index]->getSymbols()[letterIndex] << ",";
				}
				else
				{
					stringStream << this->transitions[index]->getSymbols()[letterIndex] << "},";
				}
			}
			stringStream << ((this->transitions[index]->getDestination() != State::ERROR_STATE) ? this->transitions[index]->getDestination()->getName() : State::ERROR_STATE_NAME) << "}, ";
		}
		else
		{
			stringStream << "{" << ((this->transitions[index]->getSymbols().length() > 0) ? "{" : "none");
			for(int letterIndex = 0; letterIndex < this->transitions[index]->getSymbols().length(); letterIndex++)
			{
				if(letterIndex != this->transitions[index]->getSymbols().length() - 1)
				{
					stringStream << this->transitions[index]->getSymbols()[letterIndex] << ",";
				}
				else
				{
					stringStream << this->transitions[index]->getSymbols()[letterIndex] << "},";
				}
			}
			stringStream << ((this->transitions[index]->getDestination() != State::ERROR_STATE) ? this->transitions[index]->getDestination()->getName() : State::ERROR_STATE_NAME) << "}";
		}
	}
	stringStream << endl;
	stringStream << "\t recognitionMessage: " << this->recognitionMessage << endl;
	return stringStream.str();
}

void State::setName(string name)
{
	this->name = name;
}

void State::setInitial(bool initial)
{
	this->initial = initial;
}

void State::setFinal(bool final)
{
	this->final = final;
}

void State::setTransitions(vector<Transition *> transitions)
{
	this->transitions = transitions;
}

void State::setRecognitionMessage(string recognitionMessage)
{
	this->recognitionMessage = recognitionMessage;
}

string State::getName()
{
	return this->name;
}

bool State::isInitial()
{
	return this->initial;
}

bool State::isFinal()
{
	return this->final;
}

vector<Transition *> State::getTransitions()
{
	return this->transitions;
}

string State::getRecognitionMessage()
{
	return this->recognitionMessage;
}

void State::addTransition(string symbols, State * destination)
{
	this->addTransition(new Transition(this,symbols,destination));
}

void State::addTransition(Transition * transition)
{
	this->transitions.push_back(transition);
}

bool State::removeTransition(State * destination)
{
	if(destination != ERROR_STATE)
	{
		return this->removeTransition(destination->getName());
	}
	else
	{
		return this->removeTransition(ERROR_STATE_NAME);
	}
}

bool State::removeTransition(string destination)
{
	bool result = false;
	for(int index = 0; index < this->transitions.size(); index++)
	{
		if(this->transitions[index]->getDestination()->getName().compare(destination) == State::EQUAL_STRINGS)
		{
			this->transitions.erase(this->transitions.begin() + index);
			result = true;
			break;
		}
	}
	return result;
}

bool State::removeTransition(Transition * transition)
{
	bool result = false;
	for(int index = 0; index < this->transitions.size(); index++)
	{
		if(this->transitions[index] == transition)
		{
			this->transitions.erase(this->transitions.begin() + index);
			result = true;
			break;
		}
	}
	return result;
}

bool State::hasAllTransitions(string alphabet)
{
	bool result = true;
	int alphabetSize = alphabet.length();
	if(this->transitions.size() != alphabetSize)
	{
		int counter = 0;
		for(int index = 0; index < this->transitions.size(); index++)
		{
			counter += this->transitions[index]->getSymbols().size();
		}
		if(counter != alphabetSize)
		{
			result = false;
		}
	}
	return result;
}

void State::addMissingTransitions(string alphabet)
{
	int alphabetSize = alphabet.size();
	string usedSymbols, missingSymbols;
	missingSymbols = alphabet;
	for(int index = 0; index < this->transitions.size(); index++)
	{
		Transition * currentTransition = this->transitions[index];
		usedSymbols += currentTransition->getSymbols();
	}
	for(int index = 0; index < usedSymbols.length(); index++)
	{
		missingSymbols.erase(remove(missingSymbols.begin(),missingSymbols.end(),usedSymbols[index]),missingSymbols.end());
	}
	this->addTransition(missingSymbols,(State *)State::ERROR_STATE);
}

void State::removeDuplicatedTransitions()
{
	int dynamicSize = this->transitions.size();
	for(int index = 0; index < dynamicSize; index++)
	{
		Transition * currentTransition = this->transitions[index];
		for(int repeater = 0; repeater < dynamicSize; repeater++)
		{
			if(repeater != index)
			{
				if(currentTransition->getDestination() == this->transitions[repeater]->getDestination())
				{
					currentTransition->setSymbols(currentTransition->getSymbols() + this->transitions[repeater]->getSymbols());
					currentTransition->trimSymbols();
					if(this->removeTransition(this->transitions[index]))
					{
						dynamicSize--;
					}
				}
			}
		}
	}
}

bool State::hasNondeterministicTransitions()
{
	bool result = false;
	for(int index = 0; index < this->transitions.size(); index++)
	{
		if(!result)
		{
			Transition * currentTransition = this->transitions[index];
			for(int repeater = 0; repeater < this->transitions.size(); repeater++)
			{
				if(result)
				{
					if(repeater != index)
					{
						if((currentTransition->getDestination() != this->transitions[repeater]->getDestination())
							&& (currentTransition->getSource() == this->transitions[repeater]->getSource()))
						{
							for(int symbol = 0; symbol < currentTransition->getSymbols().length(); symbol++)
							{
								char currentSymbol = currentTransition->getSymbols()[symbol];
								if(this->transitions[repeater]->getSymbols().find(currentSymbol) != string::npos)
								{
									result = true;
									break;
								}
							}
						}
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return result;
}

void State::clear()
{
	this->name.clear();
	this->initial = false;
	this->final = false;
	for(int index = 0; index < this->transitions.size(); index++)
	{
		if(this->transitions[index] != NULL)
		{
			delete this->transitions[index];
		}
	}
	this->transitions.clear();
	this->recognitionMessage.clear();
}

void State::printInfo(ofstream * fileToPrint)
{
	string info = this->getInfo();
	if(fileToPrint == NULL)
	{
		cout << info;
	}
	else
	{
		(*fileToPrint) << info;
	}
}

ostream & operator <<(ostream & output, State & state)
{
	output << state.getInfo();
  	return output;
}

ostream & operator <<(ostream & output, State * state)
{
	output << state->getInfo();
  	return output;
}
