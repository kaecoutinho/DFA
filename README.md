# DFA

**DFA**'s repository

Created by Kaê Angeli Coutinho

## Introduction

**DFA** is a deterministic finite automaton (DFA) (regular languages (T3) recognizer) _C++_ library that makes it possible to define and evaluate dfa models easily.

## Usage

#### Building a deterministic finite automaton

Let's say we want to create a dfa that's capable of recognizing the following pattern / regex: "_(a)⁺b_".

Using builders, we would have something that looks like the following.

```
DFA * dfa;
StateBuilder builderQ0, builderQ1, builderQ2;

builderQ2.buildName("q2")
		->buildFinal(true);

	builderQ1
		.buildName("q1")
		->buildTransition("a",builderQ1.getBuildingInstance())
		->buildTransition("b",builderQ2.getBuildingInstance());

	builderQ0
		.buildName("q0")
		->buildInitial(true)
		->buildTransition("a",builderQ1.getBuildingInstance());

	dfa = DFABuilder()
			.buildName("M")
			->buildDescription("Recognizes the following regex: (a)⁺b")
			->buildAlphabet("ab")
			->buildState(builderQ0.build())
			->buildState(builderQ1.build())
			->buildState(builderQ2.build())
			->build();
```

Simple as that, we have a ready-to-go dfa model.

You could also build the dfa without using the builder, which is not recommended.

Now we want to evaluate that model using a provided input such as: "_aab_".

```
try
{
	if(dfa->validate("aab"))
  {
    cout << "Valid input" << endl;
  }
  else
  {
    cout << "Invalid input" << endl;
  }
}
catch(const char * exception)
{
	cout << exception << endl;
}
```

There we go, a fully working dfa that validates any input provided.

There's also a example file provided in the project folder called **Runtime.cpp**, showing more options and class methods that could be used.

## Changelog

#### Version 1.0

<ul>
  <li>Raw DFA library</li>
  <li>Class builders</li>
  <li>DFA deep validation</li>
</ul>