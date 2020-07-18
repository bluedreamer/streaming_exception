#include <iostream>

#include "StreamingException.h"

auto function() -> void;

auto main(int argc, char *argv[]) -> int
{
   (void)argc;
   (void)argv;
   try
   {
      function();
   }
   catch(const std::exception &e)
   {
      std::cout << "Exception: " << e.what() << std::endl;
   }

   return 0;
}

auto function() -> void
{
   int         i{42};
   double      d{3.142};
   std::string s{"I kanna do it Captain!"};

   throw StreamingException() << "This is my error: " << i << ", " << d << " because: " << s;
}

// vim: ts=3 sw=3 ai et nohls mps=(\:),{\:},[\:],<\:> ff=unix ffs=unix bg=dark
