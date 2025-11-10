#ifndef EVENTS_H
# define EVENTS_H

// Forward declaration
typedef struct s_data	t_data;

/* ========== EVENT HANDLER FUNCTIONS ========== */
// Mouse event handlers
int		mouse_press(int button, int x, int y, t_data *data);
int		mouse_release(int button, int x, int y, t_data *data);
int		mouse_move(int x, int y, t_data *data);

// Keyboard event handlers
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

// Loop hook for continuous updates
int		loop_hook(t_data *data);
void	process_movement(t_data *data);

#endif
