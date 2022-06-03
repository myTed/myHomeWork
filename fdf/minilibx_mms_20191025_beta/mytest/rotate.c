#include "fdf.h"
#include <math.h>

void rotate_rcord_x(t_draw_info *pdi, double angle)
{
	int	idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		rotate_x(&(pdi->prcord[idx].x), &(pdi->prcord[idx].y), &(pdi->prcord[idx].z), angle);
		idx++;
	}
}

void rotate_rcord_y(t_draw_info *pdi, double angle)
{
	int	idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		rotate_y(&(pdi->prcord[idx].x), &(pdi->prcord[idx].y), &(pdi->prcord[idx].z), angle);
		idx++;
	}
}

void rotate_rcord_z(t_draw_info *pdi, double angle)
{
	int	idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		rotate_z(&(pdi->prcord[idx].x), &(pdi->prcord[idx].y), &(pdi->prcord[idx].z), angle);
		idx++;
	}
}

void rotate_x(double *px, double *py, double *pz, double angle)
{
	double		radian;
	double			tmp_y;

	radian = angle * PI / 180.0;
	tmp_y = *py;

	/*	
	*py = (int)((cos(radian) * (tmp_y)) - (sin(radian) * (*pz)));
	*pz = (int)((sin(radian) * (tmp_y)) + (cos(radian) * (*pz)));
	*/
	*py = ((cos(radian) * (tmp_y)) + (sin(radian) * (*pz)));
	*pz = (-(sin(radian) * (tmp_y)) + (cos(radian) * (*pz)));
	*px = *px;
}

void rotate_y(double *px, double *py, double *pz, double angle)
{
	double		radian;
	double			tmp_x;

	radian =  angle * PI / 180.0;
	tmp_x = *px;
	/*
	*px = (int)((cos(radian) * (tmp_x)) + (sin(radian) * (*pz)));
	*pz = (int)((-sin(radian) * (tmp_x)) + (cos(radian) * (*pz)));
	*/
	*px = ((cos(radian) * (tmp_x)) - (sin(radian) * (*pz)));
	*pz = ((sin(radian) * (tmp_x)) + (cos(radian) * (*pz)));
	*py = *py;
}

void rotate_z(double *px, double *py, double *pz, double angle)
{
	double 	radian;
	double		tmp_x;
	
	radian = angle * PI / 180.0;
	tmp_x = *px;
	/*
	*px = (int)((cos(radian) * (tmp_x)) - (sin(radian) * (*py)));
	*py = (int)((sin(radian) * (tmp_x)) + (cos(radian) * (*py)));
	*/
	*px = ((cos(radian) * (tmp_x)) + (sin(radian) * (*py)));
	*py = (-(sin(radian) * (tmp_x)) + (cos(radian) * (*py)));
	
	*pz = *pz;
}
