#include "include/toml.hpp"

Table::Table(const BasicValue& table) : m_table(table) {}

TOML_MAP Table::get() const {
  return this->m_table.as_table();
}

Table Table::required_table(const str& table) const {
  return Table(toml::find<BasicValue>(this->m_table, table));
}

opt<Table> Table::optional_table(const str& table) const {
  opt<Table> table_;
  try {
    table_ = Table(toml::find<BasicValue>(this->m_table, table));
  } catch (const std::out_of_range& e) {
    table_ = std::nullopt;
  }

  return table_;
}

template <typename P>
P Table::required(const str& key) const {
  return toml::find<P>(this->m_table, key);
}

template toml::string Table::required<toml::string>(const str&) const;
template toml::integer Table::required<toml::integer>(const str&) const;

template <typename P>
opt<P> Table::optional(const str& key) const {
  opt<P> optional_;
  try {
    optional_ = toml::find<P>(this->m_table, key);
  } catch (const std::out_of_range& e) {
    optional_ = std::nullopt;
  }

  return optional_;
}

template opt<toml::string> Table::optional<toml::string>(const str&) const;