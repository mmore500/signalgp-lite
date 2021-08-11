Example mini-projects using SignalGP-Lite.
Several are used as solution quality benchmarks in [our JOSS Paper](../joss/paper.md).

# Boolean Calculator Problem

This program synthesis problem requires programs to perform Boolean logic computations in response to a sequence of input events that represent button presses on a simple calculator.

> Lalejini, Alexander, Matthew Andres Moreno, and Charles Ofria. "Tag-based regulation of modules in genetic programming improves context-dependent problem solving." Genetic Programming and Evolvable Machines (2021): 1-31.

# Changing Environment Problem

The Changing Environment Problem dispatches `n` mutually-exclusive environmental signals with randomly generated labels.
Programs are tasked to respond to each signal with a unique response instruction.

> Lalejini, Alexander, and Charles Ofria. "Evolving event-driven programs with SignalGP." Proceedings of the Genetic and Evolutionary Computation Conference. 2018.

# Contextual Signal Problem

The Contextual Signal Problem assesses the ability of evolving programs to maintain memory of previously encountered signals.
In previous work, this problem was used to demonstrate an important use case of regulation instructions.
To solve this problem, programs must remember an initial signal (i.e., its "context") in order to respond appropriately to a second signal.

> Lalejini, Alexander, Matthew Andres Moreno, and Charles Ofria. "Tag-based regulation of modules in genetic programming improves context-dependent problem solving." Genetic Programming and Evolvable Machines (2021): 1-31.

# Hello World

Implements a custom instruction that prints "hello world" and runs it on SignalGP-Lite virtual hardware.

# Identity

This simple demo selects for a programs with large output values.
(The fitness function is the identical of the output.)
