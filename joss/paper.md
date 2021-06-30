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
Unlike the traditional imperative paradigm, where a single chain of execution must actively pull XXX, event-driven simulations trigger event-handlers (i.e., program modules) in response to enviromental, self-generated, and cohabitant-generated signals.
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
Cache size limitations profoundly affect memory access time, which is key to performance [@skadron1999branch].
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

Since `signalgp-lite` is intended to be a specialized alternative to the original SignalGP in artifical life situations, it must match SignalGP performance on benchmarks measuring responsitivy and plasticity.
Two experiments from the original SignalGP paper were replicated [@lalejini2018evolving].

## Changing Enviroment Problem

The Changing Enviroment Problem consisted of K mutually-exclusive enviromental signals (2, 4, 8, 16). Organisms were tasked to respond to each with a particular signaling instruction.

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

TODO: talk more about it


# Experimental Materials


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

![Wall time benchmarking results of 20 replicates. The x-axis represents different agent counts.\label{fig:raw-timings}](figures/raw-timings.png)

| Library         | Implementation | Statistic   | Wall Nanoseconds       | CPU Nanoseconds        | num agents |
|-----------------|----------------|-------------|------------------------|------------------------|------------|
| arithmetic      | vanilla        | measurement | 760.1855802385494      | 749.882302240635       | 1.0        |
| arithmetic      | vanilla        | measurement | 768.353517653824       | 754.1809000481397      | 1.0        |
| arithmetic      | vanilla        | measurement | 768.8718047121922      | 755.1567654938049      | 1.0        |
| arithmetic      | vanilla        | measurement | 757.2702403360975      | 748.9733345468779      | 1.0        |
| arithmetic      | vanilla        | measurement | 759.5047761394123      | 746.0654853612508      | 1.0        |
| arithmetic      | vanilla        | measurement | 759.3515514911907      | 747.1096697220942      | 1.0        |
| arithmetic      | vanilla        | measurement | 759.5045195402103      | 746.0732469304083      | 1.0        |
| arithmetic      | vanilla        | measurement | 752.6935430278776      | 751.918087921319       | 1.0        |
| arithmetic      | vanilla        | measurement | 741.5234705767284      | 741.5241296197398      | 1.0        |
| arithmetic      | vanilla        | measurement | 745.2377202598302      | 745.2209766330488      | 1.0        |
| arithmetic      | vanilla        | measurement | 740.7536749030298      | 740.7368281960548      | 1.0        |
| arithmetic      | vanilla        | measurement | 747.5374552170535      | 747.5379925410867      | 1.0        |
| arithmetic      | vanilla        | measurement | 745.7338597629983      | 745.7354300608938      | 1.0        |
| arithmetic      | vanilla        | measurement | 742.2138850732599      | 742.2163315345814      | 1.0        |
| arithmetic      | vanilla        | measurement | 741.1792310592932      | 741.1651477253165      | 1.0        |
| arithmetic      | vanilla        | measurement | 742.0711053168758      | 742.0724475260682      | 1.0        |
| arithmetic      | vanilla        | measurement | 746.5643268273411      | 746.5564139313476      | 1.0        |
| arithmetic      | vanilla        | measurement | 738.833539672256       | 738.8223315630922      | 1.0        |
| arithmetic      | vanilla        | measurement | 776.1955053522951      | 776.1755684927219      | 1.0        |
| arithmetic      | vanilla        | measurement | 764.0617339731097      | 764.0406687362724      | 1.0        |
| arithmetic      | vanilla        | measurement | 769.9571962292429      | 769.9325901468208      | 1.0        |
| arithmetic      | vanilla        | measurement | 760.7416849325331      | 760.7424887244514      | 1.0        |
| arithmetic      | vanilla        | measurement | 761.0623009033172      | 761.0563015322481      | 1.0        |
| arithmetic      | vanilla        | measurement | 773.9119953423642      | 773.9125589821139      | 1.0        |
| arithmetic      | vanilla        | measurement | 779.1800480068675      | 779.1820470672611      | 1.0        |
| arithmetic      | vanilla        | measurement | 743.9381925566772      | 743.9399547552478      | 1.0        |
| arithmetic      | vanilla        | measurement | 748.3893746113941      | 748.3899437346524      | 1.0        |
| arithmetic      | vanilla        | measurement | 763.5274785646566      | 763.523753493966       | 1.0        |
| arithmetic      | vanilla        | measurement | 750.3185730481417      | 750.3022735322593      | 1.0        |
| arithmetic      | vanilla        | measurement | 741.5182399068215      | 741.5068662143655      | 1.0        |
| arithmetic      | vanilla        | measurement | 773.1227453010433      | 773.1236203695677      | 1.0        |
| arithmetic      | vanilla        | measurement | 747.6102426825483      | 747.6112778516745      | 1.0        |
| arithmetic      | vanilla        | measurement | 750.5999107387825      | 750.6012375963494      | 1.0        |
| arithmetic      | vanilla        | measurement | 758.2117610031188      | 758.2017689973678      | 1.0        |
| arithmetic      | vanilla        | measurement | 756.0790708479337      | 756.0722051826405      | 1.0        |
| arithmetic      | vanilla        | measurement | 760.3699476599177      | 760.3515153043711      | 1.0        |
| arithmetic      | vanilla        | measurement | 765.7969293666088      | 765.7808447806805      | 1.0        |
| arithmetic      | vanilla        | measurement | 760.4979126665603      | 760.4993886585489      | 1.0        |
| arithmetic      | vanilla        | measurement | 760.7685170652778      | 760.4262535789492      | 1.0        |
| arithmetic      | vanilla        | measurement | 758.7680247035157      | 758.7600964548777      | 1.0        |
| arithmetic      | vanilla        | measurement | 765.4752255933706      | 765.4792708642905      | 1.0        |
| arithmetic      | vanilla        | measurement | 784.8301249344532      | 784.8319978858005      | 1.0        |
| arithmetic      | vanilla        | measurement | 765.4722911535139      | 765.4755096065613      | 1.0        |
| arithmetic      | vanilla        | measurement | 755.4673269524541      | 755.4674870521714      | 1.0        |
| arithmetic      | vanilla        | measurement | 781.8975523300039      | 781.886854130093       | 1.0        |
| arithmetic      | vanilla        | measurement | 753.2713204639175      | 753.2394451761055      | 1.0        |
| arithmetic      | vanilla        | measurement | 751.0369381816973      | 751.026774014209       | 1.0        |
| arithmetic      | vanilla        | measurement | 751.3253104141113      | 751.2594818236958      | 1.0        |
| arithmetic      | vanilla        | measurement | 749.1344885407492      | 749.1345642040146      | 1.0        |
| arithmetic      | vanilla        | measurement | 751.6837944615038      | 751.6842572173961      | 1.0        |
| arithmetic      | vanilla        | measurement | 799.4231393315299      | 799.3434118691126      | 32.0       |
| arithmetic      | vanilla        | measurement | 792.839467521623       | 792.8303008788721      | 32.0       |
| arithmetic      | vanilla        | measurement | 807.1811857668533      | 807.1731012567636      | 32.0       |
| arithmetic      | vanilla        | measurement | 780.1608004359199      | 780.1511997938858      | 32.0       |
| arithmetic      | vanilla        | measurement | 777.250704531349       | 777.2520672182343      | 32.0       |
| arithmetic      | vanilla        | measurement | 757.2426704074553      | 757.2318158655639      | 32.0       |
| arithmetic      | vanilla        | measurement | 801.7762365789041      | 801.7179330680436      | 32.0       |
| arithmetic      | vanilla        | measurement | 801.9850001436089      | 801.985477655951       | 32.0       |
| arithmetic      | vanilla        | measurement | 771.2267922474311      | 771.2272044888467      | 32.0       |
| arithmetic      | vanilla        | measurement | 789.3089645295903      | 789.2082516962048      | 32.0       |
| arithmetic      | vanilla        | measurement | 813.7674455355893      | 810.3502859923835      | 32.0       |
| arithmetic      | vanilla        | measurement | 790.6304726446336      | 787.3940282270731      | 32.0       |
| arithmetic      | vanilla        | measurement | 773.4529077311772      | 772.5679997709748      | 32.0       |
| arithmetic      | vanilla        | measurement | 775.7915421823997      | 775.7950462340046      | 32.0       |
| arithmetic      | vanilla        | measurement | 769.401249320479       | 769.4007683719343      | 32.0       |
| arithmetic      | vanilla        | measurement | 797.9947817136758      | 791.5737848902127      | 32.0       |
| arithmetic      | vanilla        | measurement | 779.2191967005299      | 779.2209441470369      | 32.0       |
| arithmetic      | vanilla        | measurement | 789.4209143743326      | 789.3751853654388      | 32.0       |
| arithmetic      | vanilla        | measurement | 851.1407254302585      | 839.1518662506093      | 32.0       |
| arithmetic      | vanilla        | measurement | 822.5891683596035      | 807.2459981105593      | 32.0       |
| arithmetic      | vanilla        | measurement | 827.1450803025248      | 812.934027654514       | 32.0       |
| arithmetic      | vanilla        | measurement | 815.0800263374626      | 798.6080249634934      | 32.0       |
| arithmetic      | vanilla        | measurement | 827.4736846922378      | 811.9264412699342      | 32.0       |
| arithmetic      | vanilla        | measurement | 810.1951034897797      | 799.0324330823588      | 32.0       |
| arithmetic      | vanilla        | measurement | 799.6908774436223      | 797.1943122155124      | 32.0       |
| arithmetic      | vanilla        | measurement | 790.4080593180399      | 790.3724222037764      | 32.0       |
| arithmetic      | vanilla        | measurement | 797.1540728853762      | 797.1136892731413      | 32.0       |
| arithmetic      | vanilla        | measurement | 813.771385873542       | 813.634881337497       | 32.0       |
| arithmetic      | vanilla        | measurement | 841.2466909050114      | 841.2061435401266      | 32.0       |
| arithmetic      | vanilla        | measurement | 835.9091477497803      | 832.5378237095982      | 32.0       |
| arithmetic      | vanilla        | measurement | 834.3413918865364      | 828.5528510492131      | 32.0       |
| arithmetic      | vanilla        | measurement | 822.8340133400028      | 818.0432234977552      | 32.0       |
| arithmetic      | vanilla        | measurement | 817.6634496585389      | 813.088863187426       | 32.0       |
| arithmetic      | vanilla        | measurement | 815.647351634595       | 810.5290131974489      | 32.0       |
| arithmetic      | vanilla        | measurement | 823.8009481559195      | 815.0996146689167      | 32.0       |
| arithmetic      | vanilla        | measurement | 787.8816375144411      | 787.6498147777023      | 32.0       |
| arithmetic      | vanilla        | measurement | 782.1995465344049      | 782.1950531046899      | 32.0       |
| arithmetic      | vanilla        | measurement | 781.2749614952904      | 781.2768303226345      | 32.0       |
| arithmetic      | vanilla        | measurement | 788.7166803128617      | 788.7152374681474      | 32.0       |
| arithmetic      | vanilla        | measurement | 810.9040829061861      | 810.9080541639254      | 32.0       |
| arithmetic      | vanilla        | measurement | 818.318222780378       | 818.2977927915075      | 32.0       |
| arithmetic      | vanilla        | measurement | 787.8710097047249      | 787.8635080587464      | 32.0       |
| arithmetic      | vanilla        | measurement | 802.6580573130539      | 802.6032372391292      | 32.0       |
| arithmetic      | vanilla        | measurement | 809.534759383135       | 809.5353433912584      | 32.0       |
| arithmetic      | vanilla        | measurement | 815.6922916614728      | 815.6963236094028      | 32.0       |
| arithmetic      | vanilla        | measurement | 802.4399679374104      | 802.4393381237206      | 32.0       |
| arithmetic      | vanilla        | measurement | 831.9165635119534      | 831.8968091380185      | 32.0       |
| arithmetic      | vanilla        | measurement | 815.7628410282749      | 815.2359978242791      | 32.0       |
| arithmetic      | vanilla        | measurement | 798.047159256046       | 798.0437296384335      | 32.0       |
| arithmetic      | vanilla        | measurement | 801.6123981563063      | 801.6133566173393      | 32.0       |
| arithmetic      | vanilla        | measurement | 1609.1744390348708     | 1609.1209913676068     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1690.6170982860706     | 1690.0549676457904     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1611.3780428336256     | 1609.005088830346      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1671.336695223913      | 1670.9555043529904     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1737.047181480137      | 1730.468951926303      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1766.9685127158384     | 1766.9127586381348     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1588.2588864818172     | 1588.2404972474692     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1682.208947878868      | 1680.912917304788      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1643.2361833526359     | 1643.233623992224      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1703.6614306680335     | 1703.643846263515      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1665.9098911407928     | 1665.9103119524304     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1658.9306304812817     | 1653.5303421220683     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1623.6143043754373     | 1616.7326489971922     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1653.1023284924381     | 1653.0537397039213     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1644.4696624769304     | 1644.47319913354       | 1024.0     |
| arithmetic      | vanilla        | measurement | 1682.1525798285445     | 1682.1547206776938     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1719.6431058163246     | 1719.63633144312       | 1024.0     |
| arithmetic      | vanilla        | measurement | 1681.7786761234966     | 1681.5671205912386     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1613.6447706685321     | 1613.568440513792      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1609.356724018054      | 1608.9844805621817     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1656.7508243764112     | 1656.651666919625      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1681.5887590426819     | 1681.5870045116744     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1710.993740713979      | 1710.9646472311397     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1669.0191296773257     | 1669.0168508579507     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1638.7054135233195     | 1638.7027138895298     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1691.1376421663008     | 1691.1413236937697     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1728.321746068102      | 1728.3204583396564     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1661.1459756154145     | 1661.1429379544231     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1622.395788205591      | 1622.3089147661033     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1648.8280306477307     | 1648.8306658940362     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1627.8422669541694     | 1625.5742605904209     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1707.3267544145972     | 1707.3028624383253     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1660.418263681009      | 1658.6419123700236     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1616.956143619305      | 1616.9054898660293     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1633.5055142408967     | 1633.4924161941335     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1594.5922865009634     | 1594.5720001655804     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1615.6975031844017     | 1615.6972709336512     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1668.2646467709535     | 1668.257573458061      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1659.4387638707308     | 1659.434063659797      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1609.2287329201135     | 1609.2060274930234     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1671.2142965540447     | 1670.363877812898      | 1024.0     |
| arithmetic      | vanilla        | measurement | 1625.1001140557923     | 1625.0922750037869     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1631.8991248047864     | 1631.8727815413004     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1608.6925431268037     | 1608.6919981419924     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1622.3218564467677     | 1617.4035421754522     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1632.6106067487883     | 1627.0667940598878     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1580.6848351475755     | 1580.0031135455265     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1686.2803685659949     | 1686.2807870785648     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1673.447288178401      | 1646.5058223761448     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1650.3715880905345     | 1613.3599341418496     | 1024.0     |
| arithmetic      | vanilla        | measurement | 1787.2793145253897     | 1778.4245653288035     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1745.0570822329707     | 1712.712382660661      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1814.9603577393025     | 1782.0925309050706     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1940.5818000591187     | 1939.8476400885236     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1669.2724210337183     | 1669.2291320325485     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1701.1096896379554     | 1700.7119108033453     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1619.6671437333748     | 1619.6632188792996     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1601.335684283475      | 1601.337874829675      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1615.9230591361013     | 1615.9217841830962     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1704.9848536940378     | 1704.8378810794857     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1679.2324944110528     | 1679.1568972413347     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1642.933718111633      | 1642.894922690394      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1614.5185243070478     | 1614.5167931202475     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1627.8727985228265     | 1627.8275814656797     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1679.478613302856      | 1679.4693667738027     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1626.587274849193      | 1626.5849718135971     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1687.0231772566156     | 1686.8952820518728     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1679.4308338468277     | 1679.4282901891843     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1640.8502806099373     | 1640.8143350874363     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1729.6812244540447     | 1728.7213573240754     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1714.4259558981457     | 1714.3981350699535     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1621.6680155762497     | 1621.660528355202      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1595.2502093629935     | 1595.2490844093493     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1631.1609127152346     | 1631.1593658987897     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1652.0163993877622     | 1651.9869192405397     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1617.5367017440776     | 1617.5013843231304     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1704.846455760332      | 1702.741350324387      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1703.7565966283332     | 1693.1664937564954     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1754.7727460212732     | 1754.340221616732      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1678.2588277887191     | 1639.8599583765981     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1662.2700086246714     | 1634.3638488556742     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1655.2223979110843     | 1629.148719422987      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1665.7835237417528     | 1636.264721322923      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1680.616017528572      | 1648.3814950689712     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1752.3959164059343     | 1728.7069766133836     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1669.390797846056      | 1669.337740459704      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1676.2403847351165     | 1672.0014311963585     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1634.836287388197      | 1634.8142569654237     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1687.7195636385075     | 1687.6651531818138     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1650.510874592383      | 1650.4191561566627     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1668.145453919917      | 1668.1490850342504     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1658.71565128626       | 1658.603914853222      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1647.3613270727265     | 1647.3702048673756     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1638.665290674642      | 1638.5891935302482     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1688.7960326514014     | 1688.7964263839822     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1634.5530136375812     | 1634.5584759321757     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1727.8173349751407     | 1727.6869367398874     | 32768.0    |
| arithmetic      | vanilla        | measurement | 1636.126942113468      | 1636.127345224506      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1661.6555785402636     | 1661.567997450135      | 32768.0    |
| arithmetic      | vanilla        | measurement | 1712.8865292537746     | 1691.9483925602754     | 32768.0    |
| complete        | vanilla        | measurement | 22792.3851184786       | 22759.790567306973     | 1.0        |
| complete        | vanilla        | measurement | 23203.624486148277     | 23118.266948202403     | 1.0        |
| complete        | vanilla        | measurement | 24437.947081252125     | 24188.152814111672     | 1.0        |
| complete        | vanilla        | measurement | 24410.703341079585     | 24330.484901711654     | 1.0        |
| complete        | vanilla        | measurement | 24124.182898589417     | 24020.804843411315     | 1.0        |
| complete        | vanilla        | measurement | 24155.325024276965     | 23968.298153823165     | 1.0        |
| complete        | vanilla        | measurement | 24780.18181475385      | 24444.825809103822     | 1.0        |
| complete        | vanilla        | measurement | 25548.30387179554      | 25401.63136258316      | 1.0        |
| complete        | vanilla        | measurement | 23486.370020200186     | 23340.78458778683      | 1.0        |
| complete        | vanilla        | measurement | 23760.35264220735      | 23582.124037670983     | 1.0        |
| complete        | vanilla        | measurement | 24136.772666182125     | 23936.80488078331      | 1.0        |
| complete        | vanilla        | measurement | 25552.983817874494     | 25415.716234397176     | 1.0        |
| complete        | vanilla        | measurement | 25193.66936991574      | 24936.470737723328     | 1.0        |
| complete        | vanilla        | measurement | 24901.95989979383      | 24608.717467673174     | 1.0        |
| complete        | vanilla        | measurement | 23956.943979406493     | 23732.903767097672     | 1.0        |
| complete        | vanilla        | measurement | 25029.20595705341      | 24858.605650646477     | 1.0        |
| complete        | vanilla        | measurement | 24957.038530553516     | 24856.431272890353     | 1.0        |
| complete        | vanilla        | measurement | 24399.096868255547     | 24123.833844083973     | 1.0        |
| complete        | vanilla        | measurement | 24196.049106820537     | 23899.28892293889      | 1.0        |
| complete        | vanilla        | measurement | 25542.33190076546      | 25512.69702518877      | 1.0        |
| complete        | vanilla        | measurement | 35583.70039496416      | 35111.39183354764      | 32.0       |
| complete        | vanilla        | measurement | 31072.11955721301      | 30814.789454345024     | 32.0       |
| complete        | vanilla        | measurement | 34756.03968404421      | 34397.73566966745      | 32.0       |
| complete        | vanilla        | measurement | 32993.72836674032      | 32660.276961234576     | 32.0       |
| complete        | vanilla        | measurement | 29274.58722211107      | 29038.10343560535      | 32.0       |
| complete        | vanilla        | measurement | 30905.559480022068     | 30728.66489068537      | 32.0       |
| complete        | vanilla        | measurement | 31758.99889765729      | 31520.895278339216     | 32.0       |
| complete        | vanilla        | measurement | 33703.312098068505     | 33402.315956274        | 32.0       |
| complete        | vanilla        | measurement | 30585.89821788914      | 30258.01566231861      | 32.0       |
| complete        | vanilla        | measurement | 34651.7127503011       | 34358.01405474912      | 32.0       |
| complete        | vanilla        | measurement | 33578.90327025094      | 33394.26988792953      | 32.0       |
| complete        | vanilla        | measurement | 32262.492283684605     | 32103.09815359187      | 32.0       |
| complete        | vanilla        | measurement | 31068.125620092163     | 30884.79579276128      | 32.0       |
| complete        | vanilla        | measurement | 35098.88471429041      | 34734.11937350737      | 32.0       |
| complete        | vanilla        | measurement | 31326.039224726457     | 31265.810169024448     | 32.0       |
| complete        | vanilla        | measurement | 29679.551350382844     | 29667.7608855411       | 32.0       |
| complete        | vanilla        | measurement | 34160.38177474951      | 33780.28026823446      | 32.0       |
| complete        | vanilla        | measurement | 32381.71918055487      | 32345.97354400146      | 32.0       |
| complete        | vanilla        | measurement | 31777.50275584732      | 31541.13577071475      | 32.0       |
| complete        | vanilla        | measurement | 31529.369465399574     | 31490.999035458277     | 32.0       |
| complete        | vanilla        | measurement | 30595.669673736404     | 30589.463958908727     | 1024.0     |
| complete        | vanilla        | measurement | 29877.091289660122     | 29468.467843577375     | 1024.0     |
| complete        | vanilla        | measurement | 34749.25064746224      | 34318.37802140886      | 1024.0     |
| complete        | vanilla        | measurement | 32068.20139848096      | 31617.809133287432     | 1024.0     |
| complete        | vanilla        | measurement | 30824.032846989292     | 30821.112353245888     | 1024.0     |
| complete        | vanilla        | measurement | 30170.31060083666      | 30089.372453384152     | 1024.0     |
| complete        | vanilla        | measurement | 29264.817506870048     | 29198.94220476518      | 1024.0     |
| complete        | vanilla        | measurement | 30249.132208209077     | 30214.929816988766     | 1024.0     |
| complete        | vanilla        | measurement | 30166.86157630598      | 30166.832743439252     | 1024.0     |
| complete        | vanilla        | measurement | 31835.437068406645     | 31834.656379488897     | 1024.0     |
| complete        | vanilla        | measurement | 33134.298687868526     | 33134.2911774864       | 1024.0     |
| complete        | vanilla        | measurement | 32381.86023820969      | 32343.311723066076     | 1024.0     |
| complete        | vanilla        | measurement | 30340.40689748664      | 30079.613777624414     | 1024.0     |
| complete        | vanilla        | measurement | 32355.056500382514     | 32126.012258287417     | 1024.0     |
| complete        | vanilla        | measurement | 34694.4364640674       | 34191.56176622917      | 1024.0     |
| complete        | vanilla        | measurement | 36885.53431457356      | 36467.54881733455      | 1024.0     |
| complete        | vanilla        | measurement | 35027.89938707058      | 34789.83023998611      | 1024.0     |
| complete        | vanilla        | measurement | 33587.62737391806      | 33326.76174033153      | 1024.0     |
| complete        | vanilla        | measurement | 37003.565737195735     | 36587.17247928177      | 1024.0     |
| complete        | vanilla        | measurement | 32903.22656250574      | 32439.149991367212     | 1024.0     |
| complete        | vanilla        | measurement | 40668.83538723743      | 40668.24981878062      | 32768.0    |
| complete        | vanilla        | measurement | 37402.74438224472      | 37402.16579901157      | 32768.0    |
| complete        | vanilla        | measurement | 46248.954991791616     | 46196.17693574949      | 32768.0    |
| complete        | vanilla        | measurement | 40634.61700160823      | 39885.51196046127      | 32768.0    |
| complete        | vanilla        | measurement | 39601.099308168006     | 38905.11861614461      | 32768.0    |
| complete        | vanilla        | measurement | 38538.95927514134      | 37783.218978583755     | 32768.0    |
| complete        | vanilla        | measurement | 38794.16915987         | 38218.78451400356      | 32768.0    |
| complete        | vanilla        | measurement | 38254.80863262567      | 37851.92856672192      | 32768.0    |
| complete        | vanilla        | measurement | 36349.79934101258      | 36349.751696870415     | 32768.0    |
| complete        | vanilla        | measurement | 37353.11288310155      | 37353.031301483        | 32768.0    |
| complete        | vanilla        | measurement | 37442.02181216463      | 36854.76112026329      | 32768.0    |
| complete        | vanilla        | measurement | 37787.89074140884      | 37014.779505765764     | 32768.0    |
| complete        | vanilla        | measurement | 38519.35018124013      | 37777.27670510716      | 32768.0    |
| complete        | vanilla        | measurement | 37983.14266889149      | 37299.05871499188      | 32768.0    |
| complete        | vanilla        | measurement | 39508.65311369559      | 38880.46464579838      | 32768.0    |
| complete        | vanilla        | measurement | 38163.34425035981      | 37575.58892915995      | 32768.0    |
| complete        | vanilla        | measurement | 37972.42741358061      | 37299.12718286648      | 32768.0    |
| complete        | vanilla        | measurement | 41130.08507421065      | 40588.81344316304      | 32768.0    |
| complete        | vanilla        | measurement | 38845.02991766798      | 38391.072751235704     | 32768.0    |
| complete        | vanilla        | measurement | 37005.04230637997      | 37005.051927512555     | 32768.0    |
| nop             | vanilla        | measurement | 303.518526960116       | 301.9014828206564      | 1.0        |
| nop             | vanilla        | measurement | 328.00512935117064     | 327.2114961197941      | 1.0        |
| nop             | vanilla        | measurement | 314.50027815324444     | 312.62834862771047     | 1.0        |
| nop             | vanilla        | measurement | 313.9945984695294      | 309.9417493344898      | 1.0        |
| nop             | vanilla        | measurement | 310.23631881672645     | 306.25389315105474     | 1.0        |
| nop             | vanilla        | measurement | 312.31619684500987     | 308.06040862208977     | 1.0        |
| nop             | vanilla        | measurement | 309.919321367975       | 305.78170782170776     | 1.0        |
| nop             | vanilla        | measurement | 311.39033433714485     | 307.72232285703535     | 1.0        |
| nop             | vanilla        | measurement | 311.690600098201       | 307.99051534711623     | 1.0        |
| nop             | vanilla        | measurement | 310.4323547440936      | 305.7173917757776      | 1.0        |
| nop             | vanilla        | measurement | 310.9938115865003      | 305.7588417137076      | 1.0        |
| nop             | vanilla        | measurement | 310.44213503193436     | 306.1118189724036      | 1.0        |
| nop             | vanilla        | measurement | 308.91487843817936     | 304.42753607474054     | 1.0        |
| nop             | vanilla        | measurement | 318.68316187544        | 314.0424687271111      | 1.0        |
| nop             | vanilla        | measurement | 312.2969739481846      | 307.2380921822759      | 1.0        |
| nop             | vanilla        | measurement | 310.80569495218964     | 307.1913491433016      | 1.0        |
| nop             | vanilla        | measurement | 312.33587337241556     | 307.7371705365466      | 1.0        |
| nop             | vanilla        | measurement | 313.6466500999225      | 308.0794974209413      | 1.0        |
| nop             | vanilla        | measurement | 310.85350280727914     | 305.635719580712       | 1.0        |
| nop             | vanilla        | measurement | 309.22869471452634     | 305.2533948206384      | 1.0        |
| nop             | vanilla        | measurement | 330.75083138598546     | 326.6084585543005      | 32.0       |
| nop             | vanilla        | measurement | 332.6648078724064      | 328.22081538818026     | 32.0       |
| nop             | vanilla        | measurement | 332.8981989037112      | 327.83205694516977     | 32.0       |
| nop             | vanilla        | measurement | 333.40105479491143     | 329.0613293779696      | 32.0       |
| nop             | vanilla        | measurement | 333.4572772050267      | 327.4372041084082      | 32.0       |
| nop             | vanilla        | measurement | 334.44057824586474     | 328.4662437672578      | 32.0       |
| nop             | vanilla        | measurement | 332.09816842648036     | 329.8143280999303      | 32.0       |
| nop             | vanilla        | measurement | 326.88920780885803     | 326.88965174960214     | 32.0       |
| nop             | vanilla        | measurement | 325.0502761532662      | 325.04652412446626     | 32.0       |
| nop             | vanilla        | measurement | 327.6612077535455      | 327.65661313431985     | 32.0       |
| nop             | vanilla        | measurement | 328.5344554039851      | 327.30260613411804     | 32.0       |
| nop             | vanilla        | measurement | 328.2994650536226      | 328.30002929724753     | 32.0       |
| nop             | vanilla        | measurement | 328.44165059127045     | 328.44223464878553     | 32.0       |
| nop             | vanilla        | measurement | 329.50903850731527     | 329.5101353853671      | 32.0       |
| nop             | vanilla        | measurement | 324.3136216160352      | 324.29934852544204     | 32.0       |
| nop             | vanilla        | measurement | 330.27945894944486     | 330.2732900149226      | 32.0       |
| nop             | vanilla        | measurement | 330.1975177063575      | 330.19785644159754     | 32.0       |
| nop             | vanilla        | measurement | 326.89945995897074     | 326.8948860969212      | 32.0       |
| nop             | vanilla        | measurement | 336.33790153435376     | 336.33913145217554     | 32.0       |
| nop             | vanilla        | measurement | 348.2359947591225      | 348.21233617011865     | 32.0       |
| nop             | vanilla        | measurement | 961.1765567078551      | 961.1280707357316      | 1024.0     |
| nop             | vanilla        | measurement | 932.1480651417346      | 932.1315413878079      | 1024.0     |
| nop             | vanilla        | measurement | 985.2599102956906      | 985.2589267545453      | 1024.0     |
| nop             | vanilla        | measurement | 957.8535952908071      | 957.8449539884227      | 1024.0     |
| nop             | vanilla        | measurement | 942.4053879888493      | 928.0729218481512      | 1024.0     |
| nop             | vanilla        | measurement | 906.3546198105088      | 890.0827515940136      | 1024.0     |
| nop             | vanilla        | measurement | 888.757977130982       | 884.2308619539616      | 1024.0     |
| nop             | vanilla        | measurement | 940.8074438125454      | 940.792631364743       | 1024.0     |
| nop             | vanilla        | measurement | 859.1868655037314      | 859.1914539432047      | 1024.0     |
| nop             | vanilla        | measurement | 837.65754160489        | 837.6589504951687      | 1024.0     |
| nop             | vanilla        | measurement | 848.949561081648       | 848.9513232567613      | 1024.0     |
| nop             | vanilla        | measurement | 844.9993386551943      | 844.9798218888498      | 1024.0     |
| nop             | vanilla        | measurement | 895.5930293040003      | 895.5679476236763      | 1024.0     |
| nop             | vanilla        | measurement | 851.0907414406681      | 851.0694653273921      | 1024.0     |
| nop             | vanilla        | measurement | 858.0790859299923      | 858.0763472800115      | 1024.0     |
| nop             | vanilla        | measurement | 849.775235710253       | 849.7764651352037      | 1024.0     |
| nop             | vanilla        | measurement | 867.2048306498549      | 867.203547526458       | 1024.0     |
| nop             | vanilla        | measurement | 904.9285562882774      | 904.8959991408119      | 1024.0     |
| nop             | vanilla        | measurement | 807.0520823923956      | 806.0381686940358      | 1024.0     |
| nop             | vanilla        | measurement | 971.0577589417946      | 967.017455005877       | 1024.0     |
| nop             | vanilla        | measurement | 1112.1677915303087     | 1111.9716139390378     | 32768.0    |
| nop             | vanilla        | measurement | 1082.2873931202844     | 1082.2714093954808     | 32768.0    |
| nop             | vanilla        | measurement | 1107.7751017067394     | 1107.6478165725491     | 32768.0    |
| nop             | vanilla        | measurement | 1056.0737090092593     | 1056.0732841275699     | 32768.0    |
| nop             | vanilla        | measurement | 1070.6960046342008     | 1070.6936226772682     | 32768.0    |
| nop             | vanilla        | measurement | 1070.9719109786386     | 1070.949320945413      | 32768.0    |
| nop             | vanilla        | measurement | 1034.7757954273766     | 1034.7422149361953     | 32768.0    |
| nop             | vanilla        | measurement | 1062.3453308408978     | 1062.3478349965105     | 32768.0    |
| nop             | vanilla        | measurement | 1001.2520040737043     | 997.6316091262539      | 32768.0    |
| nop             | vanilla        | measurement | 1004.3829740037672     | 1004.3612092886864     | 32768.0    |
| nop             | vanilla        | measurement | 1042.7626298112193     | 1042.7631862925791     | 32768.0    |
| nop             | vanilla        | measurement | 973.3301912326397      | 973.1977962685884      | 32768.0    |
| nop             | vanilla        | measurement | 1021.5056493898867     | 1021.5057095481235     | 32768.0    |
| nop             | vanilla        | measurement | 1004.2440686094927     | 1004.2421152964064     | 32768.0    |
| nop             | vanilla        | measurement | 1129.3200524140589     | 1129.2717590747477     | 32768.0    |
| nop             | vanilla        | measurement | 1071.8831394442268     | 1071.8806916881674     | 32768.0    |
| nop             | vanilla        | measurement | 1044.9765056917904     | 1044.9798464419187     | 32768.0    |
| nop             | vanilla        | measurement | 1075.3501737126123     | 1075.3331860669682     | 32768.0    |
| nop             | vanilla        | measurement | 998.7915798751891      | 998.7579354634811      | 32768.0    |
| nop             | vanilla        | measurement | 970.1559155966636      | 970.1556918761821      | 32768.0    |
| sans_regulation | vanilla        | measurement | 23738.825068529306     | 23687.111459186217     | 1.0        |
| sans_regulation | vanilla        | measurement | 29138.335481110378     | 28867.22409312591      | 1.0        |
| sans_regulation | vanilla        | measurement | 23012.358299848787     | 23011.809155957417     | 1.0        |
| sans_regulation | vanilla        | measurement | 22879.23470146041      | 22879.278024990213     | 1.0        |
| sans_regulation | vanilla        | measurement | 21606.437150686063     | 21606.055284610735     | 1.0        |
| sans_regulation | vanilla        | measurement | 24315.654444480944     | 24189.47043537076      | 1.0        |
| sans_regulation | vanilla        | measurement | 24290.38660074855      | 24256.591363781998     | 1.0        |
| sans_regulation | vanilla        | measurement | 22075.367413065887     | 22074.203623936493     | 1.0        |
| sans_regulation | vanilla        | measurement | 24206.385247900253     | 24205.96742728989      | 1.0        |
| sans_regulation | vanilla        | measurement | 23650.88106511718      | 23650.93748887542      | 1.0        |
| sans_regulation | vanilla        | measurement | 21503.51151611538      | 21503.290128510896     | 1.0        |
| sans_regulation | vanilla        | measurement | 22603.92969280309      | 22556.04364387171      | 1.0        |
| sans_regulation | vanilla        | measurement | 22832.249652884573     | 22832.306575059636     | 1.0        |
| sans_regulation | vanilla        | measurement | 21128.389199355846     | 21128.38321882456      | 1.0        |
| sans_regulation | vanilla        | measurement | 21393.670748656168     | 21393.717098002944     | 1.0        |
| sans_regulation | vanilla        | measurement | 23769.544658429677     | 23769.575878395255     | 1.0        |
| sans_regulation | vanilla        | measurement | 21918.967534143452     | 21918.465487166657     | 1.0        |
| sans_regulation | vanilla        | measurement | 21961.279840536732     | 21960.961304332315     | 1.0        |
| sans_regulation | vanilla        | measurement | 24999.865544092972     | 24999.538998255666     | 1.0        |
| sans_regulation | vanilla        | measurement | 22841.799829083673     | 22807.612865330524     | 1.0        |
| sans_regulation | vanilla        | measurement | 30745.112784305216     | 30744.647329614105     | 32.0       |
| sans_regulation | vanilla        | measurement | 30997.847618278956     | 30997.52120313653      | 32.0       |
| sans_regulation | vanilla        | measurement | 26773.265556124945     | 26772.853001989643     | 32.0       |
| sans_regulation | vanilla        | measurement | 26852.465376690587     | 26780.96020754502      | 32.0       |
| sans_regulation | vanilla        | measurement | 28659.167791518234     | 28658.562478055628     | 32.0       |
| sans_regulation | vanilla        | measurement | 28455.672726569195     | 28433.84110326529      | 32.0       |
| sans_regulation | vanilla        | measurement | 30140.9071119436       | 30125.235165606835     | 32.0       |
| sans_regulation | vanilla        | measurement | 31165.901025973508     | 31114.383021885893     | 32.0       |
| sans_regulation | vanilla        | measurement | 31729.553622241394     | 31530.9841220302       | 32.0       |
| sans_regulation | vanilla        | measurement | 27850.56922713811      | 27517.928919751797     | 32.0       |
| sans_regulation | vanilla        | measurement | 27863.727421728825     | 27490.690008972866     | 32.0       |
| sans_regulation | vanilla        | measurement | 29210.20563332853      | 28824.136932859972     | 32.0       |
| sans_regulation | vanilla        | measurement | 31009.491631888774     | 30626.252018881896     | 32.0       |
| sans_regulation | vanilla        | measurement | 31467.93746339954      | 30930.420824718043     | 32.0       |
| sans_regulation | vanilla        | measurement | 31278.665470298427     | 31062.188155892687     | 32.0       |
| sans_regulation | vanilla        | measurement | 27853.74961958565      | 27853.73222018489      | 32.0       |
| sans_regulation | vanilla        | measurement | 27778.196270441887     | 27775.59665275228      | 32.0       |
| sans_regulation | vanilla        | measurement | 32296.026138179943     | 32295.63316818164      | 32.0       |
| sans_regulation | vanilla        | measurement | 31422.34525805611      | 31360.819607537156     | 32.0       |
| sans_regulation | vanilla        | measurement | 28538.44423207017      | 28536.98146919987      | 32.0       |
| sans_regulation | vanilla        | measurement | 30988.458258912495     | 30987.942876424135     | 1024.0     |
| sans_regulation | vanilla        | measurement | 30206.436782936536     | 30206.389504187995     | 1024.0     |
| sans_regulation | vanilla        | measurement | 31261.62300030161      | 31258.946528522098     | 1024.0     |
| sans_regulation | vanilla        | measurement | 30122.97102140553      | 30122.031836767354     | 1024.0     |
| sans_regulation | vanilla        | measurement | 35259.54166168986      | 35259.20963836303      | 1024.0     |
| sans_regulation | vanilla        | measurement | 30799.627525710945     | 30796.55345162975      | 1024.0     |
| sans_regulation | vanilla        | measurement | 29496.76960026235      | 29495.437537215574     | 1024.0     |
| sans_regulation | vanilla        | measurement | 31268.153030877256     | 31266.79321980052      | 1024.0     |
| sans_regulation | vanilla        | measurement | 32659.24810447719      | 32658.48084633393      | 1024.0     |
| sans_regulation | vanilla        | measurement | 29186.145885495564     | 29185.87265293163      | 1024.0     |
| sans_regulation | vanilla        | measurement | 31275.829462934722     | 31275.838077091026     | 1024.0     |
| sans_regulation | vanilla        | measurement | 27903.06482474803      | 27902.45206621421      | 1024.0     |
| sans_regulation | vanilla        | measurement | 32888.622166635985     | 32887.919653844634     | 1024.0     |
| sans_regulation | vanilla        | measurement | 29790.59291010803      | 29788.202572347443     | 1024.0     |
| sans_regulation | vanilla        | measurement | 33735.681354419474     | 33735.25894168561      | 1024.0     |
| sans_regulation | vanilla        | measurement | 35563.131277063156     | 35560.49581199635      | 1024.0     |
| sans_regulation | vanilla        | measurement | 30951.492159888523     | 30758.95990631588      | 1024.0     |
| sans_regulation | vanilla        | measurement | 34846.644714379516     | 34189.19364058605      | 1024.0     |
| sans_regulation | vanilla        | measurement | 33492.68897625004      | 32931.72216267731      | 1024.0     |
| sans_regulation | vanilla        | measurement | 32136.118613754817     | 31705.88761859398      | 1024.0     |
| sans_regulation | vanilla        | measurement | 36815.19566032653      | 36814.18047117172      | 32768.0    |
| sans_regulation | vanilla        | measurement | 37040.27954127459      | 37040.17309361454      | 32768.0    |
| sans_regulation | vanilla        | measurement | 36282.9871668029       | 36282.962492250495     | 32768.0    |
| sans_regulation | vanilla        | measurement | 38338.96193431918      | 38337.865034098155     | 32768.0    |
| sans_regulation | vanilla        | measurement | 35984.64990697935      | 35983.68301301959      | 32768.0    |
| sans_regulation | vanilla        | measurement | 35774.72926232416      | 35774.66379417282      | 32768.0    |
| sans_regulation | vanilla        | measurement | 36623.65306876741      | 36623.80991940504      | 32768.0    |
| sans_regulation | vanilla        | measurement | 34905.897954092594     | 34904.353316800945     | 32768.0    |
| sans_regulation | vanilla        | measurement | 33155.0525727931       | 33155.12901425897      | 32768.0    |
| sans_regulation | vanilla        | measurement | 36185.56261625121      | 36184.490638561576     | 32768.0    |
| sans_regulation | vanilla        | measurement | 35980.14513325999      | 35968.70334779924      | 32768.0    |
| sans_regulation | vanilla        | measurement | 35395.238127783734     | 35395.27495350279      | 32768.0    |
| sans_regulation | vanilla        | measurement | 35854.08121512595      | 35669.64730316179      | 32768.0    |
| sans_regulation | vanilla        | measurement | 37071.68704287151      | 36384.45740855602      | 32768.0    |
| sans_regulation | vanilla        | measurement | 37510.0232486373       | 36879.26769993876      | 32768.0    |
| sans_regulation | vanilla        | measurement | 36601.62641038003      | 36601.41816490973      | 32768.0    |
| sans_regulation | vanilla        | measurement | 36582.208369545406     | 36580.7269063855       | 32768.0    |
| sans_regulation | vanilla        | measurement | 36695.067141943335     | 36695.07352758869      | 32768.0    |
| sans_regulation | vanilla        | measurement | 35868.58921264258      | 35867.27334159941      | 32768.0    |
| sans_regulation | vanilla        | measurement | 35831.20601363138      | 35830.7473031621       | 32768.0    |
| control         | vanilla        | measurement | 2.4450000637443736e-06 | 1.8740000000002331e-06 | 1.0        |
| control         | vanilla        | measurement | 1.9560002328944393e-06 | 1.3719999999999184e-06 | 1.0        |
| control         | vanilla        | measurement | 1.3970002328278497e-06 | 1.341999999999663e-06  | 1.0        |
| control         | vanilla        | measurement | 1.3970002328278497e-06 | 1.4130000000000219e-06 | 1.0        |
| control         | vanilla        | measurement | 1.396999323333148e-06  | 1.3729999999998257e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4659999578725547e-06 | 1.3219999999997817e-06 | 1.0        |
| control         | vanilla        | measurement | 2.373999450355768e-06  | 1.6729999999997788e-06 | 1.0        |
| control         | vanilla        | measurement | 1.886000063677784e-06  | 1.453000000000218e-06  | 1.0        |
| control         | vanilla        | measurement | 9.769992175279185e-07  | 1.3220000000002154e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4659999578725547e-06 | 1.2319999999998825e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4669994925498031e-06 | 1.642999999999957e-06  | 1.0        |
| control         | vanilla        | measurement | 1.886000063677784e-06  | 1.7529999999997374e-06 | 1.0        |
| control         | vanilla        | measurement | 1.9560002328944393e-06 | 1.7139999999998823e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4670004020445049e-06 | 1.311999999999841e-06  | 1.0        |
| control         | vanilla        | measurement | 1.4670004020445049e-06 | 1.3930000000001407e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4659999578725547e-06 | 1.3629999999998851e-06 | 1.0        |
| control         | vanilla        | measurement | 9.080004019779153e-07  | 1.1730000000001461e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4670004020445049e-06 | 1.432999999999903e-06  | 1.0        |
| control         | vanilla        | measurement | 1.3959997886558995e-06 | 1.2319999999998825e-06 | 1.0        |
| control         | vanilla        | measurement | 1.4669994925498031e-06 | 1.453000000000218e-06  | 1.0        |
| control         | vanilla        | measurement | 5.168999450688716e-06  | 2.61500000000095e-06   | 32.0       |
| control         | vanilla        | measurement | 3.3520000215503387e-06 | 2.2450000000014125e-06 | 32.0       |
| control         | vanilla        | measurement | 3.2819998523336835e-06 | 2.4139999999991946e-06 | 32.0       |
| control         | vanilla        | measurement | 1.886000063677784e-06  | 1.5429999999996835e-06 | 32.0       |
| control         | vanilla        | measurement | 5.658000191033352e-06  | 3.837999999999064e-06  | 32.0       |
| control         | vanilla        | measurement | 2.9340008040890098e-06 | 2.164000000002414e-06  | 32.0       |
| control         | vanilla        | measurement | 3.840999852400273e-06  | 2.505000000003338e-06  | 32.0       |
| control         | vanilla        | measurement | 5.169000360183418e-06  | 2.3639999999977568e-06 | 32.0       |
| control         | vanilla        | measurement | 1.3970002328278497e-06 | 1.3319999999997223e-06 | 32.0       |
| control         | vanilla        | measurement | 1.8159998944611289e-06 | 1.4129999999987208e-06 | 32.0       |
| control         | vanilla        | measurement | 5.308999789122026e-06  | 2.5549999999978368e-06 | 32.0       |
| control         | vanilla        | measurement | 9.080004019779153e-07  | 1.3430000000008713e-06 | 32.0       |
| control         | vanilla        | measurement | 2.3749998945277184e-06 | 1.6840000000017952e-06 | 32.0       |
| control         | vanilla        | measurement | 1.8159998944611289e-06 | 1.594000000000595e-06  | 32.0       |
| control         | vanilla        | measurement | 1.886000063677784e-06  | 1.7240000000015574e-06 | 32.0       |
| control         | vanilla        | measurement | 4.400000761961564e-06  | 2.8759999999988795e-06 | 32.0       |
| control         | vanilla        | measurement | 3.772000127355568e-06  | 2.835999999999117e-06  | 32.0       |
| control         | vanilla        | measurement | 3.3520000215503387e-06 | 2.0039999999998948e-06 | 32.0       |
| control         | vanilla        | measurement | 8.451000212517101e-06  | 3.6870000000022163e-06 | 32.0       |
| control         | vanilla        | measurement | 5.1679999160114676e-06 | 2.7860000000011487e-06 | 32.0       |
| control         | vanilla        | measurement | 3.422000190766994e-06  | 2.644999999967812e-06  | 1024.0     |
| control         | vanilla        | measurement | 6.565999683516566e-06  | 3.778000000009829e-06  | 1024.0     |
| control         | vanilla        | measurement | 4.260000423528254e-06  | 2.2839999999635374e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.840999852400273e-06  | 2.4350000000228356e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.282999387010932e-06  | 2.143999999981716e-06  | 1024.0     |
| control         | vanilla        | measurement | 3.7719992178608663e-06 | 2.3749999999989058e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.772000127355568e-06  | 2.6049999999888662e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.9120004657888785e-06 | 2.4149999999778515e-06 | 1024.0     |
| control         | vanilla        | measurement | 5.308999789122026e-06  | 3.1060000000304733e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.352999556227587e-06  | 2.3650000000041693e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.840999852400273e-06  | 2.3239999999979948e-06 | 1024.0     |
| control         | vanilla        | measurement | 6.356000085361302e-06  | 4.107999999947154e-06  | 1024.0     |
| control         | vanilla        | measurement | 3.422000190766994e-06  | 2.1049999999744884e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.3520000215503387e-06 | 2.1040000000027703e-06 | 1024.0     |
| control         | vanilla        | measurement | 2.863999725377653e-06  | 1.8039999999386325e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.772000127355568e-06  | 3.206000000033349e-06  | 1024.0     |
| control         | vanilla        | measurement | 2.8630001907004043e-06 | 1.5529999999319697e-06 | 1024.0     |
| control         | vanilla        | measurement | 2.3749998945277184e-06 | 1.5729999999214428e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.282999387010932e-06  | 1.8739999999572987e-06 | 1024.0     |
| control         | vanilla        | measurement | 4.260000423528254e-06  | 2.5649999999544093e-06 | 1024.0     |
| control         | vanilla        | measurement | 3.352999556227587e-06  | 2.5450000000759587e-06 | 32768.0    |
| control         | vanilla        | measurement | 3.353000465722289e-06  | 2.073999999296916e-06  | 32768.0    |
| control         | vanilla        | measurement | 4.2609999582055025e-06 | 2.75499999879969e-06   | 32768.0    |
| control         | vanilla        | measurement | 3.770999683183618e-06  | 2.555000000015184e-06  | 32768.0    |
| control         | vanilla        | measurement | 3.770999683183618e-06  | 2.7249999998701924e-06 | 32768.0    |
| control         | vanilla        | measurement | 3.772000127355568e-06  | 2.3850000001601757e-06 | 32768.0    |
| control         | vanilla        | measurement | 3.2830002965056337e-06 | 2.0639999984695123e-06 | 32768.0    |
| control         | vanilla        | measurement | 3.772000127355568e-06  | 2.304000000563633e-06  | 32768.0    |
| control         | vanilla        | measurement | 3.3520000215503387e-06 | 1.984000000732067e-06  | 32768.0    |
| control         | vanilla        | measurement | 2.8640006348723546e-06 | 1.794000000998608e-06  | 32768.0    |
| control         | vanilla        | measurement | 3.282999387010932e-06  | 2.024000000488968e-06  | 32768.0    |
| control         | vanilla        | measurement | 4.260000423528254e-06  | 2.5440000008813968e-06 | 32768.0    |
| control         | vanilla        | measurement | 3.770999683183618e-06  | 2.645000002132747e-06  | 32768.0    |
| control         | vanilla        | measurement | 3.352999556227587e-06  | 2.443999999712787e-06  | 32768.0    |
| control         | vanilla        | measurement | 6.104299973230809e-05  | 1.1472000000622984e-05 | 32768.0    |
| control         | vanilla        | measurement | 3.772000127355568e-06  | 2.644999998580033e-06  | 32768.0    |
| control         | vanilla        | measurement | 3.840999852400273e-06  | 2.4950000003798323e-06 | 32768.0    |
| control         | vanilla        | measurement | 4.2609999582055025e-06 | 2.666000000317581e-06  | 32768.0    |
| control         | vanilla        | measurement | 3.422000190766994e-06  | 2.0940000027280803e-06 | 32768.0    |
| control         | vanilla        | measurement | 4.819000423594844e-06  | 2.5150000020346397e-06 | 32768.0    |
| arithmetic      | lite           | measurement | 37.25939968715988      | 36.94151981585546      | 1.0        |
| arithmetic      | lite           | measurement | 36.402936588815344     | 36.40106426639122      | 1.0        |
| arithmetic      | lite           | measurement | 36.074829256523444     | 36.07387516536972      | 1.0        |
| arithmetic      | lite           | measurement | 35.99263434335295      | 35.9921233925219       | 1.0        |
| arithmetic      | lite           | measurement | 36.25945405040838      | 36.25919192936358      | 1.0        |
| arithmetic      | lite           | measurement | 36.7614544884002       | 36.733730960786744     | 1.0        |
| arithmetic      | lite           | measurement | 36.76952561471063      | 36.76862854492684      | 1.0        |
| arithmetic      | lite           | measurement | 36.33801424364706      | 36.33771970287603      | 1.0        |
| arithmetic      | lite           | measurement | 36.1752151773578       | 36.17528032975224      | 1.0        |
| arithmetic      | lite           | measurement | 36.05462551001532      | 36.05392071781429      | 1.0        |
| arithmetic      | lite           | measurement | 36.25260976895211      | 36.251134563180486     | 1.0        |
| arithmetic      | lite           | measurement | 36.48383429242734      | 36.483939213787174     | 1.0        |
| arithmetic      | lite           | measurement | 35.837375072928275     | 35.8374131740572       | 1.0        |
| arithmetic      | lite           | measurement | 36.44457045775965      | 36.444735527810664     | 1.0        |
| arithmetic      | lite           | measurement | 36.24640893223913      | 36.246412841415335     | 1.0        |
| arithmetic      | lite           | measurement | 36.149649183153045     | 36.1489214574239       | 1.0        |
| arithmetic      | lite           | measurement | 36.11878307064271      | 36.118863807489205     | 1.0        |
| arithmetic      | lite           | measurement | 36.31701496077276      | 36.31642452401514      | 1.0        |
| arithmetic      | lite           | measurement | 36.29804582541118      | 36.29771792656216      | 1.0        |
| arithmetic      | lite           | measurement | 36.05173321435791      | 36.051387594094365     | 1.0        |
| arithmetic      | lite           | measurement | 35.997805616483355     | 35.996932939667225     | 1.0        |
| arithmetic      | lite           | measurement | 35.949528083309474     | 35.94892810817672      | 1.0        |
| arithmetic      | lite           | measurement | 35.980973843194505     | 35.98105494491295      | 1.0        |
| arithmetic      | lite           | measurement | 36.10124400357101      | 36.100690886039686     | 1.0        |
| arithmetic      | lite           | measurement | 36.287499378492825     | 36.286801257888825     | 1.0        |
| arithmetic      | lite           | measurement | 36.18101608286411      | 36.181079723658144     | 1.0        |
| arithmetic      | lite           | measurement | 36.033695392793895     | 36.03277935064259      | 1.0        |
| arithmetic      | lite           | measurement | 35.97146060849447      | 35.96110138342966      | 1.0        |
| arithmetic      | lite           | measurement | 36.28039917857458      | 36.280527919662084     | 1.0        |
| arithmetic      | lite           | measurement | 36.18431268792042      | 36.18437231539695      | 1.0        |
| arithmetic      | lite           | measurement | 35.90008593848849      | 35.90014832846675      | 1.0        |
| arithmetic      | lite           | measurement | 36.09280651238392      | 36.09192189973027      | 1.0        |
| arithmetic      | lite           | measurement | 36.354496852242356     | 36.35466510175903      | 1.0        |
| arithmetic      | lite           | measurement | 35.984361453193834     | 35.98346969982697      | 1.0        |
| arithmetic      | lite           | measurement | 35.883309779494766     | 35.88216455734594      | 1.0        |
| arithmetic      | lite           | measurement | 35.89901832599877      | 35.899071386032524     | 1.0        |
| arithmetic      | lite           | measurement | 36.32183404621953      | 36.321962735144034     | 1.0        |
| arithmetic      | lite           | measurement | 36.974672619832575     | 36.618242566715125     | 1.0        |
| arithmetic      | lite           | measurement | 37.053031518433095     | 36.62524952050457      | 1.0        |
| arithmetic      | lite           | measurement | 37.25437227052867      | 36.57855232292133      | 1.0        |
| arithmetic      | lite           | measurement | 36.59231036416791      | 36.10443141327766      | 1.0        |
| arithmetic      | lite           | measurement | 36.74839086708554      | 36.23262618526465      | 1.0        |
| arithmetic      | lite           | measurement | 36.32271099701327      | 36.18125751141542      | 1.0        |
| arithmetic      | lite           | measurement | 35.979543253833484     | 35.978978878022104     | 1.0        |
| arithmetic      | lite           | measurement | 36.01893984284767      | 36.018661668386144     | 1.0        |
| arithmetic      | lite           | measurement | 36.058405285023746     | 36.05848258175133      | 1.0        |
| arithmetic      | lite           | measurement | 35.943607349548        | 35.94334439464011      | 1.0        |
| arithmetic      | lite           | measurement | 36.59782204532298      | 36.59782360890047      | 1.0        |
| arithmetic      | lite           | measurement | 35.73477636942875      | 35.73492293622595      | 1.0        |
| arithmetic      | lite           | measurement | 36.412216213269645     | 36.41120541350432      | 1.0        |
| arithmetic      | lite           | measurement | 32.42259154614784      | 32.4221331587587       | 32.0       |
| arithmetic      | lite           | measurement | 32.56184321686113      | 32.5609011067292       | 32.0       |
| arithmetic      | lite           | measurement | 33.25640111083587      | 33.25643682933786      | 32.0       |
| arithmetic      | lite           | measurement | 32.7417871674457       | 32.74188583166995      | 32.0       |
| arithmetic      | lite           | measurement | 32.566543891583464     | 32.566534015965885     | 32.0       |
| arithmetic      | lite           | measurement | 32.49130429850818      | 32.49103396386513      | 32.0       |
| arithmetic      | lite           | measurement | 32.512245216077744     | 32.512313745780766     | 32.0       |
| arithmetic      | lite           | measurement | 32.734614347759496     | 32.73463862152054      | 32.0       |
| arithmetic      | lite           | measurement | 32.675238753262484     | 32.67530755983445      | 32.0       |
| arithmetic      | lite           | measurement | 32.69375925784872      | 32.69345555829265      | 32.0       |
| arithmetic      | lite           | measurement | 32.73311384759461      | 32.730725415079895     | 32.0       |
| arithmetic      | lite           | measurement | 32.690746443772525     | 32.69012819988608      | 32.0       |
| arithmetic      | lite           | measurement | 32.64667751940818      | 32.6451820494501       | 32.0       |
| arithmetic      | lite           | measurement | 32.77765541902101      | 32.77771988775722      | 32.0       |
| arithmetic      | lite           | measurement | 33.57988442896753      | 33.579967864423786     | 32.0       |
| arithmetic      | lite           | measurement | 33.830958729880535     | 33.83095988350769      | 32.0       |
| arithmetic      | lite           | measurement | 33.18071314429759      | 33.17958205845819      | 32.0       |
| arithmetic      | lite           | measurement | 32.95961474231308      | 32.95843584712516      | 32.0       |
| arithmetic      | lite           | measurement | 34.01271126409156      | 34.0124340995952       | 32.0       |
| arithmetic      | lite           | measurement | 32.99232389093645      | 32.99133341781485      | 32.0       |
| arithmetic      | lite           | measurement | 32.741985372807825     | 32.74109153341396      | 32.0       |
| arithmetic      | lite           | measurement | 33.46988962615244      | 33.46995741745466      | 32.0       |
| arithmetic      | lite           | measurement | 33.21912571628318      | 33.218326618655006     | 32.0       |
| arithmetic      | lite           | measurement | 32.38594284055586      | 32.38547914616344      | 32.0       |
| arithmetic      | lite           | measurement | 32.52318966034744      | 32.52282421485519      | 32.0       |
| arithmetic      | lite           | measurement | 32.571978272434094     | 32.572019113366956     | 32.0       |
| arithmetic      | lite           | measurement | 32.56263188499742      | 32.56157223614725      | 32.0       |
| arithmetic      | lite           | measurement | 32.480104517623566     | 32.47934612252592      | 32.0       |
| arithmetic      | lite           | measurement | 32.73881108707303      | 32.73900352394854      | 32.0       |
| arithmetic      | lite           | measurement | 32.641615460104646     | 32.640656598356365     | 32.0       |
| arithmetic      | lite           | measurement | 32.689688686956195     | 32.68912152883289      | 32.0       |
| arithmetic      | lite           | measurement | 33.213547538476966     | 33.21359040994242      | 32.0       |
| arithmetic      | lite           | measurement | 32.98226724069425      | 32.982336462563396     | 32.0       |
| arithmetic      | lite           | measurement | 32.6031560480617       | 32.59927237628023      | 32.0       |
| arithmetic      | lite           | measurement | 32.63885881325545      | 32.63847103215657      | 32.0       |
| arithmetic      | lite           | measurement | 32.48984837723871      | 32.48869790924928      | 32.0       |
| arithmetic      | lite           | measurement | 32.533522044585965     | 32.532904585175956     | 32.0       |
| arithmetic      | lite           | measurement | 32.526015852133646     | 32.52605406267515      | 32.0       |
| arithmetic      | lite           | measurement | 32.77923344773616      | 32.77929320930392      | 32.0       |
| arithmetic      | lite           | measurement | 32.922462424323435     | 32.91530700236769      | 32.0       |
| arithmetic      | lite           | measurement | 32.49278057090668      | 32.49247871726456      | 32.0       |
| arithmetic      | lite           | measurement | 32.56692212008771      | 32.56640997031727      | 32.0       |
| arithmetic      | lite           | measurement | 32.586886455102466     | 32.58686988802015      | 32.0       |
| arithmetic      | lite           | measurement | 32.66826090857516      | 32.66652551551633      | 32.0       |
| arithmetic      | lite           | measurement | 32.77596801989131      | 32.774667386451064     | 32.0       |
| arithmetic      | lite           | measurement | 32.46760696467977      | 32.467677986354765     | 32.0       |
| arithmetic      | lite           | measurement | 32.58184733143681      | 32.573311209397374     | 32.0       |
| arithmetic      | lite           | measurement | 32.43970550786237      | 32.43975340943299      | 32.0       |
| arithmetic      | lite           | measurement | 32.57845107408995      | 32.57796850514252      | 32.0       |
| arithmetic      | lite           | measurement | 32.606537630226654     | 32.6042002835141       | 32.0       |
| arithmetic      | lite           | measurement | 32.84358767327927      | 32.84312007385357      | 1024.0     |
| arithmetic      | lite           | measurement | 32.5195875672589       | 32.51770211676165      | 1024.0     |
| arithmetic      | lite           | measurement | 33.347582953724455     | 33.347216649951505     | 1024.0     |
| arithmetic      | lite           | measurement | 32.616582941585804     | 32.616630784942316     | 1024.0     |
| arithmetic      | lite           | measurement | 32.90814654090218      | 32.90810665541945      | 1024.0     |
| arithmetic      | lite           | measurement | 32.91461574997655      | 32.913572544082726     | 1024.0     |
| arithmetic      | lite           | measurement | 33.27580884643901      | 33.27530035493703      | 1024.0     |
| arithmetic      | lite           | measurement | 33.31779595298476      | 33.316916891138476     | 1024.0     |
| arithmetic      | lite           | measurement | 33.12952267804216      | 33.1288716152079       | 1024.0     |
| arithmetic      | lite           | measurement | 34.21239141220364      | 34.212130622739906     | 1024.0     |
| arithmetic      | lite           | measurement | 33.92403964628505      | 33.92299337235164      | 1024.0     |
| arithmetic      | lite           | measurement | 34.175856627538984     | 34.17554252961088      | 1024.0     |
| arithmetic      | lite           | measurement | 34.91898814447669      | 34.91699511839519      | 1024.0     |
| arithmetic      | lite           | measurement | 34.45236030534325      | 34.450848781075535     | 1024.0     |
| arithmetic      | lite           | measurement | 33.670909321642526     | 33.67100922700995      | 1024.0     |
| arithmetic      | lite           | measurement | 33.54052335364208      | 33.53988106369734      | 1024.0     |
| arithmetic      | lite           | measurement | 33.3892812263121       | 33.38936372975349      | 1024.0     |
| arithmetic      | lite           | measurement | 33.65128663893902      | 33.649686954345974     | 1024.0     |
| arithmetic      | lite           | measurement | 33.993609459247054     | 33.993305620296326     | 1024.0     |
| arithmetic      | lite           | measurement | 33.50559309543118      | 33.505011975942345     | 1024.0     |
| arithmetic      | lite           | measurement | 33.94137126472459      | 33.94138655727061      | 1024.0     |
| arithmetic      | lite           | measurement | 34.0418954466852       | 34.041919943669505     | 1024.0     |
| arithmetic      | lite           | measurement | 32.58865708616578      | 32.587089808466864     | 1024.0     |
| arithmetic      | lite           | measurement | 33.37752192178321      | 33.37773836745836      | 1024.0     |
| arithmetic      | lite           | measurement | 32.872406253301975     | 32.87029299554492      | 1024.0     |
| arithmetic      | lite           | measurement | 33.953902630640684     | 33.95346465777551      | 1024.0     |
| arithmetic      | lite           | measurement | 33.12852937696859      | 33.12820128077356      | 1024.0     |
| arithmetic      | lite           | measurement | 33.81159052965333      | 33.81124191546676      | 1024.0     |
| arithmetic      | lite           | measurement | 33.734719330313645     | 33.73389717233693      | 1024.0     |
| arithmetic      | lite           | measurement | 33.93367773530096      | 33.93366330553433      | 1024.0     |
| arithmetic      | lite           | measurement | 33.83948258789389      | 33.83954716207635      | 1024.0     |
| arithmetic      | lite           | measurement | 33.928780166315065     | 33.92798629244465      | 1024.0     |
| arithmetic      | lite           | measurement | 34.364029517678446     | 34.36369705907616      | 1024.0     |
| arithmetic      | lite           | measurement | 33.30465561478728      | 33.304181543612465     | 1024.0     |
| arithmetic      | lite           | measurement | 33.1803566363734       | 33.179483183321075     | 1024.0     |
| arithmetic      | lite           | measurement | 33.13907351751217      | 33.13833769812138      | 1024.0     |
| arithmetic      | lite           | measurement | 33.636020434974974     | 33.636067415423334     | 1024.0     |
| arithmetic      | lite           | measurement | 33.21797844327787      | 33.21803232706158      | 1024.0     |
| arithmetic      | lite           | measurement | 33.10575329886226      | 33.10536839462608      | 1024.0     |
| arithmetic      | lite           | measurement | 32.796806450629894     | 32.79418853650992      | 1024.0     |
| arithmetic      | lite           | measurement | 32.72269722288073      | 32.722398417583115     | 1024.0     |
| arithmetic      | lite           | measurement | 33.31511221837056      | 33.31351133525802      | 1024.0     |
| arithmetic      | lite           | measurement | 33.224653695350284     | 33.22482014035019      | 1024.0     |
| arithmetic      | lite           | measurement | 32.57245031426095      | 32.571229733146026     | 1024.0     |
| arithmetic      | lite           | measurement | 32.886534187885246     | 32.886585818411426     | 1024.0     |
| arithmetic      | lite           | measurement | 33.37990531705548      | 33.37915981395145      | 1024.0     |
| arithmetic      | lite           | measurement | 33.71926482098905      | 33.71929626917182      | 1024.0     |
| arithmetic      | lite           | measurement | 33.44526342774309      | 33.444371949655874     | 1024.0     |
| arithmetic      | lite           | measurement | 33.23388056139813      | 33.233973755277795     | 1024.0     |
| arithmetic      | lite           | measurement | 33.09498988405509      | 33.094931733798816     | 1024.0     |
| arithmetic      | lite           | measurement | 74.95881326439178      | 74.9573986066382       | 32768.0    |
| arithmetic      | lite           | measurement | 77.05715202958437      | 77.05050884664948      | 32768.0    |
| arithmetic      | lite           | measurement | 71.69948144859538      | 71.69750615694373      | 32768.0    |
| arithmetic      | lite           | measurement | 74.27900210342798      | 74.27669989189465      | 32768.0    |
| arithmetic      | lite           | measurement | 79.41953061827385      | 79.41637917295803      | 32768.0    |
| arithmetic      | lite           | measurement | 89.80389308266373      | 89.80092465680538      | 32768.0    |
| arithmetic      | lite           | measurement | 83.1189896135092       | 83.11556663295939      | 32768.0    |
| arithmetic      | lite           | measurement | 82.23206862059013      | 82.23115162772883      | 32768.0    |
| arithmetic      | lite           | measurement | 84.07943198937822      | 84.07534019991743      | 32768.0    |
| arithmetic      | lite           | measurement | 76.35435357997045      | 76.3504427141991       | 32768.0    |
| arithmetic      | lite           | measurement | 82.43267737418405      | 82.43088430373678      | 32768.0    |
| arithmetic      | lite           | measurement | 92.88165813917071      | 92.65235456773455      | 32768.0    |
| arithmetic      | lite           | measurement | 80.74974280999989      | 80.23062951367402      | 32768.0    |
| arithmetic      | lite           | measurement | 83.52577094910016      | 83.24374912619243      | 32768.0    |
| arithmetic      | lite           | measurement | 87.40113328278292      | 87.34686964582342      | 32768.0    |
| arithmetic      | lite           | measurement | 84.97534787399657      | 84.97536783244543      | 32768.0    |
| arithmetic      | lite           | measurement | 85.25275449602613      | 85.2341828231458       | 32768.0    |
| arithmetic      | lite           | measurement | 80.17747187638598      | 80.17548161578672      | 32768.0    |
| arithmetic      | lite           | measurement | 74.47007578942032      | 74.46848719348638      | 32768.0    |
| arithmetic      | lite           | measurement | 74.63523347793408      | 74.51141021788662      | 32768.0    |
| arithmetic      | lite           | measurement | 73.88286462983048      | 73.83420004732149      | 32768.0    |
| arithmetic      | lite           | measurement | 80.98822578916577      | 80.98848365284937      | 32768.0    |
| arithmetic      | lite           | measurement | 80.535628446285        | 80.53350636012135      | 32768.0    |
| arithmetic      | lite           | measurement | 71.48732940357675      | 71.48650102651455      | 32768.0    |
| arithmetic      | lite           | measurement | 74.66568983173994      | 74.66162338951253      | 32768.0    |
| arithmetic      | lite           | measurement | 72.99665815068008      | 72.79788537820255      | 32768.0    |
| arithmetic      | lite           | measurement | 78.21235761742764      | 76.66590318795954      | 32768.0    |
| arithmetic      | lite           | measurement | 80.95975400767146      | 80.55143018036692      | 32768.0    |
| arithmetic      | lite           | measurement | 78.40822533208343      | 77.9470821638076       | 32768.0    |
| arithmetic      | lite           | measurement | 81.09219664027053      | 80.90049466115508      | 32768.0    |
| arithmetic      | lite           | measurement | 84.23715833433411      | 84.23594356098508      | 32768.0    |
| arithmetic      | lite           | measurement | 80.57434901136305      | 80.57309541883856      | 32768.0    |
| arithmetic      | lite           | measurement | 82.49305609268713      | 82.49114556633869      | 32768.0    |
| arithmetic      | lite           | measurement | 87.69112961951502      | 87.55319011986896      | 32768.0    |
| arithmetic      | lite           | measurement | 78.8061530822119       | 78.47188313027954      | 32768.0    |
| arithmetic      | lite           | measurement | 74.2127686624977       | 74.1765582764428       | 32768.0    |
| arithmetic      | lite           | measurement | 73.3364341506627       | 73.31743806057743      | 32768.0    |
| arithmetic      | lite           | measurement | 76.16675057540763      | 76.16272624568272      | 32768.0    |
| arithmetic      | lite           | measurement | 79.13710503516391      | 78.89499060903125      | 32768.0    |
| arithmetic      | lite           | measurement | 70.45980714707156      | 70.45688173168787      | 32768.0    |
| arithmetic      | lite           | measurement | 70.56714309895766      | 70.54434671326891      | 32768.0    |
| arithmetic      | lite           | measurement | 72.08031126061118      | 72.0795632164687       | 32768.0    |
| arithmetic      | lite           | measurement | 78.3183929745159       | 78.31737718718799      | 32768.0    |
| arithmetic      | lite           | measurement | 70.07208018046157      | 70.06832588898499      | 32768.0    |
| arithmetic      | lite           | measurement | 68.56598091642026      | 68.56537337990834      | 32768.0    |
| arithmetic      | lite           | measurement | 76.20033931430359      | 76.19502556632536      | 32768.0    |
| arithmetic      | lite           | measurement | 79.13725951404521      | 79.13033351931209      | 32768.0    |
| arithmetic      | lite           | measurement | 86.78484719638791      | 86.59293864690743      | 32768.0    |
| arithmetic      | lite           | measurement | 73.83544994764978      | 73.82324293701517      | 32768.0    |
| arithmetic      | lite           | measurement | 80.12618215372174      | 80.10648711744321      | 32768.0    |
| complete        | lite           | measurement | 723.5279090006092      | 722.5609159376743      | 1.0        |
| complete        | lite           | measurement | 689.9299645152024      | 689.7053114989237      | 1.0        |
| complete        | lite           | measurement | 624.1789696112947      | 624.1679703236015      | 1.0        |
| complete        | lite           | measurement | 653.9315293574862      | 653.916674137209       | 1.0        |
| complete        | lite           | measurement | 423.6287079914073      | 423.6317366798336      | 1.0        |
| complete        | lite           | measurement | 792.4165147021598      | 792.3879458353523      | 1.0        |
| complete        | lite           | measurement | 511.5062973823863      | 511.50934649964444     | 1.0        |
| complete        | lite           | measurement | 749.8973241093031      | 749.8136929936142      | 1.0        |
| complete        | lite           | measurement | 388.2626551933546      | 388.2642869868442      | 1.0        |
| complete        | lite           | measurement | 305.38903747960063     | 305.38522807093125     | 1.0        |
| complete        | lite           | measurement | 740.9871862242487      | 740.980073510138       | 1.0        |
| complete        | lite           | measurement | 553.8847645191187      | 553.8509768632572      | 1.0        |
| complete        | lite           | measurement | 194.43151290348658     | 194.42738576027602     | 1.0        |
| complete        | lite           | measurement | 601.5960902772182      | 601.5977776743886      | 1.0        |
| complete        | lite           | measurement | 545.330795618239       | 544.7967815768486      | 1.0        |
| complete        | lite           | measurement | 674.8158376997293      | 674.7654438807175      | 1.0        |
| complete        | lite           | measurement | 170.12929296211638     | 170.1298524009958      | 1.0        |
| complete        | lite           | measurement | 587.2471940088383      | 587.2103107102614      | 1.0        |
| complete        | lite           | measurement | 322.8478778162661      | 322.84949258941117     | 1.0        |
| complete        | lite           | measurement | 563.8738514749195      | 563.6268605906007      | 1.0        |
| complete        | lite           | measurement | 609.04551319188        | 609.0485407477425      | 1.0        |
| complete        | lite           | measurement | 306.3110416138241      | 306.3045620994985      | 1.0        |
| complete        | lite           | measurement | 218.02243318822838     | 218.02484456543633     | 1.0        |
| complete        | lite           | measurement | 674.5809559039634      | 674.364465258575       | 1.0        |
| complete        | lite           | measurement | 295.649423141528       | 294.62779790726546     | 1.0        |
| complete        | lite           | measurement | 314.86336169814024     | 314.86643124055956     | 1.0        |
| complete        | lite           | measurement | 662.8352875888231      | 662.8362112888786      | 1.0        |
| complete        | lite           | measurement | 517.3836462062272      | 517.0420442127489      | 1.0        |
| complete        | lite           | measurement | 632.4348264209331      | 632.4040379511121      | 1.0        |
| complete        | lite           | measurement | 754.6268560515682      | 752.629038206435       | 1.0        |
| complete        | lite           | measurement | 800.1500194617701      | 794.33572050261        | 1.0        |
| complete        | lite           | measurement | 681.6686721753787      | 679.886796884842       | 1.0        |
| complete        | lite           | measurement | 201.37702711633662     | 201.37070647122894     | 1.0        |
| complete        | lite           | measurement | 627.2485228175797      | 627.251651368133       | 1.0        |
| complete        | lite           | measurement | 554.924210116796       | 554.9053888899592      | 1.0        |
| complete        | lite           | measurement | 669.5785626833974      | 669.5726630346591      | 1.0        |
| complete        | lite           | measurement | 470.0901946019736      | 470.0582032796977      | 1.0        |
| complete        | lite           | measurement | 640.2799887428051      | 640.2810849270171      | 1.0        |
| complete        | lite           | measurement | 165.8120282920551      | 165.7990726692745      | 1.0        |
| complete        | lite           | measurement | 581.4286544275313      | 581.4181408221815      | 1.0        |
| complete        | lite           | measurement | 649.630423756873       | 649.618785596189       | 1.0        |
| complete        | lite           | measurement | 588.2940246635737      | 588.2872728056749      | 1.0        |
| complete        | lite           | measurement | 639.9167853451828      | 639.9053332864304      | 1.0        |
| complete        | lite           | measurement | 574.9246424637286      | 574.9282453454751      | 1.0        |
| complete        | lite           | measurement | 260.29852854859837     | 260.29892344755626     | 1.0        |
| complete        | lite           | measurement | 600.6002196910182      | 600.5923421455467      | 1.0        |
| complete        | lite           | measurement | 683.8223592021812      | 683.7702541535267      | 1.0        |
| complete        | lite           | measurement | 287.4957349836851      | 287.4844406568465      | 1.0        |
| complete        | lite           | measurement | 755.5579008648407      | 755.5587008745622      | 1.0        |
| complete        | lite           | measurement | 747.1659243417268      | 747.1626562147138      | 1.0        |
| complete        | lite           | measurement | 776.3168000001315      | 776.2680910000022      | 32.0       |
| complete        | lite           | measurement | 543.0815469990193      | 543.075224999999       | 32.0       |
| complete        | lite           | measurement | 412.9729790001875      | 412.9646849999986      | 32.0       |
| complete        | lite           | measurement | 674.3139720001636      | 674.2880940000014      | 32.0       |
| complete        | lite           | measurement | 634.8671240011754      | 634.8521429999997      | 32.0       |
| complete        | lite           | measurement | 512.6864540015958      | 512.6809889999997      | 32.0       |
| complete        | lite           | measurement | 691.3717829993402      | 691.374003             | 32.0       |
| complete        | lite           | measurement | 633.4266260000732      | 633.4187910000005      | 32.0       |
| complete        | lite           | measurement | 489.41193700011354     | 489.3602950000009      | 32.0       |
| complete        | lite           | measurement | 513.7209170006827      | 513.7216349999995      | 32.0       |
| complete        | lite           | measurement | 309.69600600110425     | 309.6972660000006      | 32.0       |
| complete        | lite           | measurement | 495.7537029986269      | 495.7237939999999      | 32.0       |
| complete        | lite           | measurement | 569.4776290001755      | 569.4802719999999      | 32.0       |
| complete        | lite           | measurement | 599.9039649996121      | 599.9052739999975      | 32.0       |
| complete        | lite           | measurement | 607.7107620003517      | 607.7117190000009      | 32.0       |
| complete        | lite           | measurement | 734.9686329998804      | 734.9156200000024      | 32.0       |
| complete        | lite           | measurement | 593.8594770013879      | 593.8521859999994      | 32.0       |
| complete        | lite           | measurement | 310.89634899944934     | 310.89884400000045     | 32.0       |
| complete        | lite           | measurement | 370.71848300001875     | 370.710944999999       | 32.0       |
| complete        | lite           | measurement | 661.2054079996597      | 661.1997110000019      | 32.0       |
| complete        | lite           | measurement | 483.797777998916       | 483.78999399999856     | 32.0       |
| complete        | lite           | measurement | 620.9343409991561      | 620.9356069999999      | 32.0       |
| complete        | lite           | measurement | 395.30866500172124     | 395.3105550000018      | 32.0       |
| complete        | lite           | measurement | 634.598955999536       | 634.5919449999968      | 32.0       |
| complete        | lite           | measurement | 658.0641679993278      | 658.0550870000011      | 32.0       |
| complete        | lite           | measurement | 644.5295499997883      | 644.5327519999964      | 32.0       |
| complete        | lite           | measurement | 585.7931290011038      | 585.793308999996       | 32.0       |
| complete        | lite           | measurement | 431.48241299968504     | 431.41328699999804     | 32.0       |
| complete        | lite           | measurement | 778.6283740006184      | 778.4097549999984      | 32.0       |
| complete        | lite           | measurement | 504.6634600003017      | 504.62722900000045     | 32.0       |
| complete        | lite           | measurement | 342.38503400047193     | 342.3669459999985      | 32.0       |
| complete        | lite           | measurement | 568.0772220002837      | 567.9875729999964      | 32.0       |
| complete        | lite           | measurement | 817.7993829995103      | 817.7901270000021      | 32.0       |
| complete        | lite           | measurement | 390.50928899996507     | 390.51038299999874     | 32.0       |
| complete        | lite           | measurement | 587.0823339992057      | 587.0631909999986      | 32.0       |
| complete        | lite           | measurement | 416.9056129994715      | 416.87725900000316     | 32.0       |
| complete        | lite           | measurement | 841.1729830004333      | 841.1669579999952      | 32.0       |
| complete        | lite           | measurement | 626.7516659991088      | 626.7257439999979      | 32.0       |
| complete        | lite           | measurement | 765.5477930002235      | 765.549417999999       | 32.0       |
| complete        | lite           | measurement | 475.855500999387       | 475.85810100000003     | 32.0       |
| complete        | lite           | measurement | 480.6617640006152      | 480.66167500000034     | 32.0       |
| complete        | lite           | measurement | 395.58328200109827     | 395.5847309999996      | 32.0       |
| complete        | lite           | measurement | 703.3904649997567      | 703.3916070000004      | 32.0       |
| complete        | lite           | measurement | 623.9100550010335      | 623.9122310000056      | 32.0       |
| complete        | lite           | measurement | 814.8501989999204      | 814.844903000001       | 32.0       |
| complete        | lite           | measurement | 438.45897699975467     | 438.46025199999866     | 32.0       |
| complete        | lite           | measurement | 500.5332190012268      | 500.5350469999996      | 32.0       |
| complete        | lite           | measurement | 723.3550299988565      | 723.3563179999933      | 32.0       |
| complete        | lite           | measurement | 448.06437700026436     | 448.06628900000334     | 32.0       |
| complete        | lite           | measurement | 592.5250799991773      | 592.5249860000008      | 32.0       |
| complete        | lite           | measurement | 1106.8748360259938     | 1106.8841259606756     | 1024.0     |
| complete        | lite           | measurement | 1086.087296470808      | 1085.9942637347988     | 1024.0     |
| complete        | lite           | measurement | 759.2298063443624      | 759.226185976529       | 1024.0     |
| complete        | lite           | measurement | 1110.697751070937      | 1110.6550588819525     | 1024.0     |
| complete        | lite           | measurement | 1206.4877604082665     | 1206.4489238944236     | 1024.0     |
| complete        | lite           | measurement | 1148.6865323754814     | 1148.688340707468      | 1024.0     |
| complete        | lite           | measurement | 1135.7528644291735     | 1135.7561105305708     | 1024.0     |
| complete        | lite           | measurement | 1105.1430731269438     | 1105.119603723379      | 1024.0     |
| complete        | lite           | measurement | 1236.0028347806197     | 1235.9706646360069     | 1024.0     |
| complete        | lite           | measurement | 1275.0093807182702     | 1274.936756564472      | 1024.0     |
| complete        | lite           | measurement | 1039.724544393963      | 1039.7241608674087     | 1024.0     |
| complete        | lite           | measurement | 1237.1267536750613     | 1237.1284360154393     | 1024.0     |
| complete        | lite           | measurement | 1218.6751154279739     | 1218.6302461999048     | 1024.0     |
| complete        | lite           | measurement | 1374.4634127814647     | 1374.2130403687854     | 1024.0     |
| complete        | lite           | measurement | 1310.888763514825      | 1310.890290222405      | 1024.0     |
| complete        | lite           | measurement | 1154.8662668336758     | 1154.8706635243193     | 1024.0     |
| complete        | lite           | measurement | 1085.1086240372922     | 1084.8112312959868     | 1024.0     |
| complete        | lite           | measurement | 834.3854451523633      | 834.3825251424829      | 1024.0     |
| complete        | lite           | measurement | 1010.9688025720333     | 1010.96792249373       | 1024.0     |
| complete        | lite           | measurement | 1093.9132575165775     | 1093.9132241664195     | 1024.0     |
| complete        | lite           | measurement | 1382.0368188176062     | 1382.0236176267883     | 1024.0     |
| complete        | lite           | measurement | 1127.8321141895935     | 1127.8298130155504     | 1024.0     |
| complete        | lite           | measurement | 664.2453513290922      | 664.2463407223185      | 1024.0     |
| complete        | lite           | measurement | 1327.7695359109885     | 1327.7718741430915     | 1024.0     |
| complete        | lite           | measurement | 1113.7395038962864     | 1113.7402376029227     | 1024.0     |
| complete        | lite           | measurement | 1075.1306464054423     | 1075.1308150091695     | 1024.0     |
| complete        | lite           | measurement | 1121.9231218175569     | 1121.9227901668337     | 1024.0     |
| complete        | lite           | measurement | 1310.8038886531228     | 1310.789505376825      | 1024.0     |
| complete        | lite           | measurement | 962.5158896021986      | 962.5145574404677      | 1024.0     |
| complete        | lite           | measurement | 1052.4198998022484     | 1052.4209651599765     | 1024.0     |
| complete        | lite           | measurement | 728.2507300027688      | 728.2480675308225      | 1024.0     |
| complete        | lite           | measurement | 835.0209199512572      | 835.0186187755288      | 1024.0     |
| complete        | lite           | measurement | 1325.9237962374355     | 1325.9236850686534     | 1024.0     |
| complete        | lite           | measurement | 1077.9636517953254     | 1077.962308513233      | 1024.0     |
| complete        | lite           | measurement | 1241.2847937069932     | 1240.9641742816546     | 1024.0     |
| complete        | lite           | measurement | 1305.9336753604957     | 1305.9093147608598     | 1024.0     |
| complete        | lite           | measurement | 1049.9126034791852     | 1049.8834756282652     | 1024.0     |
| complete        | lite           | measurement | 1219.7487938279448     | 1219.711576657695      | 1024.0     |
| complete        | lite           | measurement | 623.4981342320508      | 623.499740608164       | 1024.0     |
| complete        | lite           | measurement | 989.6119109046139      | 989.6134691064394      | 1024.0     |
| complete        | lite           | measurement | 1023.7802487936325     | 1023.7787813771474     | 1024.0     |
| complete        | lite           | measurement | 1184.9257027689446     | 1184.8060879264333     | 1024.0     |
| complete        | lite           | measurement | 1061.8913240838033     | 1061.8955781102873     | 1024.0     |
| complete        | lite           | measurement | 1068.9951679024118     | 1068.969065670592      | 1024.0     |
| complete        | lite           | measurement | 1267.6781669887555     | 1267.5211107899431     | 1024.0     |
| complete        | lite           | measurement | 1270.249720227031      | 1270.2490513670098     | 1024.0     |
| complete        | lite           | measurement | 1210.1837494722904     | 1209.9341682044974     | 1024.0     |
| complete        | lite           | measurement | 1068.3397736623865     | 1062.8797366802273     | 1024.0     |
| complete        | lite           | measurement | 1166.1845072678482     | 1159.5487860461888     | 1024.0     |
| complete        | lite           | measurement | 1092.607443803562      | 1087.2167144688642     | 1024.0     |
| complete        | lite           | measurement | 1177.9611134609809     | 1176.7434786759688     | 32768.0    |
| complete        | lite           | measurement | 1176.3125202894216     | 1176.2004268899861     | 32768.0    |
| complete        | lite           | measurement | 1026.7121697740579     | 1026.4845228515806     | 32768.0    |
| complete        | lite           | measurement | 1088.5411560128925     | 1086.1502830021482     | 32768.0    |
| complete        | lite           | measurement | 1155.7913039929804     | 1148.5600755581706     | 32768.0    |
| complete        | lite           | measurement | 1105.223596241675      | 1103.7487800220897     | 32768.0    |
| complete        | lite           | measurement | 1090.184566494866      | 1089.993673026842      | 32768.0    |
| complete        | lite           | measurement | 1220.3665784702587     | 1220.177052958906      | 32768.0    |
| complete        | lite           | measurement | 1020.2505980555331     | 1011.7139155221487     | 32768.0    |
| complete        | lite           | measurement | 1200.437177616643      | 1192.9223605788357     | 32768.0    |
| complete        | lite           | measurement | 1144.1962602807405     | 1144.1672235785038     | 32768.0    |
| complete        | lite           | measurement | 1343.6937780440192     | 1343.6825275160002     | 32768.0    |
| complete        | lite           | measurement | 995.6473479622433      | 995.6188499884095      | 32768.0    |
| complete        | lite           | measurement | 1126.9057705138587     | 1126.8913612744022     | 32768.0    |
| complete        | lite           | measurement | 1011.3190177431773     | 1011.2922532425869     | 32768.0    |
| complete        | lite           | measurement | 1090.829484051278      | 1090.7728713465478     | 32768.0    |
| complete        | lite           | measurement | 1093.6149015970873     | 1093.5960052372561     | 32768.0    |
| complete        | lite           | measurement | 1089.1282238365632     | 1089.115074808051      | 32768.0    |
| complete        | lite           | measurement | 1246.9551997377691     | 1246.9105290435216     | 32768.0    |
| complete        | lite           | measurement | 1078.4352968457056     | 1078.4350049781121     | 32768.0    |
| complete        | lite           | measurement | 1261.8833035557673     | 1261.8526493091995     | 32768.0    |
| complete        | lite           | measurement | 1209.6609784365103     | 1209.6467928697164     | 32768.0    |
| complete        | lite           | measurement | 1236.4352013735588     | 1236.3985311165945     | 32768.0    |
| complete        | lite           | measurement | 953.6447661653634      | 953.6460659292751      | 32768.0    |
| complete        | lite           | measurement | 1086.4710342197236     | 1086.4600755581737     | 32768.0    |
| complete        | lite           | measurement | 1039.5666030193054     | 1039.5016639162068     | 32768.0    |
| complete        | lite           | measurement | 939.0857489668688      | 939.0763164713984      | 32768.0    |
| complete        | lite           | measurement | 970.1934861770001      | 970.1444524760846      | 32768.0    |
| complete        | lite           | measurement | 1154.792115492083      | 1154.7634743115932     | 32768.0    |
| complete        | lite           | measurement | 1159.8957024606573     | 1159.8476971126865     | 32768.0    |
| complete        | lite           | measurement | 903.6874156109146      | 903.6914608366012      | 32768.0    |
| complete        | lite           | measurement | 958.4452216968043      | 958.0679532466879      | 32768.0    |
| complete        | lite           | measurement | 1047.5559675953236     | 1047.5075339943564     | 32768.0    |
| complete        | lite           | measurement | 959.0539340703652      | 959.0388210744615      | 32768.0    |
| complete        | lite           | measurement | 969.6542177534521      | 969.354573723754       | 32768.0    |
| complete        | lite           | measurement | 1064.8366320706366     | 1064.819507371692      | 32768.0    |
| complete        | lite           | measurement | 1057.6566631680837     | 1057.5784400103664     | 32768.0    |
| complete        | lite           | measurement | 1295.7334338052856     | 1295.7341061905943     | 32768.0    |
| complete        | lite           | measurement | 1119.6907789042928     | 1119.6672249423816     | 32768.0    |
| complete        | lite           | measurement | 1024.9618035760132     | 1024.9259216322814     | 32768.0    |
| complete        | lite           | measurement | 1029.080908608122      | 1029.041412419364      | 32768.0    |
| complete        | lite           | measurement | 898.9702159000116      | 898.9226292603647      | 32768.0    |
| complete        | lite           | measurement | 1310.3794329058114     | 1310.3604942649422     | 32768.0    |
| complete        | lite           | measurement | 1023.9365052325968     | 1023.9197501398014     | 32768.0    |
| complete        | lite           | measurement | 1211.947838955993      | 1211.9327791492244     | 32768.0    |
| complete        | lite           | measurement | 1064.8364711349407     | 1064.8139973540879     | 32768.0    |
| complete        | lite           | measurement | 901.597452297904       | 901.5964512213461      | 32768.0    |
| complete        | lite           | measurement | 958.2952701133279      | 958.2867895964466      | 32768.0    |
| complete        | lite           | measurement | 1207.8354646014614     | 1207.819079117858      | 32768.0    |
| complete        | lite           | measurement | 1329.5655937588165     | 1329.535876488357      | 32768.0    |
| nop             | lite           | measurement | 38.110806619504665     | 38.1103878926192       | 1.0        |
| nop             | lite           | measurement | 38.11982587211032      | 38.119949977731416     | 1.0        |
| nop             | lite           | measurement | 35.60234371277777      | 35.60241076147078      | 1.0        |
| nop             | lite           | measurement | 35.52463371233377      | 35.52400712354319      | 1.0        |
| nop             | lite           | measurement | 35.60890345713732      | 35.598908831390666     | 1.0        |
| nop             | lite           | measurement | 35.56469826472105      | 35.56482291633165      | 1.0        |
| nop             | lite           | measurement | 35.587525729533816     | 35.58658169680518      | 1.0        |
| nop             | lite           | measurement | 35.59162558347666      | 35.591650153373905     | 1.0        |
| nop             | lite           | measurement | 35.60446562969847      | 35.604553426382886     | 1.0        |
| nop             | lite           | measurement | 35.54877823649765      | 35.548899666793055     | 1.0        |
| nop             | lite           | measurement | 35.55656571477951      | 35.55600808581229      | 1.0        |
| nop             | lite           | measurement | 35.55250075029243      | 35.551779212311956     | 1.0        |
| nop             | lite           | measurement | 35.589655344987555     | 35.5886050608781       | 1.0        |
| nop             | lite           | measurement | 35.64580476279574      | 35.64589305086534      | 1.0        |
| nop             | lite           | measurement | 35.553413005948464     | 35.55355906071306      | 1.0        |
| nop             | lite           | measurement | 35.58651017091633      | 35.58656859282283      | 1.0        |
| nop             | lite           | measurement | 35.599918493220784     | 35.599511614578184     | 1.0        |
| nop             | lite           | measurement | 35.703484015827875     | 35.702958709952256     | 1.0        |
| nop             | lite           | measurement | 35.893405000517724     | 35.793778425745394     | 1.0        |
| nop             | lite           | measurement | 35.81522980865446      | 35.81531323732079      | 1.0        |
| nop             | lite           | measurement | 35.84754892460622      | 35.84723661309451      | 1.0        |
| nop             | lite           | measurement | 35.844696788295025     | 35.84365141812669      | 1.0        |
| nop             | lite           | measurement | 36.199621371308744     | 35.909685824925454     | 1.0        |
| nop             | lite           | measurement | 35.80679553968121      | 35.79414806724712      | 1.0        |
| nop             | lite           | measurement | 35.74602500250775      | 35.74449800636577      | 1.0        |
| nop             | lite           | measurement | 35.66693449752423      | 35.667047901552834     | 1.0        |
| nop             | lite           | measurement | 35.598739025619565     | 35.59882054330985      | 1.0        |
| nop             | lite           | measurement | 35.5881571230598       | 35.58826626833473      | 1.0        |
| nop             | lite           | measurement | 35.61087014644528      | 35.610933809983365     | 1.0        |
| nop             | lite           | measurement | 35.57156906487411      | 35.571136633422135     | 1.0        |
| nop             | lite           | measurement | 35.57613039728185      | 35.5761895290117       | 1.0        |
| nop             | lite           | measurement | 35.60136408087952      | 35.60148944231259      | 1.0        |
| nop             | lite           | measurement | 35.56451884932358      | 35.5646368943824       | 1.0        |
| nop             | lite           | measurement | 35.56032060641034      | 35.56036854513535      | 1.0        |
| nop             | lite           | measurement | 35.592723587856014     | 35.59245162569375      | 1.0        |
| nop             | lite           | measurement | 35.618258663137574     | 35.575754312998356     | 1.0        |
| nop             | lite           | measurement | 35.58992517790013      | 35.589981361223046     | 1.0        |
| nop             | lite           | measurement | 35.594627323593166     | 35.594772613965524     | 1.0        |
| nop             | lite           | measurement | 35.560348670724025     | 35.56044809722792      | 1.0        |
| nop             | lite           | measurement | 35.522294651493006     | 35.522377861739045     | 1.0        |
| nop             | lite           | measurement | 35.56033387412664      | 35.560444056833425     | 1.0        |
| nop             | lite           | measurement | 35.52965892577639      | 35.52885406821049      | 1.0        |
| nop             | lite           | measurement | 35.56817109298652      | 35.56825353890782      | 1.0        |
| nop             | lite           | measurement | 35.65557148848413      | 35.65312721351518      | 1.0        |
| nop             | lite           | measurement | 35.796585189589536     | 35.796566843987144     | 1.0        |
| nop             | lite           | measurement | 35.72708166725118      | 35.72728647156318      | 1.0        |
| nop             | lite           | measurement | 35.83322894731306      | 35.83339340235235      | 1.0        |
| nop             | lite           | measurement | 35.55572160000488      | 35.55532662413073      | 1.0        |
| nop             | lite           | measurement | 35.591038088224536     | 35.591208549168925     | 1.0        |
| nop             | lite           | measurement | 35.59113746013219      | 35.590686901472296     | 1.0        |
| nop             | lite           | measurement | 32.15815746538057      | 32.157640515155286     | 32.0       |
| nop             | lite           | measurement | 32.01621556424229      | 32.01571680258658      | 32.0       |
| nop             | lite           | measurement | 32.0283739304795       | 32.02792233960789      | 32.0       |
| nop             | lite           | measurement | 32.05420458513627      | 32.05432570445549      | 32.0       |
| nop             | lite           | measurement | 32.03679845075908      | 32.03689164420103      | 32.0       |
| nop             | lite           | measurement | 32.03965387165498      | 32.03981214887703      | 32.0       |
| nop             | lite           | measurement | 32.04951533454708      | 32.04947606371195      | 32.0       |
| nop             | lite           | measurement | 32.03388639736518      | 32.033269961191245     | 32.0       |
| nop             | lite           | measurement | 32.0627294182118       | 32.061882455761264     | 32.0       |
| nop             | lite           | measurement | 32.02344184410205      | 32.02230037384856      | 32.0       |
| nop             | lite           | measurement | 32.05258952328848      | 32.05262236379488      | 32.0       |
| nop             | lite           | measurement | 32.04441596838553      | 32.04444476698029      | 32.0       |
| nop             | lite           | measurement | 32.038449430424116     | 32.038554887345335     | 32.0       |
| nop             | lite           | measurement | 32.071815570519604     | 32.07191202503869      | 32.0       |
| nop             | lite           | measurement | 32.176388653263515     | 32.17604669904645      | 32.0       |
| nop             | lite           | measurement | 32.02859536240377      | 32.02869875245737      | 32.0       |
| nop             | lite           | measurement | 32.0670492940753       | 32.06713086699465      | 32.0       |
| nop             | lite           | measurement | 32.077792948182825     | 32.07795834469721      | 32.0       |
| nop             | lite           | measurement | 32.07947745720951      | 32.078769848615195     | 32.0       |
| nop             | lite           | measurement | 32.095405127710414     | 32.094862318540414     | 32.0       |
| nop             | lite           | measurement | 32.064849626054404     | 32.0645349087693       | 32.0       |
| nop             | lite           | measurement | 32.01090179358638      | 32.010945749300255     | 32.0       |
| nop             | lite           | measurement | 32.092971121265684     | 32.09303243875307      | 32.0       |
| nop             | lite           | measurement | 32.00502523393077      | 32.0050775948947       | 32.0       |
| nop             | lite           | measurement | 32.04682517233799      | 32.046436047308774     | 32.0       |
| nop             | lite           | measurement | 32.048628320469334     | 32.04833771680788      | 32.0       |
| nop             | lite           | measurement | 32.028052691054484     | 32.02821946541969      | 32.0       |
| nop             | lite           | measurement | 32.045869905309154     | 32.045007601993106     | 32.0       |
| nop             | lite           | measurement | 32.01345062694742      | 32.013556818731786     | 32.0       |
| nop             | lite           | measurement | 32.04937671556183      | 32.049362477047346     | 32.0       |
