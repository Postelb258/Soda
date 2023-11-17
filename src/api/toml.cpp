#include "include/toml.hpp"

Table::Table(const BasicValue& table) : m_table(table) {}

TOML_MAP Table::get() const {
  return this->m_table.as_table();
}

Table Table::required_table(const std::string& table) const {
  return Table(toml::find<BasicValue>(this->m_table, table));
}

opt<Table> Table::optional_table(const std::string& table) const {
  opt<Table> table_;
  try {
    table_ = Table(toml::find<BasicValue>(this->m_table, table));
  } catch (const std::out_of_range& e) {
    table_ = std::nullopt;
  }

  return table_;
}

template <typename P>
P Table::required(const std::string& key) const {
  return toml::find<P>(this->m_table, key);
}
template <typename P>
opt<P> Table::optional(const std::string& key) const {
  opt<P> optional_;
  try {
    optional_ = toml::find<P>(this->m_table, key);
  } catch (const std::out_of_range& e) {
    optional_ = std::nullopt;
  }

  return optional_;
}