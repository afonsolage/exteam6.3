#pragma once

#define ROTATION_SENS	5//5
#define ZOOM_MAX		600//60
#define ZOOM_MIN		15
#define ZOOM_INTER		1
#define CAMERA_DEBUG	0
#define PERCF(x, y)		((float)x / 100.0f * (float)y)
// ----------------------------------------------------------------------------------------------

typedef struct
{
	float	Zoom;
	float	RotationY;
	float	RotationZ;
	float	PositionZ;
	double	ClipX;
	float	ClipY;
	double	ClipZ;
	double	ClipX2;
	float	ClipY2;
	float	ClipZ2;
	float	ClipGL;
} DefaultData, * lpDefData;

// ----------------------------------------------------------------------------------------------

class Camera
{
public:
				Camera();
				~Camera();

	void		Load();
	// ----
	void		Init();
	void		Switch();
	void		Run(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam);
	void		Rotate();
	// ----
	bool		IsActive;
	float		ZoomPercent;
	bool		IsEnabled;
	// ----
	DefaultData Default;

	void		Enable() {IsEnabled = true;}
	void		Disable() {IsEnabled = false;}

	void		DisableRendering();
	void		EnableRendering();

private:
	BYTE		RotateMode;
	bool		InMove;
	int			TempCursorX;
	int			TempCursorY;
	// ----
}; extern Camera gCamera;
// ----------------------------------------------------------------------------------------------