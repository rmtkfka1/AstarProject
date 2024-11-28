#pragma once
class Texture
{

public:
	void LoadTexture(const char* filepath, HDC hdc);
	void RenderImage(HDC backbuffer ,int x, int y);

private:
	HBITMAP _image;
	HDC _hdcImage;
	int _width;
	int _height;
};

