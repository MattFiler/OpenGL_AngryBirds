#pragma once
#include <string>
#include "SpriteComponent.h"
#include "Vector2.h"

class UI
{
public:
	UI();
	~UI();

	bool  addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name);

	void addToX(float addX);
	void addToY(float addY);

	void subtractFromX(float minusX);
	void subtractFromY(float minusY);

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);

	float getHeight();
	float getWidth();

	void setScale(float scale);
	float getScale();

	void setOpacity(float opacity);
	float getOpacity();

	void despawn();
	void spawn();
	bool hasSpawned();

	bool animateFadeOutUp(float frame_time);
	bool animateFadeIn(float frame_time);
	bool animateFadeInUp(float frame_time);

	SpriteComponent* spriteComponent();

private:
	bool has_spawned = false;

	void freeSpriteComponent();
	SpriteComponent* sprite_component = nullptr;
};