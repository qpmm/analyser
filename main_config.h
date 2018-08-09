#ifndef MAIN_CONFIG_HPP
#define MAIN_CONFIG_HPP

#include <boost/wave.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace wv = boost::wave;
namespace fs = boost::filesystem;
namespace po = boost::program_options;

#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include "lexertl_iterator.hpp"

typedef wv::cpplexer::lex_token<> token_type;
typedef wv::cpplexer::lexertl::lex_iterator<token_type> lex_iterator_type;

#endif // MAIN_CONFIG_HPP
