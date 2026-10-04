#include "events.h"
#include <string.h>

#define _MOUSE_BUTTONS 1024


bool* events::_keys;
uint* events::_frames;
uint events::_current = 0;
float events::deltaX = 0.0f;
float events::deltaY = 0.0f;
float events::x = 0.0f;
float events::y = 0.0f;
bool events::_cursor_locked = false;
bool events::_cursor_started = false;







