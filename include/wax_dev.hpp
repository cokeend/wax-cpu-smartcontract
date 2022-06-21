#include <eosio/eosio.hpp>
#include <eosio/symbol.hpp>
#include <eosio/asset.hpp>
#include <eosio/system.hpp>
#include <eosio/print.hpp>
#include <eosio/privileged.hpp>
#include <eosio/singleton.hpp>
#include <eosio/transaction.hpp>


#include <string>
//#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <functional>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 



using namespace eosio;

using std::endl; using std::string;
using std::vector; using std::istringstream;




class [[eosio::contract("wax")]] wax : public contract {
   

   private:
      const symbol wax_symbol;

   public:
      using contract::contract;
       wax( name receiver, name code, datastream<const char*> ds )
         : contract(receiver, code, ds), stakingtab(receiver,receiver.value),configtab(receiver,receiver.value),crontab(receiver,receiver.value),packagetab(receiver,receiver.value)
         ,nodetab(receiver,receiver.value),stakenodetab(receiver,receiver.value) ,wax_symbol("WAX",8) {}

 
 
    [[eosio::on_notify("eosio.token::transfer")]]
      void deposit(name user, name to, eosio::asset quantity, std::string memo)
         {
            
        if (to != get_self() || user == get_self())
         {
            print_f("Can't transfer to your self.");
            return;
         }

         check(quantity.symbol == wax_symbol, "Symbol mismatch.");

     name wallet = name("maloanwallet");

      

   auto itr_pack1d = packagetab.find(0);
   auto itr_pack3d = packagetab.find(1);
   auto itr_pack7d = packagetab.find(2);
   auto itr_pack15d = packagetab.find(3);
   auto itr_pack30d = packagetab.find(4);


   auto stake_net_qty = asset(0,wax_symbol);
   auto stake_cpu_qty = asset(10000000000,wax_symbol);


   auto price_1d = itr_pack1d->price;
   auto price_3d = itr_pack3d->price;
   auto price_7d = itr_pack7d->price;
   auto price_15d = itr_pack15d->price;
   auto price_30d = itr_pack30d->price;
   auto itr_config = configtab.find(0);
   auto default_quantity = itr_config->default_quantity*100000000;

    auto itr_node = nodetab.find(itr_config->node_active);
    name node = name(itr_node->node_name);
    int node_id = itr_config->node_active;
        if (memo.find(",") != string::npos) {

        
               vector<string> new_memo;
               split(memo, ',', new_memo);
               int custom_day;
             
               custom_day = std::atoi(new_memo[1].c_str());
         
            double custom_qty = std::atoi(new_memo[2].c_str());
               name stake_to = name(new_memo[3]);
              
            if(new_memo[0] == "stake"){
                 auto stake_cpu_qty = asset(default_quantity*custom_qty,wax_symbol);

                  if(custom_day >= 1 && custom_day <= 2){
                  
                   double actual_price = price_1d.amount/1*custom_day*custom_qty/100000000;
                   float temp = floor(temp*100.0) / 100.0;
                     if(quantity.amount/100000000.00 >=actual_price){
                      
                           stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                           stakelog(user,stake_to,stake_cpu_qty,custom_day);
                           stakenode();
                           transfertowallet(wallet,quantity);
                      

                     } 

               }
                else if(custom_day >= 3 && custom_day <= 6){
                     double temp = price_3d.amount/3*custom_day*custom_qty/100000000;
                     float actual_price = floor(temp*100.0) / 100.0;
                     if(quantity.amount/100000000.00 >=actual_price){
                      
                           stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                           stakelog(user,stake_to,stake_cpu_qty,custom_day);
                           stakenode();
                           transfertowallet(wallet,quantity);
                      

                     } 

               }
               else if(custom_day >= 7 && custom_day <= 14){
                  
                     double temp = price_7d.amount/7*custom_day*custom_qty/100000000;
                     float actual_price = floor(temp*100.0) / 100.0;
                     if(quantity.amount/100000000.00 >=actual_price){
                      
                           stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                           stakelog(user,stake_to,stake_cpu_qty,custom_day);
                           stakenode();
                           transfertowallet(wallet,quantity);
                      

                     } 

               }else if(custom_day >= 15 && custom_day <= 29){

                  double temp = price_15d.amount/15*custom_day*custom_qty/100000000;
                  float actual_price = floor(temp*100.0) / 100.0;
                     if(quantity.amount/100000000.00 >=actual_price){
                      
                           stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                           stakelog(user,stake_to,stake_cpu_qty,custom_day);
                           stakenode();
                           transfertowallet(wallet,quantity);
                      

                     } 
                  
                  /*
                  if((custom_day < 20) && (quantity.amount/100000000 >= price_15d.amount/100000000 * custom_qty)){
                        stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                        stakelog(user,stake_to,stake_cpu_qty,custom_day);
                        stakenode();
                        transfertowallet(wallet,quantity);
                  }else if((custom_day >= 20) && (quantity.amount/100000000 >= price_15d.amount/100000000 * custom_qty)){
                        stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                        stakelog(user,stake_to,stake_cpu_qty,custom_day);
                        stakenode();
                        transfertowallet(wallet,quantity);
                  }
                  */
                     

               }else if(custom_day >= 30 && custom_day <= 60){

                  double temp = price_30d.amount/30*custom_day*custom_qty/100000000;
                  float actual_price = floor(temp*100.0) / 100.0;

                     if(quantity.amount/100000000.00 >=actual_price){
                      
                           stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                           stakelog(user,stake_to,stake_cpu_qty,custom_day);
                           stakenode();
                           transfertowallet(wallet,quantity);
                      

                     } 
                  /*
                  if((custom_day < 45) && (quantity.amount/100000000 >= price_30d.amount/100000000 * custom_qty)){
                        stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                        stakelog(user,stake_to,stake_cpu_qty,custom_day);
                        stakenode();
                        transfertowallet(wallet,quantity);
                  }else if((custom_day >= 45) && (quantity.amount/100000000 >= price_30d.amount/100000000 * custom_qty)){
                        stakecpu(node,node_id,stake_to,stake_net_qty,stake_cpu_qty);
                        stakelog(user,stake_to,stake_cpu_qty,custom_day);
                        stakenode();
                        transfertowallet(wallet,quantity);
                  }
                  */

               }
            }  // check memo custom
        } /// end check memo
            
           
      
   


      } /// end deposit

void split(const string& s, char c,
   vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

void stakenode(){
    //staking_t stakingtab;

    auto itr_laststake = --stakingtab.end();
    auto itr_stake = stakingtab.find(itr_laststake->id);
    auto itr_config = configtab.find(0);

    stakenodetab.emplace( _self, [&]( auto& u ) {
        //    u.id = stakenodetab.available_primary_key();
            u.stake_id = itr_stake->id;
            u.node_id = itr_config->node_active;
      });
}

void stakecpu(name node,int node_id,name stake_to,asset stake_net_qty,asset stake_cpu_qty){

    if(node_id != 0){
        action{
            permission_level{get_self(), "active"_n},
            "eosio.token"_n,
            "transfer"_n,
            std::make_tuple(get_self(), node, stake_cpu_qty, std::string())
        }.send();

    }

    action{
        permission_level{node, "active"_n},
            "eosio"_n,
            "delegatebw"_n,
            std::make_tuple(node, stake_to, stake_net_qty , stake_cpu_qty ,false)}
            .send();
}

void transfertowallet(name wallet, asset quantity){
    action{
            permission_level{get_self(), "active"_n},
            "eosio.token"_n,
            "transfer"_n,
            std::make_tuple(get_self(), wallet, quantity, std::string())
        }.send();
}

   /*    [[eosio::on_notify("eosio.system::transfer")]]
         void delegatebw(const name& self,const name& hodler,const asset& quantity2 ,const asset& quantity,bool transfer){
          
       };*/

      struct [[eosio::table]] staking_table {
         uint64_t id;
         name account;
         time_point_sec start;
         time_point_sec expire;
         asset stakedqty;
         uint64_t primary_key()const { return id; }
      };

      struct [[eosio::table]] package_table {
         uint64_t id;
         uint64_t days;
         asset price;
         uint64_t primary_key()const { return id; }
      };

      struct [[eosio::table]] config_table {
         uint64_t id;
         uint64_t default_quantity;
         uint64_t node_active;
         uint64_t primary_key()const { return id; }
      };
      struct [[eosio::table]] cron_table {
         uint64_t id;
         uint64_t status;
         uint64_t sec;
         uint64_t primary_key()const { return id; }
      };


      struct [[eosio::table]] node_table {
         uint64_t id;
         string node_name;
         uint64_t primary_key()const { return id; }
      };

      struct [[eosio::table]] stakenode_table {
         uint64_t stake_id;
         uint64_t node_id;
         uint64_t primary_key()const { return stake_id; }
      };


  
         typedef eosio::multi_index<"stakinglist"_n, staking_table> staking_t;

         typedef eosio::multi_index<"package"_n, package_table> package_t;

         typedef eosio::multi_index<"config"_n, config_table> config_t;

         typedef eosio::multi_index<"cron"_n, cron_table> cron_t;

         typedef eosio::multi_index<"node"_n, node_table> node_t;

         typedef eosio::multi_index<"stakenode"_n, stakenode_table> stakenode_t;

         



      staking_t stakingtab;

      package_t packagetab;

      config_t configtab;

      cron_t crontab;

      node_t nodetab;

      stakenode_t stakenodetab;

      

      //[[eosio::action]] 
     // void setcron(uint64_t status,uint64_t sec);
      [[eosio::action]] 
      void modcron(uint64_t status,uint64_t sec);
   /*   [[eosio::action]] 
      void setconfig(uint64_t default_quantity,std::string status);*/
      [[eosio::action]] 
      void modconfig(uint64_t default_quantity,uint64_t node_active);
      [[eosio::action]] 
      void initstakenode();
      
    [[eosio::action]] 
      void delallsnode();
      /*
      [[eosio::action]] 
      void delallstake();
      */
      [[eosio::action]] 
      void initnode(string node1,string node2,string node3,string node4,string node5,string node6,string node7);
      [[eosio::action]] 
      void reconfig();
      [[eosio::action]] 
      void initpackage();
      /*
      [[eosio::action]] 
      void setpackage(uint64_t days,asset price);
      */
      [[eosio::action]] 
      void modpackage(double d1, double d3, double d7, double d15 , double d30);
      /*
      [[eosio::action]] 
      void delpackage( uint64_t id );
      */
      [[eosio::action]] 
      void delallpackage();
      [[eosio::action]] 
      void stakelog(name user , name stake_to , asset qty,int custom_day);
      [[eosio::action]] 
      void run();
      [[eosio::action]] 
      void unstake();
      [[eosio::action]] 
      void modstaking(uint64_t id,time_point_sec expire);
      [[eosio::action]] 
      void patch();
    /*  [[eosio::action]] 
      void delconfig();*/
     // using del_allstake_action = action_wrapper<"delallstake"_n, &wax::delallstake>;
      using init_stakenode_action = action_wrapper<"initstakenode"_n, &wax::initstakenode>;
      using init_node_action = action_wrapper<"initnode"_n, &wax::initnode>;
      using re_config_action = action_wrapper<"reconfig"_n, &wax::reconfig>;
   //  using set_config_action = action_wrapper<"setconfig"_n, &wax::setconfig>;
    using mod_config_action = action_wrapper<"modconfig"_n, &wax::modconfig>;
     /* using set_package_action = action_wrapper<"setpackage"_n, &wax::setpackage>;
      using mod_package_action = action_wrapper<"modpackage"_n, &wax::modpackage>;
      using del_package_action = action_wrapper<"delpackage"_n, &wax::delpackage>;*/
     // using set_stakelog_action = action_wrapper<"stakelog"_n, &wax::stakelog>;
    //  using set_cron_action = action_wrapper<"setcron"_n, &wax::setcron>;
      using mod_cron_action = action_wrapper<"modcron"_n, &wax::modcron>;
      using run_action = action_wrapper<"run"_n, &wax::run>;
      using unstake_action = action_wrapper<"unstake"_n, &wax::unstake>;
      using mod_staking_action = action_wrapper<"modstaking"_n, &wax::modstaking>;
     // using del_config_action = action_wrapper<"delconfig"_n, &wax::delconfig>;


      
};


