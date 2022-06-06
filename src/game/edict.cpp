#include "edict.h"

edict_t::edict_t()
{
  m_num_entities = 0;
  
  for (entity_t i = 0; i < MAX_ENTITIES; i++)
    m_entities[i] = 0;
}

entity_t edict_t::add_entity(entity_state_t state)
{
  for (entity_t i = 0; i < m_num_entities; i++) {
    if (!m_entities[i]) {
      m_entities[i] = state;
      return i;
    }
  }
  
  entity_t entity = m_num_entities++;
  m_entities[entity] = state;
  
  return entity;
}

void edict_t::remove_entity(entity_t entity)
{
  m_entities[entity] = 0;
}

entity_t edict_t::get_entity(entity_t entity) const
{
  return m_entities[entity];
}
