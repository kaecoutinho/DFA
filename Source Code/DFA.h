// DFA.h
// Kaê Angeli Coutinho

#ifndef __dfa__
#define __dfa__

#include <unistd.h>
#include "State.h"

using namespace std;

class DFA
{
	private:
		static const int EQUAL_STRINGS;
		static const string INVALID_DFA_EXCEPTION;
		static const string INVALID_INPUT_EXCEPTION;
		string name;
		string description;
		string alphabet;
		vector<State *> states;
		bool DFAValid;
		bool allTransitionsPresent;
		void invalidate();
		bool isDFAValid();
		bool isInputValid(string input);
		bool hasState(State * state);
		bool areSymbolsInAlphabet(string symbols);
		void trimSymbols();
		State * getInitialState();
		void printPathTraceToConsole(vector<string> pathTrace, int delay);
		void printPathTraceToFile(vector<string> pathTrace, ofstream * fileToPrint);
		bool areAllTransitionsPresent();
		void addMissingTransitions();
		bool analyse(string input, bool verbose, int delay, ofstream * fileToPrint);
		string getInfo();

	public:
		static const int NO_DELAY;
		static const string EMPTY_WORD;
		DFA(string name = "Nameless DFA", string description = "No description", string alphabet = "", vector<State *> states = vector<State *>());
		~DFA();
		void setName(string name);
		void setDescription(string description);
		void setAlphabet(string alphabet);
		void setStates(vector<State *> states);
		string getName();
		string getDescription();
		vector<State *> getStates();
		string getAlphabet();
		void addState(State * state);
		bool removeState(State * state);
		bool removeState(string name);
		void preValidate();
		bool validate(string input, bool deepValidation = true, bool verbose = false, int delay = DFA::NO_DELAY, ofstream * fileToPrint = NULL);
		void clear();
		void printInfo(ofstream * fileToPrint = NULL);
		friend ostream & operator <<(ostream & output, DFA & dfa);
		friend ostream & operator <<(ostream & output, DFA * dfa);
};

#endif