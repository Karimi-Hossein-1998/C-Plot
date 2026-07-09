# C++Plot

This is a *standalone*, *header-only*, and lightweight tool for plotting in `C++`.The emphasis is on self-sustained, and performant code that can generate visual documentations for a given set of data. The data is assumed to be in the form of `std::vector<double>` (or *aliased* as `dVec`) containers.

## Table of Contents

1. [C++Plot](#cplot)
    1. [Table of Contents](#table-of-contents)
    2. [Plot2D](#plot2d)

## Plot2D

It is a header file [Plot2D.hpp](headers/Plot2D.hpp) that helps generate plots of *lines* and *curves* that visualizes *2-D* data series. It can generate plot of multiple data series on one plot. There is no multi-plot/subplots, since it is usually achieved in a better way by using conventional tools like \LaTeX and other scientific documentation tools. The documentation can be accessed on [docs/Plot2D.md](docs/Plot2D.md).

## PlotPolar

It is a header file [PlotPolar.hpp](headers/PlotPolar.hpp) that helps generate plots of *points* that visualize the *2-D polar* data series on the *polar* coordinates. Multiple data series can be plotted on one plot. The documentation is available on [docs/PlotPolar.md](docs/PlotPolar.md).
