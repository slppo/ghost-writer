#ifndef TOJ_TRIE_HPP
#define TOJ_TRIE_HPP

#include <vector>
#include <memory>
#include <string>

namespace toj
{
  class Trie
  {
  public:
    class Node
    {
      friend class Trie;
      typedef std::unique_ptr<Node> ptr_t;
    private:
      bool HasChildren_() const { return !children_.empty(); }

      char value_;
      std::vector<ptr_t> children_;
    };
    
    Trie();
    bool Contains(const std::string &word) const;
    void Insert(const std::string &word);
  private:
    bool CheckIsValid_(const std::string &word) const;

    Node roots_[26];
  };
}

#endif
