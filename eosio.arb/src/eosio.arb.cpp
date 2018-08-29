#include <eosio.arb/eosio.arb.hpp>

namespace eosioarb {
  
  system_arb::system_arb( account_name self )
        :contract(self),
         _forums(_self, _self),
         _arbitrators(_self, _self)
  {
  }
  
  /**
    *  This method will create a forum and arb_info object for 'forum'
    *
    *  @pre forum is not already registered
    *  @pre forum to register is an account
    *  @pre authority of forum to register
    *
    */
  void system_arb::regforum( const account_name forum, const eosio::public_key& forum_key, const std::string& url ) {
      eosio_assert( url.size() < 512, "url too long" );
      eosio_assert( forum_key != eosio::public_key(), "public key should not be the default value" );
      require_auth( forum );

      auto frm = _forums.find( forum );

      if ( frm != _forums.end() ) {
        _forums.modify( frm, forum, [&]( arb_info& info ){
            info.arb_key      = forum_key;
            info.is_active    = true;
            info.url          = url;
          });
      } else {
        _forums.emplace( forum, [&]( arb_info& info ){
            info.owner         = forum;
            info.arb_key       = forum_key;
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

  void system_arb::regarb( const account_name arbitrator, const eosio::public_key& arbitrator_key, const std::string& url) {
      eosio_assert( url.size() < 512, "url too long" );
      eosio_assert( arbitrator_key != eosio::public_key(), "public key should not be the default value" );
      require_auth( arbitrator );
      
      auto frm = _arbitrators.find( arbitrator );

      if ( frm != _arbitrators.end() ) {
        _arbitrators.modify( frm, arbitrator, [&]( arb_info& info ){
             info.arb_key      = arbitrator_key;
             info.is_active    = true;
             info.url          = url;
          });
      } else {
        _arbitrators.emplace( arbitrator, [&]( arb_info& info ){
             info.owner         = arbitrator;
             info.arb_key       = arbitrator_key;
             info.is_active     = true;
             info.url           = url;
        });
      }
      
   }

   void system_arb::unregarb( const account_name arbitrator ) {
      require_auth( arbitrator );
      
      const auto& frm = _arbitrators.get( arbitrator, "arbitrator not found" );
      
      _arbitrators.modify( frm, 0, [&]( arb_info& info ){
            info.deactivate();
      });
   }
   
} /// eosioarb


EOSIO_ABI( eosioarb::system_arb,
           (regforum)(unregforum)/*(regarb)(unregarb)*/
)
