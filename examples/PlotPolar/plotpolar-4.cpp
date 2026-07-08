#include "../../C++Plot/PlotPolar.hpp"
#include <random>

int main()
{
    // std::random_device rd;
    // std::mt19937 re19937(rd());
    std::mt19937 re19937;
    std::uniform_real_distribution<double> urd;

    Vec<PlotPolarData> data;
    dVec rs={};
    dVec ts={};
    for ( size_t i=0; i<100; ++i)
    {
        rs.push_back(0.9+0.1*urd(re19937));
        ts.push_back(2*PI*(urd(re19937)-0.5));
    }
    PlotPolar plot(rs,ts, 1100, 150, 50, 8.0, 6.0);
    rs = {};
    ts = {};
    for( size_t i=0; i<200; ++i )
    {
        rs.push_back(1.0);
        ts.push_back(PI*0.5*urd(re19937));
    }
    plot.addData(rs,ts,true,1.0,5.0,0.8,0.7,0,0,0,127,127,255,"Uniform from 0 to 90 at 1");
    rs = {};
    ts = {};
    for( size_t i=0; i<200; ++i )
    {
        rs.push_back(0.1*urd(re19937)+0.8);
        ts.push_back(PI*0.5*(urd(re19937)+2.0));
    }
    data.push_back(PlotPolarData(rs,ts,true,1.0,5.0,0.7,0.6,63,63,63,255,0,0,"Uniform from 180 to 270 at 0.8 to 0.9"));
    rs = {};
    ts = {};
    for( size_t i=0; i<200; ++i )
    {
        rs.push_back(0.1*urd(re19937)+0.7);
        ts.push_back(PI*0.5*(urd(re19937)+1.0));
    }
    data.push_back(PlotPolarData(rs,ts,true,1.0,5.0,0.6,0.5,31,31,63,0,255,0,"Uniform from 90 to 180 at 0.7 to 0.8"));
    rs = {};
    ts = {};
    for( size_t i=0; i<200; ++i )
    {
        rs.push_back(0.1*urd(re19937)+0.6);
        ts.push_back(PI*2.0*urd(re19937)-PI);
    }
    data.push_back(PlotPolarData(rs,ts,true,1.0,5.0,0.5,0.4,127,127,255,31,31,31,"Uniform at 0.6 to 0.7"));
    // plot.forceRMax(1.0);
    plot.addMultipleData(data);
    plot.setnumRDivisions(10);
    plot.setnumThetaDivisions(12);
    plot.setplotPad(75);
    plot.setbackColor(255,255,255);
    plot.setplotTitle(true);
    plot.setplotTitleText("Title Test!");
    plot.setplotTitleFontSize(45);
    plot.setplotTitleColor(0,127,0);
    plot.setborder(true);
    plot.setborderLineWidth(3.0);
    plot.setborderLineColor(63,31,31);
    plot.setgridLineWidth(1.0);
    plot.setgridLineColor(0,0,0);
    plot.setplotNumerals(true);
    plot.setplotNumeralsSignificantDigits(3);
    plot.setplotNumeralsFontSize(20.0);
    plot.setplotNumeralsColor(255,0,0);
    plot.setplotPointsFill(true);
    plot.setplotPointsBorderWidth(3);
    plot.setplotPointsRadius(5);
    plot.setplotPointsBorderOpacity(1.0);
    plot.setplotPointsFillOpacity(1.0);
    plot.setplotPointsBorderColor(0,0,0);
    plot.setplotPointsFillColor(255,127,127);
    plot.setplotPointsLabel("Uniform at 0.9 to 1.0");
    plot.setplotLegend(true);
    plot.setlegendPos(LegendPos::BottomLeft);
    plot.setlegendFontSize(15.0);

    std::string filename = "pp-test-4.svg";
    plot.plotSVG(filename);
}
