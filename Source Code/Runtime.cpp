// Runtime.cpp
// Kaê Angeli Coutinho

#include "DFA.h"
#include "State.h"
#include "DFABuilder.h"
#include "StateBuilder.h"
#define INPUT_QUANTITY 7
#define FILE_NAME "Results.txt"

using namespace std;

// Application lifecicle (runtime)

int main(int argc, char ** argv)
{
	DFA * dfa;
	DFABuilder dfaBuilder;
	StateBuilder builderQ0, builderQ1, builderQ2;
	ofstream * file = new ofstream(FILE_NAME,ios::out);

	builderQ2
		.buildName("q2")
		->buildRecognitionMessage("recognized regex of type (a)⁺b")
		->buildFinal(true);

	builderQ1
		.buildName("q1")
		->buildRecognitionMessage("recognition failed")
		->buildTransition("a",builderQ1.getBuildingInstance())
		->buildTransition("b",builderQ2.getBuildingInstance());

	builderQ0
		.buildName("q0")
		->buildRecognitionMessage("recognition failed")
		->buildInitial(true)
		->buildTransition("a",builderQ1.getBuildingInstance());

	dfaBuilder
		.buildName("M")
		->buildDescription("recognizes the following regex: (a)⁺b")
		->buildAlphabet("ab")
		->buildState(builderQ0.build())
		->buildState(builderQ1.build())
		->buildState(builderQ2.build());

	dfa = dfaBuilder.build();

	string inputs[INPUT_QUANTITY] = {"aaa","aab","aaba","aabb","","baa","b"};

	for(int index = 0; index < INPUT_QUANTITY; index++)
	{
		try
		{
			if(index == 0)
			{
				dfa->printInfo(file);
				(*file) << endl;
			}
			DFAValidationResult result = dfa->validate(inputs[index],true,true,DFA::NO_DELAY,file);
			cout << endl << "\tValid: ";
			if(getValidFromDFAValidationResult(result))
			{
				cout << "true";
			}
			else
			{
				cout << "false";
			}
			cout << endl;
			cout << "\tCurrent state: " << ((getCurrentStateFromDFAValidationResult(result) != State::ERROR_STATE) ? getCurrentStateFromDFAValidationResult(result)->getName() : State::ERROR_STATE_NAME);
			cout << endl << endl;
			destroyDFAValidationResult(result);
		}
		catch(const string exception)
		{
			cout << exception << endl;
		}
		catch(const char * exception)
		{
			cout << exception << endl;
		}
	}

	delete dfa;
	delete file;

	return EXIT_SUCCESS;
}