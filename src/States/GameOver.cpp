#include "GameOver.hpp"

void GameOver::Update() {
    if (this->finished) this->transparency += 4;
    if (this->transparency >= 255) this->done = true;
    if (this->start) {
        PlaySound(SoundManager::gameOver);
        this->start = false;
    }
}

void GameOver::Draw() {
    for (Enemy* e : this->enemies) e->draw();
    for (Block* b : this->layout) b->draw();

    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, 100});
    DrawText("Game Over", titlePos, Height * 0.1, 128, (Color){255, 255, 255, 255});
    titlePos = std::min(2 * titlePos + 1, Width / 2 - (65 * 4.5));

    std::string levelText = "Level Reached: " + std::to_string(this->levelReached); 
    DrawText(levelText.c_str(), Width / 2 - (16 * 5.5), Height * 0.26f, 16, (Color){255, 255, 255, 255});
    DrawText("Press Enter to Go Back to Menu", Width / 2 - (16 * 9), Height * 0.3f, 16, (Color){255, 255, 255, 255});

    for (int i = 0; i < 9; i++) {
        DrawTexturePro(icons, (Rectangle){0, (float)i * 16, 36, 16},
                       (Rectangle){(float)(Width * 0.475f - 22.5), Height * 0.4f - 5 + (20 * i), 45, 20}, (Vector2){0, 0}, 0,
                       (Color){255, 255, 255, 255});

        DrawText("0", Width * 0.525f, Height * 0.4f - 5 + (21 * i), 16, WHITE);
    }

    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, (unsigned char) transparency});
}

void GameOver::KeyPressed(int key) {
    if (key == KEY_ENTER) {
        this->finished = true;
    }
}

void GameOver::KeyReleased() {

}

void GameOver::MousePressed(int x, int y, int button) {

}

void GameOver::Reset() {

}