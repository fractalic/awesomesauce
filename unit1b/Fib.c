#include "Fib.h"

int Fibonacci_GetElement(int num)
{
   int i;
   int first = 1;
   int second = 1;
   int next;

   if (i <= 1)
     return 1;
   for (i = 2; i < num; i++)
   {
     next = first + second;
     first = second;
     second = next;
   }

   return next;
}
