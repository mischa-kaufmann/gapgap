
// ============================================================================
// line_init
// ============================================================================

void line_init(Line *line) 
{
    line->gap_start = 0;
    line->gap_end = MAX_LINE_LENGTH;   
};

// ============================================================================
// line_insert_char
// ============================================================================

void line_insert_char(Line *line, char c)
{
    if (line->gap_start >= line->gap_end)
    {
        // new_line or something like this in future
        return;        
    }

    line->text[line->gap_start] = c;
    line->gap_start++;
};


// ============================================================================
// line_delete_char_back
// ============================================================================

void line_delete_char_back(Line *line)
{
    if (line->gap_start > 0)
    {
        line->gap_start--;
        return;
    }

    return;
};


// ============================================================================
// line_delete_char_forward
// ============================================================================

void line_delete_char_forward(Line *line)
{
    
    if (line->gap_end < MAX_LINE_LENGTH)
    {
        line->gap_end++;
        return;
    
    }
    return;
};



// ============================================================================
// line_move_gap
// ============================================================================

void line_move_gap(Line *line, uint8_t num_chars, bool direct_fore) 
{

 /*
 void *memmove()
---------------
memmove input =
void *dest, -> ptr of the location i want to move the data
const void* src, -> the location / adress of source 
uint8_t n; how many Bytes. i cap this to 8 Bytes cause the line are short. 
 */ 



   
    if (direct_fore == true)
    {
         // foreward shift
        memmove(&line->text[line->gap_start],
        &line->text[line->gap_end],
        
        num_chars);
        line->gap_start += num_chars;
        line->gap_end += num_chars;

    } else {

       // backsward shift
        memmove(&line->text[line->gap_end - num_chars],
        &line->text[line->gap_start - num_chars],
        num_chars);
        
        line->gap_start -= num_chars;
        line->gap_end -= num_chars;
    }

};

// ============================================================================
// gap_length
// ============================================================================

uint8_t gap_length(Line *line)
{
    return line->gap_end - line->gap_start;

};

// ============================================================================
// line_length
// ============================================================================

uint8_t line_length(Line *line)
{
    uint8_t line_length = MAX_LINE_LENGTH - gap_lenght(line);

    return line_length;
};


// ============================================================================
// line_get_char
// ============================================================================

char line_get_char(Line *line, uint16_t pos)
{
    char c; // var for return the asked char

    if (pos < line->gap_start)
    {
        c = line->text[pos];
        return c;

    } else if (pos >= line->gap_start)
    {
        c = line->text[pos + gap_length(&line)];
        return c;
    }
     
};