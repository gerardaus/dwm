# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a dwm (dynamic window manager) build - a minimalist, fast window manager for X11. The project follows the suckless philosophy of simplicity and customization through source code modification.

## Build System

- **Build**: `make`
- **Clean**: `make clean`
- **Install**: `make clean install` (may require sudo)
- **Development**: `make clean && make` for testing changes

The build system uses a traditional Makefile with configuration in `config.mk`. The project automatically copies `config.def.h` to `config.h` if it doesn't exist.

## Core Architecture

### Main Components
- **dwm.c**: Main window manager logic (~2000+ lines)
  - Event handling system with O(1) dispatch via function pointer array
  - Client management through linked lists per monitor
  - Tag-based workspace system
  - Layout management system
- **drw.c/drw.h**: Drawing abstraction layer for X11/Xft rendering
- **util.c/util.h**: Utility functions (die, ecalloc, MIN/MAX macros)

### Configuration System
- **config.def.h**: Default configuration template
- **config.h**: Active configuration (generated from config.def.h)
- Configuration includes:
  - Visual appearance (colors, fonts, borders, gaps)
  - Keybindings and mouse bindings
  - Window rules and layouts
  - Status bar settings

### Key Concepts
- **Clients**: X11 windows managed by dwm
- **Monitors**: Physical displays with independent tag sets
- **Tags**: Workspace system (bit mask, windows can be on multiple tags)
- **Layouts**: Window arrangement algorithms (tiled, floating, monocle, etc.)
- **Focus stack**: Per-monitor history for Alt-Tab behavior

## Custom Extensions

This build includes several patches and custom layout files:
- **grid.c**: Grid layout implementation
- **fibonacci.c**: Fibonacci spiral layout
- **Patch files**: Various dwm community patches (pertag, scratchpad, gridmode, etc.)

## Development Workflow

1. Modify `config.def.h` for configuration changes
2. Delete `config.h` to force regeneration: `rm config.h`
3. Rebuild: `make clean && make`
4. Test changes before installing system-wide
5. For layout changes, modify the layout functions in the respective .c files

## Key Files for Customization
- `config.def.h`: All user-facing configuration
- `dwm.c`: Core functionality modifications
- Layout files (`grid.c`, `fibonacci.c`): Custom window arrangements
- `config.mk`: Build system and dependency configuration

## X11 Dependencies
Requires X11 development headers and libraries:
- libX11
- libXft (font rendering)
- libfontconfig
- libXinerama (multi-monitor support)