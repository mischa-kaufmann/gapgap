
// ============================================================================
// chunk_init
// ============================================================================

void chunk_init(LineChunk *chunk)
{

    chunk->gap_start = 0;
    chunk->gap_end = LINES_PER_CHUNK;
    chunk->line_count = 0;

    return;
};


// ============================================================================
// chunk_insert_line
// ============================================================================

void chunk_insert_line(LineChunk *chunk, Line *line)
{

    if (chunk->gap_start >= chunk->gap_end )
    {
        // goto next LineChunk
        printf("Chunk is Full");
        return;
    }
    
    chunk->lines[chunk->gap_start] = line;
    chunk->gap_start++;
    chunk->line_count++;

};



// ============================================================================
// chunk_delete_line
// ============================================================================

void chunk_delete_line(LineChunk *chunk, Line *line)
{

    if (chunk->gap_start > 0)
    {
        chunk->gap_start--;
        return;
    }
    
    return;
};


// ============================================================================
// chunk_move_gap
// ============================================================================

void chunk_move_gap(LineChunk *chunk, uint16_t num_lines, bool direct_down)
{


    if (direct_down == true)
    {

        memmove(&chunk->lines[chunk->gap_start], // dest
                &chunk->lines[chunk->gap_end], // src
                num_lines * sizeof(Line*)); // no. of bytes to shift

     
        chunk->gap_start += num_lines;
        chunk->gap_end += num_lines;

        return;
    } else {

        memmove(&chunk->lines[chunk->gap_end - num_lines], // dest
                &chunk->lines[chunk->gap_start - num_lines], // src
                num_lines * sizeof(Line*)); // no. of bytes to shift

     
        chunk->gap_start -= num_lines;
        chunk->gap_end -= num_lines;

        return;
    }

};


// ============================================================================
// chunk_get_line
// ============================================================================

Line* chunk_get_line(LineChunk *chunk, uint16_t pos)
{

    if (pos >= chunk->gap_start)
    {
        return chunk->lines[pos + line_chunk_gap_length(chunk)];
    
    } else {
      
        return chunk->lines[pos];
    }
      
};


// ============================================================================
// chunk_line_count
// ============================================================================

uint16_t chunk_line_count(LineChunk *chunk)
{
    return chunk->line_count;
};


// ============================================================================
// line_chunk_gap_length
// ============================================================================

uint16_t line_chunk_gap_length(LineChunk *chunk)
{
    return chunk->gap_end - chunk->gap_start;
};

