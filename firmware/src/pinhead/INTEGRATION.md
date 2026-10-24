# Pin Head ↔ Felucca Integration Notes

## Current state
- DSP engine lives in `engine.c` (float).
- Stub `eng_pinhead.c` provides `engine_t ENG_PINHEAD` with `note_on` / `render`.
- Not yet added to the `ENGINES[]` table in `engines.c` (NENGINES / ENGINE_ORDER must be updated carefully).

## To finish registration
1. In `firmware/src/core.h` increase `NENGINES` by 1 and add `ENGI_PINHEAD`.
2. In `firmware/src/engines.c`:
   - `#include "pinhead/eng_pinhead.c"`
   - Append `&ENG_PINHEAD` to `ENGINES[]`.
   - Append the new index to `ENGINE_ORDER[]`.
3. Build and confirm it appears in the engine list.
4. Wire matrix drawing into `gfx.c` / UI modes.
5. Map GLO pages to the existing global FX knobs.

The float DSP is functional for testing; a fixed-point rewrite can follow once the integration is stable.
