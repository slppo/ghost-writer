#include "Trie.hpp"
#include <cstddef>
#include <stdexcept>

namespace toj
{
  Trie::Trie() 
  {
    for(char ch = 'a'; ch <= 'z'; ++ch)
      roots_[static_cast<std::size_t>(ch-'a')].value_ = ch;
  }

  bool Trie::Contains(const std::string &word) const
  {
    if(!CheckIsValid_(word)) return false;
    const Node &root = roots_[static_cast<std::size_t>(
      std::tolower(word.front())-'a')];
    const Node *node = &root;
    for(auto it = word.begin() + 1; it != word.end(); ++it)
    {
      for(const Node::ptr_t &p : node->children_)
      {
        if(p->value_ == *it)
        {
          node = p.get();
          goto next_letter;
        }
      }
      return false;
      next_letter:
      ;
    }
    return node->children_.empty();
  }

  void Trie::Insert(const std::string &word)
  {
    if(Contains(word))
      return;
    if(!CheckIsValid_(word)) 
      throw std::runtime_error("Inserting invalid word " + word);
    Node &root = roots_[static_cast<std::size_t>(
      std::tolower(word.front())-'a')];
    Node *node = &root;
    for(auto it = word.begin() + 1; it != word.end(); ++it)
    {
      for(Node::ptr_t &p : node->children_)
      {
        if(p->value_ == *it)
        {
          node = p.get();          
          goto next_letter;
        }
      }
      node->children_.push_back(Node::ptr_t(new Node()));
      node->children_.back()->value_ = *it;
      node = node->children_.back().get();
      next_letter:
      ;
    }
  }

  bool Trie::CheckIsValid_(const std::string &word) const
  {
    if(word.empty()) return false;
    for(char ch : word)
      if(!std::islower(ch))
        return false;
    return true;
  }
}
