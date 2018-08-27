#include <eosio.system/eosio.arb.hpp>
#include <eosiolib/dispatcher.hpp>

namespace eosioarb {

   system_arb::system_arb( account_name s )
   :_forums(_self,_self),
    _arbitators(_self,_self)
   {
     
   }
  /*
   void system_arb::rmvproducer( account_name producer ) {
      require_auth( _self );
      auto prod = _producers.find( producer );
      eosio_assert( prod != _producers.end(), "producer not found" );
      _producers.modify( prod, 0, [&](auto& p) {
            p.deactivate();
         });
   }
  */
  /**
    *  This method will create a forum and arb_info object for 'forum'
    *
    *  @pre forum is not already registered
    *  @pre forum to register is an account
    *  @pre authority of forum to register
    *
    */
   void system_arb::regfoum( const account_name forum, const eosio::public_key& forum_key, const std::string& url ) {
      eosio_assert( url.size() < 512, "url too long" );
      eosio_assert( forum_key != eosio::public_key(), "public key should not be the default value" );
      require_auth( forum );

      auto frm = _forums.find( forum );

      if ( frm != _forums.end() ) {
          _forums.modify( frm, forum, [&]( arb_info& info ){
               info.pub_key = forum_key;
               info.is_active    = true;
               info.url          = url;
            });
      } else {
         _forums.emplace( forum, [&]( arb_info& info ){
               info.arb         = forum;
               info.pub_key  = forum_key;
               info.is_active     = true;
               info.url           = url;
         });
      }
   }

   void system_arb::unregforum( const account_name forum ) {
      require_auth( forum );

      const auto& frm = _forums.get( forum, "forum not found" );

      _forums.modify( frm, 0, [&]( arb_info& info ){
            info.deactivate();
      });
   }
   
} /// eosio.system


EOSIO_ABI( eosioarb::system_arb,
     // voting.cpp
     (regproducer)(unregprod)
)
