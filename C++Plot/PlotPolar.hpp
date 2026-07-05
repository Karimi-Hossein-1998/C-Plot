#pragma once
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstddef>
#include <format>

template<typename T>
using Vec  = std::vector<T>;
using dVec = Vec<double>;
using Point = std::pair<double, double>;

constexpr double PI = 3.141592653589793; // \pi

class PlotPolarData
{
    public:
        dVec rs;
        dVec thetas;
        double pointsRadius;
        double pointsColor;
        std::string pointsLabel;
};

class PlotPolar
{
    private:
        double epsilon = 1.0e-10;
        double width = 1000.0;
        dVec rVals;
        dVec thetaVals;
        double padding = 100.0;
        double plotPad = 10.0;
        double rMax;
        double rMin;
        double rRange;
        double rScale;
        dVec xVals;
        dVec yVals;
        double drawW;
        size_t numRDivisions = 5.0;
        size_t numThetaDivisions = 12;
        dVec divisionsR;
        dVec divisionsTheta;
        double rStep;
        double thetaStep;
        double gLeft;
        double gRight;
        double gTop;
        double gBottom;
        bool border=true;
        double borderLineWidth = 2.5;
        double axisLineWidth = 1.5;
        double gridLineWidth = 0.5;
        size_t plotNumeralsSignificantDigits = 3;
        double plotNumeralsFontSize = 15;
        double plotPointsBorderWidth = 1.5;
        bool plotPointsFill = true;
        double plotPointsRadius = 5;
        std::string plotPointsBorderColor = "#000000";
        std::string plotPointsFillColor = "#0000ff";
        std::string plotNumeralsColor = "#3f003f";
        std::string backColor = "#ffffff";
        std::string borderColor = "#000000";
        std::string axisColor = "#000000";
        std::string gridColor = "#101010";
        std::string plotTitleColor = "#000000";
        inline double calcRDivisionsStep()
        {
            double rawStep  = rRange / numRDivisions;
            double exponent = std::floor(std::log10(rawStep));
            double fraction = rawStep / std::pow(10.0,exponent);
            double cleanFraction = 1.0;
            if (fraction<1.2) cleanFraction = 1.0;
            else if (fraction<1.5) cleanFraction = 1.25;
            else if (fraction<2.25) cleanFraction = 2.0;
            else if (fraction<3.75) cleanFraction = 2.5;
            else if (fraction<7.5) cleanFraction = 5.0;
            else cleanFraction = 10.0;
            return cleanFraction*std::pow(10.0,exponent);
        };
        inline double toPixelX(double x) { return (width/2.0 + x*rScale); };
        inline double toPixelY(double y) { return (width/2.0 - y*rScale); };
        inline double rttox(double r, double t) { return r*cos(t); };
        inline double rttoy(double r, double t) { return r*sin(t); };
        inline void writeNumerals(std::ofstream& file);
    public:
        PlotPolar(dVec rs, dVec thetas, double w = 1000.0, double pad = 100.0, double ppad = 10.0, size_t nrd = 5, size_t ntd = 12)
        : rVals(rs), thetaVals(thetas), width(w), padding(pad), plotPad(ppad), numRDivisions(nrd), numThetaDivisions(ntd)
        {
            if ( rVals.empty() )
                throw std::runtime_error("Values of Rs are empty!");
            if ( rVals.size() != thetaVals.size() )
                throw std::runtime_error("Rs, and Thetas don't match in size!");
            if ( width<=2*padding )
                throw std::runtime_error("Padding is too large! It exceeds width!");
            rMin = *std::min_element(rVals.begin(),rVals.end());
            rMax = *std::max_element(rVals.begin(),rVals.end());
            rRange = (std::abs(rMin)<=std::abs(rMax)) ? std::abs(rMax) : std::abs(rMin);
            drawW = width - 2*padding;
            rScale = 0.5 * drawW / rRange;
        };
        inline void forceRMax(double rm)
        {
            rMax = std::abs(rm);
            rRange = rMax;
            rScale = 0.5 * drawW / rRange;
        }
        inline void plotSVG(std::string filename);
};

inline void PlotPolar::writeNumerals(std::ofstream& file)
{
    file << " \n";
    file << " <g font-family=\"sans-serif\" font-size=\"" << PlotPolar::plotNumeralsFontSize
         << "\" fill=\"" << PlotPolar::plotNumeralsColor << "\">\n";

    // --- X-AXIS NUMERALS ---
    for ( size_t i=0; i<PlotPolar::divisionsR.size(); ++i)
    {
        std::stringstream ss;
        // defaultfloat strips trailing zeros and manages scientific boundaries dynamically
        // 3 significant digits means: 1234, 123.4, 12.34, 1.234, or 1.234e+05
        ss << std::defaultfloat << std::setprecision(PlotPolar::plotNumeralsSignificantDigits) << PlotPolar::divisionsR[i];
        std::string labelStr = ss.str();

        // Elegant parsing check for scientific strings
        size_t ePos = labelStr.find('e');
        if (ePos != std::string::npos)
        {
            std::string mantissa = labelStr.substr(0, ePos);
            std::string exponent = labelStr.substr(ePos + 1);
            int expVal = std::stoi(exponent); // Strips leading '+' or zeros (e.g. "+04" -> 4)
            std::string superscriptExp = "";
            std::string expStr = std::to_string(expVal);

            for (char c : expStr)
            {
                if (c == '-') superscriptExp += "&#8315;"; // Unicode ⁻
                else if (c == '0') superscriptExp += "&#8304;";  // Unicode ⁰
                else if (c == '1') superscriptExp += "&#185;";  // Unicode ¹
                else if (c == '2') superscriptExp += "&#178;";  // Unicode ²
                else if (c == '3') superscriptExp += "&#179;";  // Unicode ³
                else if (c == '4') superscriptExp += "&#8308;"; // Unicode ⁴
                else if (c == '5') superscriptExp += "&#8309;"; // Unicode ⁵
                else if (c == '6') superscriptExp += "&#8310;"; // Unicode ⁶
                else if (c == '7') superscriptExp += "&#8311;"; // Unicode ⁷
                else if (c == '8') superscriptExp += "&#8312;"; // Unicode ⁸
                else if (c == '9') superscriptExp += "&#8313;"; // Unicode ⁹
            }
            labelStr = mantissa + "&#215;10" + superscriptExp;
        }

        file << "   <text x=\"" << PlotPolar::toPixelX(PlotPolar::divisionsR[i])
             << "\" y=\"" << PlotPolar::width*0.51 + PlotPolar::plotNumeralsFontSize
             << "\" text-anchor=\"middle\" dominant-baseline=\"hanging\">"
             << labelStr << "</text>\n";
    }
    file << "   <text x=\"" << PlotPolar::toPixelX(0.0)
         << "\" y=\"" << PlotPolar::width*0.51 + PlotPolar::plotNumeralsFontSize
         << "\" text-anchor=\"middle\" dominant-baseline=\"hanging\">"
         << "0" << "</text>\n";

    // --- Y-AXIS NUMERALS ---
    double toDegree = 180/PI;
    for ( size_t i=0; i<PlotPolar::divisionsTheta.size(); ++i )
    {
        std::stringstream ss;
        ss << std::defaultfloat << std::setprecision(PlotPolar::plotNumeralsSignificantDigits) << PlotPolar::divisionsTheta[i]*toDegree;
        std::string labelStr = ss.str();

        // Elegant parsing check for scientific strings
        size_t ePos = labelStr.find('e');
        if (ePos != std::string::npos)
        {
            std::string mantissa = labelStr.substr(0, ePos);
            std::string exponent = labelStr.substr(ePos + 1);
            int expVal = std::stoi(exponent);
            std::string superscriptExp = "";
            std::string expStr = std::to_string(expVal);
            for (char c : expStr)
            {
                if (c == '-') superscriptExp += "&#8315;"; // Unicode ⁻
                else if (c == '0') superscriptExp += "&#8304;";  // Unicode ⁰
                else if (c == '1') superscriptExp += "&#185;";  // Unicode ¹
                else if (c == '2') superscriptExp += "&#178;";  // Unicode ²
                else if (c == '3') superscriptExp += "&#179;";  // Unicode ³
                else if (c == '4') superscriptExp += "&#8308;"; // Unicode ⁴
                else if (c == '5') superscriptExp += "&#8309;"; // Unicode ⁵
                else if (c == '6') superscriptExp += "&#8310;"; // Unicode ⁶
                else if (c == '7') superscriptExp += "&#8311;"; // Unicode ⁷
                else if (c == '8') superscriptExp += "&#8312;"; // Unicode ⁸
                else if (c == '9') superscriptExp += "&#8313;"; // Unicode ⁹
            }
            labelStr = mantissa + "&#215;10" + superscriptExp;
        }

        // Added dominant-baseline="central" to keep numbers aligned with the tick line rows
        file << "   <text x=\"" <<  PlotPolar::toPixelX(PlotPolar::rttox(((drawW+plotPad*0.75)/(drawW))*rRange,divisionsTheta[i]))
             << "\" y=\"" << PlotPolar::toPixelY(PlotPolar::rttoy(((drawW+plotPad*0.75)/(drawW))*rRange,divisionsTheta[i]))+PlotPolar::plotNumeralsFontSize*0.25
             << "\" text-anchor=\"middle\" dominant-baseline=\"central\">"
             << labelStr << "</text>\n";
    }
    file << " </g>\n";
}

inline void PlotPolar::plotSVG(std::string filename)
{
    std::ofstream file(filename, std::ios::trunc);

    // Setting up some parameters
    rStep = calcRDivisionsStep();
    thetaStep = 2*PI/numThetaDivisions;
    for ( double val=rStep; val<=rRange+epsilon; val+=rStep )
    {
        divisionsR.push_back(val);
    }
    for ( size_t i=0; i<numThetaDivisions; ++i )
    {
        divisionsTheta.push_back(i*thetaStep);
    }

    // Background
    file << "<svg width=\"" << PlotPolar::width << "\" height=\"" << PlotPolar::width
        << "\" xmlns=\"http://www.w3.org/2000/svg\" style=\"background:" << PlotPolar::backColor <<";\">\n";

    file << " \n";
    file << " \n";
    // Painting background
    file << " <rect width=\"" << PlotPolar::width << "\" height=\"" << PlotPolar::width
        << "\" fill=\"" << PlotPolar::backColor << "\" />\n";
    // Marking corners
    PlotPolar::gLeft   = PlotPolar::toPixelX(PlotPolar::rttox(rRange, PI));
    PlotPolar::gRight  = PlotPolar::toPixelX(PlotPolar::rttox(rRange, 0.0));
    PlotPolar::gTop    = PlotPolar::toPixelY(PlotPolar::rttoy(rRange, PI/2.0));
    PlotPolar::gBottom = PlotPolar::toPixelY(PlotPolar::rttoy(rRange, -PI/2.0));
    // Border
    if ( border )
    {
        file << " \n";
        file << " <rect x=\"" << PlotPolar::gLeft-PlotPolar::plotPad << "\" y=\"" << PlotPolar::gTop-PlotPolar::plotPad
             << "\" width=\"" << (PlotPolar::gRight-PlotPolar::gLeft+2*PlotPolar::plotPad)
             << "\" height=\"" << (PlotPolar::gBottom-PlotPolar::gTop+2*PlotPolar::plotPad)
             << "\" fill=\"none\" stroke=\"" << PlotPolar::borderColor << "\" stroke-width=\"" << PlotPolar::borderLineWidth << "\" />\n";
    }
    // Drawing xAxis
    file << " \n";
    double xAxisX1 = PlotPolar::gLeft;
    double xAxisX2 = PlotPolar::gRight;
    double xAxisY1 = PlotPolar::toPixelY(0.0);
    double xAxisY2 = PlotPolar::toPixelY(0.0);
    // file << " <line x1=\"" << xAxisX1 << "\" y1=\"" << xAxisY1
    //     << "\" x2=\"" << xAxisX2 << "\" y2=\"" << xAxisY2
    //     << "\" stroke=\"" << PlotPolar::axisColor << "\" stroke-width=\"" << PlotPolar::axisLineWidth << "\" stroke-linecap=\"round\" />\n";
    // Drawing yAxis
    double yAxisX1 = PlotPolar::toPixelX(0.0);
    double yAxisX2 = PlotPolar::toPixelX(0.0);
    double yAxisY1 = PlotPolar::gBottom;
    double yAxisY2 = PlotPolar::gTop;
    // file << " <line x1=\"" << yAxisX1 << "\" y1=\"" << yAxisY1
    //     << "\" x2=\"" << yAxisX2 << "\" y2=\"" << yAxisY2
    //     << "\" stroke=\"" << PlotPolar::axisColor << "\" stroke-width=\"" << PlotPolar::axisLineWidth << "\" stroke-linecap=\"round\" />\n";
    // Drawing the grid
    for ( double r : PlotPolar::divisionsR )
    {
        file << " <circle cx=\"" << yAxisX1 << "\" cy=\"" << xAxisY1
            << "\" r=\"" << r*rScale << "\" stroke=\"" << PlotPolar::gridColor
            << "\" fill=\"none\" stroke-width=\"" << PlotPolar::gridLineWidth << "\" />\n";
    }
    // file << " <circle cx=\"" << yAxisX1 << "\" cy=\"" << xAxisY1
    //     << "\" r=\"" << divisionsR[divisionsR.size()-1]*rScale << "\" stroke=\"" << PlotPolar::axisColor
    //     << "\" fill=\"none\" stroke-width=\"" << PlotPolar::axisLineWidth << "\" />\n";
    for ( double t : divisionsTheta )
    {
        file << " <line x1=\"" << yAxisX1 << "\" y1=\"" << xAxisY1
            << "\" x2=\"" << PlotPolar::toPixelX(PlotPolar::rttox(rRange,t))
            << "\" y2=\"" << PlotPolar::toPixelY(PlotPolar::rttoy(rRange,t))
            << "\" stroke=\"" << PlotPolar::gridColor
            << "\" stroke-width=\"" << PlotPolar::gridLineWidth << "\" stroke-linecap=\"round\" />\n";
    }
    // Writing Numbers
    PlotPolar::writeNumerals(file);

    // Plot
    file << " \n";
    if ( PlotPolar::plotPointsFill )
    {
        for ( size_t i=0; i<rVals.size(); ++i )
        {
            file << " <circle cx=\"" << PlotPolar::toPixelX(PlotPolar::rttox(rVals[i],thetaVals[i]))
                << "\" cy=\"" << PlotPolar::toPixelY(PlotPolar::rttoy(rVals[i],thetaVals[i]))
                << "\" r=\"" << PlotPolar::plotPointsRadius
                << "\" stroke=\"" << PlotPolar::plotPointsBorderColor
                << "\" fill=\"" << PlotPolar::plotPointsFillColor
                << "\" stroke-width=\"" << PlotPolar::plotPointsBorderWidth << "\" />\n";
        }
    }
    else
    {
        for ( size_t i=0; i<rVals.size(); ++i )
        {
            file << " <circle cx=\"" << PlotPolar::toPixelX(PlotPolar::rttox(rVals[i],thetaVals[i]))
                << "\" cy=\"" << PlotPolar::toPixelY(PlotPolar::rttoy(rVals[i],thetaVals[i]))
                << "\" r=\"" << PlotPolar::plotPointsRadius
                << "\" stroke=\"" << PlotPolar::plotPointsBorderColor
                << "\" fill=\"none\" stroke-width=\"" << PlotPolar::plotPointsBorderWidth << "\" />\n";
        }
    }
    // End
    file << "</svg>\n";
    file.close();
}
