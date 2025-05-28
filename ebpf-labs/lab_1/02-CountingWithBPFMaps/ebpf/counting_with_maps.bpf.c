#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <stddef.h>
#include <stdint.h>

/* This is the data record stored in the map */
struct datarec
{
   /* TODO 1: Add packet counter */
   uint64_t packet_counter;

   /* TODO 2: Add byte counter */
   uint64_t packet_bytes;
};

/* TODO 3: Define your map here */
struct
{
   __uint(type, BPF_MAP_TYPE_ARRAY);
   __type(key, int);
   __type(value, struct datarec);
   __uint(max_entries, 1);
} xdp_stats_map SEC(".maps");

SEC("xdp")
int xdp_prog_map(struct xdp_md *ctx)
{
   void *data_end = (void *)(long)ctx->data_end;
   void *data = (void *)(long)ctx->data;

   /* TODO 4: Lookup the map to get the datarec pointer
    * Remember to add the check if it is NULL
    * return XDP_ABORTED if it is NULL
    */
   struct datarec *rec;
   int key = 0;

   rec = bpf_map_lookup_elem(&xdp_stats_map, &key);
   if (!rec)
   {
      return XDP_ABORTED;
   }

   /* TODO 5: Update the packet counter */
   /* TODO 6: Update the byte counter */
   uint64_t bytes = data_end - data;

   __sync_fetch_and_add(&rec->packet_counter, 1);
   __sync_fetch_and_add(&rec->packet_bytes, bytes);

   return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";