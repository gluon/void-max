#include "ext.h"
#include "ext_obex.h"

#include <unistd.h>

// ------------------------------------------------------------
// Object struct
// ------------------------------------------------------------

typedef struct _void_net_hostname {
    t_object ob;
    void* out;
} t_void_net_hostname;

static t_class* void_net_hostname_class = NULL;

// ------------------------------------------------------------
// Method : bang
// ------------------------------------------------------------

void void_net_hostname_bang(t_void_net_hostname* x)
{
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        hostname[sizeof(hostname) - 1] = '\0'; // safety
        outlet_anything(x->out, gensym(hostname), 0, NULL);
    } else {
        outlet_anything(x->out, gensym("unknown"), 0, NULL);
    }
}

// ------------------------------------------------------------
// Assist
// ------------------------------------------------------------

void void_net_hostname_assist(t_void_net_hostname* x,
                              void* b,
                              long m,
                              long a,
                              char* s)
{
    if (m == ASSIST_INLET) {
        snprintf(s, 256, "(bang) output the system hostname");
    } else {
        snprintf(s, 256, "(symbol) hostname");
    }
}

// ------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------

void* void_net_hostname_new(void)
{
    t_void_net_hostname* x =
        (t_void_net_hostname*)object_alloc(void_net_hostname_class);

    x->out = outlet_new((t_object*)x, NULL);

    return x;
}

void void_net_hostname_free(t_void_net_hostname* x)
{
    // nothing to free
}

// ------------------------------------------------------------
// Main
// ------------------------------------------------------------

void ext_main(void* r)
{
    t_class* c;

    c = class_new(
        "void.net.hostname",
        (method)void_net_hostname_new,
        (method)void_net_hostname_free,
        sizeof(t_void_net_hostname),
        0L,
        0
    );

    class_addmethod(c, (method)void_net_hostname_bang, "bang", 0);
    class_addmethod(c, (method)void_net_hostname_assist, "assist", A_CANT, 0);

    class_register(CLASS_BOX, c);
    void_net_hostname_class = c;
}
