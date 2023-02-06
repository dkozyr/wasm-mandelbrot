#pragma once

#include "Types.h"

extern "C" {
    
void Init(uint8_t* ptr, int width, int height);
void Resize(int width, int height);
void Update();
void ZoomIn();
void ZoomOut();
void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();
void SetRandomPosition();

}
