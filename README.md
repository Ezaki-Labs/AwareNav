# 🧠 AwareNav — Emotion & Permission-Based Navigation for Unreal Engine

**AwareNav** is a modular Unreal Engine plugin that enhances AI navigation with **emotion-aware pathfinding** and **permission-based access control**. Ideal for games with dynamic AI personalities, stealth, horror, or story-driven behaviour systems.

---

## 🔑 Features

### 🎭 Emotion-Aware Navigation *(Optional)*

- Define **emotional zones**: Fear, Safety, Nostalgia, Haunting
- Each AI agent has traits: `Courage`, `ComfortSeeking`, `Memory`
- Emotion zones alter navmesh costs dynamically per agent
- Emotion strength is stat-driven and customizable

### 🔐 Permission-Based Navigation *(Optional)*

- Tag nav areas with **access permissions**
- Agents have permission flags (bitmask)
- Navigation automatically respects allowed areas

### ⚙️ Fully Configurable

- Enable/disable Emotion and Permission systems independently
- All behaviour is configurable via **Project Settings > AwareNav**

---

## 🚀 Getting Started

### ✅ Install the Plugin

1. Copy the `AwareNav` folder to your project's `Plugins/` directory
2. Open Unreal Editor → **Enable the plugin** in Plugin Browser
3. Restart the editor

### 🧠 Emotion System Setup

1. Create data table with `FAwAgentEmotionalAbilityGroupProfile` type and set it in **Project Settings > AwareNav**
2. Set traits per `GroupID` in the data table:
   - `Courage` → resists fear zones
   - `ComfortSeeking` → prefers safe zones
   - `Memory` → amplifies nostalgia/haunting response
3. Add `UAwAgentEmotionProfileComponent` to all AI characters, which should have emotions
4. Set `GroupId` in the component
5. Place `AwEmotionalAreaVolume` actors in your level, or spawn them dynamically
6. NavMesh cost is auto-adjusted per agent during pathfinding

### 🔐 Permission System Setup

1. Create data table with `FAwAgentPermissionGroupProfile` type and set it in **Project Settings > AwareNav**
2. Define `EPermissionLevel` bitmask flags per `GroupID` in the data table
3. Add `UAwAgentPermissionProfileComponent` to all AI characters, which should have permissions
4. Set `GroupId` in the component
5. Place `AAwRestrictedAreaVolume` actors in your level, and tag areas with required permissions
6. Agents will avoid restricted areas


*Emotion- and permission-based navigation require the use of *`UAwNavigationQueryFilter`*, which enables dynamic, agent-specific cost calculations. If it’s the only NavigationQueryFilter used in your project, you can assign it directly in the AIController as the default query filter.*

---

## 🧩 Example

**Emotional Ability Group Profile data table:**
| GroupId    | Traits (Courage/Comfort/Memory) |
| ---------- | ------------------------------- |
| Civilian   | 8 / 16 / 18                     |
| Guard Dog  | 18 / 12 / 11                    |
| Rat        | 2 / 18 / 20                     |

**Permission Group Profile data table:**
| GroupId        | Permissions                   |
| -------------- | ----------------------------- |
| Civilian       | Low level permissions only    |
| Security Drone | Full permissions              |
| Guard Dog      | Low and mid level permissions |

**Agents setup:**
| Agent Type     | Emotional Ability Group ID | Permission Group ID     |
| -------------- | -------------------------- | ----------------------- |
| Civilian       | Civilian                   | Civilian                |
| Security Drone | `Not Enabled - Ignored`    | Security Drone          |
| Guard Dog      | Guard Dog                  | Guard Dog               |
| Rat            | Rat                        | `Not Enabled - Ignored` |

Each agent navigates the same map differently based on emotion and access control.

---

### 🧠 `UAwareNavSubsystem`

`UAwareNavSubsystem` is the main access point for all AwareNav systems. It provides access to emotion- and permission-based subsystems and reflects the plugin’s runtime configuration.

```Example Usage
UAwareNavSubsystem* AwareNav = UAwareNavSubsystem::Get(this);
AwareNav->SetAgentEmotionGroupProfile(AgentRef, TEXT("Civilian"));
...
AwareNav->AdjustEmotionTemporarily(AgentRef, EEmotionalAbilityType::Courage, 5, 30.0f);
...
FEmotionAreaSpawnParams SpawnParams;
SpawnParams.SpawnLocation = GetActorLocation();
SpawnParams.EmotionType = EAwEmotionType::Fear;
SpawnParams.Radius = 500.0f;
SpawnParams.bHasLifeSpan = true;
SpawnParams.LifeSpan = 50.0f;
SpawnParams.bReducing = true;
SpawnParams.ReduceIntervalInSeconds = 3.0f;
SpawnParams.ReduceAmountPerInterval = 50.0f;

AwareNav->SpawnEmotionArea(SpawnParams)

```

**List of public methods of** `UAwareNavSubsystem`
| Method                            | Purpose                                                                                             |
| --------------------------------- | --------------------------------------------------------------------------------------------------- |
| `SetAgentPermissionGroupProfile`  | Assigns a permission group profile to the specified agent.                                          |
| `SetAreaPermission`               | Sets the permission level for a restricted area volume.                                             |
| `SetAgentEmotionGroupProfile`     | Assigns an emotion group profile to the specified agent.                                            |
| `AdjustEmotion`                   | Adjusts the specified emotional ability value for an agent.                                         |
| `AdjustEmotionTemporarily`        | Temporarily adjusts the specified emotional ability value for an agent, reverting after a set time. |
| `SpawnEmotionArea`                | Spawns a new emotion area in the world with the specified parameters.                               |

*All methods are* `BlueprintCallable`

---

## ⚙️ Project Settings

Find under **Project Settings > AwareNav**:

- `EnablePermissionSystem`
- `PermissionGroupProfilesTable`
- `EnableEmotionSystem`
- `EmotionGroupProfilesTable`

---

## 📄 License

This plugin is provided under your project license. Commercial or private use permitted.

---

## 🤝 Feedback & Suggestions

This plugin is not open to forking or external contributions at this time.  
However, feedback, ideas, and bug reports are always welcome — feel free to open an issue or get in touch.