// gapgap_types.h
// Type definitions for gapgap text editor
// CS50x Final Project - Mischa Kaufmann

#ifndef GAPGAP_TYPES_H
#define GAPGAP_TYPES_H

#include <stdint.h>
#include <stdbool.h>

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

// ============================================================================
// LAYER 1: LINE (Gap Buffer for Characters)
// ============================================================================

typedef struct {
    char     text[MAX_LINE_LENGTH];
    uint8_t  gap_start;      // Index where gap begins
    uint8_t  gap_end;        // Index where gap ends (exclusive)
} Line;

// ============================================================================
// LAYER 2: LINE CHUNK (Gap Buffer for Line Pointers)
// ============================================================================

typedef struct {
    Line    *lines[LINES_PER_CHUNK];  // Array of Line pointers
    uint16_t gap_start;               // Gap start in lines array
    uint16_t gap_end;                 // Gap end in lines array
    uint16_t line_count;              // Actual lines (excluding gap)
} LineChunk;

// ============================================================================
// LAYER 3: LINE LOCATION (For O(1) Goto)
// ============================================================================

typedef struct {
    uint16_t chunk_idx;      // Which chunk (0..MAX_CHUNKS-1)
    uint16_t line_in_chunk;  // Position within chunk (0..LINES_PER_CHUNK-1)
} LineLocation;

// ============================================================================
// LAYER 4: EDITOR STATE
// ============================================================================

typedef struct {
    // Memory
    Arena        line_arena;              // Arena for Line allocations

    // Document structure
    LineChunk   *chunks[MAX_CHUNKS];      // Array of chunk pointers
    uint16_t     chunk_count;             // Number of active chunks

    // Line index (for O(1) goto)
    LineLocation *line_index;             // Flat array: line_num -> location
    uint32_t     total_lines;             // Total lines in document
    uint32_t     index_capacity;          // Allocated size of line_index

    // Index maintenance
    bool         index_dirty;             // Needs rebuild?
    uint32_t     dirty_from_line;         // Rebuild from this line onwards

    // Cursor position
    uint32_t     cursor_line;             // Current line (0-indexed)
    uint8_t      cursor_col;              // Current column (0-indexed)

    // Viewport (for ncurses)
    uint32_t     view_top_line;           // First visible line
    uint16_t     view_height;             // Terminal rows available
    uint16_t     view_width;              // Terminal cols available

    // File info
    char        *filepath;                // Current file path (NULL if new)
    bool         modified;                // Has unsaved changes?
} Editor;

// ============================================================================
// EDIT OPERATION (for future undo/redo)
// ============================================================================

typedef enum {
    OP_INSERT_CHAR,
    OP_DELETE_CHAR,
    OP_INSERT_LINE,
    OP_DELETE_LINE,
    OP_SPLIT_LINE,
    OP_JOIN_LINE
} OpType;

typedef struct {
    OpType   type;
    uint32_t line;
    uint8_t  col;
    char     ch;             // For char operations
    // Could extend with Line* for line operations
} EditOp;

#endif // GAPGAP_TYPES_H