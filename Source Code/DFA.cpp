// DFA.cpp
// Kaê Angeli Coutinho

#include "DFA.h"

const int DFA::EQUAL_STRINGS = 0;
const string DFA::INVALID_DFA_EXCEPTION = "Invalid DFA";
const string DFA::INVALID_INPUT_EXCEPTION = "Invalid input";
const int DFA::NO_DELAY = 0;
const string DFA::EMPTY_WORD = "ϵ";

DFA::DFA(string name, string description, string alphabet, vector<State *> states)
{
	this->name = name;
	this->description = description;
	this->alphabet = alphabet;
	this->states = states;
	this->exceptionDescription.clear();
	this->invalidate();
}

DFA::~DFA()
{
	this->clear();
}

void DFA::invalidate()
{
	this->DFAValid = false;
	this->allTransitionsPresent = false;
}

bool DFA::isDFAValid()
{
	bool valid = true;
	if(!this->DFAValid)
	{
		State * initialState = NULL;
		this->exceptionDescription.clear();
		this->trimSymbols();
		for(int index = 0; index < this->states.size(); index++)
		{
			if(valid == true)
			{
				State * currentState = this->states[index];
				if(currentState != NULL)
				{
					currentState->removeDuplicatedTransitions();
					if(currentState->hasNondeterministicTransitions())
					{
						valid = false;
						this->exceptionDescription = "nondeterministic transitions were found";
						break;
					}
					if(initialState == NULL)
					{
						if(currentState->isInitial())
						{
							initialState = this->states[index];
						}
					}
					else
					{
						if(currentState->isInitial())
						{
							valid = false;
							this->exceptionDescription = "multiple initial states were found";
							break;
						}
					}
					for(int transitionIndex = 0; transitionIndex < currentState->getTransitions().size(); transitionIndex++)
					{
						Transition * aux = currentState->getTransitions()[transitionIndex];
						aux->trimSymbols();
						if(!this->hasState(aux->getSource()) && aux->getSource() != State::ERROR_STATE || !this->hasState(aux->getDestination()) && aux->getDestination() != State::ERROR_STATE)
						{
							valid = false;
							this->exceptionDescription = "transitions have unrelated source or destination states";
							break;
						}
						if(!this->areSymbolsInAlphabet(aux->getSymbols()))
						{
							valid = false;
							this->exceptionDescription = "transitions have symbols that do not belong to the alphabet";
							break;
						}
						if(aux->hasEmptyWord())
						{
							valid = false;
							this->exceptionDescription = "transitions have the empty word as symbol";
							break;
						}
					}
				}
				else
				{
					valid = false;
					this->exceptionDescription = "error states must not be listed in the states vector as they are only null pointers";
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	this->DFAValid = valid;
	return valid;
}

bool DFA::isInputValid(string input)
{
	return this->areSymbolsInAlphabet(input);
}

bool DFA::hasState(State * state)
{
	return find(this->states.begin(),this->states.end(),state) != this->states.end() && state != State::ERROR_STATE;
}

bool DFA::areSymbolsInAlphabet(string symbols)
{
	bool result = true;
	for(int index = 0; index < symbols.length(); index++)
	{
		if(this->alphabet.find(symbols[index]) == string::npos)
		{
			result = false;
			break;
		}
	}
	return result;
}

void DFA::trimSymbols()
{
	sort(this->alphabet.begin(),this->alphabet.end());
	this->alphabet.erase(unique(this->alphabet.begin(),this->alphabet.end()),this->alphabet.end());
}

State * DFA::getInitialState()
{
	for(int index = 0; index < this->states.size(); index++)
	{
		if(this->states[index]->isInitial())
		{
			return this->states[index];
		}
	}
}

void DFA::printPathTraceToConsole(vector<string> pathTrace, int delay)
{
	cout << "Path trace:" << endl << endl;
	for(int index = 0; index < pathTrace.size(); index++)
	{
		if(delay != DFA::NO_DELAY)
		{
			sleep(delay);
		}
		cout << "\t" << pathTrace[index] << endl;
	}
}

void DFA::printPathTraceToFile(vector<string> pathTrace, ofstream * fileToPrint)
{
	(*fileToPrint) << "Path trace:" << endl << endl;
	for(int index = 0; index < pathTrace.size(); index++)
	{
		(*fileToPrint) << "\t" << pathTrace[index] << endl;
	}
}

bool DFA::areAllTransitionsPresent()
{
	bool result = true;
	if(!this->allTransitionsPresent)
	{
		int alphabetSize = this->alphabet.length();
		for(int index = 0; index < this->states.size(); index++)
		{
			if(!this->states[index]->hasAllTransitions(this->alphabet))
			{
				result = false;
			}
		}
	}
	return result;
}

void DFA::addMissingTransitions()
{
	for(int index = 0; index < this->states.size(); index++)
	{
		if(!this->states[index]->hasAllTransitions(this->alphabet))
		{
			if(this->states[index] != State::ERROR_STATE)
			{
				this->states[index]->addMissingTransitions(this->alphabet);
			}
		}
	}
	this->allTransitionsPresent = true;
}

bool DFA::analyse(string input, bool verbose, int delay, ofstream * fileToPrint)
{
	bool valid = true, changedState;
	State * currentState = this->getInitialState(), * oldState;
	vector<string> pathTrace;
	char currentSymbol;
	Transition * currentTransition;
	ostringstream aux;
	aux << "Input: " << ((input.length() > 0) ? input : DFA::EMPTY_WORD);
	pathTrace.push_back(aux.str());
	aux.str("");
	aux << "Initialized at " << currentState->getName();
	pathTrace.push_back(aux.str());
	for(int index = 0; index < input.length(); index++)
	{
		if(valid == true)
		{
			if(currentState != State::ERROR_STATE)
			{
				aux.str("");
				currentSymbol = input[index];
				changedState = false;
				for(int transitionIndex = 0; transitionIndex < currentState->getTransitions().size(); transitionIndex++)
				{	
					currentTransition = currentState->getTransitions()[transitionIndex];
					if(currentTransition->hasSymbol(currentSymbol))
					{
						oldState = currentState;
						currentState = currentTransition->getDestination();
						if(currentState != State::ERROR_STATE)
						{
							aux << ((oldState != State::ERROR_STATE) ? oldState->getName() : State::ERROR_STATE_NAME) << " -> Read '" << currentSymbol << "' -> " << currentState->getName();
							changedState = true;
						}
						else
						{
							aux << ((oldState != State::ERROR_STATE) ? oldState->getName() : State::ERROR_STATE_NAME) << " -> Read '" << currentSymbol << "' -> " << State::ERROR_STATE_NAME;
							valid = false;
						}
						pathTrace.push_back(aux.str());
					}
					if(valid == false || changedState == true)
					{
						break;
					}
				}
			}
			else
			{
				valid = false;
			}
		}
		else
		{
			break;
		}
	}
	aux.str("");
	if(valid && currentState != State::ERROR_STATE)
	{
		if(currentState->isFinal())
		{
			aux << "Input succeeded";
		}
		else
		{
			aux << "Input failed";
			valid = false;
		}
	}
	else
	{
		aux << "Input failed";
		valid = false;
	}
	pathTrace.push_back(aux.str());
	if(verbose)
	{
		this->printPathTraceToConsole(pathTrace,delay);
	}
	if(fileToPrint != NULL)
	{
		this->printPathTraceToFile(pathTrace,fileToPrint);
	}
	return valid;
}

string DFA::getInfo()
{
	ostringstream stringStream;
	stringStream << "DFA" << endl;
	stringStream << "\t name: " << this->name << endl;
	stringStream << "\t description: " << this->description << endl;
	stringStream << "\t alphabet: " << ((this->alphabet.length() > 0) ? "{" : "{" + DFA::EMPTY_WORD + "}");
	for(int index = 0; index < this->alphabet.length(); index++)
	{
		if(index != this->alphabet.length() - 1)
		{
			stringStream << this->alphabet[index] << ",";
		}
		else
		{
			stringStream << this->alphabet[index] << "}";
		}
	}
	stringStream << endl;
	stringStream << "\t states: " << ((this->states.size() > 0) ? "{" : "none");
	for(int index = 0; index < this->states.size(); index++)
	{
		if(index != this->states.size() - 1)
		{
			stringStream << this->states[index]->getName() << ",";
		}
		else
		{
			stringStream << this->states[index]->getName() << "}";
		}
	}
	stringStream << endl;
	return stringStream.str();
}

void DFA::setName(string name)
{
	this->name = name;
	this->invalidate();
}

void DFA::setDescription(string description)
{
	this->description = description;
	this->invalidate();
}

void DFA::setAlphabet(string alphabet)
{
	this->alphabet = alphabet;
	this->invalidate();
}

void DFA::setStates(vector<State *> states)
{
	this->states = states;
	this->invalidate();
}

string DFA::getName()
{
	return this->name;
}

string DFA::getDescription()
{
	return this->description;
}

string DFA::getAlphabet()
{
	return this->alphabet;
}

vector<State *> DFA::getStates()
{
	return this->states;
}

void DFA::addState(State * state)
{
	this->states.push_back(state);
	this->invalidate();
}

bool DFA::removeState(State * state)
{
	if(state != State::ERROR_STATE)
	{
		return this->removeState(state->getName());
	}
	else
	{
		return false;
	}
}

bool DFA::removeState(string state)
{
	bool removed = false;
	for(int index = 0; index < this->states.size(); index++)
	{
		if(this->states[index]->getName().compare(state) == DFA::EQUAL_STRINGS)
		{
			this->states.erase(this->states.begin() + index);
			removed = true;
		}
	}
	if(removed)
	{
		this->invalidate();
	}
	return removed;
}

void DFA::preValidate()
{
	this->isDFAValid();
}

bool DFA::validate(string input, bool deepValidation, bool verbose, int delay, ofstream * fileToPrint)
{
	if(deepValidation)
	{
		if(this->isDFAValid())
		{
			if(this->isInputValid(input))
			{
				if(!this->areAllTransitionsPresent())
				{
					this->addMissingTransitions();
				}
				return this->analyse(input,verbose,delay,fileToPrint);
			}
			else
			{
				throw DFA::INVALID_INPUT_EXCEPTION + ": " + input;
			}
		}
		else
		{
			throw DFA::INVALID_DFA_EXCEPTION + ": " + this->exceptionDescription;
		}
	}
	else
	{
		if(this->isInputValid(input))
		{
			if(!this->areAllTransitionsPresent())
			{
				this->addMissingTransitions();
			}
			return this->analyse(input,verbose,delay,fileToPrint);			
		}
		else
		{
			throw DFA::INVALID_INPUT_EXCEPTION + ": " + input;
		}
	}
}

void DFA::clear()
{
	this->name.clear();
	this->description.clear();
	this->alphabet.clear();
	for(int index = 0; index < this->states.size(); index++)
	{
		if(this->states[index] != NULL)
		{
			delete this->states[index];
		}
	}
	this->states.clear();
	this->exceptionDescription.clear();
	this->invalidate();
}

void DFA::printInfo(ofstream * fileToPrint)
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

ostream & operator <<(ostream & output, DFA & dfa)
{
	output << dfa.getInfo();
  	return output;
}

ostream & operator <<(ostream & output, DFA * dfa)
{
	output << dfa->getInfo();
  	return output;
}