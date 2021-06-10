---
title: 'signalgp-lite: A genetic programming implementation designed for large-scale artificial life applications'
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

Event-driven genetic programming has been shown to outperform traditional traditional imperative representations on signal-heavy problems [cite].
SignalGP is an existing implementation that is focused on extending tag-based referencing by applying event-driven techiques to genetic programming.
With signalgp-lite, our goal is to provide a performance increase in large-scale experiments, such as those undertaken in Artificial Life.
By removing some of the Genetic Programming related overhead (e.g. the call stack) and employing compile-time configuration in exchange of run-time flexibility, we achieved an 8x to 30x speedup.
`signalgp-lite` is unit- and integration-tested, achieving equivalent solution quality on two benchmark problems originally developed for SignalGP.
The library is currently used in DISHTNY [CITE IT], and our expectation is that it will be useful in future Artifical Life and Genetic Programming projects.

# Summary

`signalgp-lite` is a lightweight genetic programming framework that allows for an event-based development paradigm.
This development style has been shown to outperform imperative programming on certain problems, such as those in which many interactions with the enviroment or other organisms occur. [cite]
One example of such situation is the case of a large-scale digital evolution experiment, as well as various other artifical life simulations.
`signalgp-lite` offers a speedup over the original event-driven framework (SignalGP) by forgoing some run-time customizability, such as the ability to xxxxx on the fly.

# Statement of need

`signalgp-lite` is a C++ library for event-driven genetic programming.
C++ was chosen due to its low-level customizability as well as runtime performance.
Due to these features, C++ is the language of choice for most artificial life and genetic programming utilities.
`signalgp-lite` fills a niche for event-driven applications that do not require a high level of customizability at runtime, but instead benefit from a considerable speed-up.
Despite being able to simulate evolution at scales that greately exceed real-life experiements, the performance of artifical life simulations greatly suffers as population size increases.
A large population size is required to replicate ecological effects of interest, such as the transition to multicelularity, or the role of rare events in evolution.
Our genetic programming libary allows for a considerable speedup in performance, allowing users to replicate a greater variety of artificial life situations.
In light of the above, `signalgp-lite` is the framework of choice in DISHTINY due to its combination of performance, flexibility, and ability to be compiled into javascript.

# Results

## Replication Results

Three experiments from the original SignalGP paper were replicated [1].

### Changing Enviroment Problem

The Changing Enviroment Problem consisted of K number of enviromental signals (2, 4, 8, 16) that organisms had to learn to call a unique signaling instruction for.
Figure \autoref{fig:tts-context} shows the number of generations before a full solution was found.
`signalgp-lite` achieved a 100% replication rate, even suprassing SignalGP in signal reproduction in the `K=16` case [figure X cited in Alex's paper] (100% vs 32% average).
This is hypothesised to be caused by differences in how mutation parameters are defined across both libraries, and not due to implementation discrepancies in the simulation.

### Contextual Signal Problem

The Contextual Signal Problem involves evolving programs capable of responding to a signal depending on what signal they previously encountered.
A total of 16 input signal pairs and 4 response signals were tested.
The unordered input signal pairs were assigned a response signal that then had to be replicated by the organism.
You can refer to table 2 in the original SignalGP problem for a visual representation of this sequence. [cite it]
TODO: explain how `signalgp-lite` compared in this problem.

## Benchmarking Results

The main goal of this library is achieving fast execution of genetic programming problems compared to previous solutions.
As such, benchmarking is essential to determining whether `signalgp-lite`'s optimizations work as intended.

Memory access time and caching are important factors when it comes to performance. [cite?]
In order to determine how the libary performs are different caching levels, benchmarks were performed over a variety of memory usages, which were simulated via the different agent counts. \autoref{fig:bench-wall}
Wall times were measured using Google Benchmark version x.y.z.

Each of the five treatments serve a different purpose.

The control ensures our benchmarking process is valid.
While there is some uncertainty inherent to the benchmarking enviroment, the near-zero wall speedup means that our results are not directly affected by the chosen library, and that any resulting difference will stem from implementation choices.
As such, our analysis can be considered fair.

Benchmarking the NOP instruction alone isolates the performance impact of executing `signalgp-lite`'s byte-code interpreter compared to SignalGP's lamda-based instructions.
We observe a 10 to 30 times speedup based on this change.

The arithmetic benchmark adds to the prior improvements the performance effect of `signalgp-lite`'s registers being fixed-length arrays compared to SignalGP variable-length vectors. [TODO: FIX THIS SENTENCE]
This compares the effects of compile-time optimizations versus the runtime flexibility of being able to change the number of registers on the fly.
This trade-off results in a 20 to 50 times speed-up.

* test complex control flow within modules and in between modules
* signalgp-lite doesnt have a function stack like signal-gp
* inner while loops are implemented in terms of jump instrunctions
* we wanted to test this both with and without regulation
* because with regulation, tag matching causes caching to not work as well which can affect performance

The complete benchmark adds tag matching and complex control flow to the prior benchmarks' instruction set.
Tag-based referencing is used to toggle module activation.
This in turn allows for complex regulation mechanics and control flow.
Given the compile-time-friendly nature of `signalgp-lite`'s instructions, we can observe a 30 to 55 times speed-up compared to the vanilla SignalGP lambdas.

Finally, sans_regulation measures the previous instruction set without regulation-specific instructions ([list them here]).
This results in a 35 to 47 times speedup.
We can conclude that `signalgp-lite` offers significant performance improvements even on simulations that do not heavily depend on regulation.

# Citations

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

![Maximum fitness wrt. updates, with standard deviation confidence intervals. This is because, due to large number of datapoints, computing 95% CI takes a non-insignificant amount of time.\label{fig:max-fitness-sd}](figures/max-fitness-sd.png)

![Filtered maximum fitness wrt. updates, with 95% confidence intervals. Data has been filtered logarithmically.\label{fig:max-fitness-sd}](figures/max-fitness-log2.png)

![Time to solution for the Changing Enviroment problem.\label{fig:tts-changing}](figures/solution-time-swarmplot.png)

![Time to solution for the Contextual Signal problem.\label{fig:tts-context}](figures/solution-time-contextual-signal.png)

<!-- benchmarking results -->

![Benchmarking results of 20 replicates shown as a times-speedup of wall time.\label{fig:bench-wall}](figures/wall-time-speedup.jpeg)

# Acknowledgements

We acknowledge contributions from Brigitta Sipocz, Syrtis Major, and Semyeong
Oh, and support from Kathryn Johnston during the genesis of this project.

# References
