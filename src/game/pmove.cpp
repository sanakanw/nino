#include "pmove.h"

#include "../common/log.h"

#define TIMESTEP (1.0 / 60.0)
#define FLY_SPEED 1.0

pmove_t::pmove_t(
  const edict_t               &edict,
  const cdict_t<client_t>     &client,
  cdict_t<transform_t>        &transform)
  : m_edict(edict),
    m_client(client),
    m_transform(transform)
{
}

void pmove_t::free_look()
{
  constexpr entity_state_t mask = component_t::TRANSFORM | component_t::CLIENT;
  
  for (entity_t i = 0; i < m_edict.size(); i++) {
    if ((m_edict.get_entity(i) & mask) != mask)
      continue;
    
    vec3_t axis_up = vec3_t(0.0f, 1.0f, 0.0f);
    vec3_t axis_right = vec3_t(1.0f, 0.0f, 0.0f);
    
    quat_t rot_yaw = quat_t().init_rotation(axis_up, m_client[i].usercmd.yaw);
    vec3_t axis_pitch = axis_right.rotate(rot_yaw);
    quat_t rot_pitch = quat_t().init_rotation(axis_pitch, m_client[i].usercmd.pitch);
    
    m_transform[i].rotation = rot_pitch * rot_yaw;
  }
}

void pmove_t::free_move()
{
  constexpr entity_state_t mask = component_t::TRANSFORM | component_t::CLIENT;
  
  for (entity_t i = 0; i < m_edict.size(); i++) {
    if ((m_edict.get_entity(i) & mask) != mask)
      continue;
    
    vec3_t cmd_dir = vec3_t(m_client[i].usercmd.side, 0.0f, m_client[i].usercmd.forward);
    vec3_t move_dir = cmd_dir.rotate(m_transform[i].rotation) * FLY_SPEED * TIMESTEP;
    
    m_transform[i].position += move_dir;
  }
}
