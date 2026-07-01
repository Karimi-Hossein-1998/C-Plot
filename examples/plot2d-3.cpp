#include "../C++Plot/Plot2D.hpp"

int main()
{
    Vec<Plot2DData> plotdata = {};
    dVec xs = {};
    dVec ys = {};
    for ( int i=-5000; i<5001; ++i )
    {
        xs.push_back(i*0.001);
        ys.push_back(exp(i*0.0004));
        // ys.push_back(xs[i],3));
    }
    Plot2DData pd(xs,ys,LineStyle::Solid, "#0000ff", 5);
    plotdata.push_back(pd);
    xs = {};
    ys = {};
    for ( int i=-5000; i<5001; ++i )
    {
        xs.push_back(i*0.001);
        ys.push_back(sin(i*0.001));
        // ys.push_back(xs[i],3));
    }
    Plot2DData pd2(xs,ys,LineStyle::Solid, "#ff0000", 5);
    plotdata.push_back(pd2);
    xs = {};
    ys = {};
    for ( int i=-5000; i<5001; ++i )
    {
        xs.push_back(i*0.001);
        ys.push_back(cos(i*0.001));
        // ys.push_back(xs[i],3));
    }
    Plot2DData pd3(xs,ys,LineStyle::Solid, "#00ff00", 5);
    plotdata.push_back(pd3);
    Plot2D plot(plotdata,2000,2300,150);
    std::string filename = "test-3.svg";
    plot.forceYMinMax(-1.0,7.5);
    plot.setborder(true);
    plot.setaxis(true);
    plot.setticks(true);
    plot.setgrid(true);
    plot.setaxisLabel(true);
    plot.setplotTitle(true);
    plot.setautoTicks(true);
    plot.setnumXTicks(21);
    plot.settickMarkSize(10.0);
    plot.setplotPad(5.0);
    plot.setborderLineWidth(1.5);
    plot.setaxisLineWidth(2.5);
    plot.setgridLineWidth(0.5);
    plot.setplotNumeralsFontSize(15);
    plot.setplotAxisLabelFontSize(18);
    plot.setplotTitleFontSize(50.0);
    plot.setxAxisLabel("X axis test!");
    plot.setyAxisLabel("Y axis test!");
    plot.setplotTitleText("Testing Title!");
    plot.setplotLineWidth(10.0);
    plot.setplotLineStyle(LineStyle::Dotted); // Solid, Dotted, Dashed, DashDot
    plot.setborderLineColor(31,0,31);
    plot.setaxisLineColor(15,0,15);
    plot.setgridLineColor(63,0,63);
    plot.setplotNumeralsColor(127,95,95);
    plot.setplotLineColor(255,191,191);
    plot.setplotAxisLabelColor(191,127,127);
    plot.setplotTitleColor(191,0,191);
    plot.setbackColor(255,255,255);
    plot.setplotNumeralsSignificantDigits(3);
    plot.plotSVG(filename);
    size_t R = 127, G = 1, B = 127;
    return 0;
}
