#include "event.h"

#include "../common/log.h"

bool event_queue_t::get_event(event_t &event)
{
  if (!m_event_queue.size())
    return false;
  
  event = m_event_queue[0];
  m_event_queue.erase(m_event_queue.begin());
  
  return true;
}

void event_queue_t::post_event(event_t event)
{
  m_event_queue.push_back(event);
}
