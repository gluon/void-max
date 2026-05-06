#include "ext.h"
#include "ext_obex.h"

#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>

// ------------------------------------------------------------
// Object struct
// ------------------------------------------------------------

typedef struct _void_net_localip {
    t_object ob;
    void* out_ip;
    void* out_if;
} t_void_net_localip;

static t_class* void_net_localip_class = NULL;

// ------------------------------------------------------------
// Utility : get local IPv4 (macOS)
// ------------------------------------------------------------

static int get_local_ipv4(char* ip_out, size_t ip_len,
                          char* if_out, size_t if_len)
{
    struct ifaddrs* ifaddr = NULL;
    struct ifaddrs* ifa = NULL;

    if (getifaddrs(&ifaddr) != 0)
        return 0;

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr)
            continue;

        // IPv4 only
        if (ifa->ifa_addr->sa_family != AF_INET)
            continue;

        // interface must be UP
        if (!(ifa->ifa_flags & IFF_UP))
            continue;

        // skip loopback
        if (ifa->ifa_flags & IFF_LOOPBACK)
            continue;

        struct sockaddr_in* sa = (struct sockaddr_in*)ifa->ifa_addr;

        const char* ip = inet_ntoa(sa->sin_addr);
        if (!ip)
            continue;

        strncpy(ip_out, ip, ip_len);
        strncpy(if_out, ifa->ifa_name, if_len);

        freeifaddrs(ifaddr);
        return 1;
    }

    freeifaddrs(ifaddr);
    return 0;
}

// ------------------------------------------------------------
// Methods
// ------------------------------------------------------------

void void_net_localip_bang(t_void_net_localip* x)
{
    char ip[64] = {0};
    char iface[64] = {0};

    if (get_local_ipv4(ip, sizeof(ip), iface, sizeof(iface))) {
        outlet_anything(x->out_if, gensym(iface), 0, NULL);
        outlet_anything(x->out_ip, gensym(ip), 0, NULL);
    } else {
        outlet_anything(x->out_if, gensym("none"), 0, NULL);
        outlet_anything(x->out_ip, gensym("0.0.0.0"), 0, NULL);
    }
}

// ------------------------------------------------------------
// Assist
// ------------------------------------------------------------

void void_net_localip_assist(t_void_net_localip* x,
                             void* b,
                             long m,
                             long a,
                             char* s)
{
    if (m == ASSIST_INLET) {
        snprintf(s, 256, "(bang) output the local IPv4 address");
    } else {
        if (a == 0)
            snprintf(s, 256, "(symbol) local IPv4 address");
        else
            snprintf(s, 256, "(symbol) network interface name");
    }
}

// ------------------------------------------------------------
// Constructor / Destructor
// ------------------------------------------------------------

void* void_net_localip_new(void)
{
    t_void_net_localip* x =
        (t_void_net_localip*)object_alloc(void_net_localip_class);

    x->out_if = outlet_new((t_object*)x, NULL);
    x->out_ip = outlet_new((t_object*)x, NULL);

    return x;
}

void void_net_localip_free(t_void_net_localip* x)
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
        "void.net.localip",
        (method)void_net_localip_new,
        (method)void_net_localip_free,
        sizeof(t_void_net_localip),
        0L,
        0
    );

    class_addmethod(c, (method)void_net_localip_bang, "bang", 0);
    class_addmethod(c, (method)void_net_localip_assist, "assist", A_CANT, 0);

    class_register(CLASS_BOX, c);
    void_net_localip_class = c;
}
