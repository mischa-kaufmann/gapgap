
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





void *arena_alloc(Arena *arena, uint32_t size)
{
    if ( arena->curr_offset + size <= arena->capacity)
    {
        // find the adress of the current offset in the arena
        void *pointer = arena->buf + arena->curr_offset;
        
        // update the new previous offset
        arena->prev_offset = arena->curr_offset;

        // Update the new current offset with adding the size of the new data
        arena->curr_offset += size;
        
        // set the new space to zero, cause i can.
        memset(pointer, 0, size);

        return pointer;
    }

    // Error handling
    printf("Arena is full");
    return NULL; // Arena is full
};




void arena_free_all(Arena *arena)
{
    arena->curr_offset = 0;
	arena->prev_offset = 0;
};


void arena_destroy(Arena *arena)
{
    free(arena->buf);

    arena->buf = NULL;
    arena->capacity = 0;
    arena->curr_offset = 0;
    arena->prev_offset = 0;
    
    return;
};