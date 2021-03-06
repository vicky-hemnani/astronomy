/*=============================================================================
Copyright 2018 Pranam Lashkari <plashkari628@gmail.com>
Copyright 2019 Sarthak Singhal <singhalsarthak2007@gmail.com>
Copyright 2020 Gopi Krishna Menon <krishnagopi487.github@outlook.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_IO_FITS_HPP
#define BOOST_ASTRONOMY_IO_FITS_HPP

#include <boost/variant.hpp>
#include <boost/astronomy/io/fits_reader.hpp>
#include <boost/astronomy/io/fits_stream.hpp>
#include <boost/astronomy/io/default_card_policy.hpp>
#include <boost/astronomy/io/string_conversion_utility.hpp>
#include <boost/astronomy/io/binary_data_converter.hpp>
#include <boost/astronomy/io/default_hdus.hpp>
#include <boost/astronomy/io/ascii_table.hpp>
#include <boost/astronomy/io/binary_table.hpp>
#include <boost/astronomy/io/primary_hdu.hpp>
#include <boost/astronomy/io/image_extension.hpp>
#include <boost/astronomy/io/binary_data_converter.hpp>
#include <boost/astronomy/io/string_conversion_utility.hpp>





namespace boost { namespace astronomy {namespace io {
  

    /**
     * @brief Represents the reading options for the user
    */
    enum class reading_options {
        read_only_headers,
        read_entire_hdus
    };

    /**
     * @brief Central class for handling the Reading and Writing Operations
     * @tparam FileReader Represents the reader class for reading related operations
     * @tparam ExtensionsSupported Contains the list of extensions along with their construction methods 
    */
    template<typename FileReader, typename ExtensionsSupported>
    struct basic_fits {
    private:
        typedef fits_io<FileReader, ExtensionsSupported> fitsreader;
    public:
        /**
         * @brief Constructs a default object of basic_fits
        */
        basic_fits() {}

        /**
         * @brief Opens a fits file for reading/writing and returns a reader object
         * @param[in] filepath Location of file
         * @param[in] reading_option Mode in which file should be read
        */
        static fitsreader open(const std::string& filepath, reading_options reading_option = reading_options::read_entire_hdus) {
            fitsreader f_reader(filepath);
            if (reading_option == reading_options::read_only_headers) {
                f_reader.read_only_headers();
            }
            else {
                f_reader.read_entire_hdus();
            }

            return f_reader;
        }

        /**
         * @brief Gets the hdu object from variant in which it is stored
         * @param[in] extension Variant holding the HDU object
         * @tparam    ConversionType Holding type
        */
        template<typename ConversionType>
        static ConversionType& convert_to(typename ExtensionsSupported::Extension& extension) {
            return boost::get<ConversionType>(extension);
        }
    };

    // Some common aliases for easy use
    using fits = basic_fits<fits_stream, default_hdu_manager<card_policy,ascii_converter,binary_data_converter>>;
    using ascii_table = basic_ascii_table<card_policy, ascii_converter>;
    using binary_table = basic_binary_table_extension<card_policy, binary_data_converter>;
    using primary_hdu = basic_primary_hdu<card_policy,binary_data_converter>;
    using image_extension = basic_image_extension<card_policy, binary_data_converter>;



        }
    }
}

#endif // !BOOST_ASTRONOMY_IO_FITS_HPP

