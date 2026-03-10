#pragma once

/* Define this as you'd like *in your .c file*. */
struct cache;

void cache_access(struct cache *c, unsigned long mem_addr);
struct cache_stats {
	unsigned long num_cache_accesses, num_cache_misses;
};
struct cache_stats cache_statistics(struct cache *c);

struct cache *cache_allocate(unsigned long num_cache_lines, unsigned long num_sets);
void cache_free(struct cache *c);
