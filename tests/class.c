#include <stdio.h>

typedef struct {
	void (*draw)(void*);
	void (*getSurface)(void*);
}	shape_v_table;

typedef struct s_Shape{
	shape_v_table *v_table;
	int x, y;
}			Shape;

void shapeDraw(Shape* self)
{
	printf("Shape %i:%i\n", self->x, self->y);
}

void getSurfaceShape(Shape* self)
{
	(void)self;
	printf("Shape: %i\n", 0);
}

shape_v_table *get_shape_v_table()
{
	static shape_v_table v_table;
	if (!v_table.draw)
	{
		v_table.draw = (void(*)(void*))shapeDraw;
		v_table.getSurface = (void(*)(void*))getSurfaceShape;
	}
	return &v_table;
}

typedef struct {
	Shape sh;
	int r;
} 		Circle;

void circleDraw(Circle* self)
{
	shapeDraw((Shape*)self);
	printf("Circle r:%i\n", self->r);
}

void getSurfaceCircle(Circle* self)
{
	printf("Circle: %f\n", 2 * 3.14 * self->r * self->r);
}

shape_v_table *get_shape_circle_v_table()
{
	static shape_v_table v_table;
	if (!v_table.draw)
	{
		v_table.draw = (void(*)(void*))circleDraw;
		v_table.getSurface = (void(*)(void*))getSurfaceCircle;
	}
	return &v_table;
}

typedef struct {
	Shape sh;
	int x_s, y_s;
} 		Cub;

void cubDraw(Cub* self)
{
	shapeDraw((Shape*)self);
	printf("Cub s: %i:%i\n", self->x_s, self->y_s);
}

void getSurfaceCub(Cub* self)
{
	printf("Cub: %d\n", self->x_s * self->y_s);
}

shape_v_table *get_shape_cub_v_table()
{
	static shape_v_table v_table;
	if (!v_table.draw)
	{
		v_table.draw = (void(*)(void*))cubDraw;
		v_table.getSurface = (void(*)(void*))getSurfaceCub;
	}
	return &v_table;
}

int main()
{
	Shape sh = (Shape) { get_shape_v_table(), 1, 1 };
	Circle ch = (Circle){(Shape) { get_shape_circle_v_table(), 1, 1 }, 5 };
	Cub cub = (Cub){(Shape) { get_shape_cub_v_table(), 1, 1 }, 3, 3 };

	Shape *p_sh;

	p_sh = &sh;
	p_sh->v_table->draw(p_sh);
	p_sh->v_table->getSurface(p_sh);

	p_sh = (Shape*)&ch;
	p_sh->v_table->draw(p_sh);
	p_sh->v_table->getSurface(p_sh);

	p_sh = (Shape*)&cub;
	p_sh->v_table->draw(p_sh);
	p_sh->v_table->getSurface(p_sh);
}
