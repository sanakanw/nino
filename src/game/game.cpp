#include "game.h"

#include "../common/log.h"

game_t::game_t()
  : m_pmove(m_edict, m_client, m_transform)
{
  m_player_entity = m_edict.add_entity(component_t::TRANSFORM | component_t::CLIENT);
  
  entity_t sprite = m_edict.add_entity(component_t::TRANSFORM | component_t::SPRITE);
  m_sprite[sprite].uv_ofs = vec2_t(0.0, 3.0);
}

void game_t::update(const usercmd_t &usercmd)
{
  m_client[m_player_entity].usercmd = usercmd;
  
  m_pmove.free_look();
  m_pmove.free_move();
}
