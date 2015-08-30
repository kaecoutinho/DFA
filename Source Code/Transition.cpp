// Transition.cpp
// Kaê Angeli Coutinho

#include "Transition.h"
#include "State.h"
#include "DFA.h"

Transition::Transition(State * source, string symbols, State * destination)
{
	this->source = source;
	this->symbols = symbols;
	this->destination = destination;
}

Transition::~Transition()
{
	this->clear();
}

string Transition::getInfo()
{
	ostringstream stringStream;
	stringStream << "Transition" << endl;
	stringStream << "\t source: " << ((this->source != State::ERROR_STATE) ? this->source->getName() : State::ERROR_STATE_NAME) << endl;
	stringStream << "\t symbols: " << ((this->symbols.length() > 0) ? "{" : "{" + DFA::EMPTY_WORD + "}");
	for(int index = 0; index < this->symbols.length(); index++)
	{
		if(index != this->symbols.length() - 1)
		{
			stringStream << this->symbols[index] << ", ";
		}
		else
		{
			stringStream << this->symbols[index] << "}";
		}
	}
	stringStream << endl;
	stringStream << "\t destination: " << ((this->destination != State::ERROR_STATE) ? this->destination->getName() : State::ERROR_STATE_NAME) << endl;
	return stringStream.str();
}

void Transition::setSource(State * source)
{
	this->source = source;
}

void Transition::setSymbols(string symbols)
{
	this->symbols = symbols;
}

void Transition::setDestination(State * destination)
{	
	this->destination = destination;
}

State * Transition::getSource()
{
	return this->source;
}

string Transition::getSymbols()
{
	return this->symbols;
}

State * Transition::getDestination()
{
	return this->destination;
}

bool Transition::hasSymbol(char symbol)
{
	return (this->symbols.find(symbol) != string::npos);
}

bool Transition::hasSymbol(string symbol)
{
	return (this->symbols.find(symbol) != string::npos);
}

void Transition::trimSymbols()
{
	sort(this->symbols.begin(),this->symbols.end());
	this->symbols.erase(unique(this->symbols.begin(),this->symbols.end()),this->symbols.end());
}

bool Transition::hasEmptyWord()
{
	return (this->hasSymbol(DFA::EMPTY_WORD)) || (this->symbols.length() == 0);
}

void Transition::clear()
{
	this->source = (State *)State::ERROR_STATE;
	this->symbols.clear();
	this->destination = (State *)State::ERROR_STATE;
}

void Transition::printInfo(ofstream * fileToPrint)
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

ostream & operator <<(ostream & output, Transition & transition)
{
	output << transition.getInfo();
  	return output;
}

ostream & operator <<(ostream & output, Transition * transition)
{
	output << transition->getInfo();
  	return output;
}