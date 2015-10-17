// Transition.h
// Kaê Angeli Coutinho
// MIT license

#ifndef __transition__
#define __transition__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class State;

class Transition
{
	private:
		State * source;
		string symbols;
		State * destination;
		string getInfo();

	public:
		Transition(State * source = NULL, string symbols = "", State * destination = NULL);
		~Transition();
		void setSource(State * source);
		void setSymbols(string symbols);
		void setDestination(State * destination);
		State * getSource();
		string getSymbols();
		State * getDestination();
		bool hasSymbol(char symbol);
		bool hasSymbol(string symbol);
		void trimSymbols();
		bool hasEmptyWord();
		void clear();
		void printInfo(ofstream * fileToPrint = NULL);
		friend ostream & operator <<(ostream & output, Transition & transition);
		friend ostream & operator <<(ostream & output, Transition * transition);
};

#endif
