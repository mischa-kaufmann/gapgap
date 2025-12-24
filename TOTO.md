# TODO



## Functions to Implement:
- arena.c
	- arena_init
	- arena_alloc
	- arena_free_all
- gapbuffer.c
  -   line_init
  -   line_insert_char
  -   line_delete_char_back
  -   line_delete_char_forward
  -   line_move_gap
  -   line_length
  -   line_get_char

- editor.c
	- editor_init
	- editor_cleanup
	- editor_new_document
	- editor_move_*
	- editor_goto_line
	- editor_insert_*
	- editor_delete_*
- io.c
	- editor_load_file
	- editor_save_file
- ui.c
	- ui_init
	- ui_cleanup
	- ui_draw
	- ui_insert_mode
	- ui_goto_line
	- ui_save_as
	- ui_show_help