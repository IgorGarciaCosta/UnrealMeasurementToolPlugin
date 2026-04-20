# Unreal Measurement Tool Plugin

A spline-based measurement tool plugin for Unreal Engine 5.7 that displays distance via a decoupled widget interface.

![Engine Version](https://img.shields.io/badge/Unreal%20Engine-5.7-blue)
![Platform](https://img.shields.io/badge/Platform-Win64-lightgrey)

## Features

- **Spline-based measurement** — Uses `USplineComponent` for accurate distance calculation along curved or straight paths.
- **Real-time display** — A `UWidgetComponent` renders the measurement in-world, always facing the camera (billboard effect).
- **Editor integration** — Measurement updates live as you edit spline points in the viewport via `OnConstruction()`.
- **Manual size input** — Set an exact distance in meters and the spline rescales to match.
- **Reset spline** — One-click reset to a default 2-point configuration.
- **Decoupled architecture** — The actor communicates with the widget through a `UInterface`, so you can swap or extend the widget without touching the actor.

## Installation

1. Clone or copy this repository into your Unreal project's root directory.
2. Make sure the `Plugins/UnrealMeasurementTool` folder is inside your project.
3. Open the project in Unreal Editor — the plugin will be detected automatically.
4. Enable **Unreal Measurement Tool** in _Edit → Plugins_ if it isn't already enabled.

## Usage

1. Drag `BP_MeasurementActor` from the plugin's content folder into your level.
2. Select the actor and edit its spline points in the viewport to define the measurement path.
3. The widget automatically displays the spline length in meters.
4. To set an exact size, change the `ManualSizeMeters` property in the Details panel and call **Apply Manual Size**.
5. Use **Reset Spline** to return to the default 2-point layout.

## Architecture

```
AMeasurementActor
├── USplineComponent (root) — defines the measurement path
├── UWidgetComponent — renders the distance text in-world
└── IMeasurementTxtWgtCommunicationInterface — sends text to any implementing widget

UMeasurementTextWidget : UUserWidget, IMeasurementTxtWgtCommunicationInterface
└── UTextBlock "MeasurementText" — displays the formatted distance
```

The actor never references the concrete widget class directly. Communication goes through `IMeasurementTxtWgtCommunicationInterface`, which exposes a single method:

```cpp
void SendMeasurementText(const FText& InText);
```

This makes it straightforward to create a custom widget — just implement the interface.

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
