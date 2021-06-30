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

Event-driven genetic programming representations have been shown to outperform traditional traditional imperative representations on interaction-heavy problems.
Existing work uses the SignalGP library, which caters to traditional program synthesis applications.
However, large-scale artificial life applications require a different set of implementation priorities.
SignalGP is an existing implementation that is focused on extending tag-based referencing by applying event-driven techiques to genetic programming.
With signalgp-lite, our goal is to increase performance to enable large-scale experiments, such as those undertaken in Artificial Life, by removing control-flow overhead (e.g., the call stack) and trading run-time flexibility for better-performing compile-time configuration.
Here, we report benchmarking experiments that show an 8x to 30x speedup.
We also report solution quality equivalent to SignalGP on two benchmark problems originally developed for that implementation.
The library is currently used in Artificial Life experiments studying the evolution of multicelularity, and our expectation is that it will be useful in future Artifical Life and Genetic Programming projects.

# Summary

`signalgp-lite` is a software framework for event-driven genetic programming.
Unlike the traditional imperative paradigm, event-driven simulations trigger event-handlers (i.e., program modules) in response to enviromental, self-generated, and cohabitant-generated signals.
This representation outperforms imperative programming on interaction intensive problems, where inputs from the enviroment or other organisms ocmust be handled [cite], as is the case in large-scale digital evolution experiments as well as various other artifical life simulations.

`signalgp-lite` is written in C++.
It was chosen due to its low-level control over runtime performance.
C++ is the language of choice for many artificial life and genetic programming utilities.

# Statement of need

Despite being able to simulate evolution with faster generations than possible in biological experiements [cite avida paper], the scale of artifical life populations is profoundly limited by available computational resources [cite blog].
Large population sizes are essential to studying essential topics such as ecologies, the transition to multicelularity, and the role of rare events in evolution.
Also, parallel and distributed computing resources are ultimately key to increasing scale. [join these] Computational efficiency is crucial to enabling larger-scale artificial life situations.]

[add transition] `signalgp-lite` fills a niche for interaction-heavy genetic programming applications that can tolerate trading a high level of customizability at runtime for a considerable speed-up.


## Execution Speed

To accelerating execution of event-driven genetic programs. [????]
We performed a set of microbenchmarks to quantify the effectiveness of `signalgp-lite`'s optimizations.
Cache size limitations profoundly affect memory access time, which is key to performance @skadron1999branch.
In order to determine how the libary performs across cache levels, we benchmarked over different orders of magnitude of memory loads, by varying agent counts between from 1 and 32768. [addfig](raw timings)
\autoref{fig:bench-wall} shows wall-clock times measured using Google Benchmark version 1.5.2-1.

We performed five microbenchmark experiments, overviewed below, in order to understand how different aspects of the library influenced performance.

### control

This experiemnt verifies the validity of our benchmarking process.
The 1x wall speedup (\autoref{fig:bench-wall}) confirms that our results are not directly affected by the experimental aparatus, so that any speedups in other experiments stem solely from differences between SignalGP and `signalgp-lite`.

### nop

Benchmarking the `nop` instruction in isolation denotes the relative performance impact of `signalgp-lite`'s byte-code interpreter compared to SignalGP's lamda-based instructions.

We observe a 10x to 30x speedup under `signalgp-lite` (\autoref{fig:bench-wall}).

### arithmetic

Benchmarking arithmetic operations aids in measuring the performance effect of `signalgp-lite`'s fixed-length array registers compared to SignalGP's variable-length vectors.
This compares the effects of compile-time optimizations that streamline register access at the cost of the ability to change the number of registers on the fly.

\autoref{fig:bench-wall} shows this trade-off results in a 20x to 50x speed-up.

### `complete`

In order to improve performance, `signalgp-lite` omits a function stack and implements inner while-loops in terms of `jump` instructions.
The complete benchmark adds control flow to the prior benchmarks' instruction set.

 `signalgp-lite`'s stripped-down control flow modele nables a 30x to 55x speed-up compared to vanilla SignalGP.

### `sans_regulation`

Since regulation hinders tag-match caching, we wanted to measure changes both with and without regulation,
This benchmark measures the complete instruction set without regulation-specific instructions ([list them here]).

As shown on \autoref{fig:bench-wall}, this yields a 35x to 47x speed-up.
Thus, `signalgp-lite` offers performance improvements even on simulations that do not heavily depend on regulation.

# Test Problem Benchmarking

Since `signalgp-lite` is intended to be a specialized alternative to the original SignalGP in artifical life situations, it is important to verify how accurately it can replicate its results.
Two experiments from the original SignalGP paper were replicated @lalejini2018evolving.

## Changing Enviroment Problem

The Changing Enviroment Problem consisted of K mutually exclusive enviromental signals (2, 4, 8, 16). Organisms were tasked to respond to each with a particular signaling instruction.

\autoref{fig:tts-changing} shows the number of generations elapsed before a full solution was found [add](population size and selection scheme).
`signalgp-lite` evolved fill solutions to each problem within 3500 updates in all 100 tested replicates.

In the `K=16` case, we achieved a 100% signal reproduction rate compared to an average of 32% on the vanilla implementation  (Figure 2 in @lalejini2018evolving).
We suspect this occured due to differences in how default mutation parameters and program initialization are performed.

## Contextual Signal Problem

This problem tests regulation by evolving programs that maintain memory of previously encountered signals.
A total of 16 input signal pairs and 4 response signals were tested.
The unordered input signal pairs were assigned a response signal that then had to be replicated by the organism.
Table 2 in @lalejini2018evolving provides a visual representation of this sequence.

TODO: expand more on the problem
TODO: explain how `signalgp-lite` compared in this problem.


# Projects Using the Sofrware

In light of the above, `signalgp-lite` is the framework of choice in DISHTINY.


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

![Number of generations elapsed before a perfect solution was observed on the Changing Enviroment problem. All replicates found a perfect solution.\label{fig:tts-changing}](figures/solution-time-swarmplot.png)

![Number of generations elapsed before a perfect solution was observed on the Contextual Signal problem. Replicates that did not find a solution are on a dashed line at 10,000 generations.\label{fig:tts-context}](figures/solution-time-contextual-signal.png)

<!-- benchmarking results -->

![Benchmarking results of 20 replicates shown as a times-speedup of wall time. "Library" refers to the set of instructions tested (see Benchmarking Results section).\label{fig:bench-wall}](figures/wall-time-speedup.jpeg)


# Acknowledgements

This research was supported in part by NSF grants DEB-1655715 and DBI-0939454 as well as by Michigan State University through the computational resources provided by the Institute for Cyber-Enabled Research.
This material is based upon work supported by the National Science Foundation Graduate Research Fellowship under Grant No. DGE-1424871, and by the Michigan State University BEACON Center Luminaries program.
Any opinions, findings, and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the National Science Foundation.

# References

<div id="refs"></div>

\pagebreak
\appendix

# Supplementary Material

![Maximum fitness wrt. updates, with standard deviation confidence intervals. This is because, due to large number of datapoints, computing 95% CI takes a non-insignificant amount of time.\label{fig:max-fitness-sd}](figures/max-fitness-sd.png)

![Filtered maximum fitness wrt. updates, with 95% confidence intervals. Data has been filtered logarithmically.\label{fig:max-fitness-sd}](figures/max-fitness-log2.png)
