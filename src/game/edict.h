#ifndef EDICT_H
#define EDICT_H

#include <array>

#define MAX_ENTITIES 32

typedef int entity_t;
typedef int entity_state_t;

class edict_t {
private:
  entity_state_t  m_entities[MAX_ENTITIES];
  int             m_num_entities;

public:
  edict_t();
  
  entity_t        add_entity(entity_state_t state);
  entity_state_t  get_entity(entity_t entity) const;
  void            remove_entity(entity_t entity);
  
  int             size() const { return m_num_entities; }
};

template<class T>
using cdict_t = std::array<T, MAX_ENTITIES>;

#endif
