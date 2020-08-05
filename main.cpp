#include <iostream>

#include "StreamingException.h"

auto function() -> void;
auto function2() -> void;
auto function3() -> void;
auto function4() -> void;

auto test(void (*function)()) -> void;

auto main(int argc, char *argv[]) -> int
{
   (void)argc;
   (void)argv;

   test(function);
   test(function2);
   test(function3);
   test(function4);

   return 0;
}

auto test(void (*function)()) -> void
{
   try
   {
      function();
   }
   catch(const std::exception &e)
   {
      std::cout << "Exception: " << e.what() << std::endl;
   }
}

auto function() -> void
{
   int         i{42};
   double      d{3.142};
   std::string s{"I kanna do it Captain!"};

   throw StreamingException() << "This is my error: " << i << ", " << d << " because: " << s;
}

auto function2() -> void
{
   int         i{42};
   double      d{3.142};
   std::string s{"I kanna do it Captain!"};

   throw StreamingException(__FILE__, __func__, __LINE__) << "This is my error: " << i << ", " << d << " because: " << s;
}

auto function3() -> void
{
   int         i{42};
   double      d{3.142};
   std::string s{"I kanna do it Captain!"};

   throw StreamingException(__FILE__, __PRETTY_FUNCTION__, __LINE__) << "This is my error: " << i << ", " << d << " because: " << s;
}

auto function4() -> void
{
   int         i{42};
   double      d{3.142};
   std::string s{"I kanna do it Captain!"};

   throw StreamingException(__PRETTY_FUNCTION__, __LINE__) << "This is my error: " << i << ", " << d << " because: " << s;
}

// vim: ts=3 sw=3 ai et nohls mps=(\:),{\:},[\:],<\:> ff=unix ffs=unix bg=dark
