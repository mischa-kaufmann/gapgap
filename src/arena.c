	
   
// ============================================================================
// STANDARD LIBRARY
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

   
// Line Configuration
#define MAX_LINE_LENGTH      128      // 2^7, cache-friendly
#define INITIAL_GAP_SIZE     MAX_LINE_LENGTH

// Chunk Configuration
#define LINES_PER_CHUNK      4096     // 2^12, O(4096) worst case for insert/delete
#define MAX_CHUNKS           1024     // Max ~4M lines (1024 * 4096)

// Arena Configuration
#define ARENA_INITIAL_SIZE   (1024 * 1024 * 64)  // 64 MB initial
#define ARENA_ALIGNMENT      16


// ============================================================================
// ARENA ALLOCATOR
// Based on: https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/
// ============================================================================

typedef struct {
    uint8_t  *buf;           // Backing memory
    uint32_t  capacity;      // Total size in bytes
    uint32_t  curr_offset;   // Current allocation position
    uint32_t  prev_offset;   // Previous allocation (for limited rewind)
} Arena;



    
bool arena_init(Arena *arena, uint32_t capacity)
{
    
    // (*arena).buf == arena->buf

    arena->buf = malloc(capacity);

    if (arena->buf == NULL)
    {
        printf("Memory not allocated.\n");
        return false;
    } 

    // Update the struct with the actual capacity
    arena->capacity = capacity;

    // Setting zero for init reasons
    arena->curr_offset = 0;
    arena->prev_offset = 0;      
        
    printf("Memory successfully allocated using malloc.\n");
    return true;
};







arena_alloc




arena_free_all
