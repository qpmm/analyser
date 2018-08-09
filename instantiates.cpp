#include "main_config.h"

namespace gm = wv::grammars;

/*** instantiate_cpp_exprgrammar.cpp ***/
#if !defined(BOOST_MSVC)
#include <boost/wave/grammars/cpp_expression_grammar.hpp>
#endif
template struct boost::wave::grammars::expression_grammar_gen<token_type>;

/*** instantiate_cpp_grammar.cpp ***/
#include <boost/wave/grammars/cpp_grammar.hpp>
typedef std::list<token_type, boost::fast_pool_allocator<token_type>>
    token_sequence_type;
template struct gm::cpp_grammar_gen<lex_iterator_type, token_sequence_type>;

/*** instantiate_cpp_literalgrs.cpp ***/
#include <boost/wave/grammars/cpp_literal_grammar_gen.hpp>
#include <boost/wave/grammars/cpp_intlit_grammar.hpp>
#include <boost/wave/grammars/cpp_chlit_grammar.hpp>
template struct gm::intlit_grammar_gen<token_type>;
template struct gm::chlit_grammar_gen<int, token_type>;
template struct gm::chlit_grammar_gen<unsigned int, token_type>;

/*** instantiate_defined_grammar.cpp ***/
#include <boost/wave/grammars/cpp_defined_grammar.hpp>
template struct gm::defined_grammar_gen<lex_iterator_type>;
