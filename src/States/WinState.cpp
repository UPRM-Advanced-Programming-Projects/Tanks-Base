#include "WinState.hpp"

void Win::Update() {
    if (!IsSoundPlaying(SoundManager::winTheme)) PlaySound(SoundManager::winTheme);
    if (this->finished) this->transparency += 4;
    if (this->transparency >= 255) this->done = true;
}

void Win::Draw() {
    for (Block* b : this->layout) b->draw();
    this->player->draw();

    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, 100});
    DrawText("You Win!", titlePos, Height * 0.1, 128, (Color){255, 255, 255, 255});
    titlePos = std::min(2 * titlePos + 1, Width / 2 - (65 * 4));

    DrawText("All Levels Completed!", Width / 2 - (16 * 5.5), Height * 0.26f, 16, (Color){255, 255, 255, 255});
    DrawText("Press Enter to Go Back to Menu", Width / 2 - (16 * 9), Height * 0.3f, 16, (Color){255, 255, 255, 255});

    for (int i = 0; i < 9; i++) {
        DrawTexturePro(icons, (Rectangle){0, (float)i * 16, 36, 16},
                       (Rectangle){(float)(Width * 0.475f - 22.5), Height * 0.4f - 5 + (20 * i), 45, 20}, (Vector2){0, 0}, 0,
                       (Color){255, 255, 255, 255});

        DrawText("0", Width * 0.525f, Height * 0.4f - 5 + (21 * i), 16, WHITE);
    }

    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, (unsigned char) this->transparency});
}

void Win::KeyPressed(int key) {
    if (key == KEY_ENTER) {
        this->finished = true;
    }
}

void Win::KeyReleased() {

}

void Win::MousePressed(int x, int y, int button) {

}

void Win::Reset() {

}