#define STB_IMAGE_IMPLEMENTATION
#include "pch.h"
#include "Texture.h"

void Texture::LoadTexture(const char* filepath, HDC hdc)
{
    int channels;
    unsigned char* data = stbi_load(filepath, &_width, &_height, &channels, 4); // RGBA 포맷으로 로드
    if (!data) assert(false);

    // DIB(Bitmap) 생성
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = _width;
    bmi.bmiHeader.biHeight = -_height; // Top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 4 channels (RGBA)
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bitmapData = nullptr;
    _image = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bitmapData, nullptr, 0);

    if (_image) {
        // RGBA 데이터를 BGRA로 변환
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                int index = (y * _width + x) * 4;
                unsigned char temp = data[index];       // R
                data[index] = data[index + 2];          // B
                data[index + 2] = temp;                 // R
            }
        }

        memcpy(bitmapData, data, _width * _height * 4);
    }

    stbi_image_free(data);

    // 비트맵 크기에 맞는 DC 생성
    _hdcImage = CreateCompatibleDC(hdc);
    SelectObject(_hdcImage, _image);
}

void Texture::RenderImage(HDC backbuffer ,int x ,int y)
{
    StretchBlt(backbuffer, x, y, TILESIZE, TILESIZE, _hdcImage, 0, 0, _width, _height, SRCCOPY);
}
