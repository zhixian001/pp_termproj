#pragma once

#ifdef WIDTH
#undef WIDHT
#define WIDTH 400
#endif

#ifdef HEIGHT
#undef HEIGHT
#endif
#define HEIGHT 750

// 버블 이동 속도
#ifdef BUBBLE_SPEED_MULTIPLIER
#undef BUBBLE_SPEED_MULTIPLIER
#endif
#define BUBBLE_SPEED_MULTIPLIER 20

// 조명 효과
#ifdef LIGHTING_ON
#undef LIGHTING_ON
#endif
#define LIGHTING_ON 1
// 그 외 설정들

#ifdef GAME_ROW_COUNT
#undef GAME_ROW_COUNT
// #define GAME_ROW_COUNT 16
#endif
#define GAME_ROW_COUNT 12

#ifdef GAME_COLUMN_COUNT
#undef GAME_COLUMN_COUNT
#endif
#define GAME_COLUMN_COUNT 10

#ifdef DEFAULT_UPPER_COORD
#undef DEFAULT_UPPER_COORD
// #define DEFAULT_UPPER_COORD 375
#endif
#define DEFAULT_UPPER_COORD 275

#ifdef BUBBLE_RADIUS
#undef BUBBLE_RADIUS
#endif
#define BUBBLE_RADIUS 25.0

#ifdef BUBBLE_LAUNCH_X_COORD
#undef BUBBLE_LAUNCH_X_COORD
#endif
#define BUBBLE_LAUNCH_X_COORD 0

#ifdef BUBBLE_LAUNCH_Y_COORD
#undef BUBBLE_LAUNCH_Y_COORD
#endif
#define BUBBLE_LAUNCH_Y_COORD -150

#ifdef BUBBLE_NEXT_LAUNCH_X_COORD
#undef BUBBLE_NEXT_LAUNCH_X_COORD
#endif
#define BUBBLE_NEXT_LAUNCH_X_COORD -150

#ifdef BUBBLE_NEXT_LAUNCH_Y_COORD
#undef BUBBLE_NEXT_LAUNCH_Y_COORD
#endif
#define BUBBLE_NEXT_LAUNCH_Y_COORD -160

#ifdef BUBBLE_SPEED_MULTIPLIER
#undef BUBBLE_SPEED_MULTIPLIER
#endif
#define BUBBLE_SPEED_MULTIPLIER 20

#ifdef POINTS_PER_BUBBLE
#undef POINTS_PER_BUBBLE
#endif
#define POINTS_PER_BUBBLE 100

#ifdef BOARD_COLLISION_WIDTH
#undef BOARD_COLLISION_WIDTH
#endif
#define BOARD_COLLISION_WIDTH 175

#ifdef GAME_TIMEOUT
#undef GAME_TIMEOUT
#endif
#define GAME_TIMEOUT 5000.0

#ifdef TIME_BAR_WIDTH
#undef TIME_BAR_WIDTH
#endif
#define TIME_BAR_WIDTH 100.0