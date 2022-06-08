#include "sprite_model.h"

void build_sprite_mesh(
  const quat_t      &cam_rot,
  const vec2_t      &sprite_size,
  vertex_t          *vertices,
  const transform_t &transform,
  const sprite_t    &sprite)
{
  static vertex_t sprite_vertices[] = {
    vertex_t(vec3_t(-0.5f, -0.0f, 0.0f), vec2_t(0.0, 1.0)),
    vertex_t(vec3_t(-0.5f, +1.0f, 0.0f), vec2_t(0.0, 0.0)),
    vertex_t(vec3_t(+0.5f, -0.0f, 0.0f), vec2_t(1.0, 1.0)),
    
    vertex_t(vec3_t(+0.5f, -0.0f, 0.0f), vec2_t(1.0, 1.0)),
    vertex_t(vec3_t(-0.5f, +1.0f, 0.0f), vec2_t(0.0, 0.0)),
    vertex_t(vec3_t(+0.5f, +1.0f, 0.0f), vec2_t(1.0, 0.0)),
  };
  
  static int num_sprite_vertices = sizeof(sprite_vertices) / sizeof(vertex_t);
  
  for (int i = 0; i < num_sprite_vertices; i++) {
    vertices[i].pos = (sprite_vertices[i].pos + transform.position).rotate(cam_rot);
    vertices[i].uv = (sprite_vertices[i].uv + sprite.uv_ofs) * sprite_size;
  }
}

sprite_model_t::sprite_model_t(
    const edict_t               &edict,
    const cdict_t<sprite_t>     &sprite,
    const cdict_t<transform_t>  &transform,
    mesh_pool_t                 &mesh_pool,
    const vec2_t                &sprite_size)
  : m_edict(edict),
    m_sprite(sprite),
    m_transform(transform),
    m_mesh_pool(mesh_pool)
{
  m_sprite_size = sprite_size;
  m_mesh = mesh_pool.new_mesh(MAX_SPRITES * 6 * sizeof(vertex_t));
}

void sprite_model_t::update(const quat_t &cam_rot)
{
  static vertex_t vertices[MAX_SPRITES * 6];
  
  constexpr entity_state_t mask = component_t::SPRITE | component_t::TRANSFORM;
  
  m_num_sprites = 0;
  
  for (entity_t entity = 0; entity < m_edict.size(); entity++) {
    if ((m_edict.get_entity(entity) & mask) != mask)
      continue;
    
    build_sprite_mesh(
      cam_rot,
      m_sprite_size,
      &vertices[m_num_sprites++ * 6],
      m_transform[entity],
      m_sprite[entity]);
  }
  
  m_mesh_pool.sub_mesh(m_mesh, 0, vertices, m_num_sprites * 6 * sizeof(vertex_t));
}

void sprite_model_t::draw()
{
  m_mesh_pool.draw_sub_mesh(m_mesh, 0, m_num_sprites * 6);
}
