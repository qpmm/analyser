#if !defined(BOOST_WAVE_LEXERTL_ITERATOR_HPP_INCLUDED)
#define BOOST_WAVE_LEXERTL_ITERATOR_HPP_INCLUDED

#include <boost/spirit/include/support_multi_pass.hpp>
#include "lexertl_interface.hpp"

namespace boost { namespace wave { namespace cpplexer { namespace lexertl 
{
namespace impl {

template <typename TokenT> 
class iterator_functor_shim 
{
    typedef typename TokenT::position_type  position_type;

public:
    iterator_functor_shim() {}

    typedef TokenT result_type;
    typedef iterator_functor_shim unique;
    typedef lex_input_interface<TokenT>* shared;

    static result_type const eof;

    template <typename MultiPass>
    static result_type& get_next(MultiPass& mp, result_type& result)
    { 
        return mp.shared()->ftor->get(result); 
    }

    template <typename MultiPass>
    static void destroy(MultiPass& mp)
    { 
        delete mp.shared()->ftor; 
    }

    template <typename MultiPass>
    static void set_position(MultiPass& mp, position_type const &pos)
    {
        mp.shared()->ftor->set_position(pos);
    }

#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
    template <typename MultiPass>
    static bool has_include_guards(MultiPass& mp, std::string& guard_name) 
    {
        return mp.shared()->ftor->has_include_guards(guard_name);
    }
#endif

private:
    boost::shared_ptr<lex_input_interface<TokenT> > functor_ptr;
};

//#if 0 != __COMO_VERSION__ || !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)

//  eof token
template <typename TokenT>
typename iterator_functor_shim<TokenT>::result_type const
    iterator_functor_shim<TokenT>::eof = 
        typename iterator_functor_shim<TokenT>::result_type();
//#endif // 0 != __COMO_VERSION__
}   // namespace impl

template <typename FunctorData>
struct make_multi_pass
{
    typedef  
        std::pair<typename FunctorData::unique, typename FunctorData::shared> 
    functor_data_type;
    typedef typename FunctorData::result_type result_type;

    typedef boost::spirit::iterator_policies::split_functor_input input_policy;
    typedef boost::spirit::iterator_policies::ref_counted ownership_policy;
    typedef boost::spirit::iterator_policies::no_check check_policy;
    typedef boost::spirit::iterator_policies::split_std_deque storage_policy;
    typedef boost::spirit::iterator_policies::default_policy<
            ownership_policy, check_policy, input_policy, storage_policy>
        policy_type;
    typedef boost::spirit::multi_pass<functor_data_type, policy_type> type;
};

template <typename TokenT>
class lex_iterator 
:   public make_multi_pass<impl::iterator_functor_shim<TokenT> >::type
{
    typedef impl::iterator_functor_shim<TokenT> input_policy_type;

    typedef typename make_multi_pass<input_policy_type>::type base_type;
    typedef typename make_multi_pass<input_policy_type>::functor_data_type 
        functor_data_type;

    typedef typename input_policy_type::unique unique_functor_type;
    typedef typename input_policy_type::shared shared_functor_type;

public:
    typedef TokenT token_type;

    lex_iterator() {}

    template <typename IteratorT>
    lex_iterator(IteratorT const &first, IteratorT const &last, 
            typename TokenT::position_type const &pos, 
            boost::wave::language_support language)
    :   base_type(
            functor_data_type(
                unique_functor_type(),
                lexertl_input_interface<TokenT>
                    ::new_lexer(first, last, pos, language)
            )
        )
    {}

    void set_position(typename TokenT::position_type const &pos)
    {
        typedef typename TokenT::position_type position_type;

        // set the new position in the current token
        token_type const& currtoken = this->base_type::dereference(*this);
        position_type currpos = currtoken.get_position();

        currpos.set_file(pos.get_file());
        currpos.set_line(pos.get_line());
        const_cast<token_type&>(currtoken).set_position(currpos);

        // set the new position for future tokens as well
        if (token_type::string_type::npos != 
            currtoken.get_value().find_first_of('\n'))
        {
            currpos.set_line(pos.get_line() + 1);
        }
        unique_functor_type::set_position(*this, currpos);
    }

    bool has_include_guards(std::string& guard_name) const
    {
        return base_type::get_functor().has_include_guards(*this, guard_name);
    }
};


}}}}   // namespace boost::wave::cpplexer::lexertl

#endif // !defined(BOOST_WAVE_LEXERTL_ITERATOR_HPP_INCLUDED)
