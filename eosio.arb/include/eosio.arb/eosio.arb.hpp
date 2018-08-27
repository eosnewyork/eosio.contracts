/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/privileged.hpp>
#include <eosiolib/singleton.hpp>

#include <string>

namespace eosioarb {

   using eosio::asset;
   using eosio::indexed_by;
   using eosio::const_mem_fun;
   using eosio::block_timestamp;

   struct arb_info {
     account_name          arb;
     eosio::public_key     pub_key;
     std::string           url;
     bool                  is_active = true;
     void deactivate()     {pub_key = public_key(); is_active = false};
   }
  
   typedef eosio::multi_index< N(forum), arb_info>  forum_table;
   typedef eosio::multi_index< N(arbitrator), arb_info>  arbitrator_table;
  
   class system_arb : public native {
      private:
         forum_table            _forums;
         arbitrator_table       _arbitrators;
         
      public:
         system_arb( account_name s );
         ~system_arb();

         // functions defined in voting.cpp

         void regforum( const account_name forum, const public_key& forum_key, const std::string& url, uint16_t location );
         void unregforum( const account_name forum );
     
     /*         void regarbitrator( const account_name arbitrator, const public_key& arbitrator_key, const std::string& url, uint16_t location );

		void unregarb( const account_name forum ); */

   };

} /// eosioarb
