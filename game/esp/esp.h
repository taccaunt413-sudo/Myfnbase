#pragma once
#include <cstdint>
#include "../../render/imgui/imgui.h"

struct Vector2;
struct Vector3;

void draw_filled_rect(int x, int y, int w, int h, const ImColor color);
void draw_cornered_box(int x, int y, int w, int h);
void Skeleton(uintptr_t mesh, float distance);
void Box(int X, int Y, int W, int H);
void draw_line(Vector2 target);
void draw_distance(Vector2 location, float distance);
