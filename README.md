
# signalgp-lite

[![version](https://img.shields.io/endpoint?url=https%3A%2F%2Fmmore500.github.io%2Fsignalgp-lite%2Fversion-badge.json)](https://github.com/mmore500/signalgp-lite/releases)
[![](https://img.shields.io/travis/mmore500/signalgp-lite.svg)](https://travis-ci.com/mmore500/signalgp-lite)
[![Documentation Status](https://readthedocs.org/projects/signalgp-lite/badge/?version=latest)](https://signalgp-lite.readthedocs.io/en/latest/?badge=latest)
[![documentation coverage](https://img.shields.io/endpoint?url=https%3A%2F%2Fmmore500.github.io%2Fsignalgp-lite%2Fdocumentation-coverage-badge.json)](https://signalgp-lite.readthedocs.io/en/latest/)
[![code coverage status](https://codecov.io/gh/mmore500/signalgp-lite/branch/master/graph/badge.svg)](https://codecov.io/gh/mmore500/signalgp-lite)
[![dotos](https://img.shields.io/endpoint?url=https%3A%2F%2Fmmore500.com%2Fsignalgp-lite%2Fdoto-badge.json)](https://github.com/mmore500/signalgp-lite/search?q=todo+OR+fixme&type=)
[![GitHub stars](https://img.shields.io/github/stars/mmore500/signalgp-lite.svg?style=flat-square&logo=github&label=Stars&logoColor=white)](https://github.com/mmore500/signalgp-lite)

<!-- Check out the live in-browser web app at <https://mmore500.github.io/signalgp-lite>. -->

-   Free software: MIT license
-   Documentation: <https://signalgp-lite.readthedocs.io>.

A genetic programming implementation designed for large-scale artificial life applications.
Organized as a header-only C++ library.
Inspired by [Alex Lalejini](http://lalejini.com/)'s [SignalGP](https://github.com/amlalejini/signalgp).

## Benchmarks

signalgp-lite provides several-times speedup over the current "vanilla" SignalGP implementation.

[![lite speedup, compared to vanilla](docs/assets/measurement=wall-speedup+ext=.png)](https://osf.io/2pdur/)
*[Speedup](https://en.wikipedia.org/wiki/Speedup) of mean instruction execution time provided by signalgp-lite compared to vanilla SignalGP.
Speedup is measured for random programs generated from different subsets of instructions ("libraries") over different-size populations of virtual CPUs ("num agents").*

For randomly-generated programs composed of arbitrary instructions, signalgp-lite approaches a virtual instruction execution rate of around 10Mhz on a 3.5Ghz processor.
Virtual nop instructions execute at rate of around 200Mhz.

[![raw timings of lite and vanilla](docs/assets/fliers=True+measurement=wall-nanoseconds+ext=.png)](https://osf.io/6te73/)
*[Wall clock](https://en.wikipedia.org/wiki/Elapsed_real_time) timings of twenty randomly-generated programs composed of instructions from different libraries.*

Timings for `nop` and `arithmetic` libraries report the mean time to execute sixteen instructions on one core.
Timings for `complete` and `sans_regulation` libraries report timings for executing sixteen instructions, one each across sixteen virtual threads.
(`sans_regulation` refers to the `complete` library with tag-matching regulation disabled.)

These results are associated with [commit c10ed70](https://github.com/mmore500/signalgp-lite/commit/c10ed70), measured at 1602292830 seconds since epoch.
Details on the machine used to perform these benchmarks are available via [Open Science Framework](https://osf.io/), e.g., <https://osf.io/hu8m2/>.
[mimalloc](https://github.com/microsoft/mimalloc) memory allocator.

Microbenchmarks are performed, graphed, and uploaded as part of the project's CI build, so check the [project's OSF page](https://osf.io/j8pge/) for up-to-the-minute profiling information!

## Credits

This library draws heavily on Alex Lalejini's work with SignalGP.

This package was created with [Cookiecutter](https://github.com/audreyr/cookiecutter) and the [devosoft/cookiecutter-empirical-project](https://github.com/devosoft/cookiecutter-empirical-project) project template.

This package uses [Empirical](https://github.com/devosoft/Empirical#readme), a library of tools for scientific software development, with emphasis on also being able to build web interfaces using [Emscripten](.
