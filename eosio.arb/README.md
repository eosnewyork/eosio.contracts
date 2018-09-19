eosio.arb
----------

The `eosio.arb` contract allows for forums and arbitrators to register their information on chain.

Dependencies:
* [eosio v1.2.x](https://github.com/eosio/eos)
* [eosio.cdt v1.2.x](https://github.com/eosio/eosio.cdt)

To build the contract:
* First, ensure that your __eosio__ is compiled to the core symbol for the EOSIO blockchain that intend to deploy to.
* Second, make sure that you have ```sudo make install```ed __eosio__.
* Third, make sure that you have built and installed `eosio.cdt`
* Run `eosio-cpp /path/to/eosio.arb.cpp -o /path/to/build/directory/eosio.arb.wasm`
The naming convention is `system_arb::actionname` followed by a list of paramters.

After build:
* Use __cleos__ to _set contract_ by pointing to the previously mentioned build directory.

## Actions

#### regforum

Required authority: Forum account owner

Parameters: `account_name forum, eosio::public_key forum_key, string url`

Description: Register an account as a forum. All fields required. RAM is billed to the forum's account. Account is added to the forums table.

#### unregforum

Required authority: Forum account owner

Parameters: `account_name forum`

Description: Remove account from the forums table.

#### regarb

Required authority: Account owner

Parameters: `account_name arbitrator, eosio::public_key forum_key, string url`

Description: Register an account as a arbitrator. All fields required. RAM is billed to the arbitrator's account. Account is added to the arbitrators table.

#### unregarb

Required authority: Account owner

Parameters: `account_name arbitrator`

Description: Remove account from the arbitrators table.

## Tables

You can find information on the tables using `cleos`:
```console
cleos get table <contract account> <contract account> <table name>
```

#### forums

Description: Table of forums. Indexed by forum account name.

Code: `_self`

Scope: `_self`

#### arbitrators

Description: Table of arbitrators. Indexed by arbitrator account name.

Code: `_self`

Scope: `_self`
