/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/privileged.hpp>
#include <eosiolib/public_key.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/eosio.hpp>
#include <string>

namespace eosioarb {
  using eosio::public_key;
  

  struct arb_info {
    account_name          owner;
    eosio::public_key     arb_key;
    bool                  is_active = true;
    std::string           url;
    
    uint64_t primary_key()const { return owner; }
    void deactivate()           { arb_key = public_key(); is_active = false; };
    EOSLIB_SERIALIZE( arb_info, (owner)(arb_key)(is_active)(url))
  };
  
  typedef eosio::multi_index< N(forums), arb_info>  forum_table;
  typedef eosio::multi_index< N(arbitrators), arb_info>  arbitrator_table;
  
  class system_arb : public eosio::contract {
    private:
      forum_table            _forums;
      arbitrator_table       _arbitrators;
         
    public:
      system_arb( account_name self )
        :contract(self),
         _forums(_self, _self),
         _arbitrators(_self, _self){}
      //~system_arb();

      void regforum( const account_name forum, const public_key& forum_key, const std::string& url );
      void unregforum( const account_name forum );
     
      void regarb( const account_name arbitrator, const public_key& arbitrator_key, const std::string& url );
      void unregarb( const account_name arbitrator ); 

   };

} /// eosioarb
