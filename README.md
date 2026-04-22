# Unreal Measurement Tool Plugin

A spline-based measurement tool plugin for Unreal Engine 5.7 that measures distances and areas in-editor with real-time visual feedback.

![Engine Version](https://img.shields.io/badge/Unreal%20Engine-5.7-blue)
![Platform](https://img.shields.io/badge/Platform-Win64-lightgrey)

## Features

- **Distance & Area modes** — Measure spline length (Distance) or the enclosed polygon area (Area) using the Shoelace formula with Newell's method for arbitrary 3D polygons.
- **Multiple units** — Display results in centimeters, meters, kilometers, feet, inches, or yards. Area mode shows squared units (m², ft², etc.).
- **Spline-based measurement** — Uses `USplineComponent` for accurate distance calculation along curved or straight paths.
- **Linear / Curve splines** — Toggle between smooth curves and straight-line segments per spline.
- **Real-time display** — A `UWidgetComponent` renders the measurement in-world, always facing the camera (billboard effect).
- **Cumulative labels** — Optionally show accumulated distance at each spline point with configurable size and color.
- **Snap to geometry** — Three snap modes:
  - **Off** — No snapping.
  - **Ground Snap** — Traces downward to snap points to the ground (configurable trace distance).
  - **Surface Snap** — Finds the nearest surface within a configurable radius using six-axis cardinal traces. Debug spheres can be drawn to visualize the snap radius.
- **Manual size input** — Enter an exact value (in the selected unit) and the spline rescales to match. In Area mode, scaling uses the square-root ratio to preserve shape.
- **Reset spline** — One-click reset to a default 2-point configuration, clearing rotation and scale.
- **Editor integration** — Measurement updates live as you edit spline points in the viewport via `OnConstruction()`. Property changes trigger immediate recalculation through `PostEditChangeProperty()`.
- **Closing line** — In Area mode, a debug line is drawn from the last spline point back to the first (toggleable).
- **Decoupled architecture** — The actor communicates with the widget through a `UInterface`, so you can swap or extend the widget without touching the actor.

## Installation

1. Clone or copy this repository into your Unreal project's root directory.
2. Make sure the `Plugins/UnrealMeasurementTool` folder is inside your project.
3. Open the project in Unreal Editor — the plugin will be detected automatically.
4. Enable **Unreal Measurement Tool** in _Edit → Plugins_ if it isn't already enabled.

## Usage

1. Drag `BP_MeasurementActor` from the plugin's content folder into your level.
2. Select the actor and edit its spline points in the viewport to define the measurement path.
3. The widget automatically displays the measurement in the selected unit.
4. Use the **Mode** property to switch between Distance and Area measurement.
5. Use the **Unit** dropdown to change between cm, m, km, ft, in, and yd.
6. Enable **Linear** to switch spline segments from smooth curves to straight lines.
7. To set an exact size, enter a value in the **Size** field (in the current unit) and click **Submit**.
8. Use **Reset** to return to the default 2-point layout.
9. Enable **Show Cumulative Labels** to display the accumulated distance at each spline point.
10. Set **Snap Mode** to Ground or Surface to snap spline points to nearby geometry.

## Architecture

```
AMeasurementActor
├── USplineComponent (root) — defines the measurement path
├── UWidgetComponent — renders the measurement text in-world (billboard)
├── TArray<UTextRenderComponent> — per-point cumulative distance labels
└── IMeasurementTxtWgtCommunicationInterface — sends text to any implementing widget

UMeasurementTextWidget : UUserWidget, IMeasurementTxtWgtCommunicationInterface
└── UTextBlock "MeasurementText" — displays the formatted measurement

EMeasurementUnit   — cm | m | km | ft | in | yd
EMeasurementMode   — Distance | Area
ESnapMode          — None | GroundSnap | SurfaceSnap
```

The actor never references the concrete widget class directly. Communication goes through `IMeasurementTxtWgtCommunicationInterface`, which exposes a single method:

```cpp
void SendMeasurementText(const FText& InText);
```

This makes it straightforward to create a custom widget — just implement the interface.

## Properties

| Property                   | Category            | Description                                             |
| -------------------------- | ------------------- | ------------------------------------------------------- |
| **Mode**                   | Measurement Control | Distance (spline length) or Area (enclosed polygon).    |
| **Unit**                   | Measurement Control | cm, m, km, ft, in, yd.                                  |
| **Size**                   | Measurement Control | Target value to apply via Submit (in the current unit). |
| **Linear**                 | Measurement Control | Straight-line segments instead of smooth curves.        |
| **Show Closing Line**      | Measurement Control | Debug line from last to first point (Area mode only).   |
| **Snap Mode**              | Measurement Control | Off, Ground (Trace Down), Nearest Surface.              |
| **Snap Radius**            | Measurement Control | Search radius for Surface Snap.                         |
| **Ground Trace Distance**  | Measurement Control | Max downward trace for Ground Snap.                     |
| **Snap Trace Channel**     | Measurement Control | Collision channel used for snap traces.                 |
| **Show Snap Radius**       | Measurement Control | Debug spheres around each point (Surface Snap).         |
| **Show Cumulative Labels** | Cumulative Labels   | Display accumulated distance at each spline point.      |
| **Label Size**             | Cumulative Labels   | World-size of the label text.                           |
| **Label Color**            | Cumulative Labels   | Color of the label text.                                |

## Module Dependencies

| Type        | Modules                   |
| ----------- | ------------------------- |
| **Public**  | Core, CoreUObject, Engine |
| **Private** | Slate, SlateCore, UMG     |

## Building

The project includes VS Code build tasks. To build from the command line:

```
Engine\Build\BatchFiles\Build.bat MeasurementPluginEditor Win64 Development "path\to\MeasurementPlugin.uproject" -waitmutex
```

## Content Assets

| Asset                  | Description                                           |
| ---------------------- | ----------------------------------------------------- |
| `BP_MeasurementActor`  | Pre-configured Blueprint of `AMeasurementActor`       |
| `WBP_MeasurmentWidget` | Widget Blueprint implementing the measurement display |

## License

See [LICENSE](LICENSE) for details.
