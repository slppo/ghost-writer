#include "Trie.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <vector>
#include <thread>

const std::size_t DiscardLength = 20;
const std::size_t AcceptLength = 4;
const std::string DictionaryFile = "dict";

// throws std::runtime_error
toj::Trie ReadDictionary(const std::string &file);
char RandomLowerAlpha();
void ThreadEntry();

toj::Trie dict = ReadDictionary(DictionaryFile);

int main()
{
  std::vector<std::thread> threads;
  for(std::size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    threads.push_back(std::thread(ThreadEntry));    
  threads.front().join();
  return 0;
}

toj::Trie ReadDictionary(const std::string &file)
{
  std::ifstream ifs(file);
  if(!ifs)
    throw std::runtime_error("Could not open " + file);

  toj::Trie dict;
  for(std::string word; std::getline(ifs, word);)
  {
    std::transform(word.begin(), word.end(), word.begin(), tolower);
    for(char ch : word)
      if(!islower(ch))
        goto next_word;
    dict.Insert(word);
    next_word:
    ;
  }
  return dict;
}

char RandomLowerAlpha()
{
  static std::random_device entropy;
  std::mt19937 rng(entropy());
  std::discrete_distribution<char> dist({8167, 1492, 2782, 4253, 12702, 2228, 
    2015, 6094, 6966, 153, 772, 4025, 2406, 6749, 7507, 1929, 95, 5987, 6327, 
    9056, 2758, 978, 2360, 150, 1974, 74});
  return dist(rng) + 'a';
}

void ThreadEntry()
{
  std::string word;
  while(true)
  {
    if(word.size() >= DiscardLength)
      word.clear();
    word += RandomLowerAlpha();
    if(word.size() >= AcceptLength && dict.Contains(word))
    { 
      std::cout << word << " " << std::flush;
      word.clear();
    }
  }
}
