/**
    @file
    void.interpol - Enhanced line with 16 parametric curve types

    A drop-in replacement for line that supports curved interpolation between
    breakpoints. 16 curve types, most parametric. Compatible with function
    output (val time val time...) plus extended syntax with optional curve
    type and parameters per segment.

    @ingroup    SV
*/

#include "ext.h"
#include "ext_obex.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ─────────────────────────────────────────────────────────────────────────────
// Curve types
// ─────────────────────────────────────────────────────────────────────────────
typedef enum {
    CURVE_LINEAR = 0,
    CURVE_EXP,
    CURVE_LOG,
    CURVE_SINE,
    CURVE_COSINE,
    CURVE_POWER,
    CURVE_SQUARE,        // alias of power 2
    CURVE_SQRT,          // alias of power 0.5
    CURVE_EASE_IN,
    CURVE_EASE_OUT,
    CURVE_EASE_IN_OUT,
    CURVE_BEZIER,        // 4 params: x1 y1 x2 y2 (cubic CSS-style)
    CURVE_BEZIER2,       // 2 params: cx cy (quadratic)
    CURVE_SIGMOID,
    CURVE_BEND,          // -1..1 (curve~ style)
    CURVE_SPRING,
    CURVE_BOUNCE,
    CURVE_ELASTIC,
    CURVE_NUM_TYPES
} t_curve_type;

#define MAX_CURVE_PARAMS 4

// ─────────────────────────────────────────────────────────────────────────────
// Curve specification table: name, # params, default values
// ─────────────────────────────────────────────────────────────────────────────
typedef struct _curve_spec {
    const char    *name;
    int            num_params;
    double        default_params[MAX_CURVE_PARAMS];
} t_curve_spec;

static const t_curve_spec curve_specs[CURVE_NUM_TYPES] = {
    [CURVE_LINEAR]      = { "linear",      0, { 0, 0, 0, 0 } },
    [CURVE_EXP]         = { "exp",         1, { 3.0, 0, 0, 0 } },
    [CURVE_LOG]         = { "log",         1, { 3.0, 0, 0, 0 } },
    [CURVE_SINE]        = { "sine",        0, { 0, 0, 0, 0 } },
    [CURVE_COSINE]      = { "cosine",      0, { 0, 0, 0, 0 } },
    [CURVE_POWER]       = { "power",       1, { 2.0, 0, 0, 0 } },
    [CURVE_SQUARE]      = { "square",      0, { 2.0, 0, 0, 0 } },     // fixed: t^2
    [CURVE_SQRT]        = { "sqrt",        0, { 0.5, 0, 0, 0 } },     // fixed: t^0.5
    [CURVE_EASE_IN]     = { "ease_in",     1, { 3.0, 0, 0, 0 } },
    [CURVE_EASE_OUT]    = { "ease_out",    1, { 3.0, 0, 0, 0 } },
    [CURVE_EASE_IN_OUT] = { "ease_in_out", 1, { 3.0, 0, 0, 0 } },
    [CURVE_BEZIER]      = { "bezier",      4, { 0.42, 0.0, 0.58, 1.0 } },
    [CURVE_BEZIER2]     = { "bezier2",     2, { 0.5, 0.0, 0, 0 } },
    [CURVE_SIGMOID]     = { "sigmoid",     1, { 5.0, 0, 0, 0 } },
    [CURVE_BEND]        = { "bend",        1, { 0.0, 0, 0, 0 } },
    [CURVE_SPRING]      = { "spring",      1, { 2.0, 0, 0, 0 } },
    [CURVE_BOUNCE]      = { "bounce",      1, { 3.0, 0, 0, 0 } },
    [CURVE_ELASTIC]     = { "elastic",     1, { 2.0, 0, 0, 0 } }
};

// ─────────────────────────────────────────────────────────────────────────────
// Breakpoint: target value + time + curve type + curve params
// ─────────────────────────────────────────────────────────────────────────────
typedef struct _bp {
    double            value;
    double            time_ms;
    t_curve_type    curve;
    double            params[MAX_CURVE_PARAMS];
} t_bp;

// ─────────────────────────────────────────────────────────────────────────────
// Object structure
// ─────────────────────────────────────────────────────────────────────────────
typedef struct _void_interpol {
    t_object    ob;

    // breakpoints
    t_bp        *bps;
    long        num_bps;
    long        max_bps;
    long        current_bp;

    // state
    double        start_value;
    double        current_value;
    double        segment_elapsed;
    t_curve_type default_curve;
    double        default_params[MAX_CURVE_PARAMS];

    // timing
    void        *clock;
    double        grain;
    long        running;

    // outlets
    void        *outlet_main;
    void        *outlet_done;
} t_void_interpol;

// ─────────────────────────────────────────────────────────────────────────────
// Prototypes
// ─────────────────────────────────────────────────────────────────────────────
void    *void_interpol_new(t_symbol *s, long argc, t_atom *argv);
void    void_interpol_free(t_void_interpol *x);
void    void_interpol_assist(t_void_interpol *x, void *b, long m, long a, char *s);

void    void_interpol_float(t_void_interpol *x, double f);
void    void_interpol_int(t_void_interpol *x, long n);
void    void_interpol_list(t_void_interpol *x, t_symbol *s, long argc, t_atom *argv);
void    void_interpol_stop(t_void_interpol *x);
void    void_interpol_pause(t_void_interpol *x);
void    void_interpol_resume(t_void_interpol *x);
void    void_interpol_set(t_void_interpol *x, double f);
void    void_interpol_grain_msg(t_void_interpol *x, double f);
void    void_interpol_curve_msg(t_void_interpol *x, t_symbol *s, long argc, t_atom *argv);
void    void_interpol_anything(t_void_interpol *x, t_symbol *s, long argc, t_atom *argv);

void    void_interpol_tick(t_void_interpol *x);
double    void_interpol_apply_curve(double t, t_curve_type curve, const double *params);
int        void_interpol_lookup_curve(const char *name);
void    void_interpol_load_defaults(t_curve_type curve, double *params);

// ─────────────────────────────────────────────────────────────────────────────
// Globals
// ─────────────────────────────────────────────────────────────────────────────
static t_class *s_void_interpol_class = NULL;

// ─────────────────────────────────────────────────────────────────────────────
// Class registration
// ─────────────────────────────────────────────────────────────────────────────
void ext_main(void *r)
{
    t_class *c = class_new("void.interpol",
        (method)void_interpol_new,
        (method)void_interpol_free,
        (long)sizeof(t_void_interpol),
        0L, A_GIMME, 0);

    class_addmethod(c, (method)void_interpol_float,            "float",    A_FLOAT, 0);
    class_addmethod(c, (method)void_interpol_int,            "int",        A_LONG,  0);
    class_addmethod(c, (method)void_interpol_list,            "list",        A_GIMME, 0);
    class_addmethod(c, (method)void_interpol_anything,        "anything",    A_GIMME, 0);
    class_addmethod(c, (method)void_interpol_stop,            "stop",        0);
    class_addmethod(c, (method)void_interpol_pause,            "pause",    0);
    class_addmethod(c, (method)void_interpol_resume,        "resume",    0);
    class_addmethod(c, (method)void_interpol_set,            "set",        A_FLOAT, 0);
    class_addmethod(c, (method)void_interpol_grain_msg,        "grain",    A_FLOAT, 0);
    class_addmethod(c, (method)void_interpol_curve_msg,        "curve",    A_GIMME, 0);
    class_addmethod(c, (method)void_interpol_assist,        "assist",    A_CANT,  0);

    // Attributes
    CLASS_ATTR_DOUBLE(c, "grain", 0, t_void_interpol, grain);
    CLASS_ATTR_FILTER_MIN(c, "grain", 1.0);
    CLASS_ATTR_LABEL(c, "grain", 0, "Output grain (ms)");
    CLASS_ATTR_SAVE(c, "grain", 0);

    class_register(CLASS_BOX, c);
    s_void_interpol_class = c;
}

// ─────────────────────────────────────────────────────────────────────────────
// Curve name lookup
// ─────────────────────────────────────────────────────────────────────────────
int void_interpol_lookup_curve(const char *name)
{
    if (!name) return -1;
    for (int i = 0; i < CURVE_NUM_TYPES; i++) {
        if (strcmp(name, curve_specs[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void void_interpol_load_defaults(t_curve_type curve, double *params)
{
    if (curve < 0 || curve >= CURVE_NUM_TYPES) return;
    for (int i = 0; i < MAX_CURVE_PARAMS; i++) {
        params[i] = curve_specs[curve].default_params[i];
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Constructor / destructor
// ─────────────────────────────────────────────────────────────────────────────
void *void_interpol_new(t_symbol *s, long argc, t_atom *argv)
{
    t_void_interpol *x = (t_void_interpol *)object_alloc(s_void_interpol_class);
    if (!x) return NULL;

    // Outlets in reverse order (right first, left last)
    x->outlet_done   = bangout((t_object *)x);
    x->outlet_main   = floatout((t_object *)x);

    x->max_bps         = 64;
    x->bps             = (t_bp *)sysmem_newptr(sizeof(t_bp) * x->max_bps);
    x->num_bps         = 0;
    x->current_bp      = 0;
    x->start_value     = 0.0;
    x->current_value   = 0.0;
    x->segment_elapsed = 0.0;
    x->default_curve   = CURVE_LINEAR;
    void_interpol_load_defaults(CURVE_LINEAR, x->default_params);
    x->grain           = 20.0;
    x->running         = 0;

    x->clock = clock_new((t_object *)x, (method)void_interpol_tick);

    // Parse positional arguments BEFORE attribute parsing
    // arg 0: initial value (float)
    // arg 1: grain ms (float)
    // arg 2: default curve type (symbol)
    long pos = 0;
    if (argc > pos && (atom_gettype(argv+pos) == A_FLOAT || atom_gettype(argv+pos) == A_LONG)) {
        x->current_value = atom_getfloat(argv+pos);
        x->start_value   = x->current_value;
        pos++;
    }
    if (argc > pos && (atom_gettype(argv+pos) == A_FLOAT || atom_gettype(argv+pos) == A_LONG)) {
        double g = atom_getfloat(argv+pos);
        if (g >= 1.0) x->grain = g;
        pos++;
    }
    if (argc > pos && atom_gettype(argv+pos) == A_SYM) {
        t_symbol *sym = atom_getsym(argv+pos);
        if (sym && sym->s_name) {
            int c = void_interpol_lookup_curve(sym->s_name);
            if (c >= 0) {
                x->default_curve = (t_curve_type)c;
                void_interpol_load_defaults(x->default_curve, x->default_params);
            }
        }
        pos++;
    }

    // Then process attributes
    attr_args_process(x, argc, argv);

    return x;
}

void void_interpol_free(t_void_interpol *x)
{
    if (x->clock) {
        clock_unset(x->clock);
        object_free(x->clock);
    }
    if (x->bps) sysmem_freeptr(x->bps);
}

// ─────────────────────────────────────────────────────────────────────────────
// Assist
// ─────────────────────────────────────────────────────────────────────────────
void void_interpol_assist(t_void_interpol *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {
        snprintf_zero(s, 256,
            "float/list: target [time [curve [params...]]] | stop, pause, resume, set, grain, curve");
    } else {
        switch (a) {
            case 0: snprintf_zero(s, 256, "float: interpolated value"); break;
            case 1: snprintf_zero(s, 256, "bang: end of interpolation"); break;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Curve formulas
// ─────────────────────────────────────────────────────────────────────────────

// Cubic Bezier evaluator (CSS-style: P0=(0,0), P3=(1,1), control = (x1,y1) (x2,y2))
// We need to find y given t, where t is the linear progress.
// Standard approach: solve for the bezier parameter u from x = bezier_x(u),
// then evaluate y = bezier_y(u). Using Newton-Raphson with binary search fallback.
static double bezier_value_at_x(double x, double x1, double y1, double x2, double y2)
{
    if (x <= 0.0) return 0.0;
    if (x >= 1.0) return 1.0;

    // Find parameter u (in [0,1]) such that bezier_x(u) = x
    // bezier_x(u) = 3(1-u)^2 u x1 + 3(1-u) u^2 x2 + u^3
    // Use Newton-Raphson with binary search safety net
    double u = x;
    for (int i = 0; i < 8; i++) {
        double u1 = 1.0 - u;
        double bx = 3.0 * u1 * u1 * u * x1 + 3.0 * u1 * u * u * x2 + u * u * u;
        double dbx = 3.0 * u1 * u1 * x1 + 6.0 * u1 * u * (x2 - x1) + 3.0 * u * u * (1.0 - x2);
        if (fabs(dbx) < 1e-9) break;
        double u_new = u - (bx - x) / dbx;
        if (u_new < 0.0) u_new = 0.0;
        if (u_new > 1.0) u_new = 1.0;
        if (fabs(u_new - u) < 1e-7) { u = u_new; break; }
        u = u_new;
    }

    double u1 = 1.0 - u;
    return 3.0 * u1 * u1 * u * y1 + 3.0 * u1 * u * u * y2 + u * u * u;
}

// Quadratic Bezier: P0=(0,0), P2=(1,1), control=(cx,cy)
static double bezier2_value_at_x(double x, double cx, double cy)
{
    if (x <= 0.0) return 0.0;
    if (x >= 1.0) return 1.0;

    // Find u such that bezier2_x(u) = x:  (1-u)^2*0 + 2(1-u)u*cx + u^2 = x
    // = 2(1-u)u*cx + u^2 = x
    // Newton-Raphson
    double u = x;
    for (int i = 0; i < 8; i++) {
        double u1 = 1.0 - u;
        double bx = 2.0 * u1 * u * cx + u * u;
        double dbx = 2.0 * (1.0 - 2.0 * u) * cx + 2.0 * u;
        if (fabs(dbx) < 1e-9) break;
        double u_new = u - (bx - x) / dbx;
        if (u_new < 0.0) u_new = 0.0;
        if (u_new > 1.0) u_new = 1.0;
        if (fabs(u_new - u) < 1e-7) { u = u_new; break; }
        u = u_new;
    }

    double u1 = 1.0 - u;
    return 2.0 * u1 * u * cy + u * u;
}

// Apply curve: t in [0,1] → curved value in [0,1]
double void_interpol_apply_curve(double t, t_curve_type curve, const double *params)
{
    if (t <= 0.0) return 0.0;
    if (t >= 1.0) return 1.0;

    switch (curve) {
        case CURVE_LINEAR:
            return t;

        case CURVE_EXP: {
            // exp param k: (e^(kt) - 1) / (e^k - 1)
            double k = params[0];
            if (fabs(k) < 1e-6) return t;
            return (exp(k * t) - 1.0) / (exp(k) - 1.0);
        }

        case CURVE_LOG: {
            // log param k: log(1 + kt) / log(1 + k)
            double k = params[0];
            if (k < 1e-6) return t;
            return log(1.0 + k * t) / log(1.0 + k);
        }

        case CURVE_SINE:
            return sin(t * M_PI * 0.5);

        case CURVE_COSINE:
            return (1.0 - cos(t * M_PI)) * 0.5;

        case CURVE_POWER: {
            double n = params[0];
            if (n <= 0.0) return t;
            return pow(t, n);
        }

        case CURVE_SQUARE:
            return t * t;

        case CURVE_SQRT:
            return sqrt(t);

        case CURVE_EASE_IN: {
            double n = params[0];
            if (n <= 0.0) return t;
            return pow(t, n);
        }

        case CURVE_EASE_OUT: {
            double n = params[0];
            if (n <= 0.0) return t;
            return 1.0 - pow(1.0 - t, n);
        }

        case CURVE_EASE_IN_OUT: {
            double n = params[0];
            if (n <= 0.0) return t;
            if (t < 0.5) return pow(2.0 * t, n) * 0.5;
            else        return 1.0 - pow(2.0 * (1.0 - t), n) * 0.5;
        }

        case CURVE_BEZIER:
            return bezier_value_at_x(t, params[0], params[1], params[2], params[3]);

        case CURVE_BEZIER2:
            return bezier2_value_at_x(t, params[0], params[1]);

        case CURVE_SIGMOID: {
            // Logistic centered, normalized to [0,1] over [0,1]
            double k = params[0];
            if (k < 1e-3) return t;
            double a = 1.0 / (1.0 + exp(k * 0.5));         // value at t=0
            double b = 1.0 / (1.0 + exp(-k * 0.5));        // value at t=1
            double y = 1.0 / (1.0 + exp(-k * (t - 0.5)));
            return (y - a) / (b - a);
        }

        case CURVE_BEND: {
            // curve~ style: -1..1
            // 0 = linear, +1 = strong exp, -1 = strong log
            double p = params[0];
            if (fabs(p) < 1e-6) return t;
            double k = p * 6.0;  // scale factor
            if (k > 0.0) {
                return (exp(k * t) - 1.0) / (exp(k) - 1.0);
            } else {
                return log(1.0 + (-k) * t) / log(1.0 + (-k));
            }
        }

        case CURVE_SPRING: {
            // Damped oscillation, settles at 1
            // y = 1 - e^(-d*t) * cos(w*t) where w controls oscillations
            double oscillations = params[0];
            if (oscillations < 0.1) oscillations = 0.1;
            double w = oscillations * 2.0 * M_PI;
            double d = 6.0;  // damping
            return 1.0 - exp(-d * t) * cos(w * t);
        }

        case CURVE_BOUNCE: {
            // Simple multi-bounce: ascending bouncing approach to 1
            double bounces = params[0];
            if (bounces < 1.0) bounces = 1.0;
            double inv = 1.0 - t;
            // pow(inv, n) makes shorter bounces over time
            double phase = sin(inv * M_PI * bounces);
            return 1.0 - inv * fabs(phase);
        }

        case CURVE_ELASTIC: {
            // Elastic settling
            double oscillations = params[0];
            if (oscillations < 0.1) oscillations = 0.1;
            double w = oscillations * 2.0 * M_PI;
            double d = 4.0;
            // Ease-out elastic
            if (t >= 1.0) return 1.0;
            return 1.0 - pow(2.0, -10.0 * t) * cos((t - 0.075) * w);
        }

        default:
            return t;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Message handlers
// ─────────────────────────────────────────────────────────────────────────────
void void_interpol_grain_msg(t_void_interpol *x, double f)
{
    if (f >= 1.0) x->grain = f;
}

// curve <name> [params...] — set default curve and (optionally) its params
void void_interpol_curve_msg(t_void_interpol *x, t_symbol *s, long argc, t_atom *argv)
{
    if (argc < 1 || atom_gettype(argv) != A_SYM) {
        object_error((t_object *)x, "curve: expected symbol");
        return;
    }
    t_symbol *name = atom_getsym(argv);
    int c = void_interpol_lookup_curve(name->s_name);
    if (c < 0) {
        object_error((t_object *)x, "curve: unknown type '%s'", name->s_name);
        return;
    }
    x->default_curve = (t_curve_type)c;
    void_interpol_load_defaults(x->default_curve, x->default_params);

    // Override defaults with provided params, if any
    int n_expected = curve_specs[c].num_params;
    for (int i = 0; i < n_expected && (i + 1) < argc; i++) {
        t_atom *a = argv + i + 1;
        if (atom_gettype(a) == A_FLOAT || atom_gettype(a) == A_LONG) {
            x->default_params[i] = atom_getfloat(a);
        }
    }
}

void void_interpol_set(t_void_interpol *x, double f)
{
    clock_unset(x->clock);
    x->running         = 0;
    x->num_bps         = 0;
    x->current_bp      = 0;
    x->segment_elapsed = 0.0;
    x->current_value   = f;
    x->start_value     = f;
}

void void_interpol_stop(t_void_interpol *x)
{
    clock_unset(x->clock);
    x->running         = 0;
    x->num_bps         = 0;
    x->current_bp      = 0;
    x->segment_elapsed = 0.0;
}

void void_interpol_pause(t_void_interpol *x)
{
    if (x->running) {
        clock_unset(x->clock);
        x->running = 0;
    }
}

void void_interpol_resume(t_void_interpol *x)
{
    if (!x->running && x->num_bps > 0 && x->current_bp < x->num_bps) {
        x->running = 1;
        clock_fdelay(x->clock, x->grain);
    }
}

void void_interpol_int(t_void_interpol *x, long n)
{
    void_interpol_float(x, (double)n);
}

void void_interpol_float(t_void_interpol *x, double f)
{
    void_interpol_set(x, f);
    outlet_float(x->outlet_main, f);
}

// ─────────────────────────────────────────────────────────────────────────────
// List parser
//
// Format per breakpoint:
//   value time [curve_name [param1 [param2 [param3 [param4]]]]]
//
// Where curve_name's # of expected params is fixed by the curve_specs table.
// If params are missing, defaults are used.
// ─────────────────────────────────────────────────────────────────────────────
void void_interpol_list(t_void_interpol *x, t_symbol *s, long argc, t_atom *argv)
{
    if (argc < 1) return;

    // Single atom: jump
    if (argc == 1) {
        if (atom_gettype(argv) == A_FLOAT || atom_gettype(argv) == A_LONG) {
            void_interpol_float(x, atom_getfloat(argv));
        }
        return;
    }

    // Reset breakpoint queue
    clock_unset(x->clock);
    x->num_bps         = 0;
    x->current_bp      = 0;
    x->segment_elapsed = 0.0;
    x->start_value     = x->current_value;

    long i = 0;
    while (i < argc) {
        // Need at least value + time
        if (i + 1 >= argc) break;
        if (atom_gettype(argv+i) != A_FLOAT && atom_gettype(argv+i) != A_LONG) {
            i++; continue;
        }
        if (atom_gettype(argv+i+1) != A_FLOAT && atom_gettype(argv+i+1) != A_LONG) {
            i++; continue;
        }

        // Grow buffer if needed
        if (x->num_bps >= x->max_bps) {
            x->max_bps *= 2;
            t_bp *new_bps = (t_bp *)sysmem_resizeptr(x->bps, sizeof(t_bp) * x->max_bps);
            if (!new_bps) {
                object_error((t_object *)x, "memory allocation failed");
                return;
            }
            x->bps = new_bps;
        }

        t_bp *bp = &x->bps[x->num_bps];
        bp->value   = atom_getfloat(argv+i);
        bp->time_ms = atom_getfloat(argv+i+1);
        if (bp->time_ms < 0.0) bp->time_ms = 0.0;
        bp->curve   = x->default_curve;
        for (int p = 0; p < MAX_CURVE_PARAMS; p++) bp->params[p] = x->default_params[p];

        long advance = 2;

        // Optional curve symbol after time
        if (i + 2 < argc && atom_gettype(argv+i+2) == A_SYM) {
            t_symbol *sym = atom_getsym(argv+i+2);
            int c = void_interpol_lookup_curve(sym->s_name);
            if (c >= 0) {
                bp->curve = (t_curve_type)c;
                void_interpol_load_defaults(bp->curve, bp->params);
                advance = 3;

                // Read up to N params, where N = curve's expected count
                int n_expected = curve_specs[c].num_params;
                int n_read = 0;
                while (n_read < n_expected && (i + advance) < argc) {
                    t_atom *a = argv + i + advance;
                    int t = atom_gettype(a);
                    if (t != A_FLOAT && t != A_LONG) break;
                    bp->params[n_read] = atom_getfloat(a);
                    n_read++;
                    advance++;
                }
            }
            // If symbol was unknown, we ignore it (skip 1 atom and try next)
            else {
                object_warn((t_object *)x, "unknown curve '%s', using default", sym->s_name);
                advance = 3;
            }
        }

        x->num_bps++;
        i += advance;
    }

    if (x->num_bps == 0) return;

    x->running = 1;
    clock_fdelay(x->clock, x->grain);
}

// ─────────────────────────────────────────────────────────────────────────────
// Anything: "<curve_name> <list...>" applies that curve to the whole segment list
// ─────────────────────────────────────────────────────────────────────────────
void void_interpol_anything(t_void_interpol *x, t_symbol *s, long argc, t_atom *argv)
{
    int c = void_interpol_lookup_curve(s->s_name);
    if (c < 0) {
        object_error((t_object *)x, "unknown message: %s", s->s_name);
        return;
    }

    // Check if first atoms are this curve's params (floats up to N)
    // or directly the breakpoint list
    int n_expected = curve_specs[c].num_params;
    double override_params[MAX_CURVE_PARAMS];
    void_interpol_load_defaults((t_curve_type)c, override_params);

    int params_consumed = 0;

    // If the first 2 atoms after the curve symbol are floats AND we have at least
    // (n_expected + 2) floats following, we treat the first n_expected as params.
    // HEURISTIC: a breakpoint always has value+time = 2 floats minimum.
    // So if we have enough atoms for "params + (value time)", the first n_expected are params.
    if (n_expected > 0 && argc >= (n_expected + 2)) {
        int looks_like_params = 1;
        for (int i = 0; i < n_expected; i++) {
            int t = atom_gettype(argv + i);
            if (t != A_FLOAT && t != A_LONG) {
                looks_like_params = 0;
                break;
            }
        }
        // Also ensure we have a valid breakpoint after (value + time)
        if (looks_like_params) {
            int t1 = atom_gettype(argv + n_expected);
            int t2 = atom_gettype(argv + n_expected + 1);
            if ((t1 == A_FLOAT || t1 == A_LONG) && (t2 == A_FLOAT || t2 == A_LONG)) {
                // Use these as params
                for (int i = 0; i < n_expected; i++) {
                    override_params[i] = atom_getfloat(argv + i);
                }
                params_consumed = n_expected;
            }
        }
    }

    // Save current defaults, apply override
    t_curve_type saved_curve = x->default_curve;
    double saved_params[MAX_CURVE_PARAMS];
    for (int i = 0; i < MAX_CURVE_PARAMS; i++) saved_params[i] = x->default_params[i];

    x->default_curve = (t_curve_type)c;
    for (int i = 0; i < MAX_CURVE_PARAMS; i++) x->default_params[i] = override_params[i];

    void_interpol_list(x, gensym("list"), argc - params_consumed, argv + params_consumed);

    // Restore
    x->default_curve = saved_curve;
    for (int i = 0; i < MAX_CURVE_PARAMS; i++) x->default_params[i] = saved_params[i];
}

// ─────────────────────────────────────────────────────────────────────────────
// Clock tick
// ─────────────────────────────────────────────────────────────────────────────
void void_interpol_tick(t_void_interpol *x)
{
    if (!x->running || x->current_bp >= x->num_bps) {
        x->running = 0;
        return;
    }

    t_bp *bp = &x->bps[x->current_bp];

    x->segment_elapsed += x->grain;

    double t;
    if (bp->time_ms <= 0.0) {
        t = 1.0;
    } else {
        t = x->segment_elapsed / bp->time_ms;
        if (t > 1.0) t = 1.0;
    }

    double curved = void_interpol_apply_curve(t, bp->curve, bp->params);
    x->current_value = x->start_value + (bp->value - x->start_value) * curved;

    outlet_float(x->outlet_main, x->current_value);

    if (t >= 1.0) {
        x->current_value   = bp->value;
        x->start_value     = bp->value;
        x->segment_elapsed = 0.0;
        x->current_bp++;

        if (x->current_bp >= x->num_bps) {
            x->running = 0;
            outlet_bang(x->outlet_done);
            return;
        }
    }

    clock_fdelay(x->clock, x->grain);
}
