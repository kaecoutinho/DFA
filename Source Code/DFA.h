// DFA.h
// Kaê Angeli Coutinho

#ifndef __dfa__
#define __dfa__

#include <unistd.h>
#include <cstdio>
#include "State.h"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

typedef struct DFAValidationResult
{
	bool valid;
	State * currentState;				
}
DFAValidationResult;

void initializeDFAValidationResult(DFAValidationResult & dfaValidationResult);
void destroyDFAValidationResult(DFAValidationResult & dfaValidationResult);
void setValidToDFAValidationResult(DFAValidationResult & dfaValidationResult, bool valid);
void setCurrentStateToDFAValidationResult(DFAValidationResult & dfaValidationResult, State * state);
bool getValidFromDFAValidationResult(DFAValidationResult & dfaValidationResult);
State * getCurrentStateFromDFAValidationResult(DFAValidationResult & dfaValidationResult);

class DFA
{
	private:
		static const int EQUAL_STRINGS;
		static const string INVALID_DFA_EXCEPTION;
		static const string INVALID_INPUT_EXCEPTION;
		static const string INVALID_JSON_MODEL_EXCEPTION;
		string name;
		string description;
		string alphabet;
		vector<State *> states;
		string exceptionDescription;
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
		DFAValidationResult analyse(string input, bool verbose, int delay, ofstream * fileToPrint);
		string getInfo();
		void parseJSONFile(ifstream & dfaModelFile);
		State * findState(State * state);
		State * findState(string name);

	public:
		static const int NO_DELAY;
		static const string EMPTY_WORD;
		DFA(string name = "Nameless DFA", string description = "No description", string alphabet = "", vector<State *> states = vector<State *>());
		DFA(ifstream & dfaJSONModelFile);
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
		DFAValidationResult validate(string input, bool deepValidation = true, bool verbose = false, int delay = DFA::NO_DELAY, ofstream * fileToPrint = NULL);
		void clear();
		void printInfo(ofstream * fileToPrint = NULL);
		friend ostream & operator <<(ostream & output, DFA & dfa);
		friend ostream & operator <<(ostream & output, DFA * dfa);
};

#endif