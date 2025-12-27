// ============================================================================
// index_init
// ============================================================================

bool index_init(Editor *editor, uint32_t capacity)
{
    // Allocate Memory for an Array of Pointers
    // Mapps line_number => LineLocation
    // For  fast O(1) Lookup for goto(Line)

    editor->line_index = malloc(capacity * sizeof(LineLocation));

    if (editor->line_index == NULL)
    {
        return false;
    }
    
    editor->total_lines = 0;
    editor->index_capacity = capacity;

    return true;

};



// ============================================================================
// index_rebuild
// ============================================================================

void index_rebuild(Editor *editor)
{
    uint64_t total_lines_count = 0;
   
    for (uint16_t i = 0; i < editor->chunk_count ; i++)
    {     
        for (uint16_t j = 0; j < editor->chunks[i]->line_count; j++)
        {
            editor->line_index[total_lines_count].line_in_chunk = j;
            editor->line_index[total_lines_count].chunk_idx = i;

            total_lines_count++;
        }   
    };
    
    editor->total_lines = total_lines_count;
    
    return;
};


// ============================================================================
// index_lookup
// ============================================================================

LineLocation index_lookup(Editor *editor, uint32_t line_num)
{
    if (line_num >= editor->total_lines)
    {
        printf("asked line number is to big. Now you are at the end of the file");

        return editor->line_index[editor->total_lines -1];
        
    }
    
    return editor->line_index[line_num];
};



// ============================================================================
// index_destroy
// ============================================================================

void index_destroy(Editor *editor)
{
    free(editor->line_index);
    
    editor->line_index = NULL;

    return;
};
