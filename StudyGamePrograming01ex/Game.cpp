// Game.cpp����邱��
// 0.�R���X�g���N�^
//		mWindow:�Q�[����ʁ@�@mRenderer:�����_���[		mIsRunning:���[�v�̔��f		mUpdatingActors:�A�N�^�[�X�V���̔��f
// 1.Initialize: SDL�֌W�AActor�ǂݍ��݁ATicksCount�J�n
//		1.1LoadData : Actor�̃C���X�^���X�E�ʒu�����ݒ�
// 2.RunLoop: ���͎�t���X�V���o�́@�̃��[�v
//		2.1 ProcessInput: SDL�C�x���g���[�v�A���͏���S�A�N�^�[��ProcessInput�ɗ^����
//		2.2 UpdateGame: FPS�̒����AdeltatTime��S�A�N�^�[��Update�ɗ^����A���񂾃A�N�^�[�̍폜
//		2.3 GenerateOutput: �����_���[�̃x�[�X�J���[�ݒ�E�N���A�A�S�Ă̕`��Ώۂ�`��A�`��o�b�t�@�̌���
//			�`��Ώۂ́A�X�v���C�g�̏ꍇ�͑S�X�v���C�g�N���X��Draw�Ƀ����_���[����^����
// 3.Shutdown: ���������

// AddActor ��AddShip�EAddBall�Ȃǂ�Actor�̎q�N���X��Add������FmActors��mPendingActors�̔z���Actor��ǉ�
// Actor�̃R���X�g���N�^���������ʂ��ČĂяo��

// AddSprite: �X�v���C�g���ɐݒ肳��Ă���DrawOrder���擾���AmSprites�z��ɕ`�揇�ŃX�v���C�g��ǉ�
// Actor�̃R���X�g���N�^����SpriteComponent��������ʂ��ČĂяo��

// SDL_Texture* Game::GetTexture :�X�v���C�g�Ɏg�p����摜�t�@�C�����e�N�X�`���ɂ��邽�߂̊֐�
// Actor������Ăяo�����Ƃ����邵�A�w�i�p�͂���Game.cpp�ŌĂяo�����Ƃ�����B


#include "Game.h"
#include "SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "Court.h"

Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	mTicksCount = 0;
	mIsRunning = true;
	mIsUpdatingActors = false;
}

bool Game::Initialize()
{
	// SDL������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("SDL���������ł��܂���: %s", SDL_GetError());
		return false;
	}
	// SDL�E�B���h�E���쐬
	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 1ex)", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}
	// SDL�����_���[���쐬
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("�����_���[�̍쐬�Ɏ��s���܂���: %s", SDL_GetError());
		return false;
	}
	// SDL_image��������
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("SDL_image���������ł��܂���: %s", SDL_GetError());
		return false;
	}

	// �X�v���C�g��w�i�Ȃǂ̃f�[�^��ǂݍ���
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
	// SDL�C�x���g�ɃL���[������Ԃ͓��͂��󂯕t���Ȃ��B
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// �L�[�{�[�h���͂̎�t
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// ESC�������ꂽ�Ƃ���Shutdown
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// �p�h���̑���
	// mPaddle->ProcessKeyboard(state);
}

void Game::UpdateGame()
{
	// 60fps�ɂ��邽�߂ɒx��
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// deltatime�͑O�̃t���[���Ƃ̎����̍���b�ɕϊ������l
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	//deltatime���ő�l�Ő�������
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// �A�N�^�[���X�V
	mIsUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mIsUpdatingActors = false;

	// �҂��ɂȂ��Ă����A�N�^�[��mActors�Ɉړ�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���񂾃A�N�^�[���ꎞ�z��ɒǉ�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// ���񂾃A�N�^�[���폜
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	// �o�b�N�o�b�t�@(�Q�[���̃J�����g�o�b�t�@)��P�F�ŃN���A����
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	// �o�b�N�o�b�t�@�����݂̕`��F�ŃN���A����
	SDL_RenderClear(mRenderer);

	// �S�ẴX�v���C�g�R���|�[�l���g��`��
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
	// �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@����������
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	// �R�[�g���쐬
	mCourt = new Court(this);

	/*
	// �v���C���[�ł���L�����N�^�[���쐬
	mCharacter = new Character(this);
	mCharacter->SetPosition(Vector2(100.0f, 384.0f));
	mCharacter->SetScale(1.5f);
	*/


}

void Game::UnloadData()
{
	// actors������
	// ~Actor�ł�RemoveActor���Ăяo�����̂ŁA�ʂ̎�ނ̃��[�v���g��
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// �e�N�X�`�������łɃ}�b�v�ɓ����Ă���̂��H
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// �t�@�C�����烍�[�h
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("�e�N�X�`���t�@�C���̃��[�h�Ɏ��s %s", fileName.c_str());
			return nullptr;
		}

		// �T�[�t�F�C�X����e�N�X�`�����쐬
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		// �T�[�t�F�C�X������
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("�e�N�X�`���ւ̕ϊ��Ɏ��s %s", fileName.c_str());
			return nullptr;
		}
		// mTextures�ɍ쐬�����e�N�X�`����ǉ�
		mTextures.emplace(fileName.c_str(), tex);
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
	// �A�N�^�[�̍X�V���Ȃ�mPendingActors�ɒǉ�
	if (mIsUpdatingActors)
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
	// mPendingActors��vector����actor���������A�Y������C�e���[�^��Ԃ�
	// actor��������Ȃ��ꍇ�͍Ō�̃C�e���[�^��Ԃ�
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// �Y���̃C�e���[�^��mPendingActors�̈�ԍŌ�Ɉړ����Apop����
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// mActors��vector����actor���������A�Y������C�e���[�^��Ԃ�
	// actor��������Ȃ��ꍇ�͍Ō�̃C�e���[�^��Ԃ�
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// �Y���̃C�e���[�^��mPendingActors�̈�ԍŌ�Ɉړ����Apop����
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// �\�[�g�ς݂̔z��ő}���_��������
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

	// �C�e���[�^�̈ʒu�̑O�ɗv�f��}������
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
