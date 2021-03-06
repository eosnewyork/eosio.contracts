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
  void system_arb::regforum( account_name forum, const public_key& forum_key, const string& url ) {
    eosio_assert( url.size() < 512, "url too long" );
    eosio_assert( forum_key != eosio::public_key(), "public key should not be the default value" );
    require_auth( forum );

    auto frm = _forums.find( forum );
    
    if ( frm != _forums.end() ) {
      _forums.modify( frm, forum, [&]( forum_info& info ){
          info.forum_key      = forum_key;
          info.is_active    = true;
          info.url          = url;
        });
    } else {
      _forums.emplace( forum, [&]( forum_info& info ){
          info.owner         = forum;
          info.forum_key       = forum_key;
          info.is_active     = true;
          info.url           = url;
        });
    }
  }

  void system_arb::unregforum( account_name forum ) {
    require_auth( forum );

    const auto& frm = _forums.get( forum, "forum not found" );
      
    _forums.modify( frm, 0, [&]( forum_info& info ){
        info.deactivate();
      });
  }
  
  void system_arb::regarb( account_name arbitrator, const public_key& arbitrator_key, const string& url) {
    eosio_assert( url.size() < 512, "url too long" );
    eosio_assert( arbitrator_key != eosio::public_key(), "public key should not be the default value" );
    require_auth( arbitrator );
      
    auto arb = _arbitrators.find( arbitrator );
    
    if ( arb != _arbitrators.end() ) {
      _arbitrators.modify( arb, arbitrator, [&]( arb_info& info ){
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

  void system_arb::unregarb( account_name arbitrator ) {
    require_auth( arbitrator );
    
    const auto& frm = _arbitrators.get( arbitrator, "arbitrator not found" );
    
    _arbitrators.modify( frm, 0, [&]( arb_info& info ){
        info.deactivate();
      });
  }
   
} /// eosioarb


EOSIO_ABI( eosioarb::system_arb,
           (regforum)(unregforum)(regarb)(unregarb)
)
