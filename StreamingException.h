#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

class StreamingException : public std::runtime_error
{
public:
   StreamingException()
      : std::runtime_error("")
      , m_stream(std::make_shared<std::stringstream>())
      , m_message()
   {
   }
   StreamingException(const StreamingException &) = default;
   StreamingException(StreamingException &&)      = default;
   StreamingException &operator=(const StreamingException &) = default;
   StreamingException &operator=(StreamingException &&) = default;
   ~StreamingException() noexcept override              = default;

   template<typename T>
   auto operator<<(const T &value) noexcept -> StreamingException &
   {
      (*m_stream) << value;
      return *this;
   }

   auto what() const noexcept -> const char * override
   {
      m_message = m_stream->str();
      return m_message.c_str();
   }

private:
   mutable std::shared_ptr<std::stringstream> m_stream;
   mutable std::string                        m_message;
};

// vim: ts=3 sw=3 ai et nohls mps=(\:),{\:},[\:],<\:> ff=unix ffs=unix bg=dark
