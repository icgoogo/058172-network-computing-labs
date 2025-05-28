#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int xdp_prog_simple(struct xdp_md *ctx) {
   //TODO: Implement the BPF program
   bpf_printk("Hello world from ebpf");
   return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";