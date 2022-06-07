#ifndef GAME_H
#define GAME_H

#include "edict.h"
#include "pmove.h"
#include "gamedef.h"

class game_t {
private:
  edict_t   m_edict;
  entity_t  m_player_entity;
  
  pmove_t   m_pmove;
  
  cdict_t<client_t>     m_client;
  cdict_t<sprite_t>     m_sprite;
  cdict_t<transform_t>  m_transform;

public:
  game_t();
  
  void      update(const usercmd_t &usercmd);
  
  entity_t  get_player_entity() const { return m_player_entity; }
  
  const edict_t               &get_edict() const { return m_edict; }
  const cdict_t<sprite_t>     &get_sprite() const { return m_sprite; }
  const cdict_t<transform_t>  &get_transform() const { return m_transform; }
};

#endif
