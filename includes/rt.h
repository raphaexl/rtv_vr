/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:49:52 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/23 12:49:54 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define SCR_WIDTH 1200
# define SCR_HEIGHT 750
# define W_W 800
# define W_H 600
# define START_X (SCR_WIDTH - W_W) / 2 + 10
# define START_Y (SCR_HEIGHT - W_H) / 2 - 10
# define END_X W_W + START_X
# define END_Y  W_H + START_Y
# define NB_THREADS 10
# define ERR_CHECK(cond) if (!(cond)) perror(SDL_GetError());

# include <sys/stat.h>
# include <fcntl.h>
# include "rt_structs.h"

float		ft_rand48(void);
float		ft_atof(const char *str);
char		*ft_itoaf(long double nb, int precision);
float		ft_clamp(float min, float max, float val);
t_uv		ft_uv(float u, float v);
t_vec3		ft_reflect(t_vec3 i, t_vec3 n);
int			ft_refract(t_vec3 i, t_vec3 n, float eta, t_vec3 *r);
int			ft_lambertian_sc(t_intersect *in, t_col3 *att);
int			ft_metal_sc(t_intersect *in, t_col3 *att);
int			ft_dielectric_sc(t_intersect *in, t_col3 *att, float ref_idx);
t_col3		ft_background_color(t_ray *r);
void		ft_error(void);
int			ft_tab_len(char **tab);
void		ft_print_error(char *str);
void		ft_parsing_error(int error);
void		ft_sdl_error(void);
t_font		ft_font(const char *message, const char *font_file, int font_size);
Uint32		ft_color_sdl(SDL_Color c);
SDL_Color	ft_sdl_color(Uint32 c);
void		ft_env_load_all(t_env *e);
void		ft_env_load_images(t_env *env);
void		ft_env_init(t_env *e, int argc, char *argv[]);
int			ft_env_update_camera(t_camera *c, t_input *in);
void		ft_env_select_object(t_env *e, int x, int y);
void		ft_object_resize(t_object **s, float rev);
int			ft_prev_update(t_env *e, t_input *in);
int			ft_process_event(t_env *e, t_input *in);
int			ft_update_options(t_menu *m, t_input *in, int k);
int			ft_mouse_inside(int mousex, int mousey, SDL_Rect *r);
void		ft_env_display_text(SDL_Renderer *r, char *m);
void		ft_draw(t_env *e);
void		ft_env_quit(t_env *e);
void		ft_event_key_down(SDL_Event *e, t_input *in);
int			ft_event_edition(t_input *in);
t_vec3		ft_rotate_x(t_vec3 r, float angle);
t_vec3		ft_rotate_y(t_vec3 r, float angle);
t_vec3		ft_rotate_z(t_vec3 r, float angle);
t_vec3		ft_rotate_vec3(t_vec3 r, t_vec3 v, int invert);
t_vec3		ft_translate_vec3(t_vec3 r, t_vec3 v, int invert);
t_vec3		ft_scale_vec3(t_vec3 r, t_vec3 v, int invert);
int			ft_solve_quadric(double c[3], double s[2]);
int			ft_solve_cubic(double w[4], double s[3]);
int			ft_solve_quartic(double w[5], double s[4]);
t_col3		ft_get_light(t_intersect *in, t_light *light);
int			ft_illuminate(t_light *l, t_intersect *in);
t_col3		ft_ambient_light(t_col3 *diffuse, t_col3 *ambiant);
t_col3		ft_trace(t_intersect *in, t_material *m, t_light *l);
t_col3		ft_ray_trace(t_scene *s, t_intersect *in, int depth);
t_col3		ft_edit_trace(t_scene *s, t_intersect *in, int depth);
void		ft_create_coordinate_system(t_vec3 n, t_vec3 *nt, t_vec3 *nb);
t_vec3		ft_uniform_sample_hemisphere(float r1, const float r2);
char		*ft_parse_process_str(char *str, char start, char end);
t_rtsplit	ft_parse_process_split(char *str, char c1, char c2, char split);
int			ft_rtstrequal(char *s1, char *s2);
t_mesh		ft_default_mesh(void);
int			ft_mesh_load(t_mesh *m, const char *file_name);
void		ft_print_mesh(t_mesh *m);
void		ft_mesh_clean(t_mesh *m);
int			ft_bool_read(char *line);
char		*ft_str_read(char *line);
float		ft_float_read(char *line);
t_vec3		ft_vec3_read(char *line);
t_col3		ft_col3_read(char *line);
t_material	ft_default_material(void);
int			ft_read_all(int fd, char **dataptr, size_t *sizeptr);
t_material	ft_material_read(char **str);
int			ft_parse_material(t_material *m, char	**str);
t_object	*ft_parse_process_object(char **str, t_otype type);
t_otype		ft_parsing_object(char *str);
int			ft_parse_process_objects(t_scene *s, char *str);
t_object	*ft_parse_sphere(t_object *o, char **str);
t_object	*ft_parse_ring(t_object *o, char **str);
t_object	*ft_parse_cylinder(t_object *o, char **str);
t_object	*ft_parse_plane(t_object *o, char **str);
t_object	*ft_parse_cone(t_object *o, char **str);
t_object	*ft_parse_disk(t_object *o, char **str);
t_object	*ft_parse_box(t_object *o, char **str);
t_object	*ft_parse_cube(t_object *o, char **str);
t_object	*ft_parse_torus(t_object *o, char **str);
t_object	*ft_parse_triangle(t_object *o, char **str);
t_object	*ft_parse_parallelogram(t_object *o, char **str);
t_object	*ft_parse_mesh(t_object *o, char **str);
t_light		*ft_parse_process_light(char **str, t_ltype type);
t_ltype		ft_parsing_light(char **str);
int			ft_parse_process_lights(t_scene *s, char *str);
t_light		*ft_parse_point_light(t_light *l, char **str);
t_light		*ft_parse_spot_light(t_light *l, char **str);
t_light		*ft_parse_direct_light(t_light *l, char **str);
t_light		*ft_parse_default_light(t_light *l, char **str);
void		ft_scene_read(t_scene *s, int fd);
void		ft_parse_file(t_scene *s, int	fd);
int			ft_parse_process_camera(t_scene *s, char *str);
int			ft_parse_process_background(t_scene *s, char *str);
int			ft_parse_process_scene(t_scene *s, char *str);
void		ft_scene_init(t_scene *s, char *const input_file);
void		ft_render(t_scene *s, Uint32 *pix);
void		ft_scene_clear(t_scene *s);
t_object	*ft_sphere_new(void);
int			ft_sphere_intersect(t_sphere *s, t_ray *r, float *t);
t_vec3		ft_normal_sphere(t_sphere *s, t_vec3 p);
int			ft_sphere_compute(t_object *p, t_intersect *in);
t_object	*ft_plane_new(void);
int			ft_plane_intersect(t_plane *plane, t_ray *r, float *t);
t_vec3		ft_normal_plane(t_plane *plane, int ret);
int			ft_plane_compute(t_object *p, t_intersect *in);
t_object	*ft_cone_new(void);
t_vec3		ft_normal_cone(t_cone *cone, t_vec3 p);
int			ft_cone_intersect(t_cone *s, t_ray *r, float *t);
int			ft_cone_compute(t_object *p, t_intersect *in);
t_object	*ft_ring_new(void);
t_vec3		ft_normal_rint(t_ring *ring, t_vec3 p);
int			ft_ring_intersect(t_ring *ring, t_ray *r, float *t);
int			ft_ring_compute(t_object *p, t_intersect *in);
t_object	*ft_cylindre_new(void);
void		ft_normal_cylindre(t_object *p, t_hit *in, t_ray r, int ret);
int			ft_cylindre_intersect(t_cylinder *cylinder, t_ray *r, float *t);
int			ft_cylindre_compute(t_object *p, t_intersect *in);
t_object	*ft_disk_new(void);
int			ft_disk_intersect(t_disk *disk, t_ray *r, float *t);
int			ft_disk_compute(t_object *d, t_intersect *in);
t_vec3		ft_normal_disk(t_disk *disk, int ret);
t_object	*ft_box_new(void);
t_vec3		ft_normal_box(t_box *cone, t_vec3 p);
int			ft_box_intersect(t_box *box, t_ray *r, float *t);
int			ft_box_compute(t_object *b, t_intersect *in);
t_object	*ft_cube_new(void);
t_vec3		ft_normal_cube(t_cube *cone, t_vec3 p);
int			ft_cube_intersect(t_cube *cube, t_ray *r, float *t);
int			ft_cube_compute(t_object *b, t_intersect *in);
t_object	*ft_torus_new(void);
t_vec3		ft_normal_torus(t_torus *cone, t_vec3 p);
int			ft_torus_intersect(t_torus *torus, t_ray *r, float *t);
int			ft_torus_compute(t_object *b, t_intersect *in);
t_object	*ft_triangle_new(void);
int			ft_triangle_intersect(t_triangle *triangle, t_ray *r, float *t);
int			ft_triangle_compute(t_object *tr, t_intersect *in);
t_vec3		ft_normal_triangle(t_triangle *triangle);
t_object	*ft_parallelogram_new(void);
int			ft_parallelogram_intersect(t_parallelogram *p, t_ray *r, float *t);
int			ft_parallelogram_compute(t_object *para, t_intersect *in);
t_vec3		ft_normal_parallelogram(t_parallelogram *p);
t_object	*ft_mesh_new(void);
int			ft_mesh_intersect(t_triangle *m, t_ray *r, float *t);
int			ft_mesh_compute(t_object *mesh, t_intersect *in);
t_vec3		ft_normal_mesh(t_triangle *tr);
t_texture	*ft_texture_new(char *img);
void		ft_sphere_uv(t_object *o, t_vec3 n, t_vec3 p, t_uv *uv);
void		ft_plane_uv(t_object *o, t_vec3	n, t_vec3 p, t_uv *uv);
void		ft_cone_uv(t_cone *cone, t_vec3 n, t_vec3 p, t_uv *uv);
void		ft_cylinder_uv(t_cylinder *c, t_vec3 n, t_vec3 p, t_uv *uv);
void		ft_ring_uv(t_ring *c, t_vec3 n, t_vec3 p, t_uv *uv);
void		ft_torus_uv(t_torus *t, t_vec3 n, t_vec3 p, t_uv *uv);
void		ft_cube_uv(t_cube *cube, t_vec3 n, t_vec3 p, t_uv *uv);
void		ft_box_uv(t_box *b, t_vec3 n, t_vec3 p, t_uv *uv);
t_col3		ft_procedural_texturing(t_object *o, t_vec3 pos);
t_col3		ft_image_texturing(t_object *o, t_vec3 pos);
t_col3		ft_texture_image(t_texture *t, float u, float v);
t_col3		ft_get_texel(t_texture *t, float u, float v);
void		ft_texture_clean(t_texture **t);
int			ft_scene_intersect(t_scene *s, t_intersect *i);
int			ft_scene_intersectl(t_scene *s, t_intersect *i);
double		ft_fade(double t);
double		ft_lerp(double t, double a, double b);
double		ft_grad(int hash, double x, double y, double z);
double		ft_perlin(double x, double y, double z);
t_col3		ft_perlin_color(t_hit *hit);
t_col3		ft_marble_color(t_hit *hit);
t_col3		ft_perlin_noise(t_hit *hit);
t_vec3		ft_normal_bump(t_hit *hit);
t_object	*ft_object_new(t_type type, t_object *o);
void		ft_object_remove(t_object **s, int id);
void		ft_object_push_back(t_object **lst, t_object *nw);
void		ft_object_add_back(t_object **lst, t_type type);
void		ft_object_clean(t_object **lst);
t_light		*ft_light_new(t_ltype type, t_light *l);
void		ft_light_push_back(t_light **lst, t_light *nw);
void		ft_light_remove(t_light **s, int id);
void		ft_light_add_back(t_light **lst, t_ltype type);
void		ft_light_clean(t_light **lst);
t_camera	ft_camera_new(t_vec3 eye, t_vec3 look_at, t_vec3 up, float a);
t_ray		ft_camera_ray(t_camera *cam, float x, float y);
void		ft_camera_transform(t_camera *cam);
void		ft_update_event(t_input *in);
int			ft_sdl_init(t_ptr *ptr, const char *title);
int			ft_update_renderer(t_ptr *ptr, Uint32 *pixel);
SDL_Texture	*ft_get_render_text(SDL_Renderer *rend, t_font f, SDL_Color color);
void		ft_render_draw_img(SDL_Renderer *r, SDL_Texture *i, t_point p,\
		SDL_Rect *pos);
Uint32		ft_get_pixels(SDL_Surface *s, int x, int y);
void		ft_put_pixels(SDL_Surface *s, int x, int y, Uint32 pixel);
void		ft_save_bmp_pixels(Uint32 *pixels, int w, int h);
void		ft_save_png_pixels(Uint32 *pixels, int w, int h);
Uint32		*ft_load_pixels(char *file_name, int *w, int *h);
void		ft_sdl_error(void);
void		ft_sdl_quit(t_ptr *ptr);
int			ft_handle_input(t_input *in);
void		ft_no_object_select(t_inspector *ins);
void		ft_object_select1(t_inspector *ins, t_object *o);
int			ft_object_selectv(t_inspector *ins, t_object *o);
void		ft_object_select2(t_inspector *ins, t_object *o);
void		ft_object_select3(t_inspector *ins, t_object *o);
void		ft_object_select4(t_inspector *ins, t_object *o);
int			ft_object_select34(t_inspector *ins, t_object *o);
int			ft_object_select35(t_inspector *ins, t_object *o);
void		ft_object_select5(t_inspector *ins, t_object *o);
void		ft_inspector_object(t_inspector *ins, t_object *o);
void		ft_object_apply1(t_inspector *ins, t_object **o);
void		ft_object_apply2(t_inspector *ins, t_object **o);
void		ft_object_apply3(t_inspector *ins, t_object **o);
void		ft_object_apply4(t_inspector *ins, t_object **o);
void		ft_object_apply5(t_inspector *ins, t_object **o);
void		ft_object_apply6(t_inspector *ins, t_object **o);
void		ft_object_apply7(t_inspector *ins, t_object **o);
void		ft_object_apply8(t_inspector *ins, t_object **o);
void		ft_inspector_apply(t_inspector *ins, t_object **o);
void		ft_inspector_setup1(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_setup2(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_setup3(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_setup4(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_setup5(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_init(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_display1(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_display2(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_display3(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_display4(t_ptr *ptr, t_inspector *ins);
void		ft_inspector_display(t_ptr *ptr, t_inspector *ins);
int			ft_inspector_pupdate_event(t_inspector *ins, t_input *in);
int			ft_inspector_update_event(t_inspector *ins, t_input *in);
void		ft_inspector_clean(t_inspector *ins);
void		ft_cview_init(t_ptr *ptr, t_cview *cv);
void		ft_cview_display(t_ptr *ptr, t_cview *cv);
int			ft_cview_update_event(t_cview *cv, t_input *in);
void		ft_cview_clean(t_cview *cv);
void		ft_cview_apply(t_cview *view, t_camera *c);
void		ft_cview_camera(t_cview *view, t_camera *c);
void		ft_no_object_select(t_inspector *ins);
t_widget	ft_widget_new(t_ptr *ptr, Uint32 c);
t_widget	*ft_widget_create(t_ptr *ptr, Uint32 c);
void		ft_widget_draw(t_ptr *ptr, t_widget *w, int x, int y);
int			ft_mouse_on_widget(t_widget *w, int x, int y);
void		ft_widget_clean(t_widget *w);
t_button	ft_button_new(t_ptr *ptr, Uint32 c, Uint32 c2, const char *text);
t_button	*ft_button_create(t_ptr *pr, Uint32 c, Uint32 c2, const char *txt);
void		ft_button_draw(t_ptr *ptr, t_button *w, int x, int y);
int			ft_mouse_on_button(t_button *w, int x, int y);
void		ft_button_clean(t_button *b);
t_entry		ft_entry_new(t_ptr *ptr, Uint32 c, Uint32 c2, const char *m);
t_entry		*ft_entry_create(t_ptr *ptr, Uint32 c, Uint32 c2, const char *m);
void		ft_entry_draw(t_ptr *ptr, t_entry *w, int x, int y);
void		ft_entry_process(t_entry *w, t_input *in);
void		ft_entry_clean(t_entry *b);
int			ft_mouse_on_entry(t_entry *w, int x, int y);
int			ft_process_entry(t_entry *e, t_input *in);
int			ft_event_entry_pressed(t_entry *e, t_input *in);
int			ft_gui_event(t_entry *entry, t_input *in);
t_img		ft_load_img(SDL_Renderer *rend, const char *file_name);
int			ft_env_texture_load(t_env *e);
t_col3		ft_background_image(t_scene *s, t_intersect *in, int index);
void		ft_obj_init(t_obj *obj);
void		ft_bizzare(t_obj *obj, char **tab);
void		ft_parse_obj_faces(t_obj *obj, char *line);
void		ft_make_obj(t_obj *obj, t_vector *v, t_vector *uvs, t_vector *ns);
void		ft_print_obj(t_obj *obj);
void		ft_obj_clean(t_obj *obj);
int			ft_load_obj_file(t_obj *obj, const char *file_name);
void		ft_parse_obj_vector(t_vector *v, char *line);
void		ft_parse_obj_uv(t_vector *v, char *line);
void		ft_parse_obj_normal(t_vector *v, char *line);
void		ft_parse_obj_faces(t_obj *obj, char *line);
int			ft_mesh_triangulate(t_mesh *m, t_obj *obj);
t_col3		ft_get_col3(t_pixel color);
t_pixel		ft_scale_convert_col3(t_col3 c, double t);
t_pixel		ft_get_color(int color);
void		ft_convolute(t_env *env, double *filter, int size, int den);
int			ft_apply_convolution(t_env *e);
void		ft_sobel(t_env *env);
void		ft_grey(t_env *e);
void		ft_motion_blur(t_env *env);
void		ft_gauss_blur(t_env *env);
void		ft_emboss(t_env *env);
void		ft_sharpen(t_env *env);
void		ft_draw_borders(t_env *e);
char		**ft_default_env_map(void);
t_cubemap	*ft_cubemap_init(char	*m[6], int srgb, int exposed);
t_col3		ft_read_texture(t_col3 *tab, t_uv uv, int w, int h);
t_col3		ft_read_cubemap(t_cubemap *cm, t_ray r);

void		ft_material_print(const t_material *m);
#endif
