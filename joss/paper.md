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

* Event-driven genetic programming has been shown to outperform traditional traditional imperative representations on signal-heavy problems.
* SignalGP is an existing implementation that is focused on extending tag-based referencing by applying event-driven techiques.
* Our goal is to provide a performance benefit in large-scale experiments (such as those undertaken in Artificial Life).
* By removing some of the GP related overhead (call stack) and trading runtime configurability for compile-time optimization, we achieved a XXX% speedup.
* The software is unit- and integration-tested, achieving equivalent solution quality on benchmark problems originally developed for SignalGP.
* signalgp-lite is currently used in dishtiny, and our intention is for it to be useful in other Artifical Life projects.

# Summary

* signalgp-lite allows is a lightweight genetic programming framework that allows for event-based development.
* event-based programming has been shown to outperform imperative programming on certain problems, such as those in which many interactions with the enviroment or other organisms occur.
* this allows for a better modeling of artificial life simulations, among other things.
* signalgp-lite offers a speedup over the original event-driven framework (SignalGP) by forgoing some runtime-customizability.

# Statement of need

* signalgp-lite is a C++ library for event-driven genetic programming. C++ was chosen due to its low-level customizability as well as runtime performance. Most alife packages are written in C++.
* signalgp-lite fills a niche for event-driven applications that do not require a high level of customizability at runtime, but instead benefit from a considerable speed-up.
* Despite being able to simulate evolution at scales that greately exceed real-life experiements, the performance of artifical life simulations greatly suffers as population size increases.
* A large population size is required to replicate ecological effects of interest (transition to multicelularity, ??)
* signalgp-lite allows for a considerable speedup in performance, allowing users to replicate a greater variety of alife situations.
* signalgp-lite is the framework of choice in DISHTINY due to its combination of performance, flexibility, and ability to be compiled into javascript.

# Results

## Replication Results

Three experiments from the original SignalGP paper were replicated [1].
The first one (the "Changing Enviroment problem") consisted of K number of enviromental signals (2, 4, 8, 16) that organisms had to learn to call a unique signaling instruction for. signalgp-lite managed 100% of the results, even suprassing SignalGP in signal reproduction in the K=16 case (100% vs 32% average).
This is hypothesised to be due to a difference in how mutation parameters are defined and not due to an implementation difference.
The second experiment (the "Contextual-Signal problem") involves evolving programs capable of responding to a signal depending on what signal they previously detected.
A total of 16 input signal pairs and 4 response signals were tested.
The input signal pairs were assigned
You can refer to table 2 in the original SignalGP problem for a visual representation of this sequence.

## Benchmarking Results

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

![Filtered maximum fitness wrt. updates, with 95% confidence intervals. Data has been filtered logarithmically,\label{fig:max-fitness-sd}](figures/max-fitness-log2.png)


# Acknowledgements

We acknowledge contributions from Brigitta Sipocz, Syrtis Major, and Semyeong
Oh, and support from Kathryn Johnston during the genesis of this project.

# References
