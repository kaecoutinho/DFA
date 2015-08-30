// State.h
// Kaê Angeli Coutinho

#ifndef __state__
#define __state__

#include <vector>
#include "Transition.h"

using namespace std;

class State
{
	private:
		static const int EQUAL_STRINGS;
		string name;
		bool initial;
		bool final;
		vector<Transition *> transitions;
		string getInfo();

	public:
		static const State * ERROR_STATE;
		static const string ERROR_STATE_NAME;
		State(string name = "Nameless state", bool initial = false, bool final = false, vector<Transition *> transitions = vector<Transition *>());
		~State();
		void setName(string name);
		void setInitial(bool initial);
		void setFinal(bool final);
		void setTransitions(vector<Transition *> transitions);
		string getName();
		bool isInitial();
		bool isFinal();
		vector<Transition *> getTransitions();
		void addTransition(string symbols, State * destination);
		bool removeTransition(State * destination);
		bool removeTransition(string destination);
		bool removeTransition(Transition * transition);
		bool hasAllTransitions(string alphabet);
		void addMissingTransitions(string alphabet);
		void removeDuplicatedTransitions();
		bool hasNondeterministicTransitions();
		void clear();
		void printInfo(ofstream * fileToPrint = NULL);
		friend ostream & operator <<(ostream & output, State & state);
		friend ostream & operator <<(ostream & output, State * state);
};

#endif