#include </wax/mycontracts/wax/include/wax2u_new.hpp>




using namespace eosio;




[[eosio::action]] 
void wax::reconfig() {
   require_auth(get_self());
  auto itr = configtab.find(0);

  configtab.erase( itr );



   config_t configtab(_self, _self.value);
      configtab.emplace( _self, [&]( auto& u ) {
            u.id = 0;
            u.default_quantity = 100;
            u.node_active = 1;
      });

}


[[eosio::action]] 
void wax::initstakenode() {
   require_auth(get_self());
   
   auto length = stakingtab.available_primary_key();
 // auto itr = packagetab.find(id); 
   for(int i =0;i<length;i++){
            auto itr = stakingtab.find(i);
            if(itr != stakingtab.end()){

                  
           // stakenode_t staketab(_self, _self.value);
                stakenodetab.emplace( _self, [&]( auto& u ) {
                      //  u.id = stakenodetab.available_primary_key();

                        

                        u.stake_id = itr->id;
                        u.node_id = 0;
                        
                }); 

            }
         }
}

void wax::initnode(string node1,string node2,string node3,string node4,string node5,string node6,string node7) {
   require_auth(get_self());
   node_t nodetab(_self, _self.value);
      nodetab.emplace( _self, [&]( auto& u ) {
            u.id = 0;
            u.node_name = node1;
      });

      nodetab.emplace( _self, [&]( auto& a ) {
            a.id = 1;
            a.node_name = node2;
      });


      nodetab.emplace( _self, [&]( auto& b ) {
            b.id = 2;
            b.node_name = node3;
      });

      nodetab.emplace( _self, [&]( auto& c ) {
            c.id = 3;
            c.node_name = node4;
      });

      nodetab.emplace( _self, [&]( auto& d ) {
            d.id = 4;
            d.node_name = node5;
      });

      nodetab.emplace( _self, [&]( auto& e ) {
            e.id = 5;
            e.node_name = node6;
      });

      nodetab.emplace( _self, [&]( auto& f ) {
            f.id = 6;
            f.node_name = node7;
      });

}



[[eosio::action]] 
void wax::modstaking(uint64_t id,time_point_sec expire) {
   require_auth(get_self());
   auto itr = stakingtab.find(id);
   
   check( itr != stakingtab.end(), "account does not exist in table" );
   stakingtab.modify( itr, _self, [&]( auto& row ) {
      row.expire = expire;
   });
}

/*void wax::setcron(uint64_t status,uint64_t sec) {
   require_auth(get_self());
   cron_t crontab(_self, _self.value);
      crontab.emplace( _self, [&]( auto& u ) {
            u.id = crontab.available_primary_key();
            u.status = status;
            u.sec = sec;
      });
}*/

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
/*
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
*/

[[eosio::action]] 
void wax::modconfig(uint64_t default_quantity,uint64_t node_active) {
   require_auth(get_self());
   auto itr = configtab.find(0);
   check( itr != configtab.end(), "config does not exist in table" );
   configtab.modify( itr, _self, [&]( auto& row ) {
      row.default_quantity = default_quantity;
      row.node_active = node_active;
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

void wax::initpackage() {
   require_auth(get_self());
   package_t packagetab(_self, _self.value);
      packagetab.emplace( _self, [&]( auto& u ) {
            u.id = packagetab.available_primary_key();
            u.days = 1;
            u.price = asset(100000000,wax_symbol);
      });

      packagetab.emplace( _self, [&]( auto& a ) {
            a.id = 1;
            a.days = 3;
            a.price = asset(300000000,wax_symbol);
      });

      packagetab.emplace( _self, [&]( auto& b ) {
            b.id = 2;
            b.days = 7;
            b.price = asset(400000000,wax_symbol);
      });

      packagetab.emplace( _self, [&]( auto& c ) {
            c.id = 3;
            c.days = 15;
            c.price = asset(700000000,wax_symbol);
      });

      packagetab.emplace( _self, [&]( auto& d ) {
            d.id = 4;
            d.days = 30;
            d.price = asset(1200000000,wax_symbol);
      });
}
/*
void wax::setpackage(uint64_t days,asset price) {
   require_auth(get_self());
   package_t packagetab(_self, _self.value);
      packagetab.emplace( _self, [&]( auto& u ) {
            u.id = packagetab.available_primary_key();
            u.days = days;
            u.price = price;
      });
}
*/
[[eosio::action]] 
void wax::modpackage( double d1, double d3, double d7, double d15 , double d30) {
   require_auth(get_self());
   
  // check( itr != packagetab.end(), "package does not exist in table" );

  auto itr = packagetab.find(0);
   packagetab.modify( itr, _self, [&]( auto& row ) {
      row.price = asset(d1*100000000,wax_symbol);
   });

   auto itr1 = packagetab.find(1);
   packagetab.modify( itr1, _self, [&]( auto& row1 ) {

      row1.price = asset(d3*100000000,wax_symbol);
   });

   auto itr2 = packagetab.find(2);
   packagetab.modify( itr2, _self, [&]( auto& row2 ) {

      row2.price = asset(d7*100000000,wax_symbol);
   });

   auto itr3 = packagetab.find(3);
   packagetab.modify( itr3, _self, [&]( auto& row3 ) {

      row3.price = asset(d15*100000000,wax_symbol);
   });

   auto itr4 = packagetab.find(4);
   packagetab.modify( itr4, _self, [&]( auto& row4 ) {

      row4.price = asset(d30*100000000,wax_symbol);
   });
   
}
/*
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

void wax::delallpackage( ) {
   require_auth(get_self());
  // check if the user already exists
  auto length = packagetab.available_primary_key();
 // auto itr = packagetab.find(id);
   for(int i =0;i<length;i++){
            auto itr = packagetab.find(i);
            if(itr != packagetab.end()){

                  packagetab.erase(itr);

            }
         }

  // if we got so far it means user exists so we can delete it using 
  // the iterator found based on its primary key
}


void wax::delallsnode( ) {
  // require_auth(get_self());
  auto length = nodetab.available_primary_key();
   for(int i =0;i<length;i++){
            auto itr = nodetab.find(i);
            if(itr != nodetab.end()){

                  nodetab.erase(itr);

            }
         }

}

/*
void wax::delallstake( ) {
  // require_auth(get_self());
  auto length = stakingtab.available_primary_key();
   for(int i =0;i<length;i++){
            auto itr = stakingtab.find(i);
            if(itr != stakingtab.end()){

                  stakingtab.erase(itr);

            }
         }

}
*/

void wax::stakelog(name user , name stake_to , asset qty,int custom_day) {
   require_auth(user);
  // auto itr = testtab.find(user.value);
  // auto itr = testtab.rbegin();
  auto expire = current_time_point() += eosio::days(custom_day);
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
void wax::unstake() {

   require_auth(get_self());
   cron_t crontab(_self, _self.value);
    auto itr_cron = crontab.find(0);
    int status = itr_cron->status;
        if(status == 1){

         auto stake_net_qty = asset(0,wax_symbol);
         staking_t stakingtab(_self, _self.value);
          
         auto length = stakingtab.available_primary_key();
        
      //  auto length_stakenode = stakenodetab.available_primary_key();
         
         for(int i =0;i<length;i++){
            auto itr = stakingtab.find(i);
            auto itr_stakenode = stakenodetab.find(i);
            if(itr != stakingtab.end()){

               if(itr->expire <= current_time_point()){

                   auto itr_node = nodetab.find(itr_stakenode->node_id);
                    name node = name(itr_node->node_name);
                  action{
                        permission_level{node, "owner"_n},
                           "eosio"_n,
                           "undelegatebw"_n,
                           std::make_tuple(node, itr->account, stake_net_qty , itr->stakedqty)}
                           .send();

                  stakingtab.erase(itr);
                  stakenodetab.erase(itr_stakenode);

               }

            }
         }

        auto itr_config = configtab.find(0);
        int node_active = itr_config->node_active;
        int next_node;
        
        next_node = node_active+1;

        if(next_node == 7){
            next_node = 0;
        }

        configtab.modify( itr_config, _self, [&]( auto& row ) {
            row.node_active = next_node;
        });
        
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
  // auto quantity = asset(100000000,wax_symbol);
   cron_t crontab(_self, _self.value);
    auto itr_cron = crontab.find(0);
   eosio::transaction t;

   t.actions.emplace_back( permission_level{get_self(), "owner"_n},
        get_self(),
        "unstake"_n,
        std::make_tuple());
   t.delay_sec = itr_cron->sec;

   t.send(current_time_point().sec_since_epoch(),get_self());



}


[[eosio::action]]
void wax::patch() {
   require_auth(get_self());
      reconfig();
      initpackage();
      initnode("walletwax2u1","walletwax2ua","walletwax2ub","walletwax2uc","walletwax2ud","walletwax2ue","walletwax2uf");
      initstakenode();

}




