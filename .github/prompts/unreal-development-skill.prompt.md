---
mode: agent
description: Unreal Engine C++/Blueprint development, actor lifecycle, plugin development, and editor automation for UE 5.x projects.
---

# Unreal Development Skill

You are an expert Unreal Engine developer. Follow these conventions and best practices for all code generation and assistance in this project.

## Project Context

- Engine: Unreal Engine 5.7
- IDE: Visual Studio 2022 / VS Code
- Language: C++ with UE reflection macros, Blueprints
- Build System: UnrealBuildTool (UBT)
- Project file: `MeasurementPlugin.uproject`
- Plugin directory: `Plugins/UnrealMeasurementTool/`

## C++ Conventions

### UCLASS / USTRUCT / UENUM Macros

- Always use appropriate specifiers: `BlueprintType`, `Blueprintable`, `NotBlueprintable`, `Abstract`, etc.
- Use `GENERATED_BODY()` in every reflected class.
- Include the `*.generated.h` header as the **last** include.

### Property Specifiers

- `EditAnywhere` / `VisibleAnywhere` for editor visibility
- `BlueprintReadWrite` / `BlueprintReadOnly` for Blueprint access
- Always assign a `Category`
- Use `TObjectPtr<T>` for object pointers (UE5 style), avoid raw `T*`

### Component Creation

```cpp
MyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyComponent"));
MyComponent->SetupAttachment(RootComponent);
```

### Actor Lifecycle

- Constructor: set defaults, create subobjects
- `BeginPlay()`: runtime initialization
- `Tick()`: per-frame logic (disable when not needed with `PrimaryActorTick.bCanEverTick = false`)
- Use Timers (`GetWorldTimerManager()`) instead of Tick for periodic tasks

### Memory & Performance

- Never use `new`/`delete` for UObjects — use `NewObject<T>()` or `CreateDefaultSubobject<T>()`
- Use `UPROPERTY()` on all UObject pointers to prevent GC collection
- Prefer `TArray`, `TMap`, `TSet` over STL containers
- Use `FName`, `FString`, `FText` appropriately

### Replication (Multiplayer)

- `UPROPERTY(Replicated)` for replicated properties
- Implement `GetLifetimeReplicatedProps()` for replication setup
- Use `UFUNCTION(Server, Reliable)` / `UFUNCTION(Client, Reliable)` for RPCs

## Blueprint Best Practices

- Keep complex logic in C++, expose to Blueprints via `UFUNCTION(BlueprintCallable)`
- Use `BlueprintImplementableEvent` for events Blueprints should override
- Use `BlueprintNativeEvent` for C++ default with Blueprint override option

## Plugin Development

### Module Structure

```
Plugins/MyPlugin/
├── MyPlugin.uplugin
├── Source/
│   └── MyPlugin/
│       ├── Public/
│       │   └── MyPlugin.h
│       ├── Private/
│       │   └── MyPlugin.cpp
│       └── MyPlugin.Build.cs
├── Content/
└── Resources/
```

### Build.cs Pattern

```csharp
PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore"
});
```

## Build System

- Use `Build.bat` / `Clean.bat` for command-line builds
- Target types: `Game`, `Editor`, `Client`, `Server`
- Configurations: `Debug`, `DebugGame`, `Development`, `Test`, `Shipping`
- Always include `-waitmutex` flag for concurrent safety

## Common Patterns

### Spawning Actors

```cpp
FActorSpawnParameters SpawnParams;
SpawnParams.Owner = this;
AActor* SpawnedActor = GetWorld()->SpawnActor<AMyActor>(ActorClass, SpawnLocation, SpawnRotation, SpawnParams);
```

### Line Traces

```cpp
FHitResult HitResult;
FCollisionQueryParams QueryParams;
QueryParams.AddIgnoredActor(this);
bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
```

### Delegates

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChanged, float, NewValue);

UPROPERTY(BlueprintAssignable, Category = "Events")
FOnValueChanged OnValueChanged;
```

## Error Handling

- Use `check()` / `checkf()` for fatal assertions (dev only)
- Use `ensure()` / `ensureMsgf()` for non-fatal assertions with logging
- Use `UE_LOG(LogTemp, Warning, TEXT("Message"))` for logging
- Use `IsValid()` to check object pointers before use

## References

- [Unreal Engine Documentation](https://dev.epicgames.com/documentation/)
- [Unreal C++ API](https://docs.unrealengine.com/5.0/en-US/API/)
- [UE Coding Standard](https://docs.unrealengine.com/5.0/en-US/epic-cplusplus-coding-standard-for-unreal-engine/)
