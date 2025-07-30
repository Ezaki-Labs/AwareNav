# AwareNav

AwareNav is a plugin for Unreal Engine 5.4.4 that enhances navigation systems with awareness-driven pathfinding and AI navigation features. It is designed to help developers create more intelligent and context-aware AI agents in their Unreal Engine projects.

## Features

- **Awareness-Based Pathfinding:** Integrates awareness levels into navigation, allowing AI to choose paths based on environmental stimuli or agent states.
- **Customizable Navigation Queries:** Extend or override default navigation queries to account for custom awareness logic.
- **Seamless UE Integration:** Works with Unreal Engine's built-in navigation system and AI controllers.
- **Blueprint and C++ Support:** Expose core functionality to Blueprints for rapid prototyping, with full C++ extensibility.
- **Debugging Tools:** Includes visualization and debugging utilities for awareness zones and navigation decisions.

## Installation

1. Copy the `AwareNav` plugin folder into your project's `Plugins` directory.
2. Regenerate project files (right-click `.uproject` > "Generate Visual Studio project files").
3. Open your project in Unreal Engine.
4. Enable the plugin via `Edit > Plugins > Project > AwareNav`.

## Usage

### Basic Setup

1. Add the `AwareNav` component to your AI-controlled actors.
2. Configure awareness parameters in the component details panel or via C++.
3. Use provided Blueprint nodes or C++ API to trigger awareness-based navigation.

### Example: Blueprint Integration

```blueprint
// Pseudocode: Use the "Find Aware Path" node to get a path considering awareness
AwareNavComponent->FindAwarePath(StartLocation, EndLocation, AwarenessLevel)
```

### Example: C++ Integration

```cpp
#include "AwareNavComponent.h"

UFUNCTION()
void MoveWithAwareness(AAIController* Controller, FVector Destination, float AwarenessLevel)
{
    UAwareNavComponent* NavComp = Controller->FindComponentByClass<UAwareNavComponent>();
    if (NavComp)
    {
        NavComp->FindAwarePath(Controller->GetPawn()->GetActorLocation(), Destination, AwarenessLevel);
    }
}
```

## Configuration

- **Awareness Levels:** Define how sensitive your AI is to environmental factors (e.g., noise, light, obstacles).
- **Custom Zones:** Mark areas in your level with different awareness modifiers.
- **Debug Visualization:** Enable debug drawing to visualize awareness zones and chosen paths.

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests for bug fixes or new features.

## License

This plugin is distributed under the MIT License. See `LICENSE` for details.

## Support

For questions or support, open an issue on the repository or contact the maintainer.

