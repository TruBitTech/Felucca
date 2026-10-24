# Pin Head Engine

EMS Synthi AKS-inspired pin-matrix synthesizer, being integrated into this Felucca fork.

## Status

Initial scaffolding. The core modules (matrix, presets, joystick, UI) are here. The full DSP engine (`engine.c`) will be added next and wired into Felucca's audio and UI systems.

## Next steps

1. Complete and add `engine.c` (oscillators, filter, ring mod, envelope, spring, tape, global FX).
2. Register the engine in `engines.c`.
3. Wire matrix drawing and mode switching into Felucca's UI.
4. Test in the host simulator / browser emulator.
5. Package as a `.fwsc`.

See the original sketches in https://github.com/TruBitTech/pinhead/tree/main/firmware
