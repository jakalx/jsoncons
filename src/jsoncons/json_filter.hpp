// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSON_FILTER_HPP
#define JSONCONS_JSON_FILTER_HPP

#include <string>
#include <functional>
#include <jsoncons/json_input_handler.hpp>
#include <jsoncons/json_output_handler.hpp>
#include <jsoncons/parse_error_handler.hpp>

namespace jsoncons {

template <class CharT>
class basic_json_input_output_adapter : public basic_json_input_handler<CharT>
{
private:

    basic_null_json_output_handler<CharT> null_output_handler_;
    basic_json_output_handler<CharT>* output_handler_;
    basic_json_input_handler<CharT>* input_handler_;

    basic_json_input_output_adapter<CharT>(const basic_json_input_output_adapter<CharT>&) = delete;
    basic_json_input_output_adapter<CharT>& operator=(const basic_json_input_output_adapter<CharT>&) = delete;

public:
    basic_json_input_output_adapter()
        : output_handler_(&null_output_handler_)
    {
    }

    basic_json_input_output_adapter(basic_json_output_handler<CharT>& handler)
        : output_handler_(std::addressof(handler))
    {
    }

private:

    void do_begin_json() override
    {
        output_handler_->begin_json();
    }

    void do_end_json() override
    {
        output_handler_->end_json();
    }

    void do_begin_object(const basic_parsing_context<CharT>&) override
    {
        output_handler_->begin_object();
    }

    void do_end_object(const basic_parsing_context<CharT>&) override
    {
        output_handler_->end_object();
    }

    void do_begin_array(const basic_parsing_context<CharT>&) override
    {
        output_handler_->begin_array();
    }

    void do_end_array(const basic_parsing_context<CharT>&) override
    {
        output_handler_->end_array();
    }

    void do_name(const CharT* name, size_t length, 
                 const basic_parsing_context<CharT>&) override
    {
        output_handler_->name(name, length);
    }

    void do_string_value(const CharT* value, size_t length, 
                         const basic_parsing_context<CharT>&) override
    {
        output_handler_->value(value, length);
    }

    void do_integer_value(int64_t value, const basic_parsing_context<CharT>&) override
    {
        output_handler_->value(value);
    }

    void do_uinteger_value(uint64_t value, 
                           const basic_parsing_context<CharT>&) override
    {
        output_handler_->value(value);
    }

    void do_double_value(double value, uint8_t precision, const basic_parsing_context<CharT>&) override
    {
        output_handler_->value(value, precision);
    }

    void do_bool_value(bool value, const basic_parsing_context<CharT>&) override
    {
        output_handler_->value(value);
    }

    void do_null_value(const basic_parsing_context<CharT>&) override
    {
        output_handler_->value(null_type());
    }
};

template <class CharT>
class basic_json_output_input_adapter : public basic_json_output_handler<CharT>
{
private:
    class null_parsing_context : public parsing_context
    {
        size_t do_line_number() const override { return 0; }

        size_t do_column_number() const override { return 0; }

        char do_current_char() const override { return '\0'; }
    };
    const null_parsing_context default_context_;

    basic_null_json_input_handler<CharT> null_input_handler_;
    basic_json_input_output_adapter<CharT> default_input_output_adapter_;
    basic_json_input_handler<CharT>* input_handler_;
    const basic_json_input_output_adapter<CharT>* input_output_adapter_ptr_;

    basic_json_output_input_adapter<CharT>(const basic_json_output_input_adapter<CharT>&) = delete;
    basic_json_output_input_adapter<CharT>& operator=(const basic_json_output_input_adapter<CharT>&) = delete;

public:
    basic_json_output_input_adapter()
        : input_handler_(&null_input_handler_),
          input_output_adapter_ptr_(std::addressof(default_input_output_adapter_))
    {
    }
    basic_json_output_input_adapter(basic_json_input_handler<CharT>& input_handler)
        : input_handler_(std::addressof(input_handler)),
          input_output_adapter_ptr_(std::addressof(default_input_output_adapter_))
    {
    }
    basic_json_output_input_adapter(basic_json_input_handler<CharT>& input_handler,
                                    const basic_json_input_output_adapter<CharT>& input_output_adapter)
        : input_handler_(std::addressof(input_handler)),
          input_output_adapter_ptr_(std::addressof(input_output_adapter))
    {
    }

private:

    void do_begin_json() override
    {
        input_handler_->begin_json();
    }

    void do_end_json() override
    {
        input_handler_->end_json();
    }

    void do_begin_object() override
    {
        input_handler_->begin_object(default_context_);
    }

    void do_end_object() override
    {
        input_handler_->end_object(default_context_);
    }

    void do_begin_array() override
    {
        input_handler_->begin_array(default_context_);
    }

    void do_end_array() override
    {
        input_handler_->end_array(default_context_);
    }

    void do_name(const CharT* name, size_t length) override
    {
        input_handler_->name(name, length, default_context_);
    }

    void do_string_value(const CharT* value, size_t length) override
    {
        input_handler_->value(value, length, default_context_);
    }

    void do_integer_value(int64_t value) override
    {
        input_handler_->value(value, default_context_);
    }

    void do_uinteger_value(uint64_t value) override
    {
        input_handler_->value(value, default_context_);
    }

    void do_double_value(double value, uint8_t precision) override
    {
        input_handler_->value(value, precision, default_context_);
    }

    void do_bool_value(bool value) override
    {
        input_handler_->value(value, default_context_);
    }

    void do_null_value() override
    {
        input_handler_->value(null_type(), default_context_);
    }
};

template <class CharT>
class basic_json_filter : public basic_json_input_handler<CharT>
{
private:
    basic_json_input_output_adapter<CharT> input_output_adapter_;
    basic_json_output_input_adapter<CharT> output_input_adapter_;
    basic_json_output_handler<CharT>* output_handler_;
    basic_json_input_handler<CharT>* downstream_handler_;

    basic_json_filter<CharT>(const basic_json_filter<CharT>&) = delete;
    basic_json_filter<CharT>& operator=(const basic_json_filter<CharT>&) = delete;
public:
    basic_json_filter(basic_json_output_handler<CharT>& handler)
        : input_output_adapter_(handler),
          output_input_adapter_(*this),
          output_handler_(std::addressof(output_input_adapter_)),
          downstream_handler_(std::addressof(input_output_adapter_))
    {
    }

    basic_json_filter(basic_json_input_handler<CharT>& handler)
        : output_input_adapter_(*this),
          output_handler_(std::addressof(output_input_adapter_)),
          downstream_handler_(std::addressof(handler))
    {
    }

    operator basic_json_output_handler<CharT>&() 
    { 
        return *output_handler_; 
    }

#if !defined(JSONCONS_NO_DEPRECATED)
    basic_json_input_handler<CharT>& input_handler()
    {
        return *downstream_handler_;
    }
#endif

    basic_json_input_handler<CharT>& downstream_handler()
    {
        return *downstream_handler_;
    }

private:
    void do_begin_json() override
    {
        downstream_handler_->begin_json();
    }

    void do_end_json() override
    {
        downstream_handler_->end_json();
    }

    void do_begin_object(const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->begin_object(context);
    }

    void do_end_object(const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->end_object(context);
    }

    void do_begin_array(const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->begin_array(context);
    }

    void do_end_array(const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->end_array(context);
    }

    void do_name(const CharT* name, size_t length,
                 const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->name(name, length,context);
    }

    void do_string_value(const CharT* value, size_t length,
                         const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->value(value,length,context);
    }

    void do_double_value(double value, uint8_t precision,
                 const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->value(value,precision,context);
    }

    void do_integer_value(int64_t value,
                 const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->value(value,context);
    }

    void do_uinteger_value(uint64_t value,
                 const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->value(value,context);
    }

    void do_bool_value(bool value,
                 const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->value(value,context);
    }

    void do_null_value(const basic_parsing_context<CharT>& context) override
    {
        downstream_handler_->value(null_type(),context);
    }

};

// Filters out begin_json and end_json events
template <class CharT>
class basic_json_body_filter : public basic_json_filter<CharT>
{
public:
    basic_json_body_filter(basic_json_input_handler<CharT>& handler)
        : basic_json_filter<CharT>(handler)
    {
    }
private:
    void do_begin_json() override
    {
    }

    void do_end_json() override
    {
    }
};

template <class CharT>
class basic_rename_name_filter : public basic_json_filter<CharT>
{
private:
    std::basic_string<CharT> name_;
    std::basic_string<CharT> new_name_;
public:
    basic_rename_name_filter(const std::basic_string<CharT>& name,
                             const std::basic_string<CharT>& new_name,
                             basic_json_output_handler<CharT>& handler)
        : basic_json_filter<CharT>(handler), 
          name_(name), new_name_(new_name)
    {
    }

    basic_rename_name_filter(const std::basic_string<CharT>& name,
                             const std::basic_string<CharT>& new_name,
                             basic_json_input_handler<CharT>& handler)
        : basic_json_filter<CharT>(handler), 
          name_(name), new_name_(new_name)
    {
    }

private:
    void do_name(const CharT* p, size_t length,
                 const basic_parsing_context<CharT>& context) override
    {
        size_t len = std::min JSONCONS_NO_MACRO_EXP(name_.length(),length);
        if (len == length && std::char_traits<CharT>::compare(name_.data(),p,len) == 0)
        {
            this->downstream_handler().name(new_name_.data(),new_name_.length(),context);
        }
        else
        {
            this->downstream_handler().name(p,length,context);
        }
    }
};

template <class CharT>
struct basic_json_filter_criteria
{
    basic_json_filter_criteria()
        : if_name([](const std::basic_string<CharT>&) {return true; }),
          if_index([](size_t) {return true; })
    {
    }
    std::function<bool(std::basic_string<CharT>)> if_name;
    std::function<bool(size_t)> if_index;
};

typedef basic_json_filter<char> json_filter;
typedef basic_json_filter<wchar_t> wjson_filter;
typedef basic_rename_name_filter<char> rename_name_filter;
typedef basic_rename_name_filter<wchar_t> wrename_name_filter;

}

#endif
