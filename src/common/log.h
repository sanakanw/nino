#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <iostream>
#include <functional>

#define LOG(fn) (log_t(fn).get_stream())
#define LOG_DEBUG() (log_t(log_debug).get_stream() << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": ")
#define LOG_ERROR() (log_t(log_error).get_stream() << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": ")

class log_t {
  using logfunc_t = std::function<void(const std::string&)>;

private:
  logfunc_t           m_log_function;
  std::ostringstream  m_string_stream;

public:
  explicit log_t(logfunc_t log_function)
    : m_log_function(std::move(log_function))
  {
    
  }
  
  ~log_t()
  {
    m_log_function(m_string_stream.str());
  }
  
  std::ostringstream& get_stream()
  {
    return m_string_stream;
  }
};

void log_debug(const std::string &str);
void log_error(const std::string &str);

#endif
