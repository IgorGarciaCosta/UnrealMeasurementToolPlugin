# Unreal Measurement Tool Plugin

A spline-based measurement tool plugin for Unreal Engine 5.7 that measures distances and areas in-editor with real-time visual feedback.

![Engine Version](https://img.shields.io/badge/Unreal%20Engine-5.7-blue)
![Platform](https://img.shields.io/badge/Platform-Win64-lightgrey)

## Features

- **Distance & Area modes** — Measure spline length (Distance) or the enclosed polygon area (Area) using the Shoelace formula with Newell's method for arbitrary 3D polygons.
- **Multiple units** — Display results in centimeters, meters, kilometers, feet, inches, or yards. Area mode shows squared units (m², ft², etc.).
- **Spline-based measurement** — Uses `USplineComponent` for accurate distance calculation along curved or straight paths.
- **Linear / Curve splines** — Toggle between smooth curves and straight-line segments per spline.
- **Real-time display** — A `UWidgetComponent` renders the measurement in-world, always facing the camera (billboard effect) with configurable font size.
- **Cumulative labels** — Optionally show accumulated distance at each spline point with configurable size, color, and Z offset.
- **Angle labels** — Display the angle (in degrees) between consecutive spline segments at each point, with configurable size, color, and Z offset. Visual angle arcs can be drawn with adjustable radius, color, and segment count.
- **Snap to geometry** — Three snap modes (via `UMeasurementSnapComponent`):
  - **Off** — No snapping.
  - **Ground Snap** — Traces downward to snap points to the ground (configurable trace distance).
  - **Surface Snap** — Finds the nearest surface within a configurable radius using six-axis cardinal traces. Debug spheres can be drawn to visualize the snap radius.
- **Custom Editor Mode** — A dedicated editor mode (`EM_MeasurementMode`) accessible from the Modes dropdown, with a Slate toolkit panel featuring a details view and Add/Delete buttons. Spawns measurement actors 500 units in front of the viewport camera and auto-selects them.
- **Manual size input** — Enter an exact value (in the selected unit) and the spline rescales to match. In Area mode, scaling uses the square-root ratio to preserve shape.
- **Reset spline** — One-click reset to a default 2-point configuration, clearing rotation and scale.
- **Editor integration** — Measurement updates via `OnConstruction()` with a deferred update system using dirty flags and timers. Billboard rotation is driven by `FEditorDelegates::OnEditorCameraMoved`. Property changes propagate through component multicast delegates.
- **Closing line** — In Area mode, a debug line is drawn from the last spline point back to the first (toggleable).
- **Blueprint function library** — `UMeasurementCalculator` exposes static `BlueprintCallable` functions for polygon area, angle calculation, distance/area formatting, and camera utilities.
- **Decoupled architecture** — The actor communicates with the widget through a `UInterface`, so you can swap or extend the widget without touching the actor. Snap and label logic are encapsulated in dedicated components.

## Installation

1. Clone or copy this repository into your Unreal project's root directory.
2. Make sure the `Plugins/UnrealMeasurementTool` folder is inside your project.
3. Open the project in Unreal Editor — the plugin will be detected automatically.
4. Enable **Unreal Measurement Tool** in _Edit → Plugins_ if it isn't already enabled.

## Usage

1. Activate **Measurement Mode** from the editor Modes dropdown to open the toolkit panel.
2. Click **Add** in the toolkit panel to spawn a `BP_MeasurementActor` in front of the viewport camera.
3. Alternatively, drag `BP_MeasurementActor` from the plugin's content folder into your level.
4. Select the actor and edit its spline points in the viewport to define the measurement path.
5. The widget automatically displays the measurement in the selected unit.
6. Use the **Mode** property to switch between Distance and Area measurement.
7. Use the **Unit** dropdown to change between cm, m, km, ft, in, and yd.
8. Enable **Linear** to switch spline segments from smooth curves to straight lines.
9. To set an exact size, enter a value in the **Size** field (in the current unit) and click **Submit**.
10. Use **Reset** to return to the default 2-point layout.
11. Enable **Show Cumulative Labels** to display the accumulated distance at each spline point.
12. Enable **Show Angle Labels** to display the angle between consecutive segments at each point.
13. Set **Snap Mode** to Ground or Surface to snap spline points to nearby geometry.
14. Click **Delete** in the toolkit panel to remove the selected measurement actor.

## Architecture

```
AMeasurementActor
├── USplineComponent (root) — defines the measurement path
├── UWidgetComponent — renders the measurement text in-world (billboard)
├── UMeasurementSnapComponent — snap-to-geometry logic & properties
│   ├── ESnapMode, SnapRadius, GroundTraceDistance, SnapTraceChannel
│   ├── SnapPoints(), DrawDebugVisualization()
│   └── FOnMeasurementSnapChanged delegate
├── UMeasurementLabelComponent — cumulative & angle labels
│   ├── TArray<UTextRenderComponent> PointLabelComponents (cumulative)
│   ├── TArray<UTextRenderComponent> AngleLabelComponents (angles)
│   ├── UpdateLabels(), FaceLabelsToCamera(), DrawAngleArcs()
│   └── FOnMeasurementLabelChanged delegate
└── IMeasurementTxtWgtCommunicationInterface — sends text & font size to any implementing widget

UMeasurementCalculator : UBlueprintFunctionLibrary
└── Static functions: CalculatePolygonArea(), CalculateAngleBetweenSegments(),
    FormatDistance(), FormatArea(), GetActiveCameraLocation(), FaceComponentToCamera()

UMeasurementTextWidget : UUserWidget, IMeasurementTxtWgtCommunicationInterface
└── UTextBlock "MeasurementText" — displays the formatted measurement

FMeasurementEdMode : FEdMode (EM_MeasurementMode)
├── FMeasurementEdModeToolkit : FModeToolkit
└── SMeasurementToolkitPanel : SCompoundWidget
    ├── IDetailsView — property editor for the selected actor
    └── Add / Delete buttons

EMeasurementUnit   — cm | m | km | ft | in | yd
EMeasurementMode   — Distance | Area
ESnapMode          — None | GroundSnap | SurfaceSnap
```

The actor never references the concrete widget class directly. Communication goes through `IMeasurementTxtWgtCommunicationInterface`, which exposes:

```cpp
void SendMeasurementText(const FText& InText);
void SendMeasurementFontSize(int32 InSize);
```

This makes it straightforward to create a custom widget — just implement the interface. Snap and label logic are encapsulated in their own `UActorComponent` subclasses, communicating with the actor via multicast delegates.

## Properties

### AMeasurementActor

| Property               | Category            | Description                                             |
| ---------------------- | ------------------- | ------------------------------------------------------- |
| **Mode**               | Measurement Control | Distance (spline length) or Area (enclosed polygon).    |
| **Unit**               | Measurement Control | cm, m, km, ft, in, yd.                                  |
| **Size**               | Measurement Control | Target value to apply via Submit (in the current unit). |
| **Linear**             | Measurement Control | Straight-line segments instead of smooth curves.        |
| **Show Closing Line**  | Measurement Control | Debug line from last to first point (Area mode only).   |
| **Main Label Font Size** | Measurement Control | Font size for the main measurement widget (1–200).    |

### UMeasurementSnapComponent

| Property                  | Category            | Description                                          |
| ------------------------- | ------------------- | ---------------------------------------------------- |
| **Snap Mode**             | Measurement Control | Off, Ground (Trace Down), Nearest Surface.           |
| **Snap Radius**           | Measurement Control | Search radius for Surface Snap.                      |
| **Ground Trace Distance** | Measurement Control | Max downward trace for Ground Snap.                  |
| **Snap Trace Channel**    | Measurement Control | Collision channel used for snap traces.              |
| **Show Snap Radius**      | Measurement Control | Debug spheres around each point (Surface Snap).      |

### UMeasurementLabelComponent — Cumulative Labels

| Property                     | Category                                | Description                                          |
| ---------------------------- | --------------------------------------- | ---------------------------------------------------- |
| **Show Cumulative Labels**   | Measurement Control \| Cumulative Labels | Display accumulated distance at each spline point.  |
| **Label Size**               | Measurement Control \| Cumulative Labels | World-size of the cumulative label text.            |
| **Label Color**              | Measurement Control \| Cumulative Labels | Color of the cumulative label text.                 |
| **Cumulative Label Z Offset** | Measurement Control \| Cumulative Labels | Vertical offset above the spline point.            |

### UMeasurementLabelComponent — Angle Labels

| Property                | Category                            | Description                                              |
| ----------------------- | ----------------------------------- | -------------------------------------------------------- |
| **Show Angle Labels**   | Measurement Control \| Angle Labels | Display angle between consecutive segments at each point.|
| **Angle Label Size**    | Measurement Control \| Angle Labels | World-size of the angle label text.                      |
| **Angle Label Color**   | Measurement Control \| Angle Labels | Color of the angle label text.                           |
| **Angle Label Z Offset**| Measurement Control \| Angle Labels | Vertical offset above the spline point.                  |
| **Show Angle Arcs**     | Measurement Control \| Angle Labels | Draw visual arcs showing the angle.                      |
| **Angle Arc Radius**    | Measurement Control \| Angle Labels | Radius of the debug angle arc.                           |
| **Angle Arc Color**     | Measurement Control \| Angle Labels | Color of the angle arc.                                  |
| **Angle Arc Segments**  | Measurement Control \| Angle Labels | Number of line segments in the arc.                      |

## Module Dependencies

### UnrealMeasurementTool (Runtime)

| Type        | Modules                                            |
| ----------- | -------------------------------------------------- |
| **Public**  | Core, CoreUObject, Engine                          |
| **Private** | Slate, SlateCore, UMG, UnrealEd (editor builds only) |

### UnrealMeasurementToolEditor (Editor)

| Type        | Modules                                                     |
| ----------- | ----------------------------------------------------------- |
| **Public**  | Core, CoreUObject, Engine, UnrealEd, EditorFramework, UnrealMeasurementTool |
| **Private** | Slate, SlateCore, InputCore, LevelEditor, PropertyEditor    |

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
