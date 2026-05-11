# A-10 Warthog

A small SGDK project — me trying out the [Sega Genesis Development Kit](https://github.com/Stephane-D/SGDK) and confirming the build runs on real Mega Drive hardware. It does.

**[Play it in your browser →](https://seanbouk.github.io/A10_MegaDrive/)**

## What it is

A top-down A-10 Warthog flying over a forest, with parallax scrolling between the forest floor and the tree canopy.

**Controls (Pad 1):**
- **Up / Down** — bank left/right. The roll angle drifts the plane laterally across the screen and returns to level when released.
- **Left / Right** — throttle down / up.

The A-10 sprite animates through 11 banking frames driven by the current roll value.

## Assets

- **Backgrounds** (`res/BG4 out.png`, `res/FG4 out H.png`) were processed with [quantizeMD](https://github.com/seanbouk/quantizeMD) — a tool I wrote to crunch RGB images down to the Mega Drive's palette and tile-count limits (3 bits per channel, two 16-colour palettes, dithering, tile-count reduction).
- **The A-10 sprite** (`res/a10.png`) is a digitised 3D asset — rendered out at the 11 bank angles, then quantised down for the hardware.

## Build

Standard SGDK project — open in the SGDK toolchain and `make` produces a `.bin` in `out/` that runs on emulator or real hardware.
