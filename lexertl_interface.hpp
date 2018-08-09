#if !defined(BOOST_WAVE_LEXERTL_INTERFACE_HPP_INCLUDED)
#define BOOST_WAVE_LEXERTL_INTERFACE_HPP_INCLUDED

#include <boost/wave/cpplexer/re2clex/cpp_re2c_lexer.hpp>

namespace boost { namespace wave { namespace cpplexer { namespace lexertl 
{

template <
    typename IteratorT, 
    typename PositionT = wave::util::file_position_type
>
struct new_lexer_gen
{
    static wave::cpplexer::lex_input_interface<wave::cpplexer::lex_token<PositionT> >*
		new_lexer(IteratorT const &first, IteratorT const &last, 
			PositionT const &pos, wave::language_support language);
};

template <typename TokenT>
struct lexertl_input_interface : wave::cpplexer::lex_input_interface<TokenT>
{
    typedef typename wave::cpplexer::lex_input_interface<TokenT>::position_type 
        position_type;
    
    template <typename IteratorT>
    static wave::cpplexer::lex_input_interface<TokenT> *
		new_lexer(IteratorT const &first, IteratorT const &last, 
			position_type const &pos, wave::language_support language)
    { 
        return boost::wave::cpplexer::new_lexer_gen<IteratorT, position_type>::new_lexer(
			first, last, pos, language
		); 
    }
};

}}}}   // namespace boost::wave::cpplexer::lexertl

#endif // !defined(BOOST_WAVE_LEXERTL_INTERFACE_HPP_INCLUDED)
