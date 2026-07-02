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
    2. [Parameters and Flage](#parameters-and-flags)
        1. [Plot Shape](#plot-shape)
        2. [Shape Derived Parameters](#shape-derived-parameters)
        3. [Ticks](#ticks)
        4. [Border and Axis](#border-and-axis)
        5. [Grid](#grid)
        6. [Title](#title)
        7. [Curve (data)](#curve-data)
        8. [Miscellany](#miscellany)
    3. [Member Functions](#member-functions)
        1. [Setters](#setters)
        2. [Plot Modifiers](#plot-modifiers)
            1. [Pixel <-> Point](#pixel---point)
            2. [Calculations](#calculations)
            3. [Writing and Drawing](#writing-and-drawing)
    4. [Extras](#extras)
    5. [Other Classes](#other-classes)
        1. [`LineStyle`](#linestyle)
        2. [`Plot2DData`](#plot2ddata)

## Parameters and flags

There are many *flags* (boolean type) to determine different conditioins and many *parameters* that determine shapes, sizes, and scales.

### Plot Shape

The parameters determining the shape of the image.

1. **`size_t width`:** It represents the width of the image in *pixels*.
2. **`size_t height`:** It represents the height of the image in *pixels*.
3. **`dVec xVals`:** The $x$ values of data points.
4. **`dVec yVals`:** The $y$ values of data points.
5. **`size_t padding`:** The distance of the actual plot from the sides.

These are also the main requirements for class initiation.

```C++
Plot2D(const dVec& xs,const dVec& ys,size_t w=1000,size_t h=1000,size_t pad=100);
```

### Shape Derived Parameters

Some parameters are derived through the *shape* parameters. All except four are calculated inside class initiation function `Plot2D::Plot2D`.

1. **`size_t drawW`:** `width-2*padding` (the actual plot width).
2. **`size_t drawH`:** `height-2*padding` (the actual plot height).
3. **`double xMin`:** The *minimum* value on $x$-axis.
4. **`double xMax`:** The *maximum* value on $x$-axis.
5. **`double yMin`:** The *minimum* value on $y$-axis.
6. **`double yMax`:** The *maximum* value on $y$-axis.
7. **`double gLeft`:** The pixel address of $x_{min}$ (`xMin`). Calculated inside `Plot2D::plotSVG` function.
8. **`double gRight`:** The pixel address of $x_{max}$ (`xMax`). Calculated inside `Plot2D::plotSVG` function.
9. **`double gTop`:** The pixel address of $y_{max}$ (`yMax`). Calculated inside `Plot2D::plotSVG` function.
10. **`double gBottom`:** The pixel address of $y_{min}$ (`yMin`). Calculated inside `Plot2D::plotSVG` function.
11. **`double xRange`:** The size of the *domain*, i.e. $x_{max}-x_{min}$.
12. **`double yRange`:** The size of the *range*, i.e. $y_{max}-y_{min}$.
13. **`double xScale`:** The *scaling factor* of the $x$ values mapped to pixels (`drawW/xRange`).
14. **`double yScale`:** The *scaling factor* of the $y$ values mapped to pixels (`drawH/yRange`).
15. **`bool xAxisVisible`:** A check for visibility of $x$ axis.
16. **`bool yAxisVisible`:** A check for visibility of $y$ axis.
17. **`std::string backColor`:** Color of the background.

### Ticks

These parameters determine whether and how the *ticks* are drawn.

1. **`bool ticks`:** Whether to draw ticks.
2. **`double tickMarkSize`:** The size (length) of tick marks.
3. **`bool autoTicks`:** Whether to set tick placement automatically (if `false` it would be placed starting from the minimum values, i.e. `xMin`, and `yMin`).
4. **`size_t numXTicks`:** Expected number of ticks on $x$-axis.
5. **`size_t numYTicks`:** Expected number of ticks on $y$-axis.(`numYTicks=numXTicks*drawH/drawW`)
6. **`double plotNumeralsFontSize`:** Font size of the numbers of corresponding ticks.
7. **`std::string plotNumeralsColor`:** Color of the numbers of corresponding ticks.
8. **`size_t plotNumeralsSignificantDigits`:** Number precision.

### Border and Axis

Whether and how to draw *axis* and *border*.

1. **`bool border`:** Whether to draw border.
2. **`bool axis`:** Whether to draw axis.
3. **`bool axisLabel`:** Whether to write axis labels.
4. **`double borderLineWidth`:** Width of the border drawn.
5. **`double axisLineWidth`:** Width of the axis drawn.
6. **`std::string borderLineColor`:** Color of the border drawn.
7. **`std::string axisLineColor`:** Color of the axis drawn.
8. **`std::string xAxisLabel`:** Label written for $x$ axis (centered below axis).
9. **`std::string yAxisLabel`:** Label written for $y$ axis (centered left of the axis).
10. **`double plotPad`:** Amout of extra space on the plot region.
11. **`double plotAxisLabelFontSize`:** Font size of the axis label.
12. **`std::string plotAxisLabelColor`:** Color of the axis label.

### Grid

Whether and how to draw *grid*.

1. **`bool grid`:** Whether to draw the grids.
2. **`double gridLineWidth`:** Width of grids drawn.
3. **`std::string gridLineColor`:** Color of the grid drawn.

### Title

Whether and how to draw *title*.

1. **`bool plotTitle`:** Whether to write a title.
2. **`std::string plotTitleText`:** The text to be written.
3. **`double plotTitleFontSize`:** Size of the written title.
4. **`std::string plotTitleColor`:** Color of the written title.

### Curve (data)

1. **`double plotLineWidth`:** Width of the drawn curve.
2. **`LineStyle plotLineStyle`:** Style of the curve (`Solid`,`Dotted`,`Dashed`,`DashDot`).
3. **`std::string plotLineColor`:** Color of the curve.

### Miscellany

These are the *intermediate* parameters in a sense.

1. **`xTickPointsX`:** The $x$ points values of the $x$-axis ticks.
2. **`xTickPixelsX`:** The $x$ pixels values of the $x$-axis ticks.
3. **`yTickPointsY`:** The $y$ points values of the $y$-axis ticks.
4. **`yTickPixelsY`:** The $y$ pixels values of the $y$-axis ticks.
5. **`xStep`:** The step size between $x$-axis ticks.
6. **`yStep`:** The step size between $y$-axis ticks.

## Member Functions

Functions that call upon the parameters, change them, or use them to prepare and plot.

### Setters

Functions that *set* a new value to a *parameter* or *flag*.

1. **`void setborder(bool border_)`:** Set `border`.
2. **`void setaxis(bool axis_)`:** Set `axis`.
3. **`void setticks(bool ticks_)`:** Set `tick`.
4. **`void setgrid(bool grid_)`:** Set `grid`.
5. **`inline void setaxisLabel(bool al)`:** Set `axisLabel`.
6. **`void setplotTitle(bool title_)`:** Set `title`.
7. **`void setautoTicks(bool at)`:** Set `autoTicks`.
8. **`void setnumXTicks(size_t nt)`:** Set `numXTicks`.
9. **`void settickMarkSize(double ts)`:** Set `tickMarkSize`.
10. **`void setplotPad(double pp)`:** Set `plotPad`.
11. **`void setborderLineWidth(double blw)`:** Set `borderLineWidth`.
12. **`void setgridLineWidth(double glw)`:** Set `gridLineWidth`.
13. **`void setaxisLineWidth(double alw)`:** Set `axisLineWidth`.
14. **`void setplotLineWidth(double plw)`:** Set `plotLineWidth`.
15. **`void setplotNumeralsFontSize(double pnfs)`:** Set `plotNumeralsFontSize`.
16. **`void setplotAxisLabelFontSize(double palfs)`:** Set `plotAxisLabelFontSize`.
17. **`void setplotTitleFontSize(double ptfs)`:** Set `plotTitleFontSize`.
18. **`void setbackColor(size_t R, size_t G, size_t B)`:** Set `backColor`.
19. **`void setborderLineColor(size_t R, size_t G, size_t B)`:** Set `borderLineColor`.
20. **`void setaxisLineColor(size_t R, size_t G, size_t B)`:** Set `axisLineColor`.
21. **`void setgridLineColor(size_t R, size_t G, size_t B)`:** Set `gridLineColor`.
22. **`void setplotNumeralsColor(size_t R, size_t G, size_t B)`:** Set `plotNumeralsColor`.
23. **`void setplotLineColor(size_t R, size_t G, size_t B)`:** Set `plotLineColor`.
24. **`void setplotAxisLabelColor(size_t R, size_t G, size_t B)`:** Set `plotAxisLabelColor`.
25. **`void setplotTitleColor(size_t R, size_t G, size_t B)`:** Set `plotTitleColor`.
26. **`void setxAxisLabel(std::string xal)`:** Set `xAxisLabel`.
27. **`void setyAxisLabel(std::string yal)`:** Set `yAxisLabel`.
28. **`void setplotTitleText(std::string titletext)`:** Set `plotTitleText`.
29. **`void setplotNumeralsSignificantDigits(size_t pnsd)`:** Set `plotNumeralsSignificantDigits`.
30. **`void setplotLineStyle(LineStyle pls)`:** Set `plotLineStyle`.

### Plot Modifiers

These function modify aspects of the plot, or calculate values for the plot.

#### Pixel <-> Point

1. **`double toPixelX(double x)`:** Transforms the $x$ component of a *point* in geometric space to pixel address in image space.
2. **`double toPixelY(double y)`:** Transforms the $y$ component of a *point* in geometric space to pixel address in image space.
3. **`double toPointX(double x)`:** Inverse of `toPixelX`.
4. **`double toPointY(double y)`:** Inverse of `toPixelY`.

#### Calculations

These functions calculate underlying parameters.

1. **`double calcAutoXTicksStep()`:** Calculates the `autoTicks` step size for the $x$ axis.
2. **`double calcAutoYTicksStep()`:** Calculates the `autoTicks` step size for the $y$ axis.

#### Writing and Drawing

These functions either draw some elements of the plot, or write the required texxts.

1. **`void drawTicks(std::ofstream& file)`:** Draws the ticks based on either *automatic* style (multiples of $\dots,0.1,0.25,0.5,1.0,2.5,5.0,10.0,\dots$) or the *default* style (dividing the range by the number of ticks and starting the ticks from the axis minimum value). It uses the designated parameters to do so.
2. **`void drawGrid(std::ofstream& file)`:** Draws the grid based on designated parameters.
3. **`void writeNumbers(std::ofstream& file)`:** Writes numbers corresponding to each tick near it based on the designated parameters. It writes number only when the ticks are drawn, otherwise you won't get the numbers.
4. **`void writeAxisLabels(std::ofstream& file)`:** Writes the Axis labels centered and parallel to the axes in bottom and left side of the plot.
5. **`void writeplotTitle(std::ofstream& file)`:** Writes the *title* centered on top of the plot.
6. **`void plotSVG(std::string filename)`:** This one draws the plot and calls the other writing and drawing functions if conditions are met.

**Some modifier functions:**

1. **`void forceXMinMax(double xMin_, double xMax_)`:** This one forces `xMin` and `xMax` as the user desires, then calculates `xRange` and `xScale` based on that and sets the `yAxisVisible` flag.
2. **`void forceYMinMax(double yMin_, double yMax_)`:** This one forces `yMin` and `yMax` as the user desires, then calculates `yRange` and `yScale` based on that and sets the `xAxisVisible` flag.

## Extras

Some extra elements added to the `Plot2D` class for better control over plots.

1. **`Vec<Plot2DData> plotData`:** This is an array of a class `Plot2DData` which contains data for a plot (the $x$ values, $y$ values, the `LineStyle`, the line color, the line width).
2. **`void addData(const dVec& x, const dVec& y, LineStyle ls, std::string lc, double lw)`:** Add one set of $x$ and $y$ arrays to the plot.
3. **`void addMultipleData(const Vec<Plot2DData>& plotdata)`:** This one adds multiple sets of $x$ and $y$ array to plot.
4. **`double plotLineOpacity`:** To be able to set how opaque a line is. Default is `1.0` (fully opaque).
5. **`void setplotLineOpacity(double op)`:** Set the *opacity* of the plotted line.

## Other Classes

Two other classes has been added to add versatility to the plotting experience. One tracks the line style for the $x-y$ curve (`enum class LineStyle`) and the other is the one that helps plot multiple curves at the same plot (`class Plot2DData`).

### `LineStyle`

This is an `enum class`, which means it presents a bunch of options for a specific use, here it presents options for the style of the curve line that will be drawn. There are four styles for now.

```C++
enum class LineStyle
{
    Solid,
    Dashed,
    Dotted,
    DashDot
};
```

### `Plot2DData`

This one holds the data needed for a curve line that will be drawn.

```C++
class Plot2DData
{
    public:
        dVec xs;
        dVec ys;
        LineStyle lineStyle;
        std::string lineColor;
        double lineWidth;
        Plot2DData(const dVec& x, const dVec& y, LineStyle ls, std::string lc, double lw)
        : xs(x), ys(y), lineStyle(ls), lineColor(lc), lineWidth(lw) {};
};
```
