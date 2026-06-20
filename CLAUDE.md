# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

ZMK firmware for the "tecla-cero" split keyboard with trackball support. Uses the BMP Boost board (nRF52840-based) and supports both USB and BLE connections.

## Build System

Firmware is built via GitHub Actions using the ZMK build workflow. Push to trigger builds, or use workflow_dispatch for manual builds. Build artifacts are defined in `build.yaml`.

### Build Configurations

| Artifact Name | Description |
|--------------|-------------|
| `tecla_cero_right_central_with_trackpad` | Right half central with mini trackpad |
| `tecla_cero_right_central_no_trackpad` | Right half central without mini trackpad |
| `tecla_cero_left_peripheral_with_trackpad` | Left half peripheral with mini trackpad |
| `tecla_cero_left_peripheral_no_trackpad` | Left half peripheral without mini trackpad |
| `settings_reset` | Reset firmware for clearing settings |

Flash `tecla_cero_right_central_*` firmware to the right half and `tecla_cero_left_peripheral_*` firmware to the left half.

## Architecture

### West Manifest (`config/west.yml`)
Defines external dependencies from zmkfirmware and sekigon-gonnoc repos:
- ZMK core (v0.2)
- BMP Boost board support
- PAW3222 trackball driver
- Status LED, CDC ACM bootloader trigger, non-lipo battery management features

### Shield Definition (`boards/shields/tecla_cero_adv/`)
- `tecla_cero_adv.dtsi` - Main device tree include: GPIO matrix (5x5 per side), trackball SPI config
- `tecla_cero_left.overlay` / `tecla_cero_right.overlay` - Split half configurations
- `*.conf` - Kconfig options (ZMK Studio, BLE power, battery monitoring)

### Keymap (`config/keymap.keymap`)
Default keymap with 3 layers for 46-key layout. Editable via ZMK Studio (studio feature enabled).

## Hardware Configuration

### Matrix: 5 rows × 5 columns (per side)
- Total: 46 mapped keys (ROW3 has no physical key at COL1/COL2 on the left and COL6/COL7 on the right — thumb cluster is 3 keys per side)
- ROW0-ROW4, COL0-COL4

### Trackball
- Both sides (PAW3222 via SPI)

## Key Features

- ZMK Studio support for live keymap editing
- PAW3222 trackball via SPI
- Non-lipo battery monitoring (for AAA batteries)
- Status LED
- CDC ACM bootloader trigger for easy reflashing
