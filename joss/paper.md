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

Despite being able to simulate evolution at generation rates that greately exceed biological experiements, the scale of artifical life simulations is profoundly limited by available computational resources [cite blog].
Large population sizes are essential to studying ecological effects, the transition to multicelularity, and the role of rare events in evolution.
In addition to leveraging parallel and distributed computing resources, computational efficiency is crucial to researchers to perform larger-scale artificial life situations.
`signalgp-lite` fills a niche for interaction-heavy genetic programming applications that can tolerate trading a high level of customizability at runtime for a considerable speed-up.


## Benchmarking Results

The main goal of this library is to accelerate execution of event-driven genetic programs.
We performed a set of microbenchmarks to quantify the effectiveness of `signalgp-lite`'s optimizations.
Cache size limitations profoundly affect memory access time, which is key to performance @skadron1999branch.
In order to determine how the libary performs at different caching levels, benchmarks were performed across different orders of magnitude of memory loads.
We altered memory usage through agent counts, ranging from 1 to 32768.
\autoref{fig:bench-wall} shows wall-clock times measured using Google Benchmark version 1.5.2-1.

We performed five microbenchmark experiments, overviewed below.

### control

This experiemnt verifies the validity of our benchmarking process.
While there is some uncertainty inherent to the benchmarking enviroment, the 1x wall speedup (\autoref{fig:bench-wall}) means our results are not directly affected by our experimental aparatus, so that any speedups in other experiments stem solely from differences between SignalGP and `signalgp-lite`.

### nop

Benchmarking the `nop` instruction on its own isolates the performance impact of executing `signalgp-lite`'s byte-code interpreter compared to SignalGP's lamda-based instructions.

We observe a 10 to 30 times speedup (\autoref{fig:bench-wall}) based on this change.

### arithmetic

The arithmetic benchmark adds to the prior improvements the performance effect of `signalgp-lite`'s fixed-length array registers compared to SignalGP variable-length vectors.
This compares the effects of compile-time optimizations that streamline register access at the cost of the ability to change the number of registers on the fly.

\autoref{fig:bench-wall} shows this trade-off results in a 20 to 50 times speed-up.

### `complete`

In order to improve performance, `signalgp-lite` omits a function stack and implements inner while-loops in terms of `jump` instructions.
The complete benchmark adds tag matching and complex control flow to the prior benchmarks' instruction set.
Tag-based referencing is used to toggle module activation.
This in turn allows for complex regulation mechanics and control flow.

Given the stripped-down control flow of `signalgp-lite`'s instructions, \autoref{fig:bench-wall} shows a 30 to 55 times speed-up compared to the vanilla SignalGP lambda-based operators.

### `sans_regulation`

Since regulation hinders tag-match caching, we wanted to measure changes both with and without regulation,
This benchmark measures the complete instruction set without regulation-specific instructions ([list them here]).

As shown on \autoref{fig:bench-wall}, this introduces a 35 to 47 times speed-up.
We can conclude that `signalgp-lite` offers significant performance improvements even on simulations that do not heavily depend on regulation.

# Replication Results

Since `signalgp-lite` is intended to be a replacement for the original SignalGP in artifical life situations, it is important to verify how accurately it can replicate its results.
Two experiments from the original SignalGP paper were replicated @lalejini2018evolving.

## Changing Enviroment Problem

The Changing Enviroment Problem consisted of K enviromental signals (2, 4, 8, 16) that organisms had to learn to respond to with a unique signaling instruction.

\autoref{fig:tts-changing} shows the number of generations before a full solution was found.
`signalgp-lite` evolved fill solutions to each problem within 3500 updates in all 100 tested replicates.

In the `K=16` case, we achieved a 100% signal reproduction rate compared to an average of 32% on the vanilla implementation  (Figure 2 in @lalejini2018evolving).
We suspect this occured due to differences in how default mutation parameters and program initialization are defined across both libraries.

## Contextual Signal Problem

This problem tests regulation by evolving programs that must respond differently depending on what signal they previously encountered.
A total of 16 input signal pairs and 4 response signals were tested.
The unordered input signal pairs were assigned a response signal that then had to be replicated by the organism.
You can refer to table 2 in the original SignalGP problem for a visual representation of this sequence @lalejini2018evolving.

TODO: explain how `signalgp-lite` compared in this problem.


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
