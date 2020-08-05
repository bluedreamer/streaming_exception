#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>

class StreamingException : public std::runtime_error
{
public:
   StreamingException()
      : std::runtime_error("")
      , m_stream(std::make_shared<std::stringstream>())
      , m_message()
      , m_filename()
      , m_function()
      , m_line_number()
   {
   }
   StreamingException(std::string filename, std::string function, int line_number)
      : std::runtime_error("")
      , m_stream(std::make_shared<std::stringstream>())
      , m_message()
      , m_filename(std::move(filename))
      , m_function(std::move(function))
      , m_line_number(line_number)
   {
   }
   StreamingException(std::string function, int line_number)
      : std::runtime_error("")
      , m_stream(std::make_shared<std::stringstream>())
      , m_message()
      , m_filename()
      , m_function(std::move(function))
      , m_line_number(line_number)
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
      std::ostringstream location;
      if(m_filename && m_function && m_line_number)
      {
         location << m_filename.value() << ':' << m_function.value() << ':' << m_line_number.value() << ' ';
      }
      else if(m_function && m_line_number)
      {
         location << m_function.value() << ':' << m_line_number.value() << ' ';
      }
      auto loc_string = location.str();
      if(!loc_string.empty())
      {
         m_message = loc_string;
      }
      m_message += m_stream->str();
      return m_message.c_str();
   }

   auto filename() const noexcept -> std::string { return m_filename.value_or("not set"); }
   auto function() const noexcept -> std::string { return m_function.value_or("not set"); }
   auto line_number() const noexcept -> int { return m_line_number.value_or(-1); }

private:
   mutable std::shared_ptr<std::stringstream> m_stream;
   mutable std::string                        m_message;
   std::optional<std::string>                 m_filename;
   std::optional<std::string>                 m_function;
   std::optional<int>                         m_line_number;
};

// vim: ts=3 sw=3 ai et nohls mps=(\:),{\:},[\:],<\:> ff=unix ffs=unix bg=dark
