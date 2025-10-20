#include "Transition.hpp"

void Transition::Update() {
    if (this->finished) this->transparency += 4;
    if (this->transparency >= 255) this->done = true;
    if (this->start) {
        PlaySound(SoundManager::levelComplete);
        this->start = false;
    }
}

void Transition::Draw() {
    for (Block* b : this->layout) b->draw();
    this->player->draw();

    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, 100});
    DrawText("Level Completed!", this->titlePos, Height * 0.1, 100, (Color){255, 255, 255, 255});
    this->titlePos = std::min(2 * this->titlePos + 1, Width / 2 - (65 * 6));

    DrawText("Press Enter to Continue", Width / 2 - (16 * 6), Height * 0.26f, 16, (Color){255, 255, 255, 255});
    DrawText("Results:", Width / 2 - (16 * 2.5), Height * 0.35f, 16, (Color){255, 255, 255, 255});

    for (int i = 0; i < 9; i++) {
        DrawTexturePro(ImageManager::icons, (Rectangle){0, (float)i * 16, 36, 16},
                       (Rectangle){(float)(Width * 0.475f - 22.5), Height * 0.4f - 5 + (20 * i), 45, 20}, (Vector2){0, 0}, 0,
                       (Color){255, 255, 255, 255});

        DrawText("0", Width * 0.525f, Height * 0.4f - 5 + (21 * i), 16, WHITE);
    }

    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, (unsigned char) this->transparency});
}

void Transition::KeyPressed(int key) {
    if (key == KEY_ENTER) {
        this->finished = true;
    }
}

void Transition::KeyReleased() {

}

void Transition::MousePressed(int x, int y, int button) {

}

void Transition::Reset() {

}