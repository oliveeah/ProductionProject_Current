# Production Project - Weekly Progress Summary

This document provides a week-by-week summary of development progress on the Production Project (Unreal Engine 5 game).

---

## Week 1: September 22 - September 28, 2025

**Theme: Project Setup & Core Tool System Foundation**

### Key Accomplishments:
- **Project Initialization** (Sept 23)
  - Created initial repository and project files
  - Added Unreal Engine project files and restored retargeting from previous work
  - Textured player character model

- **Tool System Development** (Sept 24-28)
  - Added nature pack for testing assets
  - Created tool input bindings (Tool 1 and Tool 2)
  - Added axe and pickaxe tools
  - Implemented tool socket binding system
  - Created tool swapping mechanic with toggle on/off functionality
  - Added swing animation and implemented it with IA_Use input action
  - Added ability to unequip tools using boolean inside switch statement
  - Improved `toggleHandState()` function
  - Removed `AttachToComponent` in constructor to fix build errors
  - Added AnimNotifyState for tool collision (replacing AnimNotify for proper tick functionality)
  - Created collision system for tool swinging with new trace channel
  - Added 'breakable' tag for destructible objects

- **Mesh & Animation Work** (Sept 28)
  - Re-imported mesh at 8x scale to prevent IK issues
  - Got idle animation working properly

---

## Week 2: September 29 - October 5, 2025

**Theme: Card System & UI Development**

### Key Accomplishments:
- **Build Mode System** (Sept 29)
  - Added build mode binding with input control
  - Created switch statement implementation

- **Primary Data Asset System** (Sept 29)
  - Created primary data asset base class for card polymorphism
  - Added some template card designs
  - Created widget for card UI
  - Added 20 card data asset templates that inherit from base class

- **Game Mode & Widget System** (Sept 30 - Oct 1)
  - Added C++ game mode class with Blueprint child
  - Changed folder structure for organization
  - Worked on data table structure concept
  - Created widget logic for cards
  - Moved widget logic to player class (in BeginPlay instead of constructor/GameMode)
  - Successfully adding cards to screen in Blueprint, then converted to C++

- **Widget Toggle & Cleanup** (Oct 2)
  - Added ability to turn widget on and off
  - Removed junk files and cleaned up project

---

## Week 3: October 6 - October 12, 2025

*No commits this week.*

---

## Week 4: October 13 - October 19, 2025

*No commits this week.*

---

## Week 5: October 20 - October 26, 2025

**Theme: Camera, Models & Card UI Polish**

### Key Accomplishments:
- **Scene & Camera Work** (Oct 21)
  - Added new 3D models to the project
  - Made camera changes
  - Project organization and planning

- **Card Generation System** (Oct 22)
  - Implemented card system logic
  - Cards now generate and appear on screen dynamically
  - Created actual decent UI for cards
  - Implemented card fanning system (spreading cards in hand)
  - Improved fanning with customizable variables

- **Final Polish** (Oct 23)
  - Refined fan animation behavior
  - Session wrap-up and finalization

---

## Week 6: October 27 - November 2, 2025

*No commits this week.*

---

## Week 7: November 3 - November 9, 2025

**Theme: Player Animations & Interaction System**

### Key Accomplishments:
- **Player Blueprint & Animation** (Nov 4)
  - Set up test player Blueprint and Animation Blueprint
  - Started thread-safe update functions
  - Added mouse hover functionality during gameplay
  - Worked on finding better animations

- **Jump System** (Nov 4-5)
  - Added jump functionality to C++
  - Sorted out jump animations
  - Solved jump animation issues

- **Interaction & Delegate System** (Nov 5-6)
  - Created temporary Blueprint delegate sender class to add cards to player
  - Working on actor component interaction sphere receiver
  - Implemented interaction system with UI interface
  - Fixed interface display issues (cleared cache to resolve)
  - Interface is now FINALLY working!

- **Interface Polymorphism & Tool Refactoring** (Nov 6-8)
  - Interface now polymorphic and reacts differently based on interaction target
  - Tested interface in Blueprint (confirmed working)
  - Implemented tool subclasses to player Blueprint
  - Refactored tool base and child system
  - Deleted unused C++ files
  - Merged test branch into main (PR #1)

---

## Week 8: November 10 - November 16, 2025

**Theme: Advanced Animations & Board Game System**

### Key Accomplishments:
- **Advanced Animation Systems** (Nov 10)
  - Worked on holding tool animation with blend pose
  - Animation now blending by pose correctly
  - Isolated right arm from being affected and added socket
  - Added new meshes
  - Tools now showing up correctly with struct refactoring
  - Created logic for swapping weapons

- **Tool System Refactoring** (Nov 11)
  - Refactored tool system with new animation for swinging
  - Need to add hitbox to swing animation (noted for future work)
  - Added collision notify state to player
  - Organized and cleaned codebase
  - Created spectator pawn

- **Board Game System** (Nov 12)
  - Created camera pawn with FOV zooming functionality
  - Imported custom tile model
  - Created algorithm to spawn tiles in a grid
  - Completed tile creation system
  - Merged "To Board Game Test" branch (PR #3)

---

## Summary Statistics

| Week | Date Range | Focus Area | Commits |
|------|------------|------------|---------|
| 1 | Sept 22-28 | Project Setup & Tools | ~15 |
| 2 | Sept 29 - Oct 5 | Card System & UI | ~10 |
| 3 | Oct 6-12 | - | 0 |
| 4 | Oct 13-19 | - | 0 |
| 5 | Oct 20-26 | Camera & Card UI Polish | ~8 |
| 6 | Oct 27 - Nov 2 | - | 0 |
| 7 | Nov 3-9 | Animations & Interactions | ~15 |
| 8 | Nov 10-16 | Board Game System | ~15 |

---

## Major Systems Implemented

1. **Tool/Weapon System** - Complete tool equip/unequip, swapping, and swing mechanics
2. **Animation System** - Blend poses, socket attachments, swing animations, jump animations
3. **Card System** - Data assets, UI widgets, card generation, fanning display
4. **Interaction System** - Polymorphic interface for different interaction types
5. **Camera System** - FOV zooming, camera pawn for board game view
6. **Board Game System** - Tile generation algorithm, grid-based tile spawning

---

## Pull Requests

| PR# | Title | Date | Description |
|-----|-------|------|-------------|
| #1 | Test branch | Nov 8 | Initial tool and animation systems |
| #2 | Test branch | Nov 12 | Animation and interaction updates |
| #3 | To board game test | Nov 12 | Tile creation and board game systems |

---

*Generated from git commit history*
