# Plot2D

The header file [Plot2D.hpp](../headers/Plot2D.hpp) includes the main class `Plot2D` and some helper classes which will be explained here. First we will walk through the `Plot2D` class and then we will breifly explain the rest. `Plot2D` is a *class* that defines the features of the plot. It includes many features to tweak the final plot based on how you want it to look.

There are two ways to initiate a class member:

  1. **Initiate for a single curve line:** This will generate parameters for a single dataset containing one $x$ array values, and one $y$ array values.

    ```C++
    Plot2D(const dVec& xs, const dVec& ys, size_t w = 1000, size_t h = 1000, size_t pad = 100)
    ```

  2. **Initiate for multiple curve lines:** This will feed a `std::vector` of $x$ and $y$ arrays to be plotted.

    ```C++
    Plot2D(const Vec<Plot2DData> data, size_t w = 1000, size_t h = 1000, size_t pad = 100)
    ```

Although one can add new data to the plot after initiating for the single curve line type.

## Table of Contents

1. [Plot2D](#plot2d)
    1. [Table of Contents](#table-of-contents)
    2. [`Plot2D` Class](#plot2d-class)
        1. [Flags](#flags)
        2. [Labels and Titles](#labels-and-titles)
        3. [Values](#values)
        4. [Values with Default](#values-with-default)
        5. [Private Functions](#private-functions)
        6. [Adding Data Series](#adding-data-series)
        7. [Manual MinMax](#manual-minmax)
        8. [Set the Flags](#set-the-flags)
        9. [Set the Labels and Titles](#set-the-labels-and-titles)
        10. [Set Some Values](#set-some-values)
        11. [Set the Font Sizes](#set-the-font-sizes)
        12. [Set the Widths](#set-the-widths)
        13. [Set the Colors](#set-the-colors)
        14. [Plotting](#plotting)
    3. [`LineStyle` Enumeration Class](#linestyle-enumeration-class)
    4. [`LegendPos` Enumeration Class](#legendpos-enumeration-class)
    5. [`Plot2DData` Class](#plot2ddata-class)
    6. [Other Functions](#other-functions)

## `Plot2D` Class

This class has different *parameters* and *flags* for a customizable plot image.

### Initialization

There are two different initializations (i.e. *constructors*) available.

1. **`Plot2D(const dVec& xs, const dVec& ys, size_t w = 1000, size_t h = 1000, size_t pad = 100)`:** This is an option to initialize the class with one data series (`xVals`,`yVals`). It provides default values for `width=1000`, `height=1000`, `padding=100`. This is good for single data series. (Although additional data series can be added with *two* ways to do so.)
2. **`Plot2D(const Vec<Plot2DData> data, size_t w = 1000, size_t h = 1000, size_t pad = 100)`:** This one is an option to initialize the class with multiple instances of data series (`data.xs`, `data.ys`) with their own distinct features. It provides default value for width, height, and padding just like the previous option. This one is good for adding multiple lines to the plotted image.

### Flags

- **`bool border = true`:** Whether *borders* are drawn. Default is `true`.
- **`bool axis = true`:** Whether *axes* are drawn. Default is `true`.
- **`bool ticks = true`:** Whether *ticks* are drawn. Default is `true`.
- **`bool grid = true`:** Whether *grids* are drawn. Default is `true`.
- **`bool axisLabel = true`:** Whether *axes labels* are written. Default is `true`.
- **`bool autoTicks = true`:** Whether *ticks* are placed automatically or start from the minimum value up to maximum value regardless of the numbers (less pretty). Default is `true`.
- **`bool plotTitle = false`:** Whether *plot title* is written. Default is `false`.
- **`bool plotLegend = false`:** Whether *legend* is drawn. Default is `false`.
- **`bool xAxisVisible`:** Whether the *x-axis* is visible. This will be inferred from the data series and cannot be set forcefully (in an indirect way one can force the values of `yMin`, and `yMax` in a way that makes the *x-axis* visible).
- **`bool yAxisVisible`:** Whether the *y-axis* is visible. This will be inferred from the data series and cannot be set forcefully (in an indirect way one can force the values of `xMin`, and `xMax` in a way that makes the *y-axis* visible).
- **`bool errorPlot`:** Whether the *error* is plotted. (Error band plot flag).

### Labels and Titles

- **`std::string xAxisLabel = "X"`:** The *label* that is written below *x-axis* if `axisLabel=true`.
- **`std::string yAxisLabel = "Y"`:** The *label* that is written beside *y-axis* if `axisLabel=true`.
- **`std::string plotTitleText = "Title!"`:** The *title* that is written on top of the plot if `plotTitle=true`
- **`std::string plotLineLabel = ""`:** The entry corresponding to the `xVals,yVals` data series in the *legend* if `plotLegend=true`.

### Values

- **`double epsilon = 1e-10`:** A default value for a very small number.
- **`Vec<Plot2DData> plotData`:** A `std::vector` of a `class` container for data series (a set of data series).
- **`size_t width`:** Total width of the generated vector image (in pixels).
- **`size_t height`:** Total height of the generated vector image (in pixels).
- **`dVec xVals`:** A `std::vector<double>` of *x* values belonging to the initialization data series.
- **`dVec yVals`:** A `std::vector<double>` of *y* values belonging to the initialization data series.
- **`size_t padding`:** The distance of the plot border (inner rectangle) from the sides.
- **`double xMax`:** Maximum value of all *x* values of all data series.
- **`double xMin`:** Minimum value of all *x* values of all data series.
- **`double xRange`:** The range (span) of the *x* values.
- **`double yMax`:** Maximum value of all *y* values of all data series.
- **`double yMin`:** Minimum value of all *y* values of all data series.
- **`double yRange`:** The range (span) of the *y* values.
- **`double xScale`:** The scale factor of *x* (ratio of `width-2*padding` and `xRange`)
- **`double yScale`:** The scale factor of *y* (ratio of `height-2*padding` and `yRange`)
- **`size_t drawW`:** The actual plot width (`width-2*padding`).
- **`size_t drawH`:** The actual plot height (`height-2*padding`).
- **`double gLeft`:** The position of the *left* berder line.
- **`double gRight`:** The position of the *right* border line.
- **`double gBottom`:** The position of the *bottom* border line.
- **`double gTop`:** The position of the *top* border line.
- **`size_t numYTicks`:** Number of ticks on *y-axis* (is derived from number of ticks on *x-axis* and `drawW`, and `drawH`).
- **`double xStep`:** The distance between two consecutive ticks on *x-axis*.
- **`double yStep`:** The distance between two consecutive ticks on *y-axis*.
- **`dVec xTickPixelsX`:** Position of *x-axis* ticks in pixels.
- **`dVec xTickPointsX`:** Position of *x-axis* ticks in real values.
- **`dVec yTickPixelsY`:** Position of *y-axis* ticks in pixels.
- **`dVec yTickPointsY`:** Position of *y-axis* ticks in real values.
- **`dVec errors`:** The values of errors (must be the same size as `xVals` and `yVals`). *Note* that errors must be positive for it to make sense (as a measure of variation from `yVals` or something similar), but there is nothing to stop you from entering other values!
- **`dVec yValsErrorsPositive`:** The values of `yVals+errors` (upper band path).
- **`dVec yValsErrorsNegative`:** The values of `yVals-errors` (lower band path).

### Values with Default

- **`size_t numXTicks = 11`:** Number of ticks on *x-axis*. Default is `11`.
- **`double tickMarkSize = 6.0`:** The size (length) of the tick marks. Default is `6.0`.
- **`double plotPad = 4.0`:** The value of extra space padded around the actual plot (middle rectangle). Default is `4.0`.
- **`double borderLineWidth = 1.5`:** Width of the *border* lines (rectangle) separating the actual plot from the outer padding. Default is `1.0`.
- **`double axisLineWidth = 2.5`:** Width of the *axis* lines. Default is `2.5`.
- **`double gridLineWidth = 0.5`:** Width of the *grid* lines. Default is `0.5`.
- **`double plotLineWidth = 1.0`:** Width of the line corresponding to the initialization data series. Default is `1.0`.
- **`double plotNumeralsFontSize = 15.0`:** Font size of the *numerals* corresponding to ticks showing their real (as opposed to pixel) values. Default if `15.0`.
- **`double plotAxisLabelFontSize = 16.0`:** Font size of the *axis label* text. Default is `16.0`.
- **`double plotTitleFontSize = 20.0`:** Font size of the *plot title* text. Default is `20.0`.
- **`double legendFontSize = 10`:** Font size of the *legend* text entries. Default is `10.0`.
- **`size_t plotNumeralsSignificantDigits = 3`:** The number corresponding to digits of precision. Default if `3`.
- **`double plotLineOpacity = 1.0`:** The opacity of the plotted line. Default is `1.0` (fully opaque).
- **`LineStyle plotLineStyle = LineStyle::Solid`:** The style of the plotted line for the initialization data series. Default is `LineStyle::Solid`.
- **`LegendPos legendPos = LegendPos::TopLeft`:** The position of the legend (the rectangular box). Default is `LegendPos::TopLeft`.
- **`std::string backColor = "#ffffff"`:** The color of the background color. Default is `#ffffff` (i.e. (255,255,255) or *white*).
- **`std::string borderLineColor = "#000000"`:** The color of the border line. Default is `#000000` (i.e. (0,0,0) or *black*).
- **`std::string axisLineColor = "#000000"`:** The color of the axis lines. Default is `#000000` (i.e. (0,0,0) or *black*).
- **`std::string gridLineColor = "#101010"`:** The color of grid lines. Default is `#101010` (i.e. (16,16,16) or *dark gray*).
- **`std::string plotNumeralsColor = "#000000"`:** The color of the tick numbers. Default is `#000000` (i.e. (0,0,0) or *black*).
- **`std::string plotLineColor = "#0000ff"`:** The color of the line color. Default is `#0000ff` (i.e. (0,0,255) or *blue*).
- **`std::string plotAxisLabelColor = "#1f1f1f"`:** The color of labels of the axes. Default is `#1f1f1f` (i.e. (31,31,31) or *dark gray*).
- **`std::string plotTitleColor = "#000000"`:** The color of the title of the plot. Default is `#000000` (i.e. (0,0,0) or *black*).

### Private Functions

These are the functions that do the inner works of the plotting and only called by other functions (the user won't need to call them directly, but they are included here for completeness and as an aid in attempts to modify the library.)

- **`inline double toPixelX( const double x) const {return padding + (x-xMin)*xScale;}`:** It converts *x* value into pixel value on horizontal axis.
- **`inline double toPixelY( const double y) const {return (height-padding) - (y-yMin)*yScale;}`:** It converts *y* value into pixel value on vertical axis.
- **`inline double toPointX( const double x) const {return (x-padding)/xScale + xMin;}`:** It converts pixel value to real *x* value.
- **`inline double toPointY( const double y) const {return yMin - (y-height+padding)/yScale;}`:** It converts pixel value to real *y* value.
- **`inline void drawTicks(std::ofstream& file)`:** It draws the ticks and derives and stores their positions. (if axes are visible it places ticks on both axes and on left and lower border line.)
- **`inline void drawGrid(std::ofstream& file)`:** It draws the grid lines based on the tick placements.
- **`inline void writeNumbers(std::ofstream& file)`:** It writes corresponding numbers next to tick marks placed on left and lower border line. 
- **`inline void writeAxisLabels(std::ofstream& file)`:** It writes axis labels centeres and parallel to the corresponding axis.
- **`inline void writeplotTitle(std::ofstream& file)`:** It writes plot title centered on the top of the plot.
- **`inline void drawLegend(std::ofstream& file)`:** It draws the legend box and writes the line labels on the designated position.
- **`inline double calcAutoXTicksStep()`:** Calculates ticks in a way that they are multiples of {\dots, 0.1, 0.25, 0.5, 1.0, 2.5, 5.0, 10.0, \dots}. It returns a value for `xStep`.
- **`inline double calcAutoYTicksStep()`:** Calculates ticks in a way that they are multiples of {\dots, 0.1, 0.25, 0.5, 1.0, 2.5, 5.0, 10.0, \dots}. It returns a value for `yStep`.

### Adding Data Series

1. **`inline void addData(const dVec& x, const dVec& y, LineStyle ls, size_t R, size_t G, size_t B, double lw, double op = 1.0, std::string ll = "")`:** This function provides a method of adding one data series per call. It has default values for *opacity* and *line label* for the new data series.
2. **`inline void addMultipleData(const Vec<Plot2DData>& plotdata)`:** This function provides a method of adding multiple data series on one call.

### Manual MinMax

- **`inline void forceXMinMax(double xMin_, double xMax_)`:** Change `xMin`, and `xMax` (set them manually).
- **`inline void forceYMinMax(double yMin_, double yMax_)`:** Change `xMin`, and `xMax` (set them manually).

### Set the Flags

- **`inline void setborder(bool border_) {border=border_;}`:** Set the `border` flag.
- **`inline void setaxis(bool axis_) {axis=axis_;}`:** Set the `axis` flag.
- **`inline void setticks(bool ticks_) {ticks=ticks_;}`:** Set the `ticks` flag.
- **`inline void setgrid(bool grid_) {grid=grid_;}`:** Set the grid flag.
- **`inline void setplotTitle(bool title_) {plotTitle=title_;}`:** Set the `plotTitle` flag.
- **`inline void setaxisLabel(bool al) {axisLabel=al;}`:** Set the `axisLabel` flag.
- **`inline void setautoTicks(bool at) {autoTicks=at;}`:** Set the `autoTicks` flag.
- **`inline void setplotLegend(bool pl) {plotLegend=pl;}`:** Set the `plotLegend` flag.
- **`inline void seterrorPlot(bool ep) {errorPlot=ep;}`:** Set the `errorPlot` flag.

### Set the Labels and Titles

- **`inline void setxAxisLabel(std::string xal) {xAxisLabel=xal;}`:** Set the text (label) of *x-axis*.
- **`inline void setyAxisLabel(std::string yal) {yAxisLabel=yal;}`:** Set the text (label) of *y-axis*.
- **`inline void setplotTitleText(std::string titletext) {plotTitleText=titletext;}`:** Set the plot title text.
- **`inline void setplotLineLabel(std::string pll) {plotLineLabel=pll;}`:** Set the line label (the text that would eventually be written as a legend entry).

### Set Some Values

- **`inline void setnumXTicks(size_t nt) {numXTicks=nt;}`:** Set the `numXTicks` (number of tick marks on *x-axis*).
- **`inline void settickMarkSize(double ts) {tickMarkSize=ts;}`:** Set the `tickMarkSize` (size or length of the tick marks).
- **`inline void setplotPad(double pp) {plotPad=pp;}`:** Set the `plotPad` (extra space for the actual plot).
- **`inline void setplotNumeralsSignificantDigits(size_t pnsd) {plotNumeralsSignificantDigits=pnsd;}`:** Set th `plotNumeralsSignificantDigits`.
- **`inline void setplotLineOpacity(double op) {plotLineOpacity=op;}`:** Set the `plotLineOpacity`.
- **`inline void setplotLineStyle(LineStyle pls) {plotLineStyle=pls;}`:** Set the `plotLineStyle`.
- **`inline void setlegendPos(LegendPos lp) {legendPos=lp;}`:** Set the `legendPos`.
- **`inline void setplotErrors(const dVec& errs)`:** Set/Add the values of `errors`.

### Set the Font Sizes

- **`inline void setplotNumeralsFontSize(double pnfs) {plotNumeralsFontSize=pnfs;}`:** Set the `plotNumeralFontSize`.
- **`inline void setplotAxisLabelFontSize(double palfs) {plotAxisLabelFontSize=palfs;}`:** Set the `plotAxisLabelFontSize`.
- **`inline void setplotTitleFontSize(double ptfs) {plotTitleFontSize=ptfs;}`:** Set the `plotTitleFontSize`.
- **`inline void setlegendFontSize(double lfs) {legendFontSize=lfs;}`:** Set the `legendFontSize`.

### Set the Widths

- **`inline void setborderLineWidth(double blw) {borderLineWidth=blw;}`:** Set the `borderLineWidth`.
- **`inline void setaxisLineWidth(double alw) {axisLineWidth=alw;}`:** Set the `axisLineWidth`.
- **`inline void setgridLineWidth(double glw) {gridLineWidth=glw;}`:** Set the `gridLineWidth`.
- **`inline void setplotLineWidth(double plw) {plotLineWidth=plw;}`:** Set the `plotLineWidth`.

### Set the Colors

- **`inline void setbackColor(size_t R, size_t G, size_t B)`:** Set the `backColor`.
- **`inline void setborderLineColor(size_t R, size_t G, size_t B)`:** Set the `borderLineColor`.
- **`inline void setaxisLineColor(size_t R, size_t G, size_t B)`:** Set the `axisLineColor`.
- **`inline void setgridLineColor(size_t R, size_t G, size_t B)`:** Set the `gridLineColor`.
- **`inline void setplotNumeralsColor(size_t R, size_t G, size_t B)`:** Set the `plotNumeralsColor`.
- **`inline void setplotLineColor(size_t R, size_t G, size_t B)`:** Set the `plotLineColor`.
- **`inline void setplotAxisLabelColor(size_t R, size_t G, size_t B)`:** Set the `plotAxisLabelColor`.
- **`inline void setplotTitleColor(size_t R, size_t G, size_t B)`:** Set the `plotTitleColor`.

### Plotting

Only plotting function is `inline void plotSVG(const std::string& filename)`.

## `LineStyle` Enumeration Class

This class helps determine how the line is plotted based on the `Plot2D::plotLineStyle` or `Plot2D::plotData.lineStyle`. There are four different types of plot style.

```C++
enum class LineStyle
{
    Solid,
    Dashed,
    Dotted,
    DashDot
};
```

- **Solid:** A continuous solid line.
- **Dashed:** An interval of solid line segments followed by a smaller space (fragmented line).
- **Dotted:** A Series of filled circles (or dots) plotted with small gaps in between.
- **DashDot:** An interval of line fragment, space, dot, space, repeat.

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

## `Plot2DData` Class

This *class* encapsulates data needed for each set of data series. It includes two `double` vectors for *x* (`dVec xs`) and *y* (`dVec ys`), the *style* of the corresponding line in the plot (`LineStyle lineStyle`), the *color* of the line *`std::string lineColor`*, the *width* of the line (`double lineWidth`), the *opacity* of the line (`double lineOpacity`), the *label* of the line (`std::string lineLabel`). `lineOpacity`, and `lineLabel` have default values.

```C++
class Plot2DData
{
    public:
        dVec xs;
        dVec ys;
        LineStyle lineStyle;
        std::string lineColor;
        double lineWidth;
        double lineOpacity = 1.0;
        std::string lineLabel = "";
        bool errorPlot = false;
        dVec errors;
        dVec ysErrorsPositive;
        dVec ysErrorsNegative;

        Plot2DData(const dVec& x, const dVec& y, LineStyle ls, size_t R, size_t G, size_t B, double lw, double op = 1.0, std::string ll = "", bool ep=false, const dVec& errs={})
        : xs(x), ys(y), lineStyle(ls), lineWidth(lw), lineOpacity(op), lineLabel(ll), errorPlot(ep)
        {
            if ( (R<256) && (G<256) && (B<256) )
            {
                lineColor = "#"+((R<16) ? "0"+std::format("{:x}",R) : std::format("{:x}",R))
                    +((G<16) ? "0"+std::format("{:x}",G) : std::format("{:x}",G))
                    +((B<16) ? "0"+std::format("{:x}",B) : std::format("{:x}",B));
            }
            else
            {
                lineColor = "#000000";
                std::cout << "Values were out of bound! Defaulted to black for lineColor!\n";
            }
            if (errs.size() == ys.size() && errorPlot)
            {
                errors = errs;
                for ( size_t i=0; i<ys.size(); ++i )
                {
                    ysErrorsPositive.push_back(ys[i]+errors[i]);
                    ysErrorsNegative.push_back(ys[i]-errors[i]);
                }
            }
            else
            {
				throw std::runtime_error("Errors must be the same shape and size as the y values!\n");
			}
        };
};
```

## Other Functions

The function `double estimateStringWidth(const std::string& text, double fontsize)` is used inside `Plot2D::drawLegend` function to get a rough estimate of the length of the `lineLabel`s to determine the width of the legend (inside `Plot2D::drawLegend`, the `legendWidth` parameter).
