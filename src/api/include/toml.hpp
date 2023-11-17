#ifndef __TOML_API_H
#define __TOML_API_H

#include <iostream>
#include <toml.hpp>

#include "../../typedefs.hpp"

class Table {
 private:
  BasicValue m_table;
 public:
  Table(const BasicValue& table);
  TOML_MAP get() const;
  Table required_table(const str& table) const;
  opt<Table> optional_table(const str& table) const;
  template <typename P>
  P required(const str& key) const;
  template <typename P>
  opt<P> optional(const str& key) const;
};

#endif