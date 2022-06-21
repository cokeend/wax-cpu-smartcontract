#include </wax/mycontracts/wax/include/wax2u.hpp>




using namespace eosio;




[[eosio::action]] 
void wax::modstaking(uint64_t id,time_point_sec expire) {
   require_auth(get_self());
   auto itr = stakingtab.find(id);
   
   check( itr != stakingtab.end(), "account does not exist in table" );
   stakingtab.modify( itr, _self, [&]( auto& row ) {
      row.expire = expire;
   });
}

void wax::setcron(uint64_t status,uint64_t sec) {
   require_auth(get_self());
   cron_t crontab(_self, _self.value);
      crontab.emplace( _self, [&]( auto& u ) {
            u.id = crontab.available_primary_key();
            u.status = status;
            u.sec = sec;
      });
}

[[eosio::action]] 
void wax::modcron(uint64_t status,uint64_t sec) {
   require_auth(get_self());
   auto itr = crontab.find(0);
   
   check( itr != crontab.end(), "cron does not exist in table" );
   crontab.modify( itr, _self, [&]( auto& row ) {
      row.status = status;
      row.sec = sec;
   });
}

void wax::setconfig(uint64_t default_quantity,std::string status) {
   require_auth(get_self());
   config_t configtab(_self, _self.value);
      configtab.emplace( _self, [&]( auto& u ) {
            u.id = configtab.available_primary_key();
            u.default_quantity = default_quantity;
            u.active_period = current_time_point() + eosio::days(15);
            u.active2_period = current_time_point() + eosio::days(30);
            u.status = status;
      });
}


[[eosio::action]] 
void wax::modconfig(uint64_t default_quantity,time_point_sec active_period,time_point_sec active2_period,std::string status) {
   require_auth(get_self());
   auto itr = configtab.find(0);
   check( itr != configtab.end(), "config does not exist in table" );
   configtab.modify( itr, _self, [&]( auto& row ) {
      row.default_quantity = default_quantity;
      row.active_period = active_period;
      row.active2_period = active2_period;
      row.status = status;
   });
}

/*[[eosio::action]]
void wax::delconfig() {
   require_auth(get_self());
  // check if the user already exists
  auto itr = configtab.find(0);
  if ( itr == configtab.end() ) {
    printf("package does not exist in table, nothing to delete" );
    return;
  }
  configtab.erase( itr );
}*/
/*
void wax::setpackage(name pack,uint64_t days,asset price) {
   require_auth(get_self());
   package_t packagetab(_self, _self.value);
      packagetab.emplace( _self, [&]( auto& u ) {
            u.id = packagetab.available_primary_key();
            u.package = pack;
            u.days = days;
            u.price = price;
      });
}

[[eosio::action]] 
void wax::modpackage( uint64_t id, uint64_t days, asset price) {
   require_auth(get_self());
   auto itr = packagetab.find(id);
   check( itr != packagetab.end(), "package does not exist in table" );
   packagetab.modify( itr, _self, [&]( auto& row ) {
      row.days = days;
      row.price = price;
   });
}

[[eosio::action]]
void wax::delpackage( uint64_t id ) {
   require_auth(get_self());
  // check if the user already exists
  auto itr = packagetab.find(id);
  if ( itr == packagetab.end() ) {
    printf("package does not exist in table, nothing to delete" );
    return;
  }

  // if we got so far it means user exists so we can delete it using 
  // the iterator found based on its primary key
  packagetab.erase( itr );
}
*/

void wax::stakelog(name user , name stake_to , asset qty,time_point_sec expire) {
   require_auth(user);
  // auto itr = testtab.find(user.value);
  // auto itr = testtab.rbegin();
  staking_t stakingtab(_self, _self.value);
      stakingtab.emplace( _self, [&]( auto& u ) {
            u.id = stakingtab.available_primary_key();
            u.account = stake_to;
            u.start = current_time_point();
            u.expire = expire;
            u.stakedqty = qty;
           
      });
}

[[eosio::action]]
void wax::unstake(uint64_t status) {

   require_auth(get_self());
   
        if(status == 1){

         auto stake_net_qty = asset(0,wax_symbol);
         staking_t stakingtab(_self, _self.value);
          
         auto length = stakingtab.available_primary_key();
        
         
         for(int i =0;i<length;i++){
            auto itr = stakingtab.find(i);
            if(itr != stakingtab.end()){

               if(itr->expire <= current_time_point()){



                  action{
                        permission_level{get_self(), "owner"_n},
                           "eosio"_n,
                           "undelegatebw"_n,
                           std::make_tuple(get_self(), itr->account, stake_net_qty , itr->stakedqty)}
                           .send();

                  stakingtab.erase(itr);
               }

            }
         }

         eosio::transaction t;

         t.actions.emplace_back( permission_level{get_self(), "owner"_n},
        get_self(),
        "run"_n,
        std::make_tuple());

           t.send(current_time_point().sec_since_epoch(),get_self());
        }


}
[[eosio::action]]
void wax::run() {
   
   require_auth(get_self());
  // auto nname = name("coketestnets");
   auto quantity = asset(100000000,wax_symbol);
   cron_t crontab(_self, _self.value);
    auto itr_cron = crontab.find(0);
   eosio::transaction t;

   t.actions.emplace_back( permission_level{get_self(), "owner"_n},
        get_self(),
        "unstake"_n,
        std::make_tuple(itr_cron->status));
   t.delay_sec = itr_cron->sec;

   t.send(current_time_point().sec_since_epoch(),get_self());

/*
    config_t configtab(_self, _self.value);
   auto itr_config = stakingtab.find(0);

   if(itr_config->status == "active"){
      if(itr_config->active_period < current_time_point()){
         configtab.modify( itr_config, _self, [&]( auto& row ) {
            row.status = "sleep";
            row.active2_period = current_time_point()+eosio::days(15);
         });
      }
   }else if(itr_config->status == "sleep"){
      if(itr_config->active_period2 < current_time_point()){
         configtab.modify( itr_config, _self, [&]( auto& row ) {
            row.status = "active";
            row.active_period = current_time_point()+eosio::days(15);
         });
      }
   }*/


}




