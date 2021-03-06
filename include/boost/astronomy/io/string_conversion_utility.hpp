/*=============================================================================
Copyright 2020 Gopi Krishna Menon <krishnagopi487.github@outlook.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_IO_STRING_CONVERSION_UTILITY_HPP
#define BOOST_ASTRONOMY_IO_STRING_CONVERSION_UTILITY_HPP

#include <sstream>
#include <boost/spirit/include/qi.hpp>
#include <boost/type.hpp>
#include <boost/astronomy/exception/fits_exception.hpp>



namespace boost{namespace astronomy{namespace io{

    /**
     * @brief Used for serialization and deserialization of ASCII table's data
    */
    struct ascii_converter {
    private:
       static boost::spirit::qi::int_type spirit_type(boost::type<int>) { return boost::spirit::qi::int_; }
       static boost::spirit::qi::uint_type spirit_type(boost::type<unsigned int>) { return boost::spirit::qi::uint_; }
       static boost::spirit::qi::float_type spirit_type(boost::type<float>) { return boost::spirit::qi::float_; }
       static boost::spirit::qi::double_type spirit_type(boost::type<double>) { return boost::spirit::qi::double_; }
       static boost::spirit::qi::long_long_type spirit_type(boost::type<long long>) { return boost::spirit::qi::long_long; }
       static boost::spirit::qi::ulong_long_type spirit_type(boost::type<long unsigned int>) { return boost::spirit::qi::ulong_long; }
       static boost::spirit::qi::ulong_long_type spirit_type(boost::type<unsigned long long>) { return boost::spirit::qi::ulong_long; }
    public:

        /**
         * @brief Deserializes the ASCII data to the given type
         * @param[in] convert_str ASCII data to convert to given type
         * @tparam T type to deserialize the data to
         * @note The second parameter is basically the number of elements in given string
         *       but as ASCII table does not support multiple elements in single field it
         *       is left blank ( To comply to the compile time interface )
        */
        template<typename T>
        static T deserialize_to(const std::string& convert_str, int) {

            T converted_value;
            auto iter_pos = convert_str.begin();
            boost::spirit::qi::parse(iter_pos, convert_str.end(), spirit_type(boost::type<T>()), converted_value);
            if (iter_pos != convert_str.end()) {

                throw invalid_cast("Cannot convert from String to the required Type");
            }

            return converted_value;
        }

        /**
         * @brief Serializes the value of given type to string
         * @param[in] value The value to be serialized
         * @tparam T Type of value which needs to be serialized
        */
        template<typename T>
       static std::string serialize(T value) {
            // Default for now future versions should use overloads for better performance
            std::stringstream serialize_stream;
            serialize_stream << value;
            return serialize_stream.str();
        }

    };

} } }


#endif
