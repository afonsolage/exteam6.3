#pragma once

class cCustomMenuInterface
{
public:
	cCustomMenuInterface();
	int MainTableHigh;
	int MainTableWidth;
	int DrawStartX;
	int DrawStartY;
	int MenuOpen;
	bool DrawTable;

	void ImageLoad();
	void BindImages();
	void Draw();

private:
	
};
extern cCustomMenuInterface gCustomMenuInterface;