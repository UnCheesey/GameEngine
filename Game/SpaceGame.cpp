#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Assets.h"

using namespace nu;

bool SpaceGame::Initialize() {
    Game::Initialize();

    Engine::Get().GetAudio().AddSound("background", "Sounds/space_background.mp3", true);
    Engine::Get().GetAudio().AddSound("laser", "Sounds/laser.wav");
    Engine::Get().GetAudio().PlaySound("background");

    m_scene = new Scene();
    m_scene->SetGame(this);

    m_titleFont = new Font();
    m_titleFont->Load("Fonts/Blaster.ttf", 64);

    m_titleText = new Text(m_titleFont);
    
    m_gameFont = new Font();
    m_gameFont->Load("Fonts/Blaster.ttf", 32);

    m_scoreText = new Text(m_gameFont);
    m_livesText = new Text(m_gameFont);
    m_weaponText = new Text(m_gameFont);

    m_gameOverFont = new Font();
    m_gameOverFont->Load("Fonts/Blaster.ttf", 64);

    m_gameOverText = new Text(m_gameOverFont);

    m_playFont = new Font();
    m_playFont->Load("Fonts/Blaster.ttf", 32);

    m_playText = new Text(m_gameOverFont);
    m_playText->Create(Engine::Get().GetRenderer(), "Press SPACE to play", Color{ 1.0f, 1.0f, 1.0f });


    return true;
}

void SpaceGame::Update(float dt) {

    

    switch (m_gameState)
    {
    case GameState::Title:
        /*if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }*/
        m_gameState = GameState::StartGame;
        break;
    case GameState::StartGame:
        m_score = 0;
        m_lives = 1;
        m_spawnTime = 5.0f;
        m_pickUpTimer = 3.0f;
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        m_scene->RemoveAllActors();
        SpawnPlayer();
        m_gameState = GameState::Game;
        break;
    case GameState::Game:
        m_spawnTimer -= dt;
        m_pickUpTimer -= dt;
        if (m_spawnTimer <= 0.0f) {
            m_spawnTimer = m_spawnTime;
            SpawnEnemy();
        }

        if (m_pickUpTimer <= 0.0f) {
            SpawnPickup();
            m_pickUpTimer = RandomFloat(8.0f, 15.0f);
        }

        if(m_scene->GetActorByName<Player>("Player") == nullptr) {
            OnPlayerDead();
		}

        break;
    case GameState::GameOver:
        m_scene->RemoveAllActors();
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }

        break;
    default:
        break;
    }

    Game::Update(dt);
}

void SpaceGame::Draw(Renderer& renderer) {

    switch (m_gameState) {

    case SpaceGame::GameState::Title:
        m_titleText->Create(Engine::Get().GetRenderer(), "Game Engine", Color{ 1.0f, 1.0f, 1.0f });
        m_titleText->Draw(renderer, (renderer.GetWidth() - m_titleText->GetTextWidth()) / 2.0f, (renderer.GetHeight() - m_titleText->GetTextHeight()) / 2.0f);
        m_playText->Draw(renderer, (renderer.GetWidth() - m_playText->GetTextWidth()) / 2.0f, (renderer.GetHeight() / 2.0f) + m_titleText->GetTextHeight());
        break;
    case SpaceGame::GameState::StartGame:
        break;
    case SpaceGame::GameState::StartLevel:
        break;
    case SpaceGame::GameState::Game:
        m_scoreText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, 30, 30);

        m_livesText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        m_livesText->Draw(renderer, renderer.GetWidth() - m_livesText->GetTextWidth() - 30.0f, 30.0f);

        m_weaponText->Create(renderer, "Weapon: " + m_player->WeaponToString(), { 1.0f, 1.0f, 1.0f });
        m_weaponText->Draw(renderer, 30, m_scoreText->GetTextHeight() + 30);
        break;
    case SpaceGame::GameState::GameOver:
        m_gameOverText->Create(Engine::Get().GetRenderer(), "Game Over", Color{ 1.0f, 1.0f, 1.0f });
        m_gameOverText->Draw(renderer, (renderer.GetWidth() - m_gameOverText->GetTextWidth()) / 2.0f, (renderer.GetHeight() - m_gameOverText->GetTextHeight()) / 2.0f);
        m_playText->Draw(renderer, (renderer.GetWidth() - m_playText->GetTextWidth()) / 2.0f, (renderer.GetHeight() / 2.0f) + m_gameOverText->GetTextHeight());
        break;
    default:
        break;
    }

    Engine::Get().GetParticleSystem().Draw(Engine::Get().GetRenderer());
    m_scene->Draw(renderer);
}

 void SpaceGame::SpawnPickup() {
        nu::ActorDesc itemDesc;
        itemDesc.name = "Pickup";
        itemDesc.tag = "Pickup";
        itemDesc.model = assets::playerModel;
        itemDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 0.0f, 10.0f };
        itemDesc.lifespan = 6.0f;

        Pickup* pickup = new Pickup(itemDesc);
        m_scene->AddActor(std::move(std::make_unique<Pickup>(itemDesc)));
 }

void SpaceGame::OnPlayerDead() {
    m_lives--;
    m_gameState = (m_lives == 0) ? GameState::GameOver : GameState::StartLevel;
}

void SpaceGame::SpawnPlayer() {
    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.tag = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.damping = 3.0f;
    playerDesc.speed = 2500.0f;

    std::unique_ptr<Player> m_player = std::make_unique<Player>(playerDesc);
    m_scene->AddActor(std::move(m_player));
}

void SpaceGame::SpawnEnemy() {
    EnemyDesc enemyDesc;
    enemyDesc.name = "Enemy";
    enemyDesc.tag = "Enemy";
    enemyDesc.model = assets::enemyModel;
    enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
    enemyDesc.damping = 3.0f;
    enemyDesc.speed = RandomFloat(1000.0f, 1500.0f);

    m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}
