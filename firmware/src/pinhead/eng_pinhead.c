/* SPDX-License-Identifier: GPL-3.0-only
 * Pin Head engine stub for Felucca integration.
 * Full DSP lives in engine.c; this provides the engine_t entry so it can be selected.
 */
#include "engine.h"
#include "matrix.h"
#include "joystick.h"

static MatrixState ph_matrix;
static JoystickState ph_joystick;
static Engine ph_engine;
static int ph_inited = 0;

static void ph_ensure_init(void)
{
    if (ph_inited) return;
    matrix_init(&ph_matrix);
    joystick_init(&ph_joystick);
    engine_init(&ph_engine, &ph_matrix, &ph_joystick);
    preset_load(&ph_matrix, 0); /* On the Run */
    ph_inited = 1;
}

static void ph_note_on(struct track *t, voice_t *v)
{
    (void)t;
    ph_ensure_init();
    float freq = 440.0f * powf(2.0f, (v->note - 69) / 12.0f);
    engine_set_note(&ph_engine, freq);
    engine_set_gate(&ph_engine, true);
}

static void ph_render(struct track *t, voice_t *v, int32_t *out, uint32_t n, const vmod_t *m)
{
    (void)t; (void)v; (void)m;
    ph_ensure_init();
    float L[64], R[64];
    if (n > 64) n = 64;
    engine_process(&ph_engine, L, R, (int)n);
    for (uint32_t i = 0; i < n; i++) {
        /* convert float -1..1 to Q15 and add */
        int32_t s = (int32_t)(L[i] * 16000.0f);
        if (s > 32767) s = 32767;
        if (s < -32768) s = -32768;
        out[i] += s;
    }
}

static const param_desc_t PH_EDIT[8] = {
    { "PIN",  F_INT, 0, 3, 1, 0, 0 },
    { "VIEW", F_ONOFF, 0, 1, 0, 0, 0 },
    { "JX",   F_BIPCT, -64, 63, 0, 0, 0 },
    { "JY",   F_BIPCT, -64, 63, 0, 0, 0 },
    { "RVB",  F_PCT, 0, 100, 20, 0, 0 },
    { "DLY",  F_PCT, 0, 100, 15, 0, 0 },
    { "TAPE", F_PCT, 0, 100, 20, 0, 0 },
    { "PRE",  F_INT, 0, 6, 0, 0, 0 },
};

static const preset_t PH_PRESETS[] = {
    { "On the Run", {0}, {10, 40, 60, 40}, 0, 0 },
    { "Empty",      {0}, {10, 40, 60, 40}, 0, 0 },
};

const engine_t ENG_PINHEAD = {
    .name = "PINHEAD",
    .page_title = { "MATRIX", "GLO" },
    .edit = { PH_EDIT[0], PH_EDIT[1], PH_EDIT[2], PH_EDIT[3],
              PH_EDIT[4], PH_EDIT[5], PH_EDIT[6], PH_EDIT[7] },
    .presets = PH_PRESETS,
    .npresets = 2,
    .knob = { P_E0, P_E1, P_E2, P_E3 },
    .poly = 1,
    .note_on = ph_note_on,
    .render = ph_render,
};
