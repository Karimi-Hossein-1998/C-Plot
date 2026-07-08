# PlotPolar

The class `PlotPolar` is for creating a visual representation of data series better suited for *polar* coordinates. There are two ways to initialize a class object, one for a single data series and another for multiple data series. Also you can add one data series (or multiple data series) after initializing the object.

- **Single Data Series:**

```C++
    PlotPolar(dVec rs, dVec thetas, double w = 1000.0, double pad = 100.0, double ppad = 10.0, size_t nrd = 5, size_t ntd = 12)
```

- **Multiple Data Series:**

```C++
    PlotPolar(const Vec<PlotPolarData>& data, double w=1000.0, double pad=100.0, double ppad = 50.0, size_t nrd = 5, size_t ntd = 12)
```

## Table of Contents

1. [PlotPolar](#plotpolar)
    1. [Table of Contents](#table-of-contents)
    2. [`PlotPolar` Class](#plotpolar-class)
        1. [Main](#main)
        2. [Border](#border)
        3. [Grid](#grid)
        4. [Numerals](#numerals)
        5. [Title](#title)
        6. [Points](#points)
        7. [Legend](#legend)
        8. [Private Functions](#private-functions)
        9. [Plotting](#plotting)
    3. [`LegendPos` Enumeration Class](#legendpos-enumeration-class)
    4. [`PlotPolarData` Class](#plotpolardata-class)
    5. [Other Functions](#other-functions)

## `PlotPolar` Class

This *class* is aiming to visualize data series in polar coordinates.

### Main

- **`Vec<PlotPolarData> plotData`:** The *vector* of data series and plotting related arguments.
- **`double epsilon = 1.0e-10`:** Representative of *small* number (in case it is needed).
- **`double width = 1000.0`:** Width of the plot (in pixels).
- **`dVec rVals`:** Values of *r*.
- **`dVec thetaVals`:** Values of $\theta$.
- **`double padding = 100.0`:** The padding around the plot.
- **`double plotPad = 10.0`:** Outward padding from plot (plot width is extended by this value on all directions).
- **`double rMax`:** Maximum value of *r*.
- **`double rMin`:** Minimum value of *r*.
- **`double rRange`:** Highest distance from origin.
- **`double rScale`:** The *scale* of *r* (mapping points coordinates to pixels).
- **`double drawW`:** The width of the plot (without `plotPad`).
- **`size_t numRDivisions = 5.0`:** Number of segments on the *r* axis (from origin to the `rRange`).
- **`size_t numThetaDivisions = 12`:** Number of segments on the $\theta$ axis (from $0$ to $360$).
- **`dVec divisionsR`:** The *r* values of the *r* segment lines.
- **`dVec divisionsTheta`:** The $\theta$ values of the $\theta$ segment lines.
- **`double rStep`:** The distance between two segment lines on *r*.
- **`double thetaStep`:** The distance between two segment lines on $\theta$.
- **`double gLeft`:** Left side of the plot (before considering `plotPad`).
- **`double gRight`:** Right side of the plot (before considering `plotPad`).
- **`double gTop`:** Top side of the plot (before considering `plotPad`).
- **`double gBottom`:** Bottom side of the plot (before considering `plotPad`).
- **`std::string backColor = "#ffffff"`:** The background color.
- **`PlotPolar(const Vec<PlotPolarData>& data, double w=1000.0, double pad=100.0, double ppad = 50.0, size_t nrd = 5, size_t ntd = 12)`:** Initializer of the class.
- **`PlotPolar(dVec rs, dVec thetas, double w = 1000.0, double pad = 100.0, double ppad = 10.0, size_t nrd = 5, size_t ntd = 12)`:** Initializer of the class.
- **`inline void addData(const dVec& r, const dVec& t, bool pf, double pbw=1.0, double pr=5.0, double pbo=1.0, double pfo=1.0, double pbcr=0, double pbcg=0, double pbcb=0, double pfcr=0, double pfcg=0, double pfcb=255, std::string label="")`:** Add one data series.
- **`inline void addMultipleData(const Vec<PlotPolarData>& data)`:** Add multiple data series.
- **`inline void forceRMax(double rm)`:** Force a maximum for the *r*.
- **`inline void setnumRDivisions(size_t nrd=5) {numRDivisions=nrd;}`:** Set the `numRDivisions`.
- **`inline void setnumThetaDivisions(size_t ntd=8) {numThetaDivisions=ntd;}`:** Set the `numThetaDivisions`.
- **`inline void setplotPad(double pp) {plotPad=pp;}`:** Set the `plotPad`.
- **`inline void setbackColor(size_t R, size_t G, size_t B)`:** Set the `backColor`.

### Border

- **`bool border=true`:** Whether to draw border.
- **`double borderLineWidth = 2.5`:** Width of the line on the plot border.
- **`std::string borderLineColor = "#000000"`:** Color of the line on the plot border.
- **`inline void setborder(bool border_) {border=border_;}`:** Set the `border`.
- **`inline void setborderLineWidth(double blw) {borderLineWidth=blw;}`:** Set the `borderLineWidth`.
- **`inline void setborderLineColor(size_t R, size_t G, size_t B)`:** Set the `borderLineColor`.

### Grid

- **`double gridLineWidth = 0.5`:** Width of the grid lines.
- **`std::string gridLineColor = "#101010"`:** Color of the grid lines.
- **`inline void setgridLineWidth(double glw) {gridLineWidth=glw;}`:** Set the `gridLineWidth`.
- **`inline void setgridLineColor(size_t R, size_t G, size_t B)`:** Set the `girdLineColor`.

### Numerals

- **`bool plotNumerals = false`:** Whether to write the numerals corresponding to each segment line.
- **`size_t plotNumeralsSignificantDigits = 3`:** Number of significant digits.
- **`double plotNumeralsFontSize = 15`:** Font size of the numbers.
- **`std::string plotNumeralsColor = "#3f003f"`:** Color of the numbers.
- **`inline void setplotNumerals(bool pn) {plotNumerals=pn;}`:** Set the `plotNumerals`.
- **`inline void setplotNumeralsSignificantDigits(size_t pnsd) {plotNumeralsSignificantDigits=pnsd;}`:** Set the `plotNumeralsSignificantDigits`.
- **`inline void setplotNumeralsFontSize(double pnfs) {plotNumeralsFontSize=pnfs;}`:** Set the `plotNumeralsFontSize`.
- **`inline void setplotNumeralsColor(size_t R, size_t G, size_t B)`:** Set the `plotNumeralsColor`.

### Title

- **`bool plotTitle = false`:** Whether the title is written.
- **`double plotTitleFontSize = 36`:** Font size of the title text.
- **`std::string plotTitleText = "Title!"`:** The actual title text.
- **`std::string plotTitleColor = "#000000"`:** Color of the title.
- **`inline void setplotTitle(bool title_) {plotTitle=title_;}`:** Set the `plotTitle`.
- **`inline void setplotTitleFontSize(double ptfs) {plotTitleFontSize=ptfs;}`:** Set the `plotTitleFontSize`.
- **`inline void setplotTitleText(std::string titletext) {plotTitleText=titletext;}`:** Set the `plotTitleText`.
- **`inline void setplotTitleColor(size_t R, size_t G, size_t B)`:** Set the `plotTitleColor`.

### Points

- **`bool plotPointsFill = true`:** Whether to fill the circle representing a data point.
- **`double plotPointsBorderWidth = 1.5`:** Width of the hollow circle line.
- **`double plotPointsRadius = 5`:** Radius of the circle.
- **`double plotPointsBorderOpacity = 1.0`:** Opacity of the hollow circle line.
- **`double plotPointsFillOpacity = 1.0`:** Opacity of the filled circle.
- **`std::string plotPointsBorderColor = "#000000"`:** Color of the hollow circle line.
- **`std::string plotPointsFillColor = "#0000ff"`:** Color of the filled circle.
- **`std::string plotPointsLabel = ""`:** Label of the data series.
- **`inline void setplotPointsFill(bool ppf) {plotPointsFill=ppf;}`:** Set the `plotPointsFill`.
- **`inline void setplotPointsBorderWidth(double ppbw) {plotPointsBorderWidth=ppbw;}`:** Set the `plotPointsBorderWidth`.
- **`inline void setplotPointsRadius(double ppr) {plotPointsRadius=ppr;}`:** Set the `plotPointsRadius`.
- **`inline void setplotPointsBorderOpacity(double op) {plotPointsBorderOpacity=op;}`:** Set the `plotPointsBorderOpacity`.
- **`inline void setplotPointsFillOpacity(double op) {plotPointsFillOpacity=op;}`:** Set the `plotPointsFillOpacity`.
- **`inline void setplotPointsBorderColor(size_t R, size_t G, size_t B)`:** Set the `plotPointsBorderColor`.
- **`inline void setplotPointsFillColor(size_t R, size_t G, size_t B)`:** Set the `plotPointsFillColor`.
- **`inline void setplotPointsLabel(std::string ppl) {plotPointsLabel=ppl;}`:** Set the `plotPointsLabel`.

### Legend

- **`bool plotLegend = false`:** Whether to draw the legend.
- **`LegendPos legendPos = LegendPos::TopLeft`:** Position of the legend.
- **`double legendFontSize = 12`:** Font size of the legend.
- **`inline void setplotLegend(bool pl) {plotLegend=pl;}`:** Set the `plotLegend`.
- **`inline void setlegendPos(LegendPos lp) {legendPos=lp;}`:** Set the `legendPos`.
- **`inline void setlegendFontSize(double lfs) {legendFontSize=lfs;}`:** Set the `legendFontSize`.

### Private Functions

- **`inline double calcRDivisionsStep()`:** Calculates the step size of the *r* axis segments.
- **`inline double toPixelX(double x) { return (width/2.0 + x*rScale); }`:** Convert *x* value to pixel value.
- **`inline double toPixelY(double y) { return (width/2.0 - y*rScale); }`:** Convert *y* value to pixel value.
- **`inline double rttox(double r, double t) { return r*cos(t); }`:** Convert *r* and $\theta$ into *x*.
- **`inline double rttoy(double r, double t) { return r*sin(t); }`:** Convert *r* and $\theta$ into *y*.
- **`inline void writeNumerals(std::ofstream& file)`:** Writes the numbers on axis segment lines in appropriate placement.
- **`inline void writeplotTitle(std::ofstream& file)`:** Writes title in appropriate placment.
- **`inline void drawLegend(std::ofstream& file)`:** Writes legend in thedetermined position

### Plotting

- **`inline void plotSVG(std::string filename)`:** Writes an `svg` file that visualizes provided data.

## `LegendPos` Enumeration Class

This *class* is for setting the position of the plot legend (can be placed on four corners.)

```C++
enum class LegendPos
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};
```

## `PlotPolarData` Class

This is a support *class* that provides a way to add new data series to the plot.

```C++
class PlotPolarData
{
    public:
        dVec rs;
        dVec thetas;
        bool pointsFill=false;
        double pointsBorderWidth=1.0;
        double pointsRadius=5.0;
        double pointsBorderOpacity=1.0;
        double pointsFillOpacity=1.0;
        std::string pointsBorderColor="#000000";
        std::string pointsFillColor="#0000ff";
        std::string pointsLabel="";
        PlotPolarData(const dVec& r,const dVec& t, bool pf=false, double pbw=1.0, double pr=5.0, double pbo=1.0, double pfo=1.0, size_t pbcr=0, size_t pbcg=0, size_t pbcb=0, size_t pfcr=0, size_t pfcg=0, size_t pfcb=255,  std::string label="")
        : rs(r), thetas(t), pointsFill(pf), pointsBorderWidth(pbw), pointsRadius(pr), pointsBorderOpacity(pbo), pointsFillOpacity(pfo), pointsLabel(label)
        {
            // Border Color
            if ( (pbcr<256) && (pbcg<256) && (pbcb<256) )
            {
                pointsBorderColor = "#"+((pbcr<16) ? "0"+std::format("{:x}",pbcr) : std::format("{:x}",pbcr))
                    +((pbcg<16) ? "0"+std::format("{:x}",pbcg) : std::format("{:x}",pbcg))
                    +((pbcb<16) ? "0"+std::format("{:x}",pbcb) : std::format("{:x}",pbcb));
            }
            else
            {
                std::cout << "`R`, `G`, and `B` must be integers from 0 upto 255!\nDefaulting to black points' border...";
            }
            // Fill Color
            if ( (pbcr<256) && (pbcg<256) && (pbcb<256) )
            {
                pointsFillColor = "#"+((pfcr<16) ? "0"+std::format("{:x}",pfcr) : std::format("{:x}",pfcr))
                    +((pfcg<16) ? "0"+std::format("{:x}",pfcg) : std::format("{:x}",pfcg))
                    +((pfcb<16) ? "0"+std::format("{:x}",pfcb) : std::format("{:x}",pfcb));
            }
            else
            {
                std::cout << "`R`, `G`, and `B` must be integers from 0 upto 255!\nDefaulting to blue points' fill...";
            }
        }
};
```

## Other Functions

The function `double estimateStringWidth(const std::string& text, double fontsize)` is used inside `Plot2D::drawLegend` function to get a rough estimate of the length of the `lineLabel`s to determine the width of the legend (inside `Plot2D::drawLegend`, the `legendWidth` parameter).
