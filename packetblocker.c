#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("hackerman");
MODULE_DESCRIPTION("Simulate the bad wifi of an intercity train "
                    "by dropping packets.");

static struct nf_hook_ops nfhook;
/*
static struct nf_hook_ops nfhook_in;
static struct nf_hook_ops nfhook_out
*/

unsigned int processed_packets;
unsigned int accepted_packets;
unsigned int dropped_packets;

unsigned int blocker_fn(void *priv,
                        struct sk_buff *skb,
                        const struct nf_hook_state *state) {
    processed_packets++;
    if (processed_packets == 2147483646) {
        // Precautionary measure.
        processed_packets = 0;
    }
    if (processed_packets % 13 == 0) { 
        printk(KERN_INFO "Dropped packet >:)\n");
        dropped_packets++;
        return NF_DROP;
    }
    printk(KERN_INFO "Packet accepted :-)\n");
    accepted_packets++;
    return NF_ACCEPT;
}

static int init_packet_blocking(void) {

    nfhook.hook = blocker_fn;
    nfhook.hooknum = NF_INET_PRE_ROUTING; // Inbound & outbound packets
    nfhook.pf = PF_INET;
    nfhook.priority = NF_IP_PRI_FIRST;
    
    nf_register_hook(&nfhook);

    /**
     * Define specific methods for inbound and outbound
     * packets. Add IP rules or something.
    nfhook_in.hook = blocker_fn;
    nfhook_out.hook = blocker_fn;

    nfhook_in.hooknum = NF_INET_LOCAL_IN;
    nfhook_out.hooknum = NF_INET_LOCAL_OUT;

    nfhook_in.pf = PF_INET;
    nfhook_out.pf = PF_INET;

    nfhook_in.priority = NF_IP_PRI_FIRST;
    nfhook_out.priority = NF_IP_PRI_FIRST;

    nf_register_hook(&nfhook_in);
    nf_register_hook(&nfhook_out);
     */
    return 0;
}


static int __init loader(void) {
    processed_packets = 0;
    accepted_packets = 0;
    dropped_packets = 0;

    init_packet_blocking();

    printk(KERN_INFO "Arbitrary packet dropping enabled.\n");
    return 0;
}

static void __exit unloader(void) {
    nf_unregister_hook(&nfhook);
    /*
    nf_unregister_hook(&nfhook_in);
    nf_unregister_hook(&nfhook_out);
    */
    printk(KERN_INFO "Module removed\n");
    printk(KERN_INFO "Total accepted packets: %d\n",
            accepted_packets);
    printk(KERN_INFO "Total dropped packets: %d\n",
            dropped_packets);
}

module_init(loader);
module_exit(unloader);
