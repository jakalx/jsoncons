# Deprecated Features

As the `jsoncons` library has evolved, names have sometimes changed. To ease transition, jsoncons deprecates the old names but continues to support many of them.

In the table, <em>&#x2713;</em> indicates that the old name is still supported.

Category|Old name, now deprecated|<em>&#x2713;</em>|Recommendation
--------|-----------|--------------|---
class json|add(size_t index, const json& val)|<em>&#x2713;</em>|Use add(array_iterator pos, const json& val)
    |add(size_t index, json&& val)|<em>&#x2713;</em>|Use add(array_iterator pos, json&& val)
    |remove_range(size_t from_index, size_t to_index)|<em>&#x2713;</em>|erase(array_iterator first, array_iterator last)
    |remove(const std::string& name)|<em>&#x2713;</em>|Use erase(const std::string& name)
    |parse(std::istream& is)|<em>&#x2713;</em>|Use parse_stream(std::istream& is)
    |parse(std::istream& is, parse_error_handler& err_handler)|<em>&#x2713;</em>|Use parse_stream(std::istream& is, parse_error_handler& err_handler)
    |as_longlong() const|<em>&#x2713;</em>|Use as_integer or `as<long long>`
    |as_ulonglong() const|<em>&#x2713;</em>|Use as_uinteger or `as<unsigned long long>`
    |is_longlong() const|<em>&#x2713;</em>|Use is_integer() or is<long long>()
    |is_ulonglong() const|<em>&#x2713;</em>|Use is_uinteger() or is<unsigned long long>()
    |is_numeric() const|<em>&#x2713;</em>|Use `is_number()`
    |remove_member(const std::string& name)|<em>&#x2713;</em>|Use erase(const std::string& name)
    |const json& get(const std::string& name) const|<em>&#x2713;</em>|Use const json get(const std::string& name, T default_val) const with default `json::null_type()`
    |has_member(const std::string& name) const|<em>&#x2713;</em>|Use count(const std::string& name)
    |begin_members()|<em>&#x2713;</em>|Use members().begin()
    |begin_members() const|<em>&#x2713;</em>|Use members().begin()
    |end_members()|<em>&#x2713;</em>|Use members().end()
    |end_members() const|<em>&#x2713;</em>|Use members().end()
    |begin_elements()|<em>&#x2713;</em>|Use elements().begin()
    |begin_elements() const|<em>&#x2713;</em>|Use elements().begin()
    |end_elements()|<em>&#x2713;</em>|Use elements().end()
    |end_elements() const|<em>&#x2713;</em>|Use elements().end()
    |is_empty() const|<em>&#x2713;</em>|Use `empty()`
    |parse_string(const std::string& s)|<em>&#x2713;</em>|parse(const std::string& s)
    |parse_string(const std::string& s,parse_error_handler& err_handler)|<em>&#x2713;</em>|Use parse(const std::string& s,parse_error_handler& err_handler)
    |resize_array(size_t n)|<em>&#x2713;</em>|resize(size_t n)
    |resize_array(size_t n, const json& val)|<em>&#x2713;</em>|Use resize(size_t n, const json& val)
json member constants|null|<em>&#x2713;</em>|Use assignment to `jsoncons::null_type()` or `json::null_type()`
    |an_object|<em>&#x2713;</em>|Use the default constructor `json()` instead.
    |an_array|<em>&#x2713;</em>|Use assignment to `json::array()` or `json::make_array()` instead.
class json_deserializer|json& root()|<em>&#x2713;</em>|json get_result()
class json_reader|read()|<em>&#x2713;</em>|Use read_next()
    |max_depth() const|<em>&#x2713;</em>|Use max_nesting_depth() const
    |max_depth(depth)|<em>&#x2713;</em>|Use max_nesting_depth() const
    |json_input_handler& parent()|<em>&#x2713;</em>|Use json_input_handler& input_handler()
json_input_handler class|do_longlong_value(|value, const parsing_context& context)||Override do_integer_value(int64_t value, const parsing_context& context)
    |do_ulonglong_value(|value, const parsing_context& context)||Removed, override do_uinteger_value(uint64_t value, const parsing_context& context)
json_output_handler class|do_longlong_value(|value)||Removed, override do_integer_value(int64_t value)
    |do_ulonglong_value(|value)||Override do_uinteger_value(uint64_t value)

