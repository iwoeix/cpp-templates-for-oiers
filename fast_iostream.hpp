#include <iostream>
#include <stdfloat>
#include <format>

namespace fast_io
{
    template<class CharT, class Traits = std::char_traits<CharT>>
        class basic_fast_istream;
    
    using fast_istream  = basic_fast_istream<char>;
    using fast_wistream = basic_fast_istream<wchar_t>;

    template<class CharT, class Traits = std::char_traits<CharT>>
        class basic_fast_iostream;
    
    using fast_iostream  = basic_fast_iostream<char>;
    using fast_wiostream = basic_fast_iostream<wchar_t>;
    
    template<class CharT, class Traits>
        basic_fast_istream<CharT, Traits>& ws(basic_fast_istream<CharT, Traits>& is);
    
    template<class Istream, class T>
    Istream&& operator>>(Istream&& is, T&& x);
}

namespace fast_io
{
    template<class CharT, class Traits = std::char_traits<CharT>>
    class basic_fast_istream : virtual public std::basic_istream<CharT, Traits>
    {
    public:
        // types (inherited from basic_istream)
        using char_type   = CharT;
        using int_type    = typename Traits::int_type;
        using pos_type    = typename Traits::pos_type;
        using off_type    = typename Traits::off_type;
        using traits_type = Traits;
    
        // constructor/destructor
        explicit basic_fast_istream(std::basic_streambuf<CharT, Traits>* sb);
        virtual ~basic_fast_istream();
    
        // prefix/suffix
        class sentry;
    
        // formatted input
        basic_fast_istream& operator>>(basic_fast_istream& (*pf)(basic_fast_istream&));
        basic_fast_istream& operator>>(std::basic_istream& (*pf)(std::basic_istream&));
        basic_fast_istream& operator>>(std::basic_ios<CharT, Traits>& (*pf)(std::basic_ios<CharT, Traits>&));
        basic_fast_istream& operator>>(std::ios_base& (*pf)(std::ios_base&));
    
        basic_fast_istream& operator>>(bool& n);
        basic_fast_istream& operator>>(short& n);
        basic_fast_istream& operator>>(unsigned short& n);
        basic_fast_istream& operator>>(int& n);
        basic_fast_istream& operator>>(unsigned int& n);
        basic_fast_istream& operator>>(long& n);
        basic_fast_istream& operator>>(unsigned long& n);
        basic_fast_istream& operator>>(long long& n);
        basic_fast_istream& operator>>(unsigned long long& n);
        basic_fast_istream& operator>>(float& f);
        basic_fast_istream& operator>>(double& f);
        basic_fast_istream& operator>>(long double& f);
        basic_fast_istream& operator>>(std::float16_t& f);
        basic_fast_istream& operator>>(std::float32_t& f);
        basic_fast_istream& operator>>(std::float64_t& f);
        basic_fast_istream& operator>>(std::float128_t& f);
    
        basic_fast_istream& operator>>(void*& p);
        basic_fast_istream& operator>>(std::basic_streambuf<char_type, Traits>* sb);
    
        // unformatted input
        streamsize gcount() const;
        int_type get();
        basic_fast_istream& get(char_type& c);
        basic_fast_istream& get(char_type* s, streamsize n);
        basic_fast_istream& get(char_type* s, streamsize n, char_type delim);
        basic_fast_istream& get(std::basic_streambuf<char_type, Traits>& sb);
        basic_fast_istream& get(std::basic_streambuf<char_type, Traits>& sb, char_type delim);
    
        basic_fast_istream& getline(char_type* s, streamsize n);
        basic_fast_istream& getline(char_type* s, streamsize n, char_type delim);
    
        basic_fast_istream& ignore(streamsize n = 1, int_type delim = Traits::eof());
        int_type            peek();
        basic_fast_istream& read    (char_type* s, streamsize n);
        streamsize          readsome(char_type* s, streamsize n);
    
        basic_fast_istream& putback(char_type c);
        basic_fast_istream& unget();
        int sync();
    
        pos_type tellg();
        basic_fast_istream& seekg(pos_type);
        basic_fast_istream& seekg(off_type, ios_base::seekdir);
    
    protected:
        // copy/move constructor
        basic_fast_istream(const basic_fast_istream&) = delete;
        basic_fast_istream(basic_fast_istream&& rhs);
    
        // assignment and swap
        basic_fast_istream& operator=(const basic_fast_istream&) = delete;
        basic_fast_istream& operator=(basic_fast_istream&& rhs);
        void swap(basic_fast_istream& rhs);
    };
    
    // character extraction templates
    template<class CharT, class Traits>
        basic_fast_istream<CharT, Traits>& operator>>(basic_fast_istream<CharT, Traits>&, CharT&);
    template<class Traits>
        basic_fast_istream<char, Traits>& operator>>(basic_fast_istream<char, Traits>&, unsigned char&);
    template<class Traits>
        basic_fast_istream<char, Traits>& operator>>(basic_fast_istream<char, Traits>&, signed char&);
    
    template<class CharT, class Traits, size_t N>
        basic_fast_istream<CharT, Traits>& operator>>(basic_fast_istream<CharT, Traits>&, CharT(&)[N]);
    template<class Traits, size_t N>
        basic_fast_istream<char, Traits>& operator>>(basic_fast_istream<char, Traits>&, unsigned char(&)[N]);
    template<class Traits, size_t N>
        basic_fast_istream<char, Traits>& operator>>(basic_fast_istream<char, Traits>&, signed char(&)[N]);
}

namespace fast_io
{
    template<class CharT, class Traits>
    class basic_fast_istream<CharT, Traits>::sentry
    {
        bool ok_;                      // exposition only
    public:
        explicit sentry(basic_fast_istream& is, bool noskipws = false);
        ~sentry();
        explicit operator bool() const { return ok_; }
        sentry(const sentry&) = delete;
        sentry& operator=(const sentry&) = delete;
    };
}

namespace fast_io
{
    template<class CharT, class Traits = std::char_traits<CharT>>
    class basic_fast_iostream
        : public basic_fast_istream<CharT, Traits>,
        public basic_fast_ostream<CharT, Traits>
    {
    public:
        using char_type   = CharT;
        using int_type    = typename Traits::int_type;
        using pos_type    = typename Traits::pos_type;
        using off_type    = typename Traits::off_type;
        using traits_type = Traits;
    
        // constructor
        explicit basic_fast_iostream(basic_streambuf<CharT, Traits>* sb);
    
        // destructor
        virtual ~basic_fast_iostream();
    
    protected:
        // constructor
        basic_fast_iostream(const basic_fast_iostream&) = delete;
        basic_fast_iostream(basic_fast_iostream&& rhs);
    
        // assignment and swap
        basic_fast_iostream& operator=(const basic_fast_iostream&) = delete;
        basic_fast_iostream& operator=(basic_fast_iostream&& rhs);
        void swap(basic_fast_iostream& rhs);
    };
}

namespace fast_io
{
    template<class CharT, class Traits = std::char_traits<CharT>>
        class basic_fast_ostream;
    
    using fast_ostream  = basic_fast_ostream<char>;
    using fast_wostream = basic_fast_ostream<wchar_t>;
    
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& endl(basic_fast_ostream<CharT, Traits>& os);
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& ends(basic_fast_ostream<CharT, Traits>& os);
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& flush(basic_fast_ostream<CharT, Traits>& os);
    
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& emit_on_flush(basic_fast_ostream<CharT, Traits>& os);
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& noemit_on_flush(basic_fast_ostream<CharT, Traits>& os);
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& flush_emit(basic_fast_ostream<CharT, Traits>& os);
    
    template<class Ostream, class T>
        Ostream&& operator<<(Ostream&& os, const T& x);
    
    // print functions
    template<class... Args>
        void print(fast_ostream& os, std::format_string<Args...> fmt, Args&&... args);
    template<class... Args>
        void println(fast_ostream& os, std::format_string<Args...> fmt, Args&&... args);
    
    void vprint_unicode(fast_ostream& os, std::string_view fmt, std::format_args args);
    void vprint_nonunicode(fast_ostream& os, std::string_view fmt, std::format_args args);
}

namespace fast_io
{
    template<class CharT, class Traits = std::char_traits<CharT>>
    class basic_fast_ostream : virtual public std::basic_ostream<CharT, Traits>
    {
    public:
        // types (inherited from basic_fast_ostream)
        using char_type   = CharT;
        using int_type    = typename Traits::int_type;
        using pos_type    = typename Traits::pos_type;
        using off_type    = typename Traits::off_type;
        using traits_type = Traits;
    
        // constructor/destructor
        explicit basic_fast_ostream(basic_streambuf<char_type, Traits>* sb);
        virtual ~basic_fast_ostream();
    
        // prefix/suffix
        class sentry;
    
        // formatted output
        basic_fast_ostream& operator<<(basic_fast_ostream& (*pf)(basic_fast_ostream&));
        basic_fast_ostream& operator<<(std::basic_ostream& (*pf)(std::asic_ostream&));
        basic_fast_ostream& operator<<(std::basic_ios<CharT, Traits>& (*pf)(std::basic_ios<CharT, Traits>&));
        basic_fast_ostream& operator<<(std::ios_base& (*pf)(std::ios_base&));
    
        basic_fast_ostream& operator<<(bool n);
        basic_fast_ostream& operator<<(short n);
        basic_fast_ostream& operator<<(unsigned short n);
        basic_fast_ostream& operator<<(int n);
        basic_fast_ostream& operator<<(unsigned int n);
        basic_fast_ostream& operator<<(long n);
        basic_fast_ostream& operator<<(unsigned long n);
        basic_fast_ostream& operator<<(long long n);
        basic_fast_ostream& operator<<(unsigned long long n);
        basic_fast_ostream& operator<<(float f);
        basic_fast_ostream& operator<<(double f);
        basic_fast_ostream& operator<<(long double f);
        basic_fast_ostream& operator<<(std::float16_t& f);
        basic_fast_ostream& operator<<(std::float32_t& f);
        basic_fast_ostream& operator<<(std::float64_t& f);
        basic_fast_ostream& operator<<(std::float128_t& f);
    
        basic_fast_ostream& operator<<(const void* p);
        basic_fast_ostream& operator<<(const volatile void* p);
        basic_fast_ostream& operator<<(nullptr_t);
        basic_fast_ostream& operator<<(std::basic_streambuf<char_type, Traits>* sb);
    
        // unformatted output
        basic_fast_ostream& put(char_type c);
        basic_fast_ostream& write(const char_type* s, streamsize n);
    
        basic_fast_ostream& flush();
    
        // seeks
        pos_type tellp();
        basic_fast_ostream& seekp(pos_type);
        basic_fast_ostream& seekp(off_type, std::ios_base::seekdir);
    
    protected:
        // copy/move constructor
        basic_fast_ostream(const basic_fast_ostream&) = delete;
        basic_fast_ostream(basic_fast_ostream&& rhs);
    
        // assignment and swap
        basic_fast_ostream& operator=(const basic_fast_ostream&) = delete;
        basic_fast_ostream& operator=(basic_fast_ostream&& rhs);
        void swap(basic_fast_ostream& rhs);
    };
    
    // character inserters
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& operator<<(basic_fast_ostream<CharT, Traits>&, CharT);
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& operator<<(basic_fast_ostream<CharT, Traits>&, char);
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&, char);
    
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&, signed char);
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&, unsigned char);
    
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&,
                                                wchar_t) = delete;
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&,
                                                char8_t) = delete;
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&,
                                                char16_t) = delete;
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&,
                                                char32_t) = delete;
    template<class Traits>
        basic_fast_ostream<wchar_t, Traits>&
            operator<<(basic_fast_ostream<wchar_t, Traits>&, char8_t) = delete;
    template<class Traits>
        basic_fast_ostream<wchar_t, Traits>&
            operator<<(basic_fast_ostream<wchar_t, Traits>&, char16_t) = delete;
    template<class Traits>
        basic_fast_ostream<wchar_t, Traits>&
            operator<<(basic_fast_ostream<wchar_t, Traits>&, char32_t) = delete;
    
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& operator<<(basic_fast_ostream<CharT, Traits>&, const CharT*);
    template<class CharT, class Traits>
        basic_fast_ostream<CharT, Traits>& operator<<(basic_fast_ostream<CharT, Traits>&, const char*);
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&, const char*);
    
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&,
                                                const signed char*);
    template<class Traits>
        basic_fast_ostream<char, Traits>& operator<<(basic_fast_ostream<char, Traits>&,
                                                const unsigned char*);
    
    template<class Traits>
        basic_fast_ostream<char, Traits>&
            operator<<(basic_fast_ostream<char, Traits>&, const wchar_t*) = delete;
    template<class Traits>
        basic_fast_ostream<char, Traits>&
            operator<<(basic_fast_ostream<char, Traits>&, const char8_t*) = delete;
    template<class Traits>
        basic_fast_ostream<char, Traits>&
            operator<<(basic_fast_ostream<char, Traits>&, const char16_t*) = delete;
    template<class Traits>
        basic_fast_ostream<char, Traits>&
            operator<<(basic_fast_ostream<char, Traits>&, const char32_t*) = delete;
    template<class Traits>
        basic_fast_ostream<wchar_t, Traits>&
            operator<<(basic_fast_ostream<wchar_t, Traits>&, const char8_t*) = delete;
    template<class Traits>
        basic_fast_ostream<wchar_t, Traits>&
            operator<<(basic_fast_ostream<wchar_t, Traits>&, const char16_t*) = delete;
    template<class Traits>
        basic_fast_ostream<wchar_t, Traits>&
            operator<<(basic_fast_ostream<wchar_t, Traits>&, const char32_t*) = delete;
}

namespace fast_io
{
    template<class CharT, class Traits>
    class basic_fast_ostream<CharT, Traits>::sentry
    {
        bool ok_;          // exposition only
    public:
        explicit sentry(basic_fast_ostream& os);
        ~sentry();
        explicit operator bool() const { return ok_; }
    
        sentry(const sentry&) = delete;
        sentry& operator=(const sentry&) = delete;
    };
}
