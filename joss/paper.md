---
title: 'signalgp-lite: Event Driven Genetic Programming Library for Large-Scale Artificial Life Applications'
tags:
  - C++
  - artificial life
  - genetic programming
  - event driven
authors:
  - name: Matthew Andres Moreno
    orcid: 0000-0003-4726-4479
    affiliation: 1
  - name: Santiago Rodriguez Papa
    orcid: 0000-0002-6028-2105
    affiliation: 1
affiliations:
 - name: Michigan State University
   index: 1
date: 31 May 2021
bibliography: paper.bib
---

# Abstract

Event-driven genetic representations have been shown to outperform traditional traditional imperative representations on interaction-heavy problems.
Most existing work uses the SignalGP library.
This library caters to traditional program synthesis applications.
However, large-scale artificial life applications have a different set of implementation priorities.
SignalGP is an existing implementation that is focused on extending tag-based referencing by applying event-driven techiques to genetic programming.
With signalgp-lite, our goal is to provide a performance increase in large-scale experiments, such as those undertaken in Artificial Life.
By removing control-flow overhead (e.g., the call stack) and trading run-time flexibility for better-performing compile-time configuration, we achieved an 8x to 30x speedup.
`signalgp-lite` is unit- and integration-tested, achieving equivalent solution quality on two benchmark problems originally developed for SignalGP.
The library is currently used in DISHTNY, and our expectation is that it will be useful in future Artifical Life and Genetic Programming projects.

# Summary

`signalgp-lite` is a genetic programming framework that allows for an event-based development paradigm.
Compared to the traditional imperative paradigm, event-driven simulations trigger event-handlers (i.e., modules) in response to enviromental and inter-programmatic signals.
This representation has been shown to outperform imperative programming on certain problems, such as those in which many interactions with the enviroment or other organisms occur. [cite]
One example of such situation is the case of a large-scale digital evolution experiment, as well as various other artifical life simulations.
In light of the above, `signalgp-lite` is the framework of choice in DISHTINY.

`signalgp-lite` is written in C++.
It was chosen due to its low-level control over runtime performance.
C++ is the language of choice for many artificial life and genetic programming utilities.

# Statement of need

`signalgp-lite` fills a niche for event-driven applications that do not require a high level of customizability at runtime, but instead benefit from a considerable speed-up.
Despite being able to simulate evolution at generation rates that greately exceed real-life experiements, the scale of artifical life simulations is profoundly limited by available computational resources.
A large population size is required to study ecological effects, the transition to multicelularity, and the role of rare events in evolution.
Our genetic programming framework allows for a considerable speedup, allowing users to perform larger-scale artificial life situations.

# Replication Results

Since `signalgp-lite` is intended to be a replacement for the original SignalGP in artifical life situations, it is important to quantitatively determine how accurately it can replicate its results.
Two experiments from the original SignalGP paper were replicated [1].

## Changing Enviroment Problem

The Changing Enviroment Problem consisted of K enviromental signals (2, 4, 8, 16) that organisms had to learn to respond to with a unique signaling instruction.

\autoref{fig:tts-context} shows the number of generations before a full solution was found.
`signalgp-lite` evolved fill solutions to each problem within XX updates in all YY tested replicates.

In the `K=16` case, we achieved a 100% signal reproduction rate compared to an average of 32% on the vanilla implementation  [figure X cited in Alex's paper].
We suspect this occured due to differences in how default mutation parameters and program initialization are defined across both libraries.

## Contextual Signal Problem

This problem tests regulation by evolving programs that must respond differently depending on what signal they previously encountered.
A total of 16 input signal pairs and 4 response signals were tested.
The unordered input signal pairs were assigned a response signal that then had to be replicated by the organism.
You can refer to table 2 in the original SignalGP problem for a visual representation of this sequence. [cite it]

TODO: explain how `signalgp-lite` compared in this problem.

## Benchmarking Results

The main goal of this library is to accelerate execution of event-driven genetic programs for more rapid evaluation.
As such, benchmarking is essential to determining whether `signalgp-lite`'s optimizations work as intended.

Cache size limitations profoundly affect memory access time [cite?], which is key to performance [cite?].
In order to determine how the libary performs at different caching levels, benchmarks were performed over a variety of memory usages.
We altered memory usage via the different agent counts.
\autoref{fig:bench-wall} shows wall-clock times measured using Google Benchmark version x.y.z.

Each of the five treatments serve a different purpose.

### `control`

The control ensures our benchmarking process is valid.
While there is some uncertainty inherent to the benchmarking enviroment, the near-zero wall speedup means that our results are not directly affected by the chosen library, and that any resulting difference will stem from implementation choices.
As such, our analysis can be considered fair.

### `NOP`

Benchmarking the NOP instruction alone isolates the performance impact of executing `signalgp-lite`'s byte-code interpreter compared to SignalGP's lamda-based instructions.
We observe a 10 to 30 times speedup based on this change.

### `arithmetic`

The arithmetic benchmark adds to the prior improvements the performance effect of `signalgp-lite`'s registers being fixed-length arrays compared to SignalGP variable-length vectors. [TODO: FIX THIS SENTENCE]
This compares the effects of compile-time optimizations versus the runtime flexibility of being able to change the number of registers on the fly.
This trade-off results in a 20 to 50 times speed-up.

### `complete`

In order to improve performance compared to SignalGP, `signalgp-lite` lacks a function stack and implements inner while-loops in terms of `JUMP` instructions.
Since a paramount part of benchmarking `signalgp-lite` involves the complex control flow that occurs within and in-between modules, we wanted to test these changes both with and without regulation.
Performance can be affected by enabling regulation because tag-matching causes caching to underperform.

The complete benchmark adds tag matching and complex control flow to the prior benchmarks' instruction set.
Tag-based referencing is used to toggle module activation.
This in turn allows for complex regulation mechanics and control flow.
Given the striped-down control flow of `signalgp-lite`'s instructions, we can observe a 30 to 55 times speed-up compared to the vanilla SignalGP lambda-based operators.

### `sans_regulation`

Finally, sans_regulation measures the previous instruction set without regulation-specific instructions ([list them here]).
This introduces a 35 to 47 times speedup.
We can conclude that `signalgp-lite` offers significant performance improvements even on simulations that do not heavily depend on regulation.

# Experimental Materials

Citations to entries in paper.bib should be in
[rMarkdown](http://rmarkdown.rstudio.com/authoring_bibliographies_and_citations.html)
format.

If you want to cite a software repository URL (e.g. something on GitHub without a preferred
citation) then you can do it with the example BibTeX entry below for @fidgit.

<!-- For a quick reference, the following citation commands can be used:
- `@author:2001`  ->  "Author et al. (2001)"
- `[@author:2001]` -> "(Author et al., 2001)"
- `[@author1:2001; @author2:2001]` -> "(Author1 et al., 2001; Author2 et al., 2002)" -->

# Figures

<!-- Figures can be included like this:
![Caption for example figure.\label{fig:example}](figure.png)
and referenced from text using \autoref{fig:example}.

Figure sizes can be customized by adding an optional second parameter:
![Caption for example figure.](figure.png){ width=20% } -->

![Number of generations elapsed before a perfect solution was observed on the Changing Enviroment problem.\label{fig:tts-changing}](figures/solution-time-swarmplot.png)

![Number of generations elapsed before a perfect solution was observed on the Contextual Signal problem.\label{fig:tts-context}](figures/solution-time-contextual-signal.png)

<!-- benchmarking results -->

![Benchmarking results of 20 replicates shown as a times-speedup of wall time. "Library" refers to the set of instructions tested (see Benchmarking Results section).\label{fig:bench-wall}](figures/wall-time-speedup.jpeg)


# Acknowledgements

We acknowledge contributions from Brigitta Sipocz, Syrtis Major, and Semyeong
Oh, and support from Kathryn Johnston during the genesis of this project.

# References

\pagebreak
\appendix

# Supplementary Material

![Maximum fitness wrt. updates, with standard deviation confidence intervals. This is because, due to large number of datapoints, computing 95% CI takes a non-insignificant amount of time.\label{fig:max-fitness-sd}](figures/max-fitness-sd.png)

![Filtered maximum fitness wrt. updates, with 95% confidence intervals. Data has been filtered logarithmically.\label{fig:max-fitness-sd}](figures/max-fitness-log2.png)
