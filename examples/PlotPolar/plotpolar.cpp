#include "../../C++Plot/PlotPolar.hpp"
#include <random>

int main()
{
    // std::random_device rd;
    // std::mt19937 re19937(rd());
    std::mt19937 re19937;
    std::uniform_real_distribution<double> urd;

    dVec rs={};
    dVec ts={};
    for ( size_t i=0; i<100; ++i)
    {
        rs.push_back(0.9+0.1*urd(re19937));
        ts.push_back(2*PI*(urd(re19937)-0.5));
    }
    PlotPolar plot(rs,ts, 1100, 150, 50, 8.0, 6.0);
    plot.forceRMax(1.0);
    std::string filename = "pp-test.svg";
    plot.plotSVG(filename);
}
