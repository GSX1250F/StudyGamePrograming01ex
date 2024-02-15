// Game.cppがやること
// 0.コンストラクタ
//		mWindow:ゲーム画面　　mRenderer:レンダラー		mIsRunning:ループの判断		mUpdatingActors:アクター更新中の判断
// 1.Initialize: SDL関係、Actor読み込み、TicksCount開始
//		1.1LoadData : Actorのインスタンス・位置初期設定
// 2.RunLoop: 入力受付→更新→出力　のループ
//		2.1 ProcessInput: SDLイベントループ、入力情報を全アクターのProcessInputに与える
//		2.2 UpdateGame: FPSの調整、deltatTimeを全アクターのUpdateに与える、死んだアクターの削除
//		2.3 GenerateOutput: レンダラーのベースカラー設定・クリア、全ての描画対象を描画、描画バッファの交換
//			描画対象は、スプライトの場合は全スプライトクラスのDrawにレンダラー情報を与える
// 3.Shutdown: メモリ解放

// AddActor ※AddShip・AddBallなどはActorの子クラスのAddもある：mActorsかmPendingActorsの配列にActorを追加
// Actorのコンストラクタから引数を通して呼び出し

// AddSprite: スプライト毎に設定されているDrawOrderを取得し、mSprites配列に描画順でスプライトを追加
// ActorのコンストラクタからSpriteComponentを引数を通して呼び出し

// SDL_Texture* Game::GetTexture :スプライトに使用する画像ファイルをテクスチャにするための関数
// Actor側から呼び出すこともあるし、背景用はこのGame.cppで呼び出すこともある。


#include "Game.h"
#include "SDL_image.h"
//#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
//#include "Random.h"

Game::Game()	:mWindow(nullptr),mRenderer(nullptr),mIsRunning(true),mUpdatingActors(false){}

bool Game::Initialize()
{
	// SDL初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("SDLを初期化できません: %s", SDL_GetError());
		return false;
	}
	// SDLウィンドウを作成
	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter1 ex)", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("ウィンドウの作成に失敗しました: %s", SDL_GetError());
		return false;
	}
	// SDLレンダラーを作成
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("レンダラーの作成に失敗しました: %s", SDL_GetError());
		return false;
	}
	// SDL_imageを初期化
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("SDL_imageを初期化できません: %s", SDL_GetError());
		return false;
	}

	//Random::Init();

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;

}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	// キューにイベントがあれば繰り返す
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	// デルタタイムの計算
	// 前のフレームから 16ms 経つまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// デルタタイムを最大値で制限する
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// すべてのアクターを更新
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 待ちアクターをmActorsに移動
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 死んだアクターを一時配列に追加
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// 死んだアクターを削除
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// すべてのスプライトコンポーネントを描画
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	//プレイヤーの宇宙船を作成
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.0f, 384.0f));
	mShip->SetRotation(Math::PiOver2);


	// 小惑星を生成
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}

}

void Game::UnloadData()
{
	// アクターを消去
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// テクスチャを消去
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// ファイルからロード
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}

		// サーフェイスからテクスチャを作成
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
			return nullptr;
		}

		mTextures.emplace(filename.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}