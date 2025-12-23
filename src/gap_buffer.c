

typedef struct {
    char     text[MAX_LINE_LENGTH];
    uint8_t  gap_start;      // Index where gap begins
    uint8_t  gap_end;        // Index where gap ends (exclusive)
} Line;
