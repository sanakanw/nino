#ifndef PMOVE_H
#define PMOVE_H

#include "edict.h"
#include "gamedef.h"

class pmove_t {
  const edict_t               &m_edict;
  const cdict_t<client_t>     &m_client;
  cdict_t<transform_t>        &m_transform;
  
public:
  pmove_t(
    const edict_t           &edict,
    const cdict_t<client_t> &client,
    cdict_t<transform_t>    &transform);
  
  void  free_look();
  void  free_move();
};

#endif
