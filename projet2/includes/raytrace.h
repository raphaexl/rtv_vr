/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/26 09:57:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "camera.h"
# include "col3.h"
# include "defines.h"

typedef enum	e_type
{
	NONE = 0, SPHERE, CONE, CYLINDER, BOX, PLANE, DISK, TORUS, CUBE, TRIANGLE,
	PARALLELOGRAM, RING, ELLIPSOID, PARABOLOID, MESH
}				t_type;

typedef enum	e_ltype
{
	DISTANT, POINT
}				t_ltype;

typedef enum	e_ftype
{
	NOFILTER, CONVOLUTION, BLUR, BLUR2, GAUSSIAN_BLUR,  GAUSSIAN_BLUR2, MOTION_BLUR,
	EDGE, EDGE2, EDGE3, SHARPEN, EMBOSS, EMBOSS2, MEAN_AND_MEDIAN
}				t_ftype;

typedef enum	e_mtype
{
	DIFFUSE, SPECULAR, METAL, DIELECTRIC
}				t_mtype;

typedef	enum	e_itype
{
		DEFAULT, EDITING
}				t_itype;

typedef struct	s_ray
{
	t_vec3		start;
	t_vec3		dir;
}				t_ray;

typedef	struct	s_l
{
	t_ltype		type;
	t_vec3		pos;
	t_vec3		dir;
	t_col3		color;
	float		intensity;
	int			id;
	struct s_l	*next;
}				t_light;

typedef struct	s_texture
{
	int		w;
	int		h;
	Uint32	*data;
}				t_texture;

typedef	struct	s_filter
{
	t_ftype		type;
	int			w;
	int			h;
	float		**filter;
	float		factor;
	float		bias;
}				t_filter;

typedef struct s_perlin
{
	t_vec3		*ranvec;
	int			*perm_x;
	int			*perm_y;
	int			*perm_z;
}				t_perlin;

typedef struct	s_material
{
	t_mtype		type;
	float		albedo[4];
	t_col3		diffuse;
	t_col3		specular;
	float		spec_pow;
	float		reflection;
	float		refraction;
	int			chess;
	t_perlin	perlin;
}				t_material;

typedef struct	s_sphere
{
	float		radius;
	float		radius2;
}				t_sphere;

typedef struct	s_cylinder
{
	float		radius;
	float		radius2;
	float		height;
	t_vec3		v;
}				t_cylinder;

typedef struct	s_disk
{
	float		radius;
	float		radius2;
	t_vec3		normal;
}				t_disk;

typedef struct	s_cone
{
	float		angle;
	float		height;
	t_vec3		v;
}				t_cone;

typedef struct	s_plane
{
	t_vec3		normal;
}				t_plane;

typedef struct	s_box
{
	t_vec3		bounds[2];
}				t_box;

typedef struct	s_torus
{
	float		radius1;
	float		radius2;
}				t_torus;

typedef struct	s_cube
{
	float		radius;
}				t_cube;

typedef struct	s_triangle
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	float		u;
	float		v;
	float		t;
}				t_triangle;

typedef struct	s_parallelogram
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	t_vec3		d;
	float		u;
	float		v;
	float		t;
}				t_parallelogram;

typedef struct	s_ring
{
	float		radius;
	float		radius2;
	float		height;
	t_vec3		v;
}				t_ring;

typedef struct	s_ellipsoid
{
	float		k;
	float		radius;
	float		radius2;
	t_vec3		v;
	t_vec3		c;
}				t_ellipsoid;

typedef struct	s_paraboloid
{
	float		k;
	t_vec3		v;
	t_vec3		c;
}				t_paraboloid;

typedef struct	s_mesh
{
	char		*name;
	int			n_faces;
	int			verts_index_array_size;
	int			max_verts_index;
	int			num_tris;
	int			verts_array_size;
	int			*face_index;
	int			*verts_index;
	t_vec3		*verts;
	t_vec3		*normals;
	t_vec2		*st;
}				t_mesh;

typedef union	s_union
{
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_disk			disk;
	t_cone			cone;
	t_plane			plane;
	t_box			box;
	t_torus			torus;
	t_cube			cube;
	t_triangle		triangle;
	t_parallelogram	para;
	t_ring			ring;
	t_ellipsoid		ellipse;
	t_paraboloid	parab;
	t_mesh			mesh;
}				t_union;

typedef	struct	s_o
{
	t_material	material;
	t_vec3		pos;
	t_vec3		translate;
	t_vec3		rotate;
	t_vec3		scale;
	t_union		e;
	int			id;
	t_type		type;
	char		*name;
	struct s_o	*next;
}				t_object;

typedef struct	s_iterm
{
	t_vec3		pos;
	t_col3		color;
}				t_iterm;

typedef struct	s_intersect
{
	t_ray		ray;
	t_ray		ray_light;
	t_vec3		n;
	t_vec3		p;
	float		t;
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	t_camera	cam;
	t_col3		c;
	t_col3		bg_color;
	t_col3		ambiant;
	int			nb_samples;
	int			a;
	t_object	*obj;
	t_light		*light;
	t_texture	*earth;
	t_texture	*img[N_TEXTURES];
	t_filter	*filter;
	t_col3		(*ft_rtv1)(struct s_scene *, t_intersect *, int);
	t_col3		(*ft_bg_color)(struct s_scene *, t_intersect *, int);
}				t_scene;
#endif