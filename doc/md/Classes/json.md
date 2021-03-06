```c++
jsoncons::json

typedef basic_json<char,
                   JsonTraits = json_traits<char>,
                   Allocator = std::allocator<char>> json
```
The `json` class is an instantiation of the `basic_json` class template that uses `char` as the character type. The order of an object's name/value pairs is not preserved, they are sorted alphabetically by name. If you want to preserve the original insertion order, use [ojson](ojson) instead.

The `jsoncons` library will always rebind the supplied allocator from the template parameter to internal data structures.

### Header
```c++
#include <jsoncons/json.hpp>
```

### Member types

Member type                         |Definition
------------------------------------|------------------------------
`json_type`|json type
`allocator_type`|Allocator type
`char_allocator`|String allocator type
`array_allocator`|Array allocator type
`object_allocator`|Object allocator 
`string_view_type`|A non-owning view of a string, holds a pointer to character data and length. Supports conversion to and from strings. Will be typedefed to the C++ 17 [string view](http://en.cppreference.com/w/cpp/string/basic_string_view) if `JSONCONS_HAS_STRING_VIEW` is defined in `jsoncons_config.hpp`, otherwise proxied.  
`key_value_pair_type`|[key_value_pair_type](key_value_pair_type) is a class that stores a name and a json value
`null_type`|An alias for `jsoncons::null_type`
`object`|json object type
`array`|json array type
`object_iterator`|A [RandomAccessIterator](http://en.cppreference.com/w/cpp/concept/RandomAccessIterator) to [key_value_pair_type](key_value_pair_type)
`const_object_iterator`|A const [RandomAccessIterator](http://en.cppreference.com/w/cpp/concept/RandomAccessIterator) to const [key_value_pair_type](key_value_pair_type)
`array_iterator`|A [RandomAccessIterator](http://en.cppreference.com/w/cpp/concept/RandomAccessIterator) to `json`
`const_array_iterator`|A const [RandomAccessIterator](http://en.cppreference.com/w/cpp/concept/RandomAccessIterator) to `const json`

### Static member functions

<table border="0">
  <tr>
    <td><a href="json%20parse">parse</a></td>
    <td>Parses JSON.</td> 
  </tr>
  <tr>
    <td><a href="json%20make_array">make_array</a></td>
    <td>Makes a multidimensional json array.</td> 
  </tr>
</table>

    static const json& null()
Returns a null value        

### Constructors

    json()
Constructs an empty json object. 

    json(const allocator_type& allocator)
Constructs a json object. 

    json(std::initializer_list<json> list, const allocator_type& allocator)
Constructs a json array with the elements of the initializer-list `init`. 

    json(const json& val)
Constructs a copy of val

    json(const json& val, const allocator_type& allocator)
Copy with allocator

    json(json&& val) noexcept
Acquires the contents of val, leaving val a `null` value

    json(json&& val, const allocator_type& allocator) 
Move with allocator

    template <class T>
    json(const T& val, const allocator_type& allocator=allocator_type())
Constructs a `json` value for types supported in [json_type_traits](json_type_traits).

    template <class T>
    json(const CharT* val, const allocator_type& allocator=allocator_type())
Constructs a `json` value for string literals.

    template <class InputIterator>
    json(InputIterator first, InputIterator last, 
         const allocator_type& allocator=allocator_type())

Constructs a json array with the elements in the range [first,last).

### Destructor

    ~json()
Destroys all values and deletes all memory allocated for strings, arrays, and objects.

### Assignment operator

    json& operator=(const json& rhs)
    json& operator=(json&& rhs) noexcept
Assigns a new `json` value to a `json` variable, replacing it's current contents.

    template <class T>
    json& operator=(const T& rhs)
Assigns the templated value to a `json` variable using [json_type_traits](json_type_traits).

    json& operator=(const char_type* rhs)

### Ranges and Iterators

<table border="0">
  <tr>
    <td><a href="json%20array_range">array_range</a></td>
    <td>Returns a "range" that supports a range-based for loop over the elements of a `json` array.</td> 
  </tr>
  <tr>
    <td><a href="json%20object_range">obect_range</a></td>
    <td>Returns a "range" that supports a range-based for loop over the key-value pairs of a `json` object.</td> 
  </tr>
</table>

### Capacity

    size_t size() const noexcept
Returns the number of elements in a json array, or the number of members in a json object, or `zero`

    bool empty() const noexcept
Returns `true` if a json string, object or array has no elements, otherwise `false`.

    size_t capacity() const
Returns the size of the storage space currently allocated for a json object or array.

    void reserve(size_t n)
Increases the capacity of a json object or array to allow at least `n` members or elements. 

    void resize(size_t n)
Resizes a json array so that it contains `n` elements. 

    void resize(size_t n, const json& val)
Resizes a json array so that it contains `n` elements that are initialized to `val`. 

### Accessors

    bool has_key(string_view_type name) const
Returns `true` if an object has a member with the given `name`, otherwise `false`.    

    size_t count(string_view_type name) const
Returns the number of object members that match `name`.    

<table border="0">
  <tr>
    <td><a href="json%20is">is</a></td>
    <td>Checks if a json value matches a type.</td> 
  </tr>
  <tr>
    <td><a href="json%20as">as</a></td>
    <td>Attempts to convert a json value to a value of a type.</td> 
  </tr>
</table>

    bool is_null() const noexcept
    bool is_string() const noexcept
    bool is_number() const noexcept
    bool is_integer() const noexcept
    bool is_uinteger() const noexcept
    bool is_double() const noexcept
    bool is_bool() const noexcept
    bool is_object() const noexcept
    bool is_array() const noexcept
Non-generic versions of `is_` methods

    bool as_bool() const
    int64_t as_integer() const
    uint64_t as_uinteger() const
    double as_double() const
    string_view_type as_string_view() const
    unsigned int as<unsigned int> const 
Non-generic versions of `as` methods

    json& operator[](size_t i)
    const json& operator[](size_t i) const
Returns a reference to the value at position i in a json object or array.
Throws `std::runtime_error` if not an object or array.

    json& operator[](string_view_type name)
Returns a proxy to a keyed value. If written to, inserts or updates with the new value. If read, evaluates to a reference to the keyed value, if it exists, otherwise throws. 
Throws `std::runtime_error` if not an object.
If read, throws `std::out_of_range` if the object does not have a member with the specified name.  

    const json& operator[](string_view_type name) const
If `name` matches the name of a member in the json object, returns a reference to the json object, otherwise throws.
Throws `std::runtime_error` if not an object.
Throws `std::out_of_range` if the object does not have a member with the specified name.  

    object_iterator find(string_view_type name)
    const_object_iterator find(string_view_type name) const
Returns an object iterator to a member whose name compares equal to `name`. If there is no such member, returns `end_member()`.
Throws `std::runtime_error` if not an object.

    json& at(string_view_type name)
    const json& at(string_view_type name) const
Returns a reference to the value with the specifed name in a json object.
Throws `std::runtime_error` if not an object.
Throws `std::out_of_range` if the object does not have a member with the specified name.  

    json& at(size_t i)
    const json& at(size_t i) const
Returns a reference to the element at index `i` in a json array.  
Throws `std::runtime_error` if not an array.
Throws `std::out_of_range` if the index is outside the bounds of the array.  

    template <class T>
    T get_with_default(string_view_type name, 
                       const T& default_val) const
If `name` matches the name of a member in the json object, returns the member value converted to the default's data type, otherwise returns `default_val`.
Throws `std::runtime_error` if not an object.

    const char_type* get_with_default(string_view_type name, 
                                      const char_type* default_val) const
Make `get_with_default` do the right thing for string literals.

### Modifiers

    void clear()
Remove all elements from an array or object value, otherwise do nothing

    void erase(array_iterator first, array_iterator last)
Remove the elements from an array in the range '[first,last)'.
Throws `std::runtime_error` if not an object.

    void erase(object_iterator first, object_iterator last)
Remove the members from an object in the range '[first,last)'.
Throws `std::runtime_error` if not an object.

    void erase(string_view_type name)
Remove a member with the specified name from an object
Throws `std::runtime_error` if not an object.

    void shrink_to_fit()
Requests the removal of unused capacity.

<table border="0">
  <tr>
    <td><a href="json%20add">add</a></td>
    <td>Adds a value to a json array</td> 
  </tr>
  <tr>
    <td><a href="json%20emplace_back">emplace_back</a></td>
    <td>Constructs a value in place at the end of a json array</td> 
  </tr>
  <tr>
    <td><a href="json%20emplace">emplace</a></td>
    <td>Constructs a value in place before a specified position in a json array</td> 
  </tr>
  <tr>
    <td><a href="json%20try_emplace">try_emplace</a></td>
    <td>Constructs a key-value pair in place in a json object if the key does not exist, does nothing if the key exists</td> 
  </tr>
  <tr>
    <td><a href="json%20set">set</a></td>
    <td>Inserts a key-value pair in a json object if the key does not exist, or assigns a new value if the key already exists</td> 
  </tr>
</table>

    void swap(json& val)
Exchanges the content of the `json` value with the content of `val`, which is another `json` value.

### Relational operators

    bool operator==(const json& rhs) const
Returns `true` if two json objects compare equal, `false` otherwise.

    bool operator!=(const json& rhs) const
Returns `true` if two json objects do not compare equal, `false` otherwise.

### Serialization

    template <class SAllocator>
    void dump(std::basic_string<char_type,char_traits_type,SAllocator>& s) const
Inserts json value into string using default serialization_options.

    template <class SAllocator>
    void dump(std::basic_string<char_type,char_traits_type,SAllocator>& s, 
              const serialization_options& options) const
Inserts json value into string using specified [serialization_options](serialization_options).

    void dump(basic_json_output_handler<char_type>& output_handler) const
Calls `begin_json()` on `output_handler`, emits json value to `output_handler`, and calls `end_json()` on `output_handler`.

    void dump(std::ostream& os) const
Inserts json value into stream with default serialization options.

    void dump(std::ostream<CharT> os, const serialization_options& options) const
Inserts json value into stream using specified [serialization_options](serialization_options).

    void dump_body(json_output_handler& handler) const
Emits JSON events for JSON objects, arrays, object members and array elements to a [json_output_handler](json_output_handler), such as a [json_serializer](json_serializer).

### Non member functions

    std::istream& operator>> (std::istream& os, json& val)
Reads a `json` value from a stream.

    std::ostream& operator<< (std::ostream& os, const json& val)
Inserts json value into stream.

    std::ostream& print(const json& val)  
    std::ostream& print(const json& val, const serialization_options<CharT>& options)  
Inserts json value into stream using the specified [serialization_options](serialization_options) if supplied.

    std::ostream& pretty_print(const json& val)  
    std::ostream& pretty_print(const json& val, const serialization_options<CharT>& options)  
Inserts json value into stream using the specified [serialization_options](serialization_options) if supplied.

    void swap(json& a, json& b)
Exchanges the values of `a` and `b`

### Deprecated names

As the `jsoncons` library has evolved, names have sometimes changed. To ease transition, jsoncons deprecates the old names but continues to support many of them. See the [deprecated list](deprecated) for the status of old names. The deprecated names can be suppressed by defining macro JSONCONS_NO_DEPRECATED, which is recommended for new code.

### See also

- [ojson](ojson) constructs a json value that preserves the original name-value insertion order

- [wjson](wjson) constructs a wide character json value that sorts name-value members alphabetically

- [wojson](wojson) constructs a wide character json value that preserves the original name-value insertion order

## Examples
  
### Accessors and defaults
```c++
json val;

val["field1"] = 1;
val["field3"] = "Toronto";

double x1 = obj.has_key("field1") ? val["field1"].as<double>() : 10.0;
double x2 = obj.has_key("field2") ? val["field2"].as<double>() : 20.0;

std::string x3 = obj.get_with_default("field3","Montreal");
std::string x4 = obj.get_with_default("field4","San Francisco");

std::cout << "x1=" << x1 << '\n';
std::cout << "x2=" << x2 << '\n';
std::cout << "x3=" << x3 << '\n';
std::cout << "x4=" << x4 << '\n';
```
Output:
```c++
x1=1
x2=20
x3=Toronto
x4=San Francisco
```
### Nulls
```c++
json obj;
obj["field1"] = json::null();
std::cout << obj << std::endl;
```
Output: 
```json
{"field1":null}
```
### Array from std::vector
```c++
std::vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);

json arr(v.begin(),v.end());

std::cout << arr << std::endl;
```
Output: 
```json
[10,20,30]
```
### Constructing json structures
```c++
json root;

root["persons"] = json::array();

json person;
person["first_name"] = "John";
person["last_name"] = "Smith";
person["birth_date"] = "1972-01-30";

json address;
address["city"] = "Toronto";
address["country"] = "Canada";

person["address"] = std::move(address);

root["persons"].add(std::move(person));

std::cout << pretty_print(root) << std::endl;
```
Output:
```c++
{
    "persons":
    [
        {
            "address":
            {
                "city":"Toronto",
                "country":"Canada"
            },
            "birth_date":"1972-01-30",
            "first_name":"John",
            "last_name":"Smith"
        }
    ]
}
```
