
// shared ptr, producer consumer


///Concurrency: 1 Part
/// What issues can be spotted in the following code? verbal answers only
 
#include <chrono>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <map>
 
std::mutex m;
std::condition_variable cv;
bool ready = false;
bool proceed  = false;
std::queue<int> messageQ;
 
void Producer()
{
   std::cout << "=== Producer" << std::endl;
   std::unique_lock lk(m);
   auto x = 1;
   while (true)
   {
      std::cout << "Producing message: " << x << std::endl;
      messageQ.push(++x);
      ready = true;
      lk.unlock();
      cv.notify_one();
      cv.wait(lk,[]{return proceed;});
   }
}
 
 
void Consumer()
{
   std::cout << "=== Consumer" << std::endl;
   std::unique_lock lk(m);
   cv.wait(lk,[]{return ready;});
   while (!messageQ.empty())
   {
      auto i = messageQ.front();
      std::cout << "Consuming message: " << i << std::endl;
      messageQ.pop();
      proceed = true;
      cv.notify_one();
   }
}
 
int main()
{
  /**Given a string containing shuffled letters from several concatenated words, where each word is a numeral
from 'zero' to 'nine' i.e. words from the set:
  {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" }
Write a program that outputs integers corresponding to the numerals that would appear used to form the jumbled
string. Integers must be sorted in ascending order.
 fotworu -> four(3 characters) five(3 character) one(2 characters) , four(2 characters), two(2 characters)    
Examples:
1. input: "eon", expected output: 1
2. input: "eowotn", expected output: 12
3. input: "ninezerothree", expected output: 039
4. input: "fvornuofiee", expected output: 145
*/


 
}