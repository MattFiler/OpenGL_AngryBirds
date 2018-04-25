#pragma once
#include "GameObject.h"
#include "../AngryEnums/AngryGameVars.h"

class FX : public GameObject
{
public:
	FX();
	~FX();

	bool addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name, int frame);

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);

	float getHeight();
	float getWidth();

	void setScale(float scale);
	float getScale();

	void setFrame(int frame);
	int getFrame();

	bool animate(float frame_time);

	SpriteComponent* spriteComponent();

private:
	int current_frame = 0;
	float runtime_count = 0;

	void freeSpriteComponent(int frame);
	SpriteComponent* sprite[(int)GameVars::NUMBER_OF_FRAMES_IN_FX];
};