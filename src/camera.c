#include "simple_logger.h"

#include "gfc_shape.h"



typedef struct
{
	GFC_Vector2D position;
	GFC_Vector2D size;
	GFC_Rect bounds; //collsion
	Bool BindCamera;
}Camera;

static Camera _camera = { 0 };

void camera_set_bounds(GFC_Rect bounds) //set bounds
{
	gfc_rect_copy(_camera.bounds, bounds);
}

void camera_enable_binding(Bool bindCamera)
{
	_camera.BindCamera = bindCamera;
}

GFC_Vector2D camera_get_position()
{
	return _camera.position;
}

GFC_Vector2D camera_get_offset()
{
	return gfc_vector2d(-_camera.position.x, -_camera.position.y); //check back
}

GFC_Vector2D camera_get_size()
{
	return _camera.size;
}

GFC_Vector2D camera_get_diff()
{
	return _camera.size;
}

void camera_apply_bounds()
{
	if ((_camera.position.x + _camera.size.x) > (_camera.bounds.x + _camera.bounds.w))
	{
		_camera.position.x = (_camera.bounds.x + _camera.bounds.w) - (_camera.size.x);
	}
	if ((_camera.position.y + _camera.size.y) > (_camera.bounds.y + _camera.bounds.h))
	{
		_camera.position.y = (_camera.bounds.y + _camera.bounds.h) - (_camera.size.y);
	}

	if (_camera.position.x < _camera.bounds.x)_camera.position.x = (_camera.bounds.x);
	if (_camera.position.y < _camera.bounds.y)_camera.position.y = (_camera.bounds.y);
}


void camera_set_position(GFC_Vector2D position)
{
	gfc_vector2d_copy(_camera.position,position);
	if (_camera.BindCamera)
	{
		camera_apply_bounds();
	}
}

void camera_set_size(GFC_Vector2D size)
{
	gfc_vector2d_copy(_camera.size,size);
	
}

void camera_center_on(GFC_Vector2D target)
{
	GFC_Vector2D position;

	position.x = target.x - (_camera.size.x * 0.5);
	position.y = target.y - (_camera.size.y * 0.5);

	camera_set_position(position);
	if (_camera.BindCamera)camera_apply_bounds();
}








